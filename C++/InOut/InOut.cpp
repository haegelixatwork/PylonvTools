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
// The sample uses the std::list.
#include <list>

// Namespaces for using pylon objects
using namespace Pylon;
using namespace Pylon::DataProcessing;

// Namespace for using cout
using namespace std;

class ResultData
{
public:
	ResultData()
		: hasError(false)
	{
	}
	String_t Out;

	bool hasError;     // If something doesn't work as expected
	// while processing data, this is set to true.

	String_t errorMessage; // Contains an error message if
	// hasError has been set to true.
};

class MyOutputObserver : public IOutputObserver
{
public: 
	MyOutputObserver()
		: m_waitObject(WaitObjectEx::Create())
	{
	}

	void OutputDataPush(CRecipe& recipe, CVariantContainer valueContainer, const CUpdate& update, intptr_t userProvidedId) override
	{
        ResultData currentResultData;
        auto pos = valueContainer.find("RecipeOutput");
		
        const CVariant& value = pos->second;
        if (!value.HasError()) {
            currentResultData.Out= value.ToString();
        }
		else
		{
			currentResultData.hasError = true;
			currentResultData.errorMessage = value.GetErrorDescription();
		}

		// Add data to the result queue in a thread-safe way.
		{
			AutoLock scopedLock(m_memberLock);
			m_queue.emplace_back(currentResultData);
		}

		m_waitObject.Signal();
	}
	// Get the wait object for waiting for data.
	const WaitObject& GetWaitObject()
	{
		return m_waitObject;
	}
	// Get one result data object from the queue.
	bool GetResultData(ResultData& resultDataOut)
	{
		AutoLock scopedLock(m_memberLock);
		if (m_queue.empty())
		{
			return false;
		}

		resultDataOut = std::move(m_queue.front());
		m_queue.pop_front();
		if (m_queue.empty())
		{
			m_waitObject.Reset();
		}
		return true;
	}
private:
	CLock m_memberLock;        // The member lock is required to ensure
	// thread-safe access to the member variables.
	WaitObjectEx m_waitObject; // Signals that ResultData is available.
	// It is set if m_queue is not empty.
	list<ResultData> m_queue;  // The queue of ResultData
};

class MyUpdateObserver : public IUpdateObserver
{
public:
	virtual void Pylon::DataProcessing::IUpdateObserver::UpdateDone(CRecipe& recipe, const CUpdate& update, intptr_t  userProvidedId)
	{
		cout << "Update " << userProvidedId << " has been triggered! " << endl << endl;
	}
};


int main()
{
	int exitCode = 0;
	try
	{
		MyOutputObserver resultCollector;
		CRecipe recipe;
		recipe.Load("C:\\Personal\\SourceCode\\pylon\\pylonDataProcessing\\C++\\InOut\\InOut.precipe");
		recipe.PreAllocateResources();
		recipe.RegisterAllOutputsObserver(&resultCollector, RegistrationMode_Append);

		MyUpdateObserver updateObserver;
		intptr_t id = 5;
		CVariant value("test1");
		recipe.Start();

		recipe.TriggerUpdate("RecipeInput", value, 500, TimeoutHandling_ThrowException, &updateObserver, id);
		if (resultCollector.GetWaitObject().Wait(5000)) 
		{
			ResultData result;
			resultCollector.GetResultData(result);
			cout << "Get Result " << result.Out << endl << endl;
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
