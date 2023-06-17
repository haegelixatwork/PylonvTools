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

	VTOOLSWRAPPER_API uint8_t* GetImage(char* name, int* w, int* h, int* channels)
	{
		auto cimg = tools->ResultCollector.GetImage(name, w, h, channels);
		int imgW = *w;
		int imgH = *h;
		int imgC = *channels;
		int size = imgW * imgH * imgC;
		uint8_t* result = (uint8_t*)malloc(size * sizeof(uint8_t*));
		memcpy(result, cimg.GetBuffer(), size);
		cimg.Release();
		return result;
	}
	VTOOLSWRAPPER_API const char* GetString(char* name)
	{
		String_t value = tools->ResultCollector.GetString(name);
		int len = MultiByteToWideChar(CP_ACP, 0, value.c_str(), -1, NULL, 0);
		wchar_t* wstr = new wchar_t[len + 1];
		memset(wstr, 0, len + 1);
		MultiByteToWideChar(CP_ACP, 0, value.c_str(), -1, wstr, len);
		len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
		char* str = new char[len + 1];
		memset(str, 0, len + 1);
		WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
		if (wstr) delete[] wstr;
		return str;
	}
	VTOOLSWRAPPER_API LPSAFEARRAY GetStringArray(char* name)
	{	
		auto vectors = tools->ResultCollector.GetStringList(name);

		CComSafeArray<BSTR> safeArray(static_cast<ULONG>(vectors.size()));
		vector<string>::const_iterator it;
		int i = 0;
		for (it = vectors.begin(); it != vectors.end(); ++it, ++i)
		{
			// note: you could also use std::wstring instead and avoid A2W conversion
			safeArray.SetAt(i, A2BSTR_EX((*it).c_str()), FALSE);
		}
		
		return safeArray;
	}
}