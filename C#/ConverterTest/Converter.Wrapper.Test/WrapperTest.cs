using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Runtime.InteropServices;
using NUnit.Framework;
using Assert = NUnit.Framework.Assert;
using TestContext = NUnit.Framework.TestContext;
using System.Drawing;
using System.Drawing.Imaging;

namespace Converter.Wrapper.Test
{
    class Wrapper
    {
        [DllImport("Converter.Wrapper.dll", EntryPoint = "GetStringT")]
        public static extern IntPtr GetStringT(string fileName);
        [DllImport("Converter.Wrapper.dll", EntryPoint = "GetImage")]
        public static extern IntPtr GetImage(IntPtr image, int w, int h, out int imgW, out int imgH, out int imgC);
    }

    [TestClass]
    public class WrapperTest
    {
        private string _samplesFolder;
        [OneTimeSetUp]
        public void AssemblyInitialize()
        {
            var type = typeof(WrapperTest);
            var ns = type.Namespace;
            var root = TestContext.CurrentContext.TestDirectory;
            var index = root.IndexOf(ns);
            if (index > 0)
                _samplesFolder = $@"{root.Substring(0, index + ns.Length)}\Samples\";
            else
                _samplesFolder = $@"{root}\Samples";
        }

        [Test]
        public void GetStringT()
        {
            var ans = "Test1";
            var result = Marshal.PtrToStringAnsi(Wrapper.GetStringT("Test1"));
            Assert.AreEqual(ans, result);
        }
        [Test]
        public void GetImage()
        {
            var imagePath = $@"{_samplesFolder}pcb_detail_8bit_gray.tif";
            var bitmap = new Bitmap(imagePath);
            var bmpData = bitmap.LockBits(new Rectangle(0, 0, bitmap.Width, bitmap.Height), ImageLockMode.ReadWrite, bitmap.PixelFormat);
            //IntPtr ptrBmp = bmpData.Scan0;
            var result = Wrapper.GetImage(bmpData.Scan0, bitmap.Width, bitmap.Height, out int imgW, out int imgH, out int imgC);
            
            var bytesAns = new byte[bitmap.Width * bitmap.Height];
            var bytesResult = new byte[bitmap.Width * bitmap.Height];
            Marshal.Copy(bmpData.Scan0, bytesAns, 0, bytesAns.Length);
            Marshal.Copy(result, bytesResult, 0, bytesResult.Length);
            bitmap.UnlockBits(bmpData);
            var bitmap1 = new Bitmap(bitmap.Width, bitmap.Height, PixelFormat.Format8bppIndexed);
            ColorPalette palette;
            using (Bitmap tempBmp = new Bitmap(1, 1, PixelFormat.Format8bppIndexed))
            {
                palette = tempBmp.Palette;
            }
            for (int i = 0; i < 256; i++)
            {
                palette.Entries[i] = Color.FromArgb(i, i, i);
            }
            bitmap1.Palette = palette;
            var bmpData1 = bitmap1.LockBits(new Rectangle(0, 0, bitmap.Width, bitmap.Height), ImageLockMode.ReadWrite, bitmap.PixelFormat);
            Marshal.Copy(bytesResult, 0, bmpData1.Scan0, bytesResult.Length);
            bitmap1.UnlockBits(bmpData1);
            for (int i = 0; i < bytesResult.Length; i++)
            {
                Assert.AreEqual(bytesAns[i], bytesResult[i]);
            }
        }
    }
}
