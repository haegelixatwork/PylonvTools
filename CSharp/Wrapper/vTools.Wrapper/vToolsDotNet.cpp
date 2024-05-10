#include "vToolsDotNet.h"

void vToolsDotNet::EnableCameraEmulator()
{
	_putenv("PYLON_CAMEMU=1");
}

void vToolsDotNet::PylonInitialize()
{
	Pylon::PylonInitialize();
}

void vToolsDotNet::PylonTerminate()
{
	Pylon::PylonTerminate();
}

vToolsDotNet::vToolsDotNet()
{
	tools = new vTools();
}

vToolsDotNet::!vToolsDotNet()
{
	throw gcnew System::NotImplementedException();
}

void vToolsDotNet::LoadRecipe(String^ fileName)
{
	tools->LoadRecipe(ConvertToStringt(fileName));
}

void vToolsDotNet::SetParameters(String^ name, String^ value)
{
	tools->SetParameters(ConvertToStringt(name), ConvertToStringt(value));
}

void vToolsDotNet::RegisterAllOutputsObserver()
{
	tools->RegisterAllOutputsObserver();
}

void vToolsDotNet::Start()
{
	tools->Start();
}

bool vToolsDotNet::WaitObject(UInt32 timeOut)
{
	return tools->WaitObject(timeOut);
}

void vToolsDotNet::Stop()
{
	tools->Stop();
}

void vToolsDotNet::SetString(String^ name, String^ value)
{
	tools->SetString(ConvertToStringt(name), ConvertToStringt(value));
}

void vToolsDotNet::SetBool(String^ name, bool value)
{
	tools->SetBool(ConvertToStringt(name), value);
}

void vToolsDotNet::SetLong(String^ name, long value)
{
	tools->SetLong(ConvertToStringt(name), value);
}

void vToolsDotNet::SetDouble(String^ name, double value)
{
	tools->SetDouble(ConvertToStringt(name), value);
}

void vToolsDotNet::SetImage(String^ name, cli::array<Byte>^ img, int w, int h, int channels)
{
	auto ptr = Marshal::AllocHGlobal(sizeof(Byte)* img->Length);
	Marshal::Copy(img, 0, ptr, img->Length);
	tools->SetImage(ConvertToStringt(name), ptr.ToPointer(), w, h, channels);
	Marshal::FreeHGlobal(ptr);
}

bool vToolsDotNet::NextOutput()
{
	return tools->ResultCollector.NextOutput();
}

cli::array<Byte>^ vToolsDotNet::GetImage(String^ name, [Out] int% imgW, [Out] int% imgH, [Out] int% imgC)
{
	int w , h , c;
	w = h = c = 0;
	auto cimg = tools->ResultCollector.GetImage(ConvertToStringt(name), &w, &h, &c);
	imgW = w;
	imgH = h;
	imgC = c;
	cli::array< Byte >^ byteArray = gcnew cli::array< Byte >(imgW * imgH + 2);
	Marshal::Copy((IntPtr)cimg.GetBuffer(), byteArray, 0, byteArray->Length);
	cimg.Release();
	return byteArray;
}

String^ vToolsDotNet::GetString(String^ name)
{
	return gcnew String(tools->ResultCollector.GetString(ConvertToStringt(name)));
}

bool vToolsDotNet::GetBool(String^ name)
{
	return tools->ResultCollector.GetBool(ConvertToStringt(name));
}

int64_t vToolsDotNet::GetLong(String^ name)
{
	return tools->ResultCollector.GetLong(ConvertToStringt(name));
}

double vToolsDotNet::GetDouble(String^ name)
{
	return tools->ResultCollector.GetDouble(ConvertToStringt(name));
}

void vToolsDotNet::GetPointF(String^ name, [Out] double% x, [Out] double% y)
{
	double X , Y;
	X = Y = 0;
	tools->ResultCollector.GetPointF(ConvertToStringt(name), &X, &Y);
	x = X;
	y = Y;
}

void vToolsDotNet::GetRectangleF(String^ name, [Out] double% x, [Out] double% y, [Out] double% w, [Out] double% h, [Out] double% a)
{
	double X, Y, H, W, A;
	X = Y = H = W = A = 0;
	tools->ResultCollector.GetRectangleF(ConvertToStringt(name), &X, &Y, &H, &W, &A);
	x = X;
	y = Y;
	h = H;
	w = W;
	a = A;
}

void vToolsDotNet::GetCircleF(String^ name, [Out] double% x, [Out] double% y, [Out] double% r)
{
	double X, Y, R;
	X = Y = R = 0;
	tools->ResultCollector.GetCircleF(ConvertToStringt(name), &X, &Y, &R);
	x = X;
	y = Y;
	r = R;
}

