using Microsoft.VisualStudio.TestTools.UnitTesting;
using NUnit.Framework;
using System;
using System.IO;
using TestContext = NUnit.Framework.TestContext;
using Assert = NUnit.Framework.Assert;
using vTools.DotNet.Models;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;

namespace vTools.DotNet.Test
{
    [TestClass]
    public class Wrapper
    {
        private string _recipesFolder;
        private double _delta = 1E-20;
        [OneTimeSetUp]
        public void AssemblyInitialize()
        {
            var type = typeof(Wrapper);
            var ns = type.Namespace;
            var root = TestContext.CurrentContext.TestDirectory;
            var index = root.IndexOf(ns);
            if (index > 0)
                _recipesFolder = $@"{root.Substring(0, index + ns.Length)}\Recipes\";
            else
                _recipesFolder = $@"{root}\Recipes";
        }
        [Test]
        [TestCase(true)]
        [TestCase(false)]
        public void BoolInIout(bool value)
        {
            vToolsImpl.PylonInitialize();
            try
            {
                var tools = new vToolsImpl();

                var recipeFile = $@"{_recipesFolder}\BoolInOut.precipe";
                tools.LoadRecipe(recipeFile);
                tools.RegisterAllOutputsObserver();
                tools.Start();
                var input = value;
                tools.SetBool("RecipeInput", input);
                var output = !value;
                if (tools.WaitObject(5000) && tools.NextOutput())
                {
                    output = tools.GetBool("RecipeOutput");

                }
                Assert.AreEqual(input, output);
                tools.Stop();
                tools.Dispose();
            }
            finally
            {
                vToolsImpl.PylonTerminate();
            }
        }
        [Test]
        [TestCase(5)]
        [TestCase(33)]
        public void IntInOut(int value)
        {
            vToolsImpl.PylonInitialize();
            try
            {
                var tools = new vToolsImpl();

                var recipeFile = $@"{_recipesFolder}\IntInOut.precipe";
                tools.LoadRecipe(recipeFile);
                tools.RegisterAllOutputsObserver();
                tools.Start();
                var input = value;
                tools.SetLong("RecipeInput", input);
                long output = 0;
                if (tools.WaitObject(5000) && tools.NextOutput())
                {
                    output = tools.GetLong("RecipeOutput");
                }
                Assert.AreEqual(input, output);
                tools.Stop();
                tools.Dispose();
            }
            finally
            {
                vToolsImpl.PylonTerminate();
            }
        }
        [Test]
        [TestCase(5.0)]
        [TestCase(33.33321)]
        public void DoubleInOut(double value)
        {
            vToolsImpl.PylonInitialize();
            try
            {
                var tools = new vToolsImpl();

                var recipeFile = $@"{_recipesFolder}\DoubleInOut.precipe";
                tools.LoadRecipe(recipeFile);
                tools.RegisterAllOutputsObserver();
                tools.Start();
                var input = value;
                tools.SetDouble("RecipeInput", input);
                var output = 0.0;
                if (tools.WaitObject(5000) && tools.NextOutput())
                {
                    output = tools.GetDouble("RecipeOutput");
                }

                Assert.AreEqual(input, output, _delta);
                tools.Stop();
                tools.Dispose();
            }
            finally
            {
                vToolsImpl.PylonTerminate();
            }
        }
        [Test]
        public void ImageInOut()
        {
            vToolsImpl.PylonInitialize();
            try
            {
                var tools = new vToolsImpl();
                
                var recipeFile = $@"{_recipesFolder}\ImageInOut.precipe";
                tools.LoadRecipe(recipeFile);
                tools.RegisterAllOutputsObserver();
                tools.Start();
                var bmp = new Bitmap($@"{_recipesFolder}\shapes01.png");
                var bmpData = bmp.LockBits(new System.Drawing.Rectangle(0, 0, bmp.Width, bmp.Height), ImageLockMode.ReadWrite, bmp.PixelFormat);
                var c = bmp.PixelFormat == PixelFormat.Format24bppRgb ? 3 : 1;
                var bytes = new byte[bmp.Width* bmp.Height*c];
                Marshal.Copy(bmpData.Scan0, bytes, 0, bytes.Length);
                bmp.UnlockBits(bmpData);
                tools.SetImage("RecipeInput", bytes, bmp.Width, bmp.Height, bmp.PixelFormat == PixelFormat.Format24bppRgb ? 3 : 1);
                var output = 0.0;
                if (tools.WaitObject(5000) && tools.NextOutput())
                {
                    var img = tools.GetImage("RecipeOutput");
                }
                
                //Assert.AreEqual(input, output, _delta);
                tools.Stop();
                tools.Dispose();
            }
            finally
            {
                vToolsImpl.PylonTerminate();
            }
        }
        [Test]
        [TestCase(5,5.0)]
        [TestCase(33,33.33321)]
        public void TwoRecipes(int vlaueInt, double valueDouble)
        {
            vToolsImpl.PylonInitialize();
            try
            {
                var toolInt = new vToolsImpl();
                var toolDouble = new vToolsImpl();
                var recipeFile = $@"{_recipesFolder}\DoubleInOut.precipe";
                toolInt.LoadRecipe($@"{_recipesFolder}\IntInOut.precipe");
                toolInt.RegisterAllOutputsObserver();
                toolInt.Start();

                toolDouble.LoadRecipe($@"{_recipesFolder}\DoubleInOut.precipe");
                toolDouble.RegisterAllOutputsObserver();
                toolDouble.Start();

                toolDouble.SetDouble("RecipeInput", valueDouble);
                toolInt.SetLong("RecipeInput", vlaueInt);

                long outputInt = 0;
                if (toolInt.WaitObject(5000) && toolInt.NextOutput())
                {
                    outputInt = toolInt.GetLong("RecipeOutput");
                }
                var outputDouble = 0.0;
                if (toolDouble.WaitObject(5000) && toolDouble.NextOutput())
                {
                    outputDouble = toolDouble.GetDouble("RecipeOutput");
                }

                Assert.AreEqual(vlaueInt, outputInt);
                Assert.AreEqual(valueDouble, outputDouble, _delta);
                toolInt.Stop();
                toolInt.Dispose();
                toolDouble.Stop();
                toolDouble.Dispose();
            }
            finally
            {
                vToolsImpl.PylonTerminate();
            }
        }
        [Test]
        public void GetPararameterNames()
        {
            vToolsImpl.PylonInitialize();
            try
            {
                var tool = new vToolsImpl();
                var recipeFile = $@"{_recipesFolder}barcode.precipe";
                tool.LoadRecipe(recipeFile);
                var names = tool.GetAllParameterNames();
                Assert.AreEqual(names.Length, 4);
            }
            finally
            {
                vToolsImpl.PylonTerminate();
            }
        }
        [Test]
        public void SetPararameter()
        {
            vToolsImpl.PylonInitialize();
            var result = false;
            try
            {
                var tool = new vToolsImpl();
                var recipeFile = $@"{_recipesFolder}barcode.precipe"; 
                tool.LoadRecipe(recipeFile);
                tool.SetParameters("BarcodeReaderBasic/@vTool/MaxNumBarcodes", 2);
                tool.SetParameters("BarcodeReaderBasic/@vTool/DetectionTimeoutEnable", false);
                tool.SetParameterByEnum("BarcodeReaderBasic/@vTool/BarcodeType", "EAN");
                result = true;
                Assert.IsTrue(result);
            }
            finally
            {
                vToolsImpl.PylonTerminate();
            }
        }
        #region Not support
        /*
        [Test]
        [TestCase(5.0, 3.321)]
        [TestCase(33.33321, 4340.99)]
        public void PointInOut(double x, double y)
        {
            var tools = new vToolsDotNet();

            var recipeFile = $@"{_recipesFolder}\PointInOut.precipe";
            tools.LoadRecipe(recipeFile);
            tools.RegisterAllOutputsObserver();
            tools.Start();
            tools.SetPoint("RecipeInput", x, y);
            var output = new Point();
            if (tools.WaitObject(5000) && tools.NextOutput())
            {
                output = tools.GetPoint("RecipeOutput");
            }

            Assert.AreEqual(x, output.X, _delta);
            Assert.AreEqual(y, output.Y, _delta);
            tools.Stop();
            tools.Dispose();
        }

        [Test]
        [TestCase(5.0, 3.321, 50.1, 30.7, 1.543216)]
        [TestCase(33.33321, 4340.99, 123.11, 1500.379, 3.141596321325)]
        public void RectangleInOut(double x, double y, double w, double h, double a)
        {
            var tools = new vToolsDotNet();

            var recipeFile = $@"{_recipesFolder}\RectangleInOut.precipe";
            tools.LoadRecipe(recipeFile);
            tools.RegisterAllOutputsObserver();
            tools.Start();
            tools.SetRectangle("RecipeInput", x, y, w, h, a);
            var output = new Rectangle();
            if (tools.WaitObject(5000) && tools.NextOutput())
            {
                output = tools.GetRectangle("RecipeOutput");
            }
            Assert.AreEqual(x, output.Point.X, _delta);
            Assert.AreEqual(y, output.Point.Y, _delta);
            Assert.AreEqual(w, output.Size.Width, _delta);
            Assert.AreEqual(h, output.Size.Height, _delta);
            Assert.AreEqual(a, output.Angle, _delta);
            tools.Stop();
            tools.Dispose();
        }
        [Test]
        [TestCase(5.0, 3.321, 50.1)]
        [TestCase(33.33321, 4340.99, 9978.32178985)]
        public void CircleInOut(double x, double y, double r)
        {
            var tools = new vToolsDotNet();

            var recipeFile = $@"{_recipesFolder}\CircleInOut.precipe";
            tools.LoadRecipe(recipeFile);
            tools.RegisterAllOutputsObserver();
            tools.Start();
            tools.SetCircle("RecipeInput", x, y, r);
            var output = new Circle();
            if (tools.WaitObject(5000) && tools.NextOutput())
            {
                output = tools.GetCircle("RecipeOutput");
            }
            Assert.AreEqual(x, output.Center.X, _delta);
            Assert.AreEqual(y, output.Center.Y, _delta);
            Assert.AreEqual(r, output.Radius, _delta);
            tools.Stop();
            tools.Dispose();
        }
        [Test]
        [TestCase(5.0, 3.321, 50.1, 30.7, 1.543216)]
        [TestCase(33.33321, 4340.99, 123.11, 1500.379, 3.141596321325)]
        public void EllipseInOut(double x, double y, double r1, double r2, double a)
        {
            var tools = new vToolsDotNet();

            var recipeFile = $@"{_recipesFolder}\EllipseInOut.precipe";
            tools.LoadRecipe(recipeFile);
            tools.RegisterAllOutputsObserver();
            tools.Start();
            tools.SetEllipse("RecipeInput", x, y, r1, r2, a);
            var output = new Ellipse();
            if (tools.WaitObject(5000) && tools.NextOutput())
            {
                output = tools.GetEllipse("RecipeOutput");
            }
            Assert.AreEqual(x, output.Center.X, _delta);
            Assert.AreEqual(y, output.Center.Y, _delta);
            Assert.AreEqual(r1, output.Radius1, _delta);
            Assert.AreEqual(r2, output.Radius2, _delta);
            Assert.AreEqual(a, output.Angle, _delta);
            tools.Stop();
            tools.Dispose();
        }
        [Test]
        [TestCase(5.0, 3.321, 50.1, 30.7)]
        [TestCase(33.33321, 4340.99, 123.11, 1500.379)]
        public void LineInOut(double x1, double y1, double x2, double y2)
        {
            var tools = new vToolsDotNet();

            var recipeFile = $@"{_recipesFolder}\LineInOut.precipe";
            tools.LoadRecipe(recipeFile);
            tools.RegisterAllOutputsObserver();
            tools.Start();
            tools.SetLine("RecipeInput", x1, y2, x2, y2);
            var output = new Line();
            if (tools.WaitObject(5000) && tools.NextOutput())
            {
                output = tools.GetLine("RecipeOutput");
            }
            Assert.AreEqual(x1, output.Point1.X, _delta);
            Assert.AreEqual(y1, output.Point1.Y, _delta);
            Assert.AreEqual(x2, output.Point2.X, _delta);
            Assert.AreEqual(y2, output.Point2.Y, _delta);
            tools.Stop();
            tools.Dispose();
        }
        */
        #endregion
    }
}
