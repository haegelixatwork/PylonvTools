#pragma once
#include <pylon/PylonIncludes.h>
#include <pylondataprocessing/PylonDataProcessingIncludes.h>
#include <list>
#include "ResultData.h"
using namespace Pylon::DataProcessing;
using namespace Pylon;
using namespace std;

class OutputObserver : public IOutputObserver
{
public:
	CVariantContainer Container;
	string ErrorMsg;
	OutputObserver();
	void OutputDataPush(CRecipe& recipe, CVariantContainer valueContainer,
		const CUpdate& update, intptr_t userProvidedId) override;
	const WaitObject& GetWaitObject();
	bool NextOutput();
	CPylonImage GetImage(string name, int* w, int* h, int* channels);
	const char* GetString(string name);
	bool GetBool(string name);
	int64_t GetLong(string name);
	double GetDouble(string name);
	void GetPointF(string name, double* x, double* y);
	void GetRectangleF(string name, double* x, double* y, double* w, double* h, double* a);
	void GetCircleF(string name, double* x, double* y, double* r);
	void GetEllipseF(string name, double* x, double* y, double* r1, double* r2, double* a);
	void GetLineF(string name, double* x1, double* y1, double* x2, double* y2);
	const char** GetStringList(string name, int* num);
	bool* GetBoolArray(string name, int* num);
	int64_t* GetLongArray(string name, int* num);
	double* GetDoubleArray(string name, int* num);
	void GetPointFArray(string name, int* num, double** x, double** y);
	void GetRectangleFArray(string name, int* num, double** x, double** y, double** w, double** h, double** a);
	void GetCircleFArray(string name, int* num, double** x, double** y, double** r);
	void GetEllipseFArray(string name, int* num, double** x, double** y, double** r1, double** r2, double** a);
	void GetLineFArray(string name, int* num, double** x1, double** y1, double** x2, double** y2);
	const char* GetCurrentErrorMsg();
private:
	CLock m_memberLock;
	WaitObjectEx m_waitObject;
	list<CVariantContainer> m_queue;	
	double GetCenterX(const CVariant& value);
	double GetCenterY(const CVariant& value);
	int GetChannels(EPixelType pixelType);
	char* ConvertToChar(const char* data);
	void IteratorCheckError(CVariantContainer::iterator it, string name);
	void VariantCheckError(CVariant v);
};