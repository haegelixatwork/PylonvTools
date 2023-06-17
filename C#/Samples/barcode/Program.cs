using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using vTools.DotNet;
namespace barcode
{
    internal class Program
    {
        static void Main(string[] args)
        {
            try
            {
                vToolsDotNet tools = new vToolsDotNet();
                tools.EnableCameraEmulator();
                var result = tools.LoadRecipe(@"C:\Personal\SourceCode\pylon\vTools\C#\Samples\barcode\barcode.precipe");
                tools.SetParameters("MyCamera/@CameraDevice/ImageFilename", @"C:\Program Files\Basler\pylon 7\Development\Samples\pylonDataProcessing\C++\images\barcode\");
                tools.RegisterAllOutputsObserver();
                tools.Start();
                for (int i = 0; i < 100; i++) 
                {
                    if(tools.WaitObject(5000) && tools.NextOutput())
                    {                        
                        var img = tools.GetImage("Image");
                        var barcode = tools.GetString("Barcodes");
                    }
                }
                //int result = tool.Sub();
            }
            catch (Exception ex) 
            { 
            }
        }
    }
}