void vToolsDotNet::GetEllipseF(String^ name, [Out] double% x, [Out] double% y, [Out] double% r1, [Out] double% r2, [Out] double% a)
{
	double X, Y, R1, R2, A;
	X = Y = R1 = R2 = A = 0;
	tools->ResultCollector.GetEllipseF(ConvertToStringt(name), &X, &Y, &R1, &R2, &A);
	x = X;
	y = Y;
	r1 =R1;
	r2 =R2;
	a = A;
}

void vToolsDotNet::GetLineF(String^ name, [Out] double% x1, [Out] double% y1, [Out] double% x2, [Out] double% y2)
{
	double X1, Y1, X2, Y2;
	X1 = Y1 = X2 = Y2 = 0;
	tools->ResultCollector.GetLineF(ConvertToStringt(name), &X1, &Y1, &X1, &Y2);
	x1 = X1;
	y1 = Y1;
	x2 = X2;
	y2 = Y2;
}

cli::array<String^>^ vToolsDotNet::GetStringArray(String^ name)
{
	int num = 0;
	auto pData = tools->ResultCollector.GetStringList(ConvertToStringt(name), &num);
	auto intptrs = gcnew cli::array<IntPtr>(num);
	try
	{
		Marshal::Copy((IntPtr)pData, intptrs, 0, intptrs->Length);
		auto values = gcnew cli::array<String^>(num);
		int i;
		for (i = 0; i < num; i++)
		{
			values[i] = Marshal::PtrToStringAnsi(intptrs[i]);
		}
		return values;
	}
	finally
	{
		free(pData);
	}
}

cli::array<bool>^ vToolsDotNet::GetBoolArray(String^ name)
{
	int num = 0;
	auto pData = tools->ResultCollector.GetBoolArray(ConvertToStringt(name), &num);
	auto values = gcnew cli::array<bool>(num);
	int i;
	for (i = 0; i < num; i++)
	{
		values[i] = pData[i];
	}
	return values;
}

cli::array<int64_t>^ vToolsDotNet::GetLongArray(String^ name)
{
	int num = 0;
	auto pData = tools->ResultCollector.GetLongArray(ConvertToStringt(name), &num);
	auto values = gcnew cli::array<int64_t>(num);
	try
	{
		Marshal::Copy((IntPtr)pData, values, 0, values->Length);
		return values;
	}
	finally
	{
		free(pData);
	}
}

cli::array<double>^ vToolsDotNet::GetDoubleArray(String^ name)
{
	int num = 0;
	auto pData = tools->ResultCollector.GetDoubleArray(ConvertToStringt(name), &num);
	auto values = gcnew cli::array<double>(num);
	try
	{
		Marshal::Copy((IntPtr)pData, values, 0, values->Length);
		return values;
	}
	finally
	{
		free(pData);
	}
}

void vToolsDotNet::GetPointFArray(String^ name, [Out] cli::array<double>^% x, [Out] cli::array<double>^% y)
{
	int num = 0;
	double* pX = nullptr; double* pY = nullptr;
	tools->ResultCollector.GetPointFArray(ConvertToStringt(name), &num, &pX, &pY);
	auto valuesX = gcnew cli::array<double>(num);
	auto valuesY = gcnew cli::array<double>(num);
	try
	{
		Marshal::Copy((IntPtr)pX, valuesX, 0, valuesX->Length);
		Marshal::Copy((IntPtr)pY, valuesY, 0, valuesY->Length);
		x = valuesX;
		y = valuesY;
	}
	finally
	{
		free(pX);
		free(pY);
	}
}

void vToolsDotNet::GetRectangleFArray(String^ name, [Out] cli::array<double>^% x, [Out] cli::array<double>^% y, [Out] cli::array<double>^% w, [Out] cli::array<double>^% h, [Out] cli::array<double>^% a)
{
	int num = 0;
	double* pX = nullptr; double* pY = nullptr; double* pH = nullptr; double* pW = nullptr; double* pA = nullptr;
	tools->ResultCollector.GetRectangleFArray(ConvertToStringt(name), &num, &pX, &pY, &pH, &pW, &pA);
	auto valuesX = gcnew cli::array<double>(num);
	auto valuesY = gcnew cli::array<double>(num);
	auto valuesW = gcnew cli::array<double>(num);
	auto valuesH = gcnew cli::array<double>(num);
	auto valuesA = gcnew cli::array<double>(num);
	try
	{
		Marshal::Copy((IntPtr)pX, valuesX, 0, valuesX->Length);
		Marshal::Copy((IntPtr)pY, valuesY, 0, valuesY->Length);
		Marshal::Copy((IntPtr)pW, valuesW, 0, valuesW->Length);
		Marshal::Copy((IntPtr)pH, valuesH, 0, valuesH->Length);
		Marshal::Copy((IntPtr)pA, valuesA, 0, valuesA->Length);
		x = valuesX;
		y = valuesY;
		w = valuesW;
		h = valuesH;
		a = valuesA;
	}
	finally
	{
		free(pX);
		free(pY);
		free(pW);
		free(pH);
		free(pA);
	}
}

