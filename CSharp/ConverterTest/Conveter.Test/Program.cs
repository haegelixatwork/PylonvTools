using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Conveter.Test
{
    class Wrapper
    {
        [DllImport("Converter.Wrapper.dll", EntryPoint = "GetStringT")]
        public static extern string GetStringT(string fileName);
        [DllImport("Converter.Wrapper.dll", EntryPoint = "GetImage")]
        public static extern IntPtr GetImage();
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            var txt = Wrapper.GetStringT("Test1");
        }
    }
}
