/*
    Note: Before getting started, Basler recommends reading the Programmer's Guide topic
    in the pylon .NET API documentation: https://docs.baslerweb.com/pylonapi/net/

    This sample illustrates the implementation of a viewer GUI. This can be used 
    to easily check the camera output. 

*/
using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace PylonLiveView
{
    static class PylonLiveView
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            try
            {
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault( false );
                Application.Run( new MainForm() );
            }
            catch
            {
                throw;
            }
        }
    }
}