void vToolsDotNet::GetCircleFArray(String^ name, [Out] cli::array<double>^% x, [Out] cli::array<double>^% y, [Out] cli::array<double>^% r)
{
	int num = 0;
	double* pX = nullptr; double* pY = nullptr; double* pR = nullptr;
	tools->ResultCollector.GetCircleFArray(ConvertToStringt(name), &num, &pX, &pY, &pR);
	auto valuesX = gcnew cli::array<double>(num);
	auto valuesY = gcnew cli::array<double>(num);
	auto valuesR = gcnew cli::array<double>(num);
	try
	{
		Marshal::Copy((IntPtr)pX, valuesX, 0, valuesX->Length);
		Marshal::Copy((IntPtr)pY, valuesY, 0, valuesY->Length);
		Marshal::Copy((IntPtr)pR, valuesR, 0, valuesR->Length);
		x = valuesX;
		y = valuesY;
		r = valuesR;
	}
	finally
	{
		free(pX);
		free(pY);
		free(pR);
	}
}

void vToolsDotNet::GetEllipseFArray(String^ name, [Out] cli::array<double>^% x, [Out] cli::array<double>^% y, [Out] cli::array<double>^% r1, [Out] cli::array<double>^% r2, [Out] cli::array<double>^% a)
{
	int num = 0;
	double** pX = nullptr; double** pY = nullptr; double** pR1 = nullptr; double** pR2 = nullptr; double** pA = nullptr;
	tools->ResultCollector.GetEllipseFArray(ConvertToStringt(name), &num, pX, pY, pR1, pR2, pA);
	auto valuesX = gcnew cli::array<double>(num);
	auto valuesY = gcnew cli::array<double>(num);
	auto valuesR1 = gcnew cli::array<double>(num);
	auto valuesR2 = gcnew cli::array<double>(num);
	auto valuesA = gcnew cli::array<double>(num);
	try
	{
		Marshal::Copy((IntPtr)pX, valuesX, 0, valuesX->Length);
		Marshal::Copy((IntPtr)pY, valuesY, 0, valuesY->Length);
		Marshal::Copy((IntPtr)pR1, valuesR1, 0, valuesR1->Length);
		Marshal::Copy((IntPtr)pR2, valuesR2, 0, valuesR2->Length);
		Marshal::Copy((IntPtr)pA, valuesA, 0, valuesA->Length);
		x = valuesX;
		y = valuesY;
		r1 = valuesR1;
		r2 = valuesR2;
		a = valuesA;
	}
	finally
	{
		free(pX);
		free(pY);
		free(pR1);
		free(pR2);
		free(pA);
	}
}

void vToolsDotNet::GetLineFArray(String^ name, [Out] cli::array<double>^% x1, [Out] cli::array<double>^% y1, [Out] cli::array<double>^% x2, [Out] cli::array<double>^% y2)
{
	int num = 0;
	double** pX1 = nullptr; double** pY1 = nullptr; double** pX2 = nullptr; double** pY2 = nullptr;
	tools->ResultCollector.GetLineFArray(ConvertToStringt(name), &num, pX1, pY1, pX2, pY2);
	auto valuesX1 = gcnew cli::array<double>(num);
	auto valuesY1 = gcnew cli::array<double>(num);
	auto valuesX2 = gcnew cli::array<double>(num);
	auto valuesY2 = gcnew cli::array<double>(num);
	try
	{
		Marshal::Copy((IntPtr)pX1, valuesX1, 0, valuesX1->Length);
		Marshal::Copy((IntPtr)pY1, valuesY1, 0, valuesY1->Length);
		Marshal::Copy((IntPtr)pX2, valuesX2, 0, valuesX2->Length);
		Marshal::Copy((IntPtr)pY2, valuesY2, 0, valuesY2->Length);
		x1= valuesX1;
		y1= valuesY1;
		x2 = valuesX2;
		y2 = valuesY2;
	}
	finally
	{
		free(pX1);
		free(pY1);
		free(pX2);
		free(pY2);
	}
}

vToolsDotNet::~vToolsDotNet()
{
	tools->Dispose();
}

String_t vToolsDotNet::ConvertToStringt(String^ value)
{
	IntPtr ptr = Marshal::StringToHGlobalAnsi(value);
	const char* chars = (const char*)(ptr).ToPointer();
	int len = MultiByteToWideChar(CP_ACP, 0, chars, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, chars, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);

	Marshal::FreeHGlobal(ptr);
	//msg = nullptr;
	String_t txt(str);	
	if (wstr) delete[] wstr;
	return txt;
}