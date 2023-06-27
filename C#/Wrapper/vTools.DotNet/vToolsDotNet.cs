using Basler.Pylon;
using System;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using vTools.DotNet.Models;

namespace vTools.DotNet
{
    public class vToolsDotNet
    {
        /// <summary>
        /// Initializes the pylon runtime system.
        /// </summary>
        public static void PylonInitialize() => Wrapper.PylonInitialize();
        /// <summary>
        /// Frees up resources allocated by the pylon runtime system.
        /// </summary>
        public static void PylonTerminate() => Wrapper.PylonTerminate();
        public vToolsDotNet() { }
        private byte[] _imgByte;
        ~vToolsDotNet()
        {
            Wrapper.Dispose();
        }
        /// <summary>
        /// Enable camera emulator. Create a vitural caemra. But it needs to set image files folder.
        /// </summary>
        /// <returns></returns>
        public bool EnableCameraEmulator()
        {
            return Wrapper.EnableCameraEmulator();
        }
        /// <summary>
        /// Load vTools recipe file.
        /// </summary>
        /// <param name="fileName"></param>
        /// <returns></returns>
        /// <exception cref="NullReferenceException"></exception>
        public bool LoadRecipe(string fileName)
        {
            if(!File.Exists(fileName))
            {
                throw new NullReferenceException($"{fileName} not exist!");
            }
            return Wrapper.LoadRecipe(fileName);
        }
        /// <summary>
        /// Directly Set paratmers to operator.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        public bool SetParameters(string name, string value)
        {
            return Wrapper.SetParameters(name, value);
        }
        /// <summary>
        /// Register all outputs observer.
        /// </summary>
        /// <returns></returns>
        public bool RegisterAllOutputsObserver()
        {
            return Wrapper.RegisterAllOutputsObserver();
        }
        /// <summary>
        /// Recipe start.
        /// </summary>
        /// <returns></returns>
        public bool Start()
        {
            return Wrapper.Start();
        }
        /// <summary>
        /// Wait next output result.
        /// </summary>
        /// <param name="timeout"></param>
        /// <returns></returns>
        public bool WaitObject(uint timeout)
        {
            return Wrapper.WaitObject(timeout);
        }
        /// <summary>
        /// Recipe stop.
        /// </summary>
        /// <returns></returns>
        public bool Stop()
        {
            return Wrapper.Stop();
        }
        /// <summary>
        /// Set input value by string.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="value"></param>
        public void SetString(string name, string value)
        {            
            Wrapper.SetString(name, value);
        }
        /// <summary>
        /// Set input value by boolean.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="value"></param>
        public void SetBool(string name, bool value)
        {
            Wrapper.SetBool(name, value);
        }
        /// <summary>
        /// Set input value by intger.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="value"></param>
        public void SetLong(string name, long value)
        {
            Wrapper.SetLong(name, value);
        }
        /// <summary>
        /// Set input value by double.
        /// </summary>
        /// <param name="name"></param>
        /// <param name="value"></param>
        public void SetDouble(string name, double value)
        {
            Wrapper.SetDouble(name, value);
        }
        public bool Dispose()
        {
            return Wrapper.Dispose();
        }

        public bool NextOutput()
        {
            return Wrapper.NextOutput();
        }

        public (byte[] byteArray, int w, int h, int channels) GetImage(string name)
        {
            var ptr = Wrapper.GetImage(name, out int w, out int h, out int c);
            try
            {
                _imgByte = null;
                _imgByte = new byte[w * h * c];
                Marshal.Copy(ptr, _imgByte, 0, _imgByte.Length);
                
                return (_imgByte, w, h, c);
            }
            finally 
            {
                // It can't use Marshal free pointer. It must free pointer in C++.
                Wrapper.Free(ptr);
            }
        }

        public string GetString(string name)
        {
            return Marshal.PtrToStringAnsi(Wrapper.GetString(name));
        }

        public bool GetBool(string name)
        {
            return Wrapper.GetBool(name);
        }

        public long GetLong(string name)
        {
            return Wrapper.GetLong(name);
        }

        public double GetDouble(string name)
        {
            return Wrapper.GetDouble(name);
        }

