#include "vTools.h"

vTools::vTools()
{
	
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

void vTools::SetString(string name, string value)
{
	CVariant cvalue(value.c_str());
	recipe.TriggerUpdate(name.c_str(), cvalue, 500, TimeoutHandling_ThrowException, &updateObserver, 5);
}

void vTools::SetBool(string name, bool value)
{
	CVariant cvalue(value);
	recipe.TriggerUpdate(name.c_str(), cvalue, 500, TimeoutHandling_ThrowException, &updateObserver, 5);
}

void vTools::SetLong(string name, long value)
{
	int64_t l = value;
	CVariant cvalue(static_cast<int64_t>(value));
	recipe.TriggerUpdate(name.c_str(), cvalue, 500, TimeoutHandling_ThrowException, &updateObserver, 5);
}

void vTools::SetDouble(string name, double value)
{
	CVariant cvalue(static_cast<double>(value));
	recipe.TriggerUpdate(name.c_str(), cvalue, 500, TimeoutHandling_ThrowException, &updateObserver, 5);
}

void vTools::SetPointF(string name, double x, double y)
{
	CVariant cvalue = CVariant::CreateFromTypeName("PointF");
	cvalue.SetSubValue("X", CVariant(x));
	cvalue.SetSubValue("Y", CVariant(y));
	recipe.TriggerUpdate(name.c_str(), cvalue, 500, TimeoutHandling_ThrowException, &updateObserver, 5);
}

void vTools::SetRectangleF(string name, double x, double y, double w, double h, double a)
{
	CVariant cvalue = CVariant::CreateFromTypeName("RectangleF");
	cvalue.SetSubValue("Center.X", CVariant(x));
	cvalue.SetSubValue("Center.Y", CVariant(y));
	cvalue.SetSubValue("Width", CVariant(w));
	cvalue.SetSubValue("Height", CVariant(h));
	cvalue.SetSubValue("Rotation ", CVariant(a));
	recipe.TriggerUpdate(name.c_str(), cvalue, 500, TimeoutHandling_ThrowException, &updateObserver, 5);
}

void vTools::SetCircleF(string name, double x, double y, double r)
{
	CVariant cvalue = CVariant::CreateFromTypeName("CircleF");
	cvalue.SetSubValue("Center.X", CVariant(x));
	cvalue.SetSubValue("Center.Y", CVariant(y));
	cvalue.SetSubValue("Radius", CVariant(r));
	recipe.TriggerUpdate(name.c_str(), cvalue, 500, TimeoutHandling_ThrowException, &updateObserver, 5);
}

void vTools::SetEllipseF(string name, double x, double y, double r1, double r2, double a)
{
	CVariant cvalue = CVariant::CreateFromTypeName("EllipseF");
	cvalue.SetSubValue("Center.X", CVariant(x));
	cvalue.SetSubValue("Center.Y", CVariant(y));
	cvalue.SetSubValue("Radius1", CVariant(r1));
	cvalue.SetSubValue("Radius2", CVariant(r2));
	cvalue.SetSubValue("Rotation ", CVariant(a));
	recipe.TriggerUpdate(name.c_str(), cvalue, 500, TimeoutHandling_ThrowException, &updateObserver, 5);
}

void vTools::SetLineF(string name, double x1, double y1, double x2, double y2)
{
	CVariant cvalue = CVariant::CreateFromTypeName("LineF");
	cvalue.SetSubValue("PointA.X", CVariant(x1));
	cvalue.SetSubValue("PointA.Y", CVariant(y1));
	cvalue.SetSubValue("PointB.X", CVariant(x2));
	cvalue.SetSubValue("PointB.Y", CVariant(y2));
	recipe.TriggerUpdate(name.c_str(), cvalue, 500, TimeoutHandling_ThrowException, &updateObserver, 5);
}

void vTools::Dispose()
{
	recipe.Stop();
	recipe.DeallocateResources();
	recipe.Unload();
}