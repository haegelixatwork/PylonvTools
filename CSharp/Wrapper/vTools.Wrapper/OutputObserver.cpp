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

CPylonImage OutputObserver::GetImage(String_t name, int* w, int* h, int* channels)
{
	auto pos = Container.find(name);
	IteratorCheckError(pos, name);
	// Now we can use the value of the key/value pair.
	const CVariant& value = pos->second;	
	VariantCheckError(value);
	if (value.GetDataType() != VariantDataType_PylonImage)
	{
		throw gcnew Exception("Wrong output type");
	}
	auto img = value.ToImage();
	*w = img.GetWidth();
	*h = img.GetHeight();
	*channels = GetChannels(img.GetPixelType());
	auto pixelType = img.GetPixelType() == PixelType_Mono8 ? 1 : 1;
	return img;
}

const char* OutputObserver::GetString(String_t name)
{
	auto pos = Container.find(name);
	IteratorCheckError(pos, name);
	const CVariant& value = pos->second;	
	VariantCheckError(value);
	if (value.GetDataType() != VariantDataType_String)
	{
		throw gcnew Exception("Wrong output type");
	}
	return ConvertToChar(value.ToString().c_str());
}

bool OutputObserver::GetBool(String_t name)
{
	auto pos = Container.find(name);
	IteratorCheckError(pos, name);
	const CVariant& value = pos->second;
	VariantCheckError(value);
	if (value.GetDataType() != VariantDataType_Boolean)
	{
		throw gcnew Exception("Wrong output type");
	}
	return value.ToBool();
}

double OutputObserver::GetDouble(String_t name)
{
	auto pos = Container.find(name);
	IteratorCheckError(pos, name);
	const CVariant& value = pos->second;
	VariantCheckError(value);
	if (value.GetDataType() != VariantDataType_Float)
	{
		throw gcnew Exception("Wrong output type");
	}
	return value.ToDouble();
}

void OutputObserver::GetPointF(String_t name, double* x, double* y)
{
	auto pos = Container.find(name);
	IteratorCheckError(pos, name);
	const CVariant& value = pos->second;
	VariantCheckError(value);
	if (value.GetDataType() != VariantDataType_PointF2D)
	{
		throw gcnew Exception("Wrong output type");
	}
	*x = value.GetSubValue("X").ToDouble();
	*y = value.GetSubValue("Y").ToDouble();
}

void OutputObserver::GetRectangleF(String_t name, double* x, double* y, double* w, double* h, double* a)
{
	auto pos = Container.find(name);
	IteratorCheckError(pos, name);
	const CVariant& value = pos->second;
	*x = GetCenterX(value);
	*y = GetCenterY(value);
	VariantCheckError(value);
	if (value.GetDataType() != VariantDataType_RectangleF)
	{
		throw gcnew Exception("Wrong output type");
	}
	*w = value.GetSubValue("Width").ToDouble();
	*h = value.GetSubValue("Height").ToDouble();
	*a = value.GetSubValue("Rotation").ToDouble();
}

void OutputObserver::GetCircleF(String_t name, double* x, double* y, double* r)
{
	auto pos = Container.find(name);
	IteratorCheckError(pos, name);
	const CVariant& value = pos->second;
	*x = GetCenterX(value);
	*y = GetCenterY(value);
	VariantCheckError(value);
	if (value.GetDataType() != VariantDataType_CircleF)
	{
		throw gcnew Exception("Wrong output type");
	}
	*r = value.GetSubValue("Radius").ToDouble();
}

void OutputObserver::GetEllipseF(String_t name, double* x, double* y, double* r1, double* r2, double* a)
{
	auto pos = Container.find(name);
	IteratorCheckError(pos, name);
	const CVariant& value = pos->second;
	*x = GetCenterX(value);
	*y = GetCenterY(value);
	VariantCheckError(value);
	if (value.GetDataType() != VariantDataType_EllipseF)
	{
		throw gcnew Exception("Wrong output type");
	}
	*r1 = value.GetSubValue("Radius1").ToDouble();
	*r2 = value.GetSubValue("Radius2").ToDouble();
	*a = value.GetSubValue("Rotation").ToDouble();
}
void OutputObserver::GetLineF(String_t name, double* x1, double* y1, double* x2, double* y2)
{
	auto pos = Container.find(name);
	IteratorCheckError(pos, name);
	const CVariant& value = pos->second;
	VariantCheckError(value);
	if (value.GetDataType() != VariantDataType_LineF2D)
	{
		throw gcnew Exception("Wrong output type");
	}
	*x1 = value.GetSubValue("PointA.X").ToDouble();
	*y1 = value.GetSubValue("PointA.Y").ToDouble();
	*x2 = value.GetSubValue("PointB.X").ToDouble();
	*y2 = value.GetSubValue("PointB.Y").ToDouble();
}

