#pragma once
#include <pylon/PylonIncludes.h>
#include <pylondataprocessing/PylonDataProcessingIncludes.h>
#include <list>
#include "ResultData.h"
using namespace Pylon::DataProcessing;
using namespace Pylon;
using namespace std;
using namespace System;
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
	CPylonImage GetImage(String_t name, int* w, int* h, int* channels);
	const char* GetString(String_t name);
	bool GetBool(String_t name);
	int64_t GetLong(String_t name);
	double GetDouble(String_t name);
	void GetPointF(String_t name, double* x, double* y);
	void GetRectangleF(String_t name, double* x, double* y, double* w, double* h, double* a);
	void GetCircleF(String_t name, double* x, double* y, double* r);
	void GetEllipseF(String_t name, double* x, double* y, double* r1, double* r2, double* a);
	void GetLineF(String_t name, double* x1, double* y1, double* x2, double* y2);
	const char** GetStringList(String_t name, int* num);
	bool* GetBoolArray(String_t name, int* num);
	int64_t* GetLongArray(String_t name, int* num);
	double* GetDoubleArray(String_t name, int* num);
	void GetPointFArray(String_t name, int* num, double** x, double** y);
	void GetRectangleFArray(String_t name, int* num, double** x, double** y, double** w, double** h, double** a);
	void GetCircleFArray(String_t name, int* num, double** x, double** y, double** r);
	void GetEllipseFArray(String_t name, int* num, double** x, double** y, double** r1, double** r2, double** a);
	void GetLineFArray(String_t name, int* num, double** x1, double** y1, double** x2, double** y2);
	const char* GetCurrentErrorMsg();
	char* ConvertToChar(const char* data);
private:
	CLock m_memberLock;
	WaitObjectEx m_waitObject;
	list<CVariantContainer> m_queue;	
	double GetCenterX(const CVariant& value);
	double GetCenterY(const CVariant& value);
	int GetChannels(EPixelType pixelType);
	void IteratorCheckError(CVariantContainer::iterator it, String_t name);
	void VariantCheckError(CVariant v);
};