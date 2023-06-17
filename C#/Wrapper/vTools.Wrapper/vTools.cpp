#include "vTools.h"

vTools::vTools()
{
	PylonInitialize();
}

void vTools::LoadRecipe(string fileName)
{
	recipe.Load(fileName.c_str());
	recipe.PreAllocateResources();
}

void vTools::SetParameters(string name, string value)
{
	recipe.GetParameters().Get(StringParameterName(name.c_str())).SetValue(value.c_str());

}

void vTools::RegisterAllOutputsObserver()
{
	recipe.RegisterAllOutputsObserver(&ResultCollector, RegistrationMode_Append);
}

void vTools::Start()
{
	recipe.Start();
}

bool vTools::WaitObject(unsigned int timeOut)
{
	return ResultCollector.GetWaitObject().Wait(timeOut);
}

void vTools::Stop()
{
	recipe.Stop();	
}

void vTools::SetRecipeInput(string name, string value)
{
	CVariant cvalue(value.c_str());
	recipe.TriggerUpdate(name.c_str(), cvalue, 500, TimeoutHandling_ThrowException, &updateObserver, 5);
}

void vTools::Dispose()
{
	recipe.Stop();
	recipe.DeallocateResources();
	recipe.Unload();
}