/*
	Sample using the InOut vTool (license required)
*/
// Include files to use the pylon API.
#include <pylon/PylonIncludes.h>
#ifdef PYLON_WIN_BUILD
#  include <pylon/PylonGUI.h>
#endif
// Extend the pylon API for using pylon data processing.
#include <pylondataprocessing/PylonDataProcessingIncludes.h>

// Namespaces for using pylon objects
using namespace Pylon;
using namespace Pylon::DataProcessing;

// Namespace for using cout
using namespace std;

class MyUpdateObserver : public IUpdateObserver
{
public:
	void IUpdateObserver::UpdateDone(CRecipe& recipe, const CUpdate& update, intptr_t  userProvidedId) override
	{
		cout << "Update " << userProvidedId << " has been triggered! " << endl << endl;
	}
};


int main()
{
	int exitCode = 0;
	try
	{
		TCHAR tRoot[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, tRoot);
		wstring wRoot(&tRoot[0]);
		string recipePath(wRoot.begin(), wRoot.end());
		recipePath += "\\InOut.precipe";

		// This object is used for collecting the output data.
		// If placed on the stack, it must be created before the recipe
		// so that it is destroyed after the recipe.
		CGenericOutputObserver resultCollector;
		CRecipe recipe;
		recipe.Load(recipePath.c_str());
		recipe.PreAllocateResources();
		recipe.RegisterAllOutputsObserver(&resultCollector, RegistrationMode_Append);

		MyUpdateObserver updateObserver;
		intptr_t id = 5;
		CVariant value("test1");
		recipe.Start();

		recipe.TriggerUpdate("RecipeInput", value, 500, TimeoutHandling_ThrowException, &updateObserver, id);
		if (resultCollector.GetWaitObject().Wait(5000)) 
		{
			CVariantContainer result = resultCollector.RetrieveResult();
			CVariant out = result["RecipeOutput"];
			cout << "Get Result " << out.ToString() << endl << endl;
		}
		else {
			throw RUNTIME_EXCEPTION("Result timeout");
		}
	}
	catch (const GenericException& e)
	{
		// Error handling
		cerr << "An exception occurred." << endl << e.GetDescription() << endl;
		exitCode = 1;
	}
    std::cout << "Hello World!\n";
	return exitCode;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
