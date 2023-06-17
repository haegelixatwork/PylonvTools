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

double OutputObserver::GetPointFX(string name)
{
	auto pos = Container.find(name.c_str());

	const CVariant& value = pos->second;
	if (!value.HasError()) {
		return value.GetSubValue("X").ToDouble();
	}
	else
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}

double OutputObserver::GetPointFY(string name)
{
	auto pos = Container.find(name.c_str());

	const CVariant& value = pos->second;
	if (!value.HasError()) {
		return value.GetSubValue("Y").ToDouble();
	}
	else
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}

double OutputObserver::GetRectangleFCenterX(string name)
{
	auto pos = Container.find(name.c_str());
	return GetCenterX(pos->second);
}

double OutputObserver::GetRectangleFCenterY(string name)
{
	auto pos = Container.find(name.c_str());
	return GetCenterY(pos->second);
}

double OutputObserver::GetRectangleFWidth(string name)
{
	auto pos = Container.find(name.c_str());

	const CVariant& value = pos->second;
	if (!value.HasError()) {
		return value.GetSubValue("Width").ToDouble();
	}
	else
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}

double OutputObserver::GetRectangleFHeight(string name)
{
	auto pos = Container.find(name.c_str());

	const CVariant& value = pos->second;
	if (!value.HasError()) {
		return value.GetSubValue("Height").ToDouble();
	}
	else
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}

double OutputObserver::GetRectangleFRotation(string name)
{
	auto pos = Container.find(name.c_str());

	const CVariant& value = pos->second;
	if (!value.HasError()) {
		return value.GetSubValue("Rotation").ToDouble();
	}
	else
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}

double OutputObserver::GetCircleFCenterX(string name)
{
	auto pos = Container.find(name.c_str());
	return GetCenterX(pos->second);
}

double OutputObserver::GetCircleFCenterY(string name)
{
	auto pos = Container.find(name.c_str());
	return GetCenterY(pos->second);
}

double OutputObserver::GetCircleFRadius(string name)
{
	auto pos = Container.find(name.c_str());

	const CVariant& value = pos->second;
	if (!value.HasError()) {
		return value.GetSubValue("Radius").ToDouble();
	}
	else
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}

double OutputObserver::GetEllipseFCenterX(string name)
{
	return GetCenterY(Container.find(name.c_str())->second);
}

double OutputObserver::GetEllipseFCenterY(string name)
{
	return GetCenterX(Container.find(name.c_str())->second);
}

double OutputObserver::GetEllipseFRadius1(string name)
{
	auto pos = Container.find(name.c_str());

	const CVariant& value = pos->second;
	if (!value.HasError()) {
		return value.GetSubValue("Radius1").ToDouble();
	}
	else
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}

double OutputObserver::GetEllipseFRadius2(string name)
{
	auto pos = Container.find(name.c_str());

	const CVariant& value = pos->second;
	if (!value.HasError()) {
		return value.GetSubValue("Radius2").ToDouble();
	}
	else
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}

double OutputObserver::GetEllipseFRotation(string name)
{
	auto pos = Container.find(name.c_str());

	const CVariant& value = pos->second;
	if (!value.HasError()) {
		return value.GetSubValue("Rotation").ToDouble();
	}
	else
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}

double OutputObserver::GetLineFPointAX(string name)
{
	auto pos = Container.find(name.c_str());
	const CVariant& value = pos->second;
	if (!value.HasError()) {
		return value.GetSubValue("PointA.X").ToDouble();
	}
	else
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}

double OutputObserver::GetLineFPointAY(string name)
{
	auto pos = Container.find(name.c_str());
	const CVariant& value = pos->second;
	if (!value.HasError()) {
		return value.GetSubValue("PointA.Y").ToDouble();
	}
	else
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}

double OutputObserver::GetLineFPointBX(string name)
{
	auto pos = Container.find(name.c_str());
	const CVariant& value = pos->second;
	if (!value.HasError()) {
		return value.GetSubValue("PointB.X").ToDouble();
	}
	else
	{
		throw std::runtime_error("Keyname " + name + " is not exist.");
	}
}

double OutputObserver::GetLineFPointBY(string name)
{
	auto pos = Container.find(name.c_str());
	const CVariant& value = pos->second;
	if (!value.HasError()) {
		return value.GetSubValue("PointB.Y").ToDouble();
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