        public Point GetPoint(string name)
        {
            Wrapper.GetPointF(name, out double x, out double y);
            return new Point(x, y);
        }

        public Rectangle GetRectangle(string name)
        {
            Wrapper.GetRectangleF(name, out double cenX, out double cenY, out double width, out double height, out double angle);
            return new Rectangle(new Point(cenX, cenY), new Size(width, height), angle);
        }

        public Circle GetCircle(string name)
        {
            Wrapper.GetCircleF(name, out double cenX, out double cenY, out double radius);
            return new Circle(new Point(cenX, cenY), radius);
        }

        public Ellipse GetEllipse(string name)
        {
            Wrapper.GetEllipseF(name, out double cenX, out double cenY, out double radius1, out double radius2, out double angle);
            return new Ellipse(new Point(cenX, cenY), radius1, radius2, angle);
        }

        public Line GetLine(string name)
        {
            Wrapper.GetLineF(name, out double x1, out double y1, out double x2, out double y2);
            return new Line(new Point(x1, x2), new Point(y1, y2));
        }

        public string[] GetStringArray(string name)
        {
            var pData = Wrapper.GetStringArray(name, out int num);
            try
            {
                var pGetData = new IntPtr[num];
                Marshal.Copy(pData, pGetData, 0, pGetData.Length);
                var values = new string[num];
                for (int i = 0; i < num; i++)
                {
                    values[i] = Marshal.PtrToStringAnsi(pGetData[i]);
                    Wrapper.Free(pGetData[i]);
                }                
                return values;
            }
            finally { Wrapper.Free(pData); }
        }

        public bool[] GetBoolArray(string name)
        {
            var pData = Wrapper.GetStringArray(name, out int num);
            try
            {
                var values = new int[num];
                Marshal.Copy(pData, values, 0, values.Length);
                return values.Cast<bool>().ToArray();
            }
            finally { Wrapper.Free(pData); }
        }

        public long[] GetLongArray(string name)
        {
            var pData = Wrapper.GetLongArray(name, out int num);
            try
            {
                var values = new long[num];
                Marshal.Copy(pData, values, 0, values.Length);
                return values;
            }
            finally { Wrapper.Free(pData); }
        }

        public double[] GetDoubleArray(string name)
        {
            var pData = Wrapper.GetDoubleArray(name, out int num);
            try
            {
                var values = new double[num];
                Marshal.Copy(pData, values, 0, values.Length);
                return values;
            }
            finally
            {
                Wrapper.Free(pData);
            }
        }

        public Point[] GetPointArray(string name)
        {
            Wrapper.GetPointFArray(name, out int num, out IntPtr ptrX, out IntPtr ptrY);
            try
            {
                var valuesX = new double[num];
                var valuesY = new double[num];
                Marshal.Copy(ptrX, valuesX, 0, valuesX.Length);
                Marshal.Copy(ptrY, valuesY, 0, valuesY.Length);
                var values = new Point[num];
                for (int i = 0; i < num; i++)
                {
                    values[i] = new Point(valuesX[i], valuesY[i]);
                }
                return values;
            }
            finally
            {
                Wrapper.Free(ptrX);
                Wrapper.Free(ptrY);
            }
        }

        public Rectangle[] GetRectangleArray(string name)
        {
            Wrapper.GetRectangleFArray(name, out int num, out IntPtr ptrX, out IntPtr ptrY, out IntPtr ptrW, out IntPtr ptrH, out IntPtr ptrA);
            try
            {
                var valuesX = new double[num];
                var valuesY = new double[num];
                var valuesW = new double[num];
                var valuesH = new double[num];
                var valuesA = new double[num];
                Marshal.Copy(ptrX, valuesX, 0, valuesX.Length);
                Marshal.Copy(ptrY, valuesY, 0, valuesY.Length);
                Marshal.Copy(ptrW, valuesW, 0, valuesW.Length);
                Marshal.Copy(ptrH, valuesH, 0, valuesH.Length);
                Marshal.Copy(ptrA, valuesA, 0, valuesA.Length);
                var values = new Rectangle[num];
                for (int i = 0; i < num; i++)
                {
                    var p1 = new Point(valuesX[i], valuesY[i]);
                    var size = new Size(valuesW[i], valuesH[i]);
                    values[i] = new Rectangle(p1, size, valuesA[i]);
                }
                return values;
            }
            finally
            {
                Wrapper.Free(ptrX);
                Wrapper.Free(ptrY);
                Wrapper.Free(ptrW);
                Wrapper.Free(ptrH);
                Wrapper.Free(ptrA);
            }
        }

