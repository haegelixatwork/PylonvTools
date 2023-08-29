#pragma once
#include <pylon/PylonIncludes.h>
#include <pylondataprocessing/PylonDataProcessingIncludes.h>
using namespace Pylon;
using namespace Pylon::DataProcessing;

class UpdateObserver : public IUpdateObserver
{
public:
	virtual void IUpdateObserver::UpdateDone(CRecipe& recipe, const CUpdate& update, intptr_t  userProvidedId) {};
};