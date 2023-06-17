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
	OutputObserver();
	void OutputDataPush(CRecipe& recipe, CVariantContainer valueContainer,
		const CUpdate& update, intptr_t userProvidedId) override;
	const WaitObject& GetWaitObject();
	bool NextOutput();
	CPylonImage GetImage(string name, int* w, int* h, int* channels);
	const char* GetString(string name);
	bool GetBool(string name);
	int GetInt(string name);
	double GetDouble(string name);
	double GetPointFX(string name);
	double GetPointFY(string name);
	double GetRectangleFCenterX(string name);
	double GetRectangleFCenterY(string name);
	double GetRectangleFWidth(string name);
	double GetRectangleFHeight(string name);
	double GetRectangleFRotation(string name);
	double GetCircleFCenterX(string name);
	double GetCircleFCenterY(string name);
	double GetCircleFRadius(string name);
	double GetEllipseFCenterX(string name);
	double GetEllipseFCenterY(string name);
	double GetEllipseFRadius1(string name);
	double GetEllipseFRadius2(string name);
	double GetEllipseFRotation(string name);
	double GetLineFPointAX(string name);
	double GetLineFPointAY(string name);
	double GetLineFPointBX(string name);
	double GetLineFPointBY(string name);
	const char** GetStringList(string name, int* num);
private:
	CLock m_memberLock;
	WaitObjectEx m_waitObject;
	list<CVariantContainer> m_queue;
	double GetCenterX(const CVariant& value);
	double GetCenterY(const CVariant& value);
	int GetChannels(EPixelType pixelType);
	char* ConvertToChar(const char* data);
};