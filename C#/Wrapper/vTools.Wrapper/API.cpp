#ifdef VTOOLSWRAPPER_EXPORTS //同專案名稱，只是後面固定為_EXPORTS
#define VTOOLSWRAPPER_API __declspec(dllexport) //請注意！正確的是Export要亮起
#else
#define VTOOLSWRAPPER_API __declspec(dllimport)
#endif
#include "vTools.h"

extern "C"
{
	static vTools* tools = NULL;

	VTOOLSWRAPPER_API bool EnableCameraEmulator()
	{
		_putenv("PYLON_CAMEMU=1");
		return 1;
	}

	VTOOLSWRAPPER_API bool LoadRecipe(char* fileName)
	{
		tools = new vTools();
		tools->LoadRecipe(string(fileName));
		return 1;
	}
	VTOOLSWRAPPER_API bool SetParameters(char* name, char* value)
	{
		tools->SetParameters(name, value);
		return 1;
	}
	VTOOLSWRAPPER_API bool RegisterAllOutputsObserver()
	{
		tools->RegisterAllOutputsObserver();
		return 1;
	}
	VTOOLSWRAPPER_API bool Start()
	{
		tools->Start();
		return 1;
	}
	VTOOLSWRAPPER_API bool WaitObject(unsigned int timeOut)
	{
		return tools->WaitObject(timeOut);
	}
	VTOOLSWRAPPER_API bool Stop()
	{
		tools->Stop();
		return 1;
	}
	VTOOLSWRAPPER_API bool SetRecipeInput(char* name, char* value)
	{
		tools->SetRecipeInput(name, value);
		return 1;
	}
	VTOOLSWRAPPER_API bool Dispose()
	{
		tools->Dispose();
		return 1;
	}

	VTOOLSWRAPPER_API bool NextOutput()
	{
		return tools->ResultCollector.NextOutput();
	}

	VTOOLSWRAPPER_API byte* GetImage(char* name, int* w, int* h, int* channels)
	{
		auto cimg = tools->ResultCollector.GetImage(name, w, h, channels);
		int imgW = *w;
		int imgH = *h;
		int imgC = *channels;
		int size = imgW * imgH * imgC;
		byte* result = (byte*)malloc(size * sizeof(byte*));
		memcpy(result, cimg.GetBuffer(), size);
		cimg.Release();
		return result;
	}
	VTOOLSWRAPPER_API const char* GetString(char* name)
	{
		return tools->ResultCollector.GetString(name);
	}

	VTOOLSWRAPPER_API bool GetBool(char* name)
	{
		return tools->ResultCollector.GetBool(name);
	}

	VTOOLSWRAPPER_API int GetInt(char* name)
	{
		return tools->ResultCollector.GetInt(name);
	}

	VTOOLSWRAPPER_API double GetDouble(char* name)
	{
		return tools->ResultCollector.GetDouble(name);
	}

	VTOOLSWRAPPER_API void GetPointF(char* name, double* x, double* y)
	{
		tools->ResultCollector.GetPointF(name, x, y);
	}

	VTOOLSWRAPPER_API void GetRectangleF(char* name, double* x, double* y, double* w, double* h, double* a)
	{
		tools->ResultCollector.GetRectangleF(name, x, y, h, w, a);
	}

	VTOOLSWRAPPER_API void GetCircleF(char* name, double* x, double* y, double* r)
	{
		tools->ResultCollector.GetCircleF(name, x, y, r);
	}

	VTOOLSWRAPPER_API void GetEllipseF(char* name, double* x, double* y, double* r1, double* r2, double* a)
	{
		tools->ResultCollector.GetEllipseF(name, x, y, r1, r2, a);
	}

	VTOOLSWRAPPER_API void GetLineF(char* name, double* x1, double* y1, double* x2, double* y2)
	{
		tools->ResultCollector.GetLineF(name, x1, y1, x1, y2);
	}

	VTOOLSWRAPPER_API const char** GetStringArray(char* name, int* num)
	{	
		return tools->ResultCollector.GetStringList(name, num);
	}

	VTOOLSWRAPPER_API const bool* GetBoolArray(char* name, int* num)
	{
		return tools->ResultCollector.GetBoolArray(name, num);
	}

	VTOOLSWRAPPER_API const int* GetIntArray(char* name, int* num)
	{
		return tools->ResultCollector.GetIntArray(name, num);
	}

	VTOOLSWRAPPER_API const double* GetDoubleArray(char* name, int* num)
	{
		return tools->ResultCollector.GetDoubleArray(name, num);
	}

	VTOOLSWRAPPER_API void GetPointFArray(char* name, int* num, double** x, double** y)
	{
		tools->ResultCollector.GetPointFArray(name, num, x, y);
	}

	VTOOLSWRAPPER_API void GetRectangleFArray(char* name, int* num, double** x, double** y, double** w, double** h, double** a)
	{
		tools->ResultCollector.GetRectangleFArray(name, num, x, y, h, w, a);
	}

	VTOOLSWRAPPER_API void GetCircleFArray(char* name, int* num, double** x, double** y, double** r)
	{
		tools->ResultCollector.GetCircleFArray(name, num, x, y, r);
	}

	VTOOLSWRAPPER_API void GetEllipseFArray(char* name, int* num, double** x, double** y, double** r1, double** r2, double** a)
	{
		tools->ResultCollector.GetEllipseFArray(name, num, x, y, r1, r2, a);
	}

	VTOOLSWRAPPER_API void GetLineFArray(char* name, int* num, double** x1, double** y1, double** x2, double** y2)
	{
		tools->ResultCollector.GetLineFArray(name, num, x1, y1, x1, y2);
	}

	VTOOLSWRAPPER_API void Free(void* ptr)
	{
		free(ptr);
	}
}