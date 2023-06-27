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
	void SetString(string name, string value);
	void SetBool(string name, bool value);
	void SetLong(string name, long value);
	void SetDouble(string name, double value);
	void SetPointF(string name, double x, double y);
	void SetRectangleF(string name, double x, double y, double w, double h, double a);
	void SetCircleF(string name, double x, double y, double r);
	void SetEllipseF(string name, double x, double y, double r1, double r2, double a);
	void SetLineF(string name, double x1, double y1, double x2, double y2);
	void Dispose();
private:
	UpdateObserver updateObserver;
	CRecipe recipe;
};