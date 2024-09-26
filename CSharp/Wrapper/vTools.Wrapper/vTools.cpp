#include "vTools.h"

vTools::vTools()
{
	count = 0;
}

void vTools::LoadRecipe(String_t fileName)
{
	recipe.Load(fileName);
	recipe.PreAllocateResources();
}

void vTools::SetParameters(String_t name, String_t value)
{
	recipe.GetParameters().Get(StringParameterName(name)).SetValue(value.c_str());

}

void vTools::SetParameters(String_t name, double value)
{
	recipe.GetParameters().Get(FloatParameterName(name)).SetValue(value);
}

void vTools::SetParameters(String_t name, int value)
{
	recipe.GetParameters().Get(IntegerParameterName(name)).SetValue(value);
}

void vTools::SetParameters(String_t name, bool value)
{
	recipe.GetParameters().Get(BooleanParameterName(name)).SetValue(value);
}

void vTools::SetParameterByEnum(String_t name, String_t value)
{
	recipe.GetParameters().Get(EnumParameterName(name)).SetValue(value.c_str());
}

const char** vTools::GetAllParameterNames(int* num)
{
	auto list = recipe.GetParameters().GetAllParameterNames();
	auto size = list.size();
	char** data = new char* [size];
	*num = static_cast<int>(size);
	for (size_t i = 0; i < list.size(); i++)
	{
		data[i] = ResultCollector.ConvertToChar(list[i].c_str());
	}
	return const_cast<const char**>(data);
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

void vTools::SetString(String_t name, String_t value)
{
	CVariant cvalue(value);
	recipe.TriggerUpdate(name, cvalue, 500, TimeoutHandling_ThrowException, &updateObserver, count++);
}

void vTools::SetBool(String_t name, bool value)
{
	CVariant cvalue(value);
	recipe.TriggerUpdate(name, cvalue, 500, TimeoutHandling_ThrowException, &updateObserver, count++);
}

void vTools::SetLong(String_t name, long value)
{
	int64_t l = value;
	CVariant cvalue(static_cast<int64_t>(value));
	recipe.TriggerUpdate(name, cvalue, 500, TimeoutHandling_ThrowException, &updateObserver, count++);
}

void vTools::SetDouble(String_t name, double value)
{
	CVariant cvalue(static_cast<double>(value));
	recipe.TriggerUpdate(name, cvalue, 500, TimeoutHandling_ThrowException, &updateObserver, count++);
}

void vTools::SetPointF(String_t name, double x, double y)
{
	SPointF2D s = SPointF2D(x, y);	
	recipe.TriggerUpdate(name, CVariant(s), 500, TimeoutHandling_ThrowException, &updateObserver, count++);
}

void vTools::SetRectangleF(String_t name, double x, double y, double w, double h, double a)
{
	SRectangleF s = SRectangleF(x, y, w, h, a);
	recipe.TriggerUpdate(name, CVariant(s), 500, TimeoutHandling_ThrowException, &updateObserver, count++);
}

void vTools::SetCircleF(String_t name, double x, double y, double r)
{	 
	SCircleF s = SCircleF(x, y, r);
	recipe.TriggerUpdate(name, CVariant(s), 500, TimeoutHandling_ThrowException, &updateObserver, count++);
}

void vTools::SetEllipseF(String_t name, double x, double y, double r1, double r2, double a)
{
	SEllipseF s = SEllipseF( x, y, r1, r2, a );
	recipe.TriggerUpdate(name, CVariant(s), 500, TimeoutHandling_ThrowException, &updateObserver, count++);
}

void vTools::SetLineF(String_t name, double x1, double y1, double x2, double y2)
{
	SLineF2D s = SLineF2D(x1, y1, x2, y2);
	recipe.TriggerUpdate(name, CVariant(s), 500, TimeoutHandling_ThrowException, &updateObserver, count++);
}

void vTools::SetImage(String_t name, void* img, unsigned int w, unsigned int h, unsigned int channels)
{	
	EPixelType type = channels == 3 ? Pylon::EPixelType::PixelType_BGR8packed : Pylon::EPixelType::PixelType_Mono8;
	CPylonImage image;
	image.AttachUserBuffer(img, w * h * channels, type, w, h, 0, ImageOrientation_TopDown);
	CVariant cvalue(image);
	recipe.TriggerUpdate(name, cvalue, 1000, TimeoutHandling_ThrowException, &updateObserver, count++);
}

void vTools::Dispose()
{
	recipe.Stop();
	recipe.DeallocateResources();
	recipe.Unload();
}