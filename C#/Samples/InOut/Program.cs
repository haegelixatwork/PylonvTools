using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using vTools.DotNet;
using Basler.Pylon;
using System.IO;
using System.Reflection;

namespace InOut
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var tools = new vToolsDotNet();
            try
            {
                var recipeFile = $@"{Directory.GetParent(Directory.GetCurrentDirectory()).Parent.FullName}\InOut.precipe";
                tools.LoadRecipe(recipeFile);
                tools.RegisterAllOutputsObserver();
                tools.Start();
                var input = "test2";
                tools.SetRecipeInput("RecipeInput", "test2");
                Console.WriteLine($@"Set input: {input}.");
                if (tools.WaitObject(5000) && tools.NextOutput())
                {
                    var output = tools.GetString("RecipeOutput");
                    Console.WriteLine($@"Get output: {output}.");
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($@"Error: {ex}.");
            }
            tools.Stop();
            tools.Dispose();
        }

    }
}
