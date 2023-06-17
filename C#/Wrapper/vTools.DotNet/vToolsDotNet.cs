using Basler.Pylon;
using System;
using System.IO;
using System.Runtime.InteropServices;

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
            _imgByte = null;
            _imgByte = new byte[w * h * c];
            Marshal.Copy(ptr, _imgByte, 0, _imgByte.Length);
            // It can't use Marshal free pointer. It must free pointer in C++.
            Wrapper.Free(ptr);
            return (_imgByte, w, h, c);
        }

        public string GetString(string name)
        {
            return Marshal.PtrToStringAnsi(Wrapper.GetString(name));
        }
        public string[] GetStringArray(string name)
        {

            var pData = Wrapper.GetStringArray(name, out int num);
            var pGetData = new IntPtr[num];
            Marshal.Copy(pData, pGetData, 0, pGetData.Length);
            var values = new string[num];
            for (int i = 0; i < num; i++)
            {
                values[i] = Marshal.PtrToStringAnsi(pGetData[i]);
                Wrapper.Free(pGetData[i]);
            }
            Wrapper.Free(pData);
            return values;
        }
    }
}
