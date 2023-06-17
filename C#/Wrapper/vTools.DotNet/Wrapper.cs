using Basler.Pylon;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace vTools.DotNet
{
    public class Wrapper
    {
        [DllImport("vTools.Wrapper.dll", EntryPoint = "EnableCameraEmulator")]
        public static extern bool EnableCameraEmulator();
        [DllImport("vTools.Wrapper.dll", EntryPoint = "LoadRecipe")]
        public static extern bool LoadRecipe(string fileName);
        [DllImport("vTools.Wrapper.dll", EntryPoint = "SetParameters")]
        public static extern bool SetParameters(string name, string value);
        [DllImport("vTools.Wrapper.dll", EntryPoint = "RegisterAllOutputsObserver")]
        public static extern bool RegisterAllOutputsObserver();
        [DllImport("vTools.Wrapper.dll", EntryPoint = "Start")]
        public static extern bool Start();
        [DllImport("vTools.Wrapper.dll", EntryPoint = "WaitObject")]
        public static extern bool WaitObject(uint timeout);
        [DllImport("vTools.Wrapper.dll", EntryPoint = "Stop")]
        public static extern bool Stop();
        [DllImport("vTools.Wrapper.dll", EntryPoint = "SetRecipeInput")]
        public static extern bool SetRecipeInput(string name, string value);
        [DllImport("vTools.Wrapper.dll", EntryPoint = "Dispose")]
        public static extern bool Dispose();
        [DllImport("vTools.Wrapper.dll", EntryPoint = "NextOutput")]
        public static extern bool NextOutput();
        [DllImport("vTools.Wrapper.dll", EntryPoint = "GetImage")]
        public static extern IntPtr GetImage(string name, out int w, out int h, out int channels);
        [DllImport("vTools.Wrapper.dll", EntryPoint = "GetString")]
        public static extern IntPtr GetString(string name);
        [DllImport("vTools.Wrapper.dll", EntryPoint = "GetStringArray")]
        public static extern IntPtr GetStringArray(string name, out int num);
        [DllImport("vTools.Wrapper.dll", EntryPoint = "Free")]
        public static extern void Free(IntPtr ptr);
    }
}