const char** OutputObserver::GetStringList(String_t name, int* num)
{
	auto pos = Container.find(name);
	IteratorCheckError(pos, name);
	const CVariant& value = pos->second;
	VariantCheckError(value);
	auto length = value.GetNumArrayValues();
	*num = static_cast<int>(length);
	int i = 0;
	if (length <= 0)
	{
		return nullptr;
	}
	char** data = new char* [length];
	for (i = 0; i < length; ++i)
	{
		const CVariant variant = value.GetArrayValue(i);
		if (variant.GetDataType() != VariantDataType_String)
		{
			throw gcnew Exception("Wrong output type");
		}
		VariantCheckError(variant);
		data[i] = ConvertToChar(variant.ToString().c_str());
	}
	return const_cast<const char**>(data);
}

double OutputObserver::GetCenterX(const CVariant& value)
{
	VariantCheckError(value);
	return value.GetSubValue("Center.X").ToDouble();
}

double OutputObserver::GetCenterY(const CVariant& value)
{
	VariantCheckError(value);
	return value.GetSubValue("Center.Y").ToDouble();
}

int OutputObserver::GetChannels(EPixelType pixelType)
{
	if (IsBGR(pixelType))
		return 3;
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

int64_t OutputObserver::GetLong(String_t name)
{
	auto pos = Container.find(name);
	IteratorCheckError(pos, name);
	const CVariant& value = pos->second;
	VariantCheckError(value);
	return value.ToInt64();
}

bool* OutputObserver::GetBoolArray(String_t name, int* num)
{
	auto pos = Container.find(name);
	IteratorCheckError(pos, name);
	const CVariant& value = pos->second;
	VariantCheckError(value);
	auto length = value.GetNumArrayValues();
	*num = static_cast<int>(length);
	int i = 0;
	if (length <= 0)
	{
		return nullptr;
	}
	bool* bools = new bool[length];
	for (i = 0; i < length; ++i)
	{
		const CVariant variant = value.GetArrayValue(i);
		VariantCheckError(variant);
		if (variant.GetDataType() != VariantDataType_Boolean)
		{
			throw gcnew Exception("Wrong output type");
		}
		bools[i] = variant.ToBool();
	}
	return bools;
}

int64_t* OutputObserver::GetLongArray(String_t name, int* num)
{
	auto pos = Container.find(name);
	IteratorCheckError(pos, name);
	const CVariant& value = pos->second;
	VariantCheckError(value);
	auto length = value.GetNumArrayValues();
	*num = static_cast<int>(length);
	int i = 0;
	if (length <= 0)
	{
		return nullptr;
	}
	int64_t* ints = new int64_t[length];
	for (i = 0; i < length; ++i)
	{
		const CVariant variant = value.GetArrayValue(i);
		VariantCheckError(variant);
		if (variant.GetDataType() != VariantDataType_Int64)
		{
			throw gcnew Exception("Wrong output type");
		}
		ints[i] = variant.ToInt64();
	}
	return ints;
}

double* OutputObserver::GetDoubleArray(String_t name, int* num)
{
	auto pos = Container.find(name);
	IteratorCheckError(pos, name);
	const CVariant& value = pos->second;
	VariantCheckError(value);
	auto length = value.GetNumArrayValues();
	*num = static_cast<int>(length);
	int i = 0;
	if (length <= 0)
	{
		return nullptr;
	}
	double* doubles = new double[length];
	for (i = 0; i < length; ++i)
	{
		const CVariant variant = value.GetArrayValue(i);
		VariantCheckError(variant);
		if (variant.GetDataType() != VariantDataType_Float)
		{
			throw gcnew Exception("Wrong output type");
		}
		doubles[i] = variant.ToDouble();
	}
	return doubles;
}

void OutputObserver::GetPointFArray(String_t name, int* num, double** x, double** y)
{
	auto pos = Container.find(name);
	IteratorCheckError(pos, name);
	const CVariant& value = pos->second;
	VariantCheckError(value);
	auto length = value.GetNumArrayValues();
	*num = static_cast<int>(length);
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
		VariantCheckError(variant);
		if (variant.GetDataType() != VariantDataType_PointF2D)
		{
			throw gcnew Exception("Wrong output type");
		}
		xs[i] = variant.GetSubValue("X").ToDouble();
		ys[i] = variant.GetSubValue("Y").ToDouble();
	}
	*x = xs;
	*y = ys;
}
void OutputObserver::GetRectangleFArray(String_t name, int* num, double** x, double** y, double** w, double** h, double** a)
{
	auto pos = Container.find(name);
	IteratorCheckError(pos, name);
	const CVariant& value = pos->second;
	VariantCheckError(value);
	auto length = value.GetNumArrayValues();
	*num = static_cast<int>(length);
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
		VariantCheckError(variant);
		if (variant.GetDataType() != VariantDataType_RectangleF)
		{
			throw gcnew Exception("Wrong output type");
		}
		xs[i] = GetCenterX(variant);
		ys[i] = GetCenterY(variant);
		ws[i] = variant.GetSubValue("Width").ToDouble();
		hs[i] = variant.GetSubValue("Height").ToDouble();
		as[i] = variant.GetSubValue("Rotation").ToDouble();
	}
	*x = xs;
	*y = ys;
	*w = ws;
	*h = hs;
	*a = as;
}

