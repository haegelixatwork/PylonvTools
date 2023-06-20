#include "OutputObserver.h"

OutputObserver::OutputObserver()
{
	m_waitObject = WaitObjectEx::Create();
}

void OutputObserver::OutputDataPush(CRecipe& recipe, CVariantContainer valueContainer, const CUpdate& update, intptr_t userProvidedId)
{
	// The following variables are not used here:
	PYLON_UNUSED(recipe);
	PYLON_UNUSED(update);
	PYLON_UNUSED(userProvidedId);

	// Add data to the result queue in a thread-safe way.
	{
		AutoLock scopedLock(m_memberLock);
		m_queue.emplace_back(CVariantContainer(valueContainer));
	}

	// Signal that data is ready.
	m_waitObject.Signal();
}

const WaitObject& OutputObserver::GetWaitObject()
{
	return m_waitObject;
}

bool OutputObserver::NextOutput()
{
	AutoLock scopedLock(m_memberLock);
	if (m_queue.empty())
	{
		return false;
	}
	/*if (!Container.empty())
	{
		Container.clear();
		Container.~CVariantContainer();
	}*/
	Container = CVariantContainer(std::move(m_queue.front()));
	//resultDataOut = std::move(m_queue.front());
	m_queue.pop_front();
	if (m_queue.empty())
	{
		m_waitObject.Reset();
	}
	return true;
}

CPylonImage OutputObserver::GetImage(string name, int* w, int* h, int* channels)
{
	auto posImage = Container.find(name.c_str());
	PYLON_ASSERT(posImage != Container.end());
	if (posImage != Container.end())
	{
		// Now we can use the value of the key/value pair.
		const CVariant& value = posImage->second;
		if (!value.HasError())
		{
			auto img = value.ToImage();
			*w = img.GetWidth();
			*h = img.GetHeight();
			*channels = GetChannels(img.GetPixelType());
			auto pixelType = img.GetPixelType() == PixelType_Mono8 ? 1 : 1;
			return img;
		}
		else
		{
			throw std::runtime_error("Keyname " + name + " is not exist.");
		}
	}
	else
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}

const char* OutputObserver::GetString(string name)
{
	auto pos = Container.find(name.c_str());

	const CVariant& value = pos->second;
	if (!value.HasError()) {
		return ConvertToChar(value.ToString().c_str());
	}
	else
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}

bool OutputObserver::GetBool(string name)
{
	auto pos = Container.find(name.c_str());

	const CVariant& value = pos->second;
	if (!value.HasError()) {
		return value.ToBool();
	}
	else
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}

double OutputObserver::GetDouble(string name)
{
	auto pos = Container.find(name.c_str());

	const CVariant& value = pos->second;
	if (!value.HasError()) {
		return value.ToDouble();
	}
	else
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}

void OutputObserver::GetPointF(string name, double* x, double* y)
{
	auto pos = Container.find(name.c_str());

	const CVariant& value = pos->second;
	if (!value.HasError()) {
		*x = value.GetSubValue("X").ToDouble();
		*y = value.GetSubValue("X").ToDouble();
	}
	else
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}

void OutputObserver::GetRectangleF(string name, double* x, double* y, double* w, double* h, double* a)
{
	auto pos = Container.find(name.c_str());
	const CVariant& value = pos->second;
	*x = GetCenterX(value);
	*y = GetCenterY(value);
	if (!value.HasError()) 
	{
		*w = value.GetSubValue("Width").ToDouble();
		*h = value.GetSubValue("Height").ToDouble();
		*a = value.GetSubValue("Rotation").ToDouble();
	}
	else
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}

void OutputObserver::GetCircleF(string name, double* x, double* y, double* r)
{
	auto pos = Container.find(name.c_str());
	const CVariant& value = pos->second;
	*x = GetCenterX(value);
	*y = GetCenterY(value);
	if (!value.HasError())
	{
		*r = value.GetSubValue("Radius").ToDouble();
	}
	else
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}

void OutputObserver::GetEllipseF(string name, double* x, double* y, double* r1, double* r2, double* a)
{
	auto pos = Container.find(name.c_str());
	const CVariant& value = pos->second;
	*x = GetCenterX(value);
	*y = GetCenterY(value);
	if (!value.HasError())
	{
		*r1 = value.GetSubValue("Radius1 ").ToDouble();
		*r2 = value.GetSubValue("Radius2 ").ToDouble();
		*a = value.GetSubValue("Rotation").ToDouble();
	}
	else
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}
void OutputObserver::GetLineF(string name, double* x1, double* y1, double* x2, double* y2)
{
	auto pos = Container.find(name.c_str());
	const CVariant& value = pos->second;
	
	if (!value.HasError())
	{
		*x1 = value.GetSubValue("PointA.X").ToDouble();
		*y1 = value.GetSubValue("PointA.Y").ToDouble();
		*x2 = value.GetSubValue("PointB.X").ToDouble();
		*y2 = value.GetSubValue("PointB.Y").ToDouble();
	}
	else
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}

