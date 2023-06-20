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
        public vToolsDotNet() { }
        private byte[] _imgByte;
        ~vToolsDotNet()
        {
            Wrapper.Dispose();
        }
        public bool EnableCameraEmulator()
        {
            return Wrapper.EnableCameraEmulator();
        }
        public bool LoadRecipe(string fileName)
        {
            if(!File.Exists(fileName))
            {
                throw new NullReferenceException($"{fileName} not exist!");
            }
            return Wrapper.LoadRecipe(fileName);
        }

        public bool SetParameters(string name, string value)
        {
            return Wrapper.SetParameters(name, value);
        }

        public bool RegisterAllOutputsObserver()
        {
            return Wrapper.RegisterAllOutputsObserver();
        }

        public bool Start()
        {
            return Wrapper.Start();
        }

        public bool WaitObject(uint timeout)
        {
            return Wrapper.WaitObject(timeout);
        }

        public bool Stop()
        {
            return Wrapper.Stop();
        }

        public bool SetRecipeInput(string name, string value)
        {
            return Wrapper.SetRecipeInput(name, value);
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
                // It can't use Marshal free pointer. It must free pointer in C++.
                Wrapper.Free(ptr);
                return (_imgByte, w, h, c);
            }
            finally 
            {
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

        public int GetInt(string name)
        {
            return Wrapper.GetInt(name);
        }

        public double GetDouble(string name)
        {
            return Wrapper.GetDouble(name);
        }

        public void GetPoint(string name, out double x, out double y)
        {
            Wrapper.GetPointF(name, out x, out y);
        }

        public void GetRectangle(string name, out double cenX, out double cenY, out double width, out double height, out double angle)
        {
            Wrapper.GetRectangleF(name, out cenX, out cenY, out width, out height, out angle);
        }

        public void GetCircle(string name, out double cenX, out double cenY, out double radius)
        {
            Wrapper.GetCircleF(name, out cenX, out cenY, out radius);
        }

        public void GetEllipse(string name, out double cenX, out double cenY, out double radius1, out double radius2, out double angle)
        {
            Wrapper.GetEllipseF(name, out cenX, out cenY, out radius1, out radius2, out angle);
        }

        public void GetLine(string name, out double x1, out double y1, out double x2, out double y2)
        {
            Wrapper.GetLineF(name, out x1, out y1, out x2, out y2);
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

        public int[] GetIntArray(string name)
        {
            var pData = Wrapper.GetIntArray(name, out int num);
            try
            {
                var values = new int[num];
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
    }
}