void OutputObserver::GetCircleFArray(String_t name, int* num, double** x, double** y, double** r)
{
	auto pos = Container.find(name);
	IteratorCheckError(pos, name);
	const CVariant& value = pos->second;
	VariantCheckError(value);
	auto length = value.GetNumArrayValues();
	*num = static_cast<int>(length);
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
		VariantCheckError(variant);
		if (variant.GetDataType() != VariantDataType_CircleF)
		{
			throw gcnew Exception("Wrong output type");
		}
		xs[i] = GetCenterX(variant);
		ys[i] = GetCenterY(variant);
		rs[i] = variant.GetSubValue("Rotation").ToDouble();
	}
	*x = xs;
	*y = ys;
	*r = rs;
}

void OutputObserver::GetEllipseFArray(String_t name, int* num, double** x, double** y, double** r1, double** r2, double** a)
{
	auto pos = Container.find(name);
	IteratorCheckError(pos, name);
	const CVariant& value = pos->second;
	VariantCheckError(value);
	auto length = value.GetNumArrayValues();
	*num = static_cast<int>(length);
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
		VariantCheckError(variant);
		if (variant.GetDataType() != VariantDataType_EllipseF)
		{
			throw gcnew Exception("Wrong output type");
		}
		xs[i] = GetCenterX(variant);
		ys[i] = GetCenterY(variant);
		r1s[i] = variant.GetSubValue("Radius1").ToDouble();
		r2s[i] = variant.GetSubValue("Radius2").ToDouble();
		as[i] = variant.GetSubValue("Rotation").ToDouble();
	}
	*x = xs;
	*y = ys;
	*r1 = r1s;
	*r2 = r2s;
	*a = as;
}
void OutputObserver::GetLineFArray(String_t name, int* num, double** x1, double** y1, double** x2, double** y2)
{
	auto pos = Container.find(name);
	IteratorCheckError(pos, name);
	const CVariant& value = pos->second;
	VariantCheckError(value);
	auto length = value.GetNumArrayValues();
	*num = static_cast<int>(length);
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
		VariantCheckError(variant);
		if (variant.GetDataType() != VariantDataType_LineF2D)
		{
			throw gcnew Exception("Wrong output type");
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
const char* OutputObserver::GetCurrentErrorMsg()
{
	return ConvertToChar(ErrorMsg.c_str());
}
void OutputObserver::IteratorCheckError(CVariantContainer::iterator it, String_t name)
{
	if (it == Container.end())
	{
		ErrorMsg = "Keyname " + name + " is not exist.";
		throw std::runtime_error(ErrorMsg);
	}
}
void OutputObserver::VariantCheckError(CVariant v)
{
	if (v.HasError())
	{
		ErrorMsg = v.GetErrorDescription();
		throw std::runtime_error(ErrorMsg);
	}
}

