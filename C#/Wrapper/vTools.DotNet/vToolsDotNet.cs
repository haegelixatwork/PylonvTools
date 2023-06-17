using Basler.Pylon;
using System;
using System.IO;
using System.Runtime.InteropServices;

namespace vTools.DotNet
{
    public class vToolsDotNet
    {
        public vToolsDotNet() { }
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
            var imgByte = new byte[w * h * c];
            return (imgByte, w, h, c);
        }

        public string GetString(string name)
        {
            return Marshal.PtrToStringAnsi(Wrapper.GetString(name));
        }
        public string[] GetStringArray(string name)
        {
            return Wrapper.GetStringArray(name);
        }
    }
}
