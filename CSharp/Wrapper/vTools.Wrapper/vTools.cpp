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

const char** vTools::GetAllParameterNames(int* num)
{
	auto list = recipe.GetParameters().GetAllParameterNames();
	auto size = list.size();
	char** data = new char* [size];
	*num = size;
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
	CVariant cvalue = CVariant::CreateFromTypeName("PointF");
	cvalue.SetSubValue("X", CVariant(x));
	cvalue.SetSubValue("Y", CVariant(y));
	recipe.TriggerUpdate(name, cvalue, 500, TimeoutHandling_ThrowException, &updateObserver, count++);
}

void vTools::SetRectangleF(String_t name, double x, double y, double w, double h, double a)
{
	CVariant cvalue = CVariant::CreateFromTypeName("RectangleF");
	cvalue.SetSubValue("Center.X", CVariant(x));
	cvalue.SetSubValue("Center.Y", CVariant(y));
	cvalue.SetSubValue("Width", CVariant(w));
	cvalue.SetSubValue("Height", CVariant(h));
	cvalue.SetSubValue("Rotation ", CVariant(a));
	recipe.TriggerUpdate(name, cvalue, 500, TimeoutHandling_ThrowException, &updateObserver, count++);
}

void vTools::SetCircleF(String_t name, double x, double y, double r)
{
	CVariant cvalue = CVariant::CreateFromTypeName("CircleF");
	cvalue.SetSubValue("Center.X", CVariant(x));
	cvalue.SetSubValue("Center.Y", CVariant(y));
	cvalue.SetSubValue("Radius", CVariant(r));
	recipe.TriggerUpdate(name, cvalue, 500, TimeoutHandling_ThrowException, &updateObserver, count++);
}

void vTools::SetEllipseF(String_t name, double x, double y, double r1, double r2, double a)
{
	CVariant cvalue = CVariant::CreateFromTypeName("EllipseF");
	cvalue.SetSubValue("Center.X", CVariant(x));
	cvalue.SetSubValue("Center.Y", CVariant(y));
	cvalue.SetSubValue("Radius1", CVariant(r1));
	cvalue.SetSubValue("Radius2", CVariant(r2));
	cvalue.SetSubValue("Rotation ", CVariant(a));
	recipe.TriggerUpdate(name, cvalue, 500, TimeoutHandling_ThrowException, &updateObserver, count++);
}

void vTools::SetLineF(String_t name, double x1, double y1, double x2, double y2)
{
	CVariant cvalue = CVariant::CreateFromTypeName("LineF");
	cvalue.SetSubValue("PointA.X", CVariant(x1));
	cvalue.SetSubValue("PointA.Y", CVariant(y1));
	cvalue.SetSubValue("PointB.X", CVariant(x2));
	cvalue.SetSubValue("PointB.Y", CVariant(y2));
	recipe.TriggerUpdate(name, cvalue, 500, TimeoutHandling_ThrowException, &updateObserver, count++);
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