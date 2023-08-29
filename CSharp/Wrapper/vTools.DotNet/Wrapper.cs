using Basler.Pylon;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace vTools.DotNet
{
    //public class Wrapper
    //{
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "EnableCameraEmulator")]
    //    public static extern bool EnableCameraEmulator();
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "LoadRecipe")]
    //    public static extern bool LoadRecipe(string fileName);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "SetParameters")]
    //    public static extern bool SetParameters(string name, string value);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "RegisterAllOutputsObserver")]
    //    public static extern bool RegisterAllOutputsObserver();
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "Start")]
    //    public static extern bool Start();
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "WaitObject")]
    //    public static extern bool WaitObject(uint timeout);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "Stop")]
    //    public static extern bool Stop();
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "SetString")]
    //    public static extern void SetString(string name, string value);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "SetBool")]
    //    public static extern void SetBool(string name, bool value);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "SetLong")]
    //    public static extern void SetLong(string name, long value);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "SetDouble")]
    //    public static extern void SetDouble(string name, double value);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "Dispose")]
    //    public static extern bool Dispose();
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "NextOutput")]
    //    public static extern bool NextOutput();
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "GetImage")]
    //    public static extern IntPtr GetImage(string name, out int w, out int h, out int channels);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "GetString")]
    //    public static extern IntPtr GetString(string name);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "GetBool")]
    //    public static extern bool GetBool(string name);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "GetLong")]
    //    public static extern long GetLong(string name);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "GetDouble")]
    //    public static extern double GetDouble(string name);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "GetPointF")]
    //    public static extern void GetPointF(string name, out double x, out double y);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "GetRectangleF")]
    //    public static extern void GetRectangleF(string name, out double x, out double y, out double w, out double h, out double a);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "GetCircleF")]
    //    public static extern void GetCircleF(string name, out double x, out double y, out double r);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "GetEllipseF")]
    //    public static extern void GetEllipseF(string name, out double x, out double y, out double r1, out double r2, out double a);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "GetEllipseF")]
    //    public static extern void GetLineF(string name, out double x1, out double y1, out double x2, out double y2);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "GetStringArray")]
    //    public static extern IntPtr GetStringArray(string name, out int num);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "GetBoolArray")]
    //    public static extern IntPtr GetBoolArray(string name, out int num);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "GetLongArray")]
    //    public static extern IntPtr GetLongArray(string name, out int num);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "GetDoubleArray")]
    //    public static extern IntPtr GetDoubleArray(string name, out int num);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "GetPointFArray")]
    //    public static extern void GetPointFArray(string name, out int num, out IntPtr x, out IntPtr y);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "GetRectangleFArray")]
    //    public static extern void GetRectangleFArray(string name, out int num, out IntPtr x, out IntPtr y, out IntPtr w, out IntPtr h, out IntPtr a);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "GetCircleFArray")]
    //    public static extern void GetCircleFArray(string name, out int num, out IntPtr x, out IntPtr y, out IntPtr r);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "GetEllipseFArray")]
    //    public static extern void GetEllipseFArray(string name, out int num, out IntPtr x, out IntPtr y, out IntPtr r1, out IntPtr r2, out IntPtr a);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "GetLineFArray")]
    //    public static extern void GetLineFArray(string name, out int num, out IntPtr x1, out IntPtr y1, out IntPtr x2, out IntPtr y2);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "Free")]
    //    public static extern void Free(IntPtr ptr);
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "PylonInitialize")]
    //    public static extern void PylonInitialize();
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "PylonTerminate")]
    //    public static extern void PylonTerminate();
    //    [DllImport("vTools.Wrapper.dll", EntryPoint = "GetCurrentErrorMsg")]
    //    public static extern IntPtr GetCurrentErrorMsg();
    //}
}
