using System;
using System.ComponentModel;
using System.IO;
using vTools.DotNet;
using Emgu.CV;
using Emgu.CV.Structure;

namespace LoadImageWithBarcode
{
    internal class Program
    {
        static void Main(string[] args)
        {
            vToolsImpl.PylonInitialize();
            vToolsImpl tools = new vToolsImpl();
            try
            {
                var pylonDir = Environment.GetEnvironmentVariable("PYLON_DEV_DIR");
                var root = Directory.GetParent(Directory.GetParent(Directory.GetCurrentDirectory()).Parent.FullName);
                var recipeFile = $@"{root}\barcode.precipe";
                tools.LoadRecipe(recipeFile);
                tools.RegisterAllOutputsObserver();
                tools.Start();
                var image = new Image<Gray, byte>($@"{root}\barcode01.png");
                while (true) 
                {
                    tools.SetImage("Image", image.Bytes, image.Width, image.Height, 1);
                    if (tools.WaitObject(5000) && tools.NextOutput())
                    {
                        var barcode = tools.GetStringArray("Barcodes");
                        Console.WriteLine($"Barcode: {string.Join(",", barcode)}");
                    }
                }
            }
            catch (Win32Exception ex)
            {
                Console.WriteLine(ex);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex);
            }
            finally
            {
                vToolsImpl.PylonTerminate();
            }
        }
    }
}
