using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.VisualStyles;
using vTools.DotNet;

namespace MultiRecipes
{
    public partial class Form1 : Form
    {
        private vToolsImpl _toolsBarcode;
        private vToolsImpl _toolsInOut;
        private vToolsImpl _toolsQRCode;
        public Form1()
        {
            InitializeComponent();
        }

        private void buttons_Click(object sender, EventArgs e)
        {
            var but = (Button)sender;
            if(but.Text == "Barcode")
            {
                BarcodeExecute();
            }
            else if (but.Text == "InOut")
            {
                InOutExecute();
            }
            else if (but.Text == "QRCode")
            {
                QRCodeExecute();
            }
        }

        private void BarcodeExecute()
        {
            try
            {
                _toolsBarcode.Start();
                if (_toolsBarcode.WaitObject(5000) && _toolsBarcode.NextOutput())
                {
                    var img = _toolsBarcode.GetImage("Image");
                    var barcode = _toolsBarcode.GetStringArray("Barcodes");
                    textBox1.Text = $"Barcode: {string.Join(",", barcode)}";
                }
                _toolsBarcode.Stop();
                //int result = tool.Sub();
            }
            catch (Win32Exception ex)
            {
                Console.WriteLine(ex);
                textBox1.Text = ex.Message;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex);
                textBox1.Text = ex.Message;
            }
        }

        private void InOutExecute()
        {            
            try
            {
                _toolsInOut.Start();
                var input = "test2";
                _toolsInOut.SetString("RecipeInput", "test2");
                Console.WriteLine($@"Set input: {input}.");
                if (_toolsInOut.WaitObject(5000) && _toolsInOut.NextOutput())
                {
                    var output = _toolsInOut.GetString("RecipeOutput");
                    textBox1.Text = output;
                }
                _toolsInOut.Stop();
                //int result = tool.Sub();
            }
            catch (Win32Exception ex)
            {
                Console.WriteLine(ex);
                textBox1.Text = ex.Message;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex);
                textBox1.Text = ex.Message;
            }
        }

        private void QRCodeExecute()
        {
            try
            {
                _toolsQRCode.Start();
                if (_toolsQRCode.WaitObject(5000) && _toolsQRCode.NextOutput())
                {
                    var img = _toolsQRCode.GetImage("Image");
                    var barcode = _toolsQRCode.GetStringArray("Texts");
                    textBox1.Text = $"Barcode: {string.Join(",", barcode)}";
                    Console.WriteLine($"Barcode: {string.Join(",", barcode)}");
                    Task.Delay(100).Wait();
                }
                _toolsQRCode.Stop();
            }
            catch (Win32Exception ex)
            {
                Console.WriteLine(ex);
                textBox1.Text = ex.Message;
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex);
                textBox1.Text = ex.Message;
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            vToolsImpl.PylonInitialize();
            _toolsBarcode = new vToolsImpl();
            _toolsInOut = new vToolsImpl();
            _toolsQRCode = new vToolsImpl();
            var pylonDir = Environment.GetEnvironmentVariable("PYLON_DEV_DIR");
            var rootPath = Directory.GetParent(Directory.GetParent(Directory.GetCurrentDirectory()).Parent.FullName).FullName;
            _toolsBarcode.EnableCameraEmulator();
            _toolsBarcode.LoadRecipe($@"{rootPath}\barcode.precipe");
            _toolsBarcode.SetParameters("MyCamera/@CameraDevice/ImageFilename", $@"{pylonDir}\Samples\pylonDataProcessing\C++\images\barcode\");
            _toolsBarcode.RegisterAllOutputsObserver();

            _toolsInOut.LoadRecipe($@"{rootPath}\InOut.precipe");
            _toolsInOut.RegisterAllOutputsObserver();

            _toolsQRCode.LoadRecipe($@"{rootPath}\barcode.precipe");
            _toolsQRCode.RegisterAllOutputsObserver();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            _toolsBarcode.Stop();
            _toolsBarcode.Dispose();
            _toolsInOut.Stop();
            _toolsInOut.Dispose();
            _toolsQRCode.Stop();
            _toolsQRCode.Dispose();
            vToolsImpl.PylonTerminate();
        }
    }
}