        public Circle[] GetCircleArray(string name)
        {
            Wrapper.GetCircleFArray(name, out int num, out IntPtr ptrX, out IntPtr ptrY, out IntPtr ptrR);
            try
            {
                var valuesX = new double[num];
                var valuesY = new double[num];
                var valuesR = new double[num];
                Marshal.Copy(ptrX, valuesX, 0, valuesX.Length);
                Marshal.Copy(ptrY, valuesY, 0, valuesY.Length);
                Marshal.Copy(ptrR, valuesR, 0, valuesR.Length);
                var values = new Circle[num];
                for (int i = 0; i < num; i++)
                {
                    var p1 = new Point(valuesX[i], valuesY[i]);
                    values[i] = new Circle(p1, valuesR[i]);
                }
                return values;
            }
            finally
            {
                Wrapper.Free(ptrX);
                Wrapper.Free(ptrY);
                Wrapper.Free(ptrR);
            }
        }

        public Ellipse[] GetEllipseArray(string name)
        {
            Wrapper.GetEllipseFArray(name, out int num, out IntPtr ptrX, out IntPtr ptrY, out IntPtr ptrR1, out IntPtr ptrR2, out IntPtr ptrA);
            try
            {
                var valuesX = new double[num];
                var valuesY = new double[num];
                var valuesR1 = new double[num];
                var valuesR2 = new double[num];
                var valuesA = new double[num];
                Marshal.Copy(ptrX, valuesX, 0, valuesX.Length);
                Marshal.Copy(ptrY, valuesY, 0, valuesY.Length);
                Marshal.Copy(ptrR1, valuesR1, 0, valuesR1.Length);
                Marshal.Copy(ptrR2, valuesR2, 0, valuesR2.Length);
                Marshal.Copy(ptrA, valuesA, 0, valuesA.Length);
                var values = new Ellipse[num];
                for (int i = 0; i < num; i++)
                {
                    var p1 = new Point(valuesX[i], valuesY[i]);
                    values[i] = new Ellipse(p1, valuesR1[i], valuesR2[i], valuesA[i]);
                }
                return values;
            }
            finally
            {
                Wrapper.Free(ptrX);
                Wrapper.Free(ptrY);
                Wrapper.Free(ptrR1);
                Wrapper.Free(ptrR2);
                Wrapper.Free(ptrA);
            }
        }

        public Line[] GetLineArray(string name)
        {
            Wrapper.GetLineFArray(name, out int num, out IntPtr ptrX1, out IntPtr ptrY1, out IntPtr ptrX2, out IntPtr ptrY2);
            try
            {
                var valuesX1 = new double[num];
                var valuesY1 = new double[num];
                var valuesX2 = new double[num];
                var valuesY2 = new double[num];
 
                Marshal.Copy(ptrX1, valuesX1, 0, valuesX1.Length);
                Marshal.Copy(ptrY1, valuesY1, 0, valuesY1.Length);
                Marshal.Copy(ptrX2, valuesX2, 0, valuesX2.Length);
                Marshal.Copy(ptrY2, valuesY2, 0, valuesY2.Length);
                var values = new Line[num];
                for (int i = 0; i < num; i++)
                {
                    var p1 = new Point(valuesX1[i], valuesY1[i]);
                    var p2 = new Point(valuesX2[i], valuesY2[i]);
                    values[i] = new Line(p1, p2);
                }
                return values;
            }
            finally
            {
                Wrapper.Free(ptrX1);
                Wrapper.Free(ptrY1);
                Wrapper.Free(ptrX2);
                Wrapper.Free(ptrY2);
            }
        }

        public string GetCurrentErrorMsg()
        {
            return Marshal.PtrToStringAnsi(Wrapper.GetCurrentErrorMsg());
        }
    }
}