const char** OutputObserver::GetStringList(string name, int* num)
{
	auto pos = Container.find(name.c_str());

	if (pos != Container.end())
	{
		const CVariant& value = pos->second;
		if (value.HasError())
		{
			throw std::runtime_error("Keyname " + name + " is not exist.");
		}
		int length = value.GetNumArrayValues();
		*num = length;
		int i = 0;
		if (length <= 0)
		{
			return nullptr;
		}
		char** data = new char* [length];
		for (i = 0; i < length; ++i)
		{
			const CVariant stringValue = value.GetArrayValue(i);
			if (stringValue.HasError())
			{
				throw std::runtime_error("Keyname " + name + " is not exist.");
			}
			data[i] = ConvertToChar(stringValue.ToString().c_str());
		}
		return const_cast<const char**>(data);
	}
	else
	{		
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}

double OutputObserver::GetCenterX(const CVariant& value)
{
	if (!value.HasError()) {
		return value.GetSubValue("Center.X").ToDouble();
	}
	else
	{
		throw std::runtime_error("Keyname " + value.GetValueName() + " is not exist.");
	}
}

double OutputObserver::GetCenterY(const CVariant& value)
{
	if (!value.HasError()) {
		return value.GetSubValue("Center.Y").ToDouble();
	}
	else
	{
		throw std::runtime_error("Keyname " + value.GetValueName() + " is not exist.");
	}
}

int OutputObserver::GetChannels(EPixelType pixelType)
{
	return PlaneCount(pixelType);
}

char* OutputObserver::ConvertToChar(const char* value)
{
	int len = MultiByteToWideChar(CP_ACP, 0, value, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, value, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

int OutputObserver::GetInt(string name)
{
	auto pos = Container.find(name.c_str());

	const CVariant& value = pos->second;
	
	if (!value.HasError()) {
		return static_cast<int>(value.ToInt64());
	}
	else
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}

bool* OutputObserver::GetBoolArray(string name, int* num)
{
	auto pos = Container.find(name.c_str());

	if (pos == Container.end())
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
	const CVariant& value = pos->second;
	if (value.HasError())
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
	int length = value.GetNumArrayValues();
	*num = length;
	int i = 0;
	if (length <= 0)
	{
		return nullptr;
	}
	bool* bools = new bool[length];
	for (i = 0; i < length; ++i)
	{
		const CVariant boolValue = value.GetArrayValue(i);
		if (boolValue.HasError())
		{
			throw std::runtime_error(boolValue.GetErrorDescription().c_str());
		}
		bools[i] = boolValue.ToBool();
	}
	return bools;
}

int* OutputObserver::GetIntArray(string name, int* num)
{
	auto pos = Container.find(name.c_str());

	if (pos == Container.end())
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
	const CVariant& value = pos->second;
	if (value.HasError())
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
	int length = value.GetNumArrayValues();
	*num = length;
	int i = 0;
	if (length <= 0)
	{
		return nullptr;
	}
	int* ints = new int[length];
	for (i = 0; i < length; ++i)
	{
		const CVariant variant = value.GetArrayValue(i);
		if (variant.HasError())
		{
			throw std::runtime_error(variant.GetErrorDescription().c_str());
		}
		ints[i] = variant.ToInt64();
	}
	return ints;
}

double* OutputObserver::GetDoubleArray(string name, int* num)
{
	auto pos = Container.find(name.c_str());

	if (pos == Container.end())
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
	const CVariant& value = pos->second;
	if (value.HasError())
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
	int length = value.GetNumArrayValues();
	*num = length;
	int i = 0;
	if (length <= 0)
	{
		return nullptr;
	}
	double* doubles = new double[length];
	for (i = 0; i < length; ++i)
	{
		const CVariant variant = value.GetArrayValue(i);
		if (variant.HasError())
		{
			throw std::runtime_error(variant.GetErrorDescription().c_str());
		}
		doubles[i] = variant.ToDouble();
	}
	return doubles;
}

void OutputObserver::GetPointFArray(string name, int* num, double** x, double** y)
{
	auto pos = Container.find(name.c_str());

	if (pos == Container.end())
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
	const CVariant& value = pos->second;
	if (value.HasError())
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
	int length = value.GetNumArrayValues();
	*num = length;
	int i = 0;
	if (length <= 0)
	{
		return;
	}
	double* xs = new double[length];
	double* ys = new double[length];
	for (i = 0; i < length; ++i)
	{
		const CVariant variant = value.GetArrayValue(i);
		if (variant.HasError())
		{
			throw std::runtime_error(variant.GetErrorDescription().c_str());
		}
		xs[i] = variant.GetSubValue("X").ToDouble();
		ys[i] = variant.GetSubValue("Y").ToDouble();
	}
	*x = xs;
	*y = ys;
}
void OutputObserver::GetRectangleFArray(string name, int* num, double** x, double** y, double** w, double** h, double** a)
{
	auto pos = Container.find(name.c_str());

	if (pos == Container.end())
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
	const CVariant& value = pos->second;
	if (value.HasError())
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
	int length = value.GetNumArrayValues();
	*num = length;
	int i = 0;
	if (length <= 0)
	{
		return;
	}
	double* xs = new double[length];
	double* ys = new double[length];
	double* ws = new double[length];
	double* hs = new double[length];
	double* as = new double[length];
	for (i = 0; i < length; ++i)
	{
		const CVariant variant = value.GetArrayValue(i);
		if (variant.HasError())
		{
			throw std::runtime_error(variant.GetErrorDescription().c_str());
		}
		xs[i] = GetCenterX(variant);
		ys[i] = GetCenterY(variant);
		ws[i] = variant.GetSubValue("Width").ToDouble();
		hs[i] = variant.GetSubValue("Height").ToDouble();
		as[i] = variant.GetSubValue("Rotation ").ToDouble();
	}
	*x = xs;
	*y = ys;
	*w = ws;
	*h = hs;
	*a = as;
}

void OutputObserver::GetCircleFArray(string name, int* num, double** x, double** y, double** r)
{
	auto pos = Container.find(name.c_str());

	if (pos == Container.end())
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
	const CVariant& value = pos->second;
	if (value.HasError())
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
	int length = value.GetNumArrayValues();
	*num = length;
	int i = 0;
	if (length <= 0)
	{
		return;
	}
	double* xs = new double[length];
	double* ys = new double[length];
	double* rs = new double[length];
	for (i = 0; i < length; ++i)
	{
		const CVariant variant = value.GetArrayValue(i);
		if (variant.HasError())
		{
			throw std::runtime_error(variant.GetErrorDescription().c_str());
		}
		xs[i] = GetCenterX(variant);
		ys[i] = GetCenterY(variant);
		rs[i] = variant.GetSubValue("Rotation ").ToDouble();
	}
	*x = xs;
	*y = ys;
	*r = rs;
}

void OutputObserver::GetEllipseFArray(string name, int* num, double** x, double** y, double** r1, double** r2, double** a)
{
	auto pos = Container.find(name.c_str());

	if (pos == Container.end())
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
	const CVariant& value = pos->second;
	if (value.HasError())
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
	int length = value.GetNumArrayValues();
	*num = length;
	int i = 0;
	if (length <= 0)
	{
		return;
	}
	double* xs = new double[length];
	double* ys = new double[length];
	double* r1s = new double[length];
	double* r2s = new double[length];
	double* as = new double[length];
	for (i = 0; i < length; ++i)
	{
		const CVariant variant = value.GetArrayValue(i);
		if (variant.HasError())
		{
			throw std::runtime_error(variant.GetErrorDescription().c_str());
		}
		xs[i] = GetCenterX(variant);
		ys[i] = GetCenterY(variant);
		r1s[i] = variant.GetSubValue("Radius1 ").ToDouble();
		r2s[i] = variant.GetSubValue("Radius2 ").ToDouble();
		as[i] = variant.GetSubValue("Rotation ").ToDouble();
	}
	*x = xs;
	*y = ys;
	*r1 = r1s;
	*r2 = r2s;
	*a = as;
}
void OutputObserver::GetLineFArray(string name, int* num, double** x1, double** y1, double** x2, double** y2) 
{
	auto pos = Container.find(name.c_str());

	if (pos == Container.end())
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
	const CVariant& value = pos->second;
	if (value.HasError())
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
	int length = value.GetNumArrayValues();
	*num = length;
	int i = 0;
	if (length <= 0)
	{
		return;
	}
	double* x1s = new double[length];
	double* y1s = new double[length];
	double* x2s = new double[length];
	double* y2s = new double[length];
	for (i = 0; i < length; ++i)
	{
		const CVariant variant = value.GetArrayValue(i);
		if (variant.HasError())
		{
			throw std::runtime_error(variant.GetErrorDescription().c_str());
		}
		x1s[i] = variant.GetSubValue("PointA.X").ToDouble();
		y1s[i] = variant.GetSubValue("PointA.Y").ToDouble();
		x2s[i] = variant.GetSubValue("PointB.X").ToDouble();
		y2s[i] = variant.GetSubValue("PointB.Y").ToDouble();
	}
	*x1 = x1s;
	*y1 = y1s;
	*x2 = x2s;
	*y2 = y2s;
}

