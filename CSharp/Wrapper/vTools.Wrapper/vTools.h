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
	void LoadRecipe(String_t fileName);
	void SetParameters(String_t name, String_t value);
	void SetParameters(String_t name, double value);
	void SetParameters(String_t name, int value);
	void SetParameters(String_t name, bool value);
	const char** GetAllParameterNames(int* num);
	void RegisterAllOutputsObserver();
	void Start();
	bool WaitObject(unsigned int timeOut);
	void Stop();
	void SetString(String_t name, String_t value);
	void SetBool(String_t name, bool value);
	void SetLong(String_t name, long value);
	void SetDouble(String_t name, double value);
	void SetPointF(String_t name, double x, double y);
	void SetRectangleF(String_t name, double x, double y, double w, double h, double a);
	void SetCircleF(String_t name, double x, double y, double r);
	void SetEllipseF(String_t name, double x, double y, double r1, double r2, double a);
	void SetLineF(String_t name, double x1, double y1, double x2, double y2);
	void SetImage(String_t name, void* img, unsigned int w, unsigned int h, unsigned int channels);
	void Dispose();
private:
	UpdateObserver updateObserver;
	int count;
	CRecipe recipe;
};