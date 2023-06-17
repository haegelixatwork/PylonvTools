using Basler.Pylon;
using System;
using System.Collections.Generic;
using System.IO;
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
                var recipeFile = $@"{Directory.GetParent(Directory.GetCurrentDirectory()).Parent.FullName}\barcode.precipe";
                vToolsDotNet tools = new vToolsDotNet();
                tools.EnableCameraEmulator();
                var result = tools.LoadRecipe(recipeFile);
                tools.SetParameters("MyCamera/@CameraDevice/ImageFilename", @"C:\Program Files\Basler\pylon 7\Development\Samples\pylonDataProcessing\C++\images\barcode\");
                tools.RegisterAllOutputsObserver();
                tools.Start();
                for (int i = 0; i < 10000; i++) 
                {
                    if(tools.WaitObject(5000) && tools.NextOutput())
                    {
                        //var img = tools.GetImage("Image");
                        //var barcode = tools.GetStringArray("Barcodes");
                        //Console.WriteLine($"Barcode: {string.Join(",", barcode)}");
                        //ImageWindow.DisplayImage(0, img.byteArray, PixelType.Mono8, img.w, img.h, 0, ImageOrientation.TopDown);
                        Console.WriteLine(i);
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
