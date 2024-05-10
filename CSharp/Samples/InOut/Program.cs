using System;
using System.IO;

namespace InOut
{
    internal class Program
    {
        static void Main(string[] args)
        {
            vToolsDotNet.PylonInitialize();
            var tools = new vToolsDotNet();
            try
            {
                var recipeFile = $@"{Directory.GetParent(Directory.GetCurrentDirectory()).Parent.FullName}\InOut.precipe";
                tools.LoadRecipe(recipeFile);
                tools.RegisterAllOutputsObserver();
                tools.Start();
                var input = "test2";
                tools.SetString("RecipeInput", "test2");
                Console.WriteLine($@"Set input: {input}.");
                if (tools.WaitObject(5000) && tools.NextOutput())
                {
                    var output = tools.GetString("RecipeOutput");
                    Console.WriteLine($@"Get output: {output}.");
                }
                tools.Stop();
                tools.Dispose();
            }
            catch (Exception ex)
            {
                Console.WriteLine($@"Error: {ex}.");
            }
            finally
            {
                vToolsDotNet.PylonTerminate();
            }            
        }

    }
}
