#pragma once
#include <pylon/PylonIncludes.h>
// Extend the pylon API for using pylon data processing.
#include <pylondataprocessing/PylonDataProcessingIncludes.h>
#include "ResultData.h"
#include "OutputObserver.h"
#include "UpdateObserver.h"
//#include <list>
using namespace Pylon;
using namespace Pylon::DataProcessing;
using namespace std;
#include <atlsafe.h>
class vTools
{
public:
	OutputObserver ResultCollector;
	vTools();
	void LoadRecipe(string fileName);
	void SetParameters(string name, string value);
	void RegisterAllOutputsObserver();
	void Start();
	bool WaitObject(unsigned int timeOut);
	void Stop();
	void SetRecipeInput(string name, string value);
	void Dispose();
private:
	UpdateObserver updateObserver;
	CRecipe recipe;
};