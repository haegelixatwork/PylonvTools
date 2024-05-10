#pragma once
#include "pch.h" 
#include <pylon/PylonIncludes.h>
#include "vTools.h"
using namespace Pylon;
using namespace std;
using namespace System;
using namespace System::Runtime::InteropServices;
public ref class vToolsDotNet 
{
public:
	/// <summary>
	/// Enable camera emulator. Create a vitural caemra. But it needs to set image files folder.
	/// </summary>
	/// <returns></returns>
	void EnableCameraEmulator();
	/// <summary>
	/// Initializes the pylon runtime system.
	/// </summary>
	static void PylonInitialize();
	/// <summary>
	/// Frees up resources allocated by the pylon runtime system.
	/// </summary>
	static void PylonTerminate();
	vToolsDotNet();
	!vToolsDotNet();
	/// <summary>
	/// Load vTools recipe file.
	/// </summary>
	/// <param name="fileName"></param>
	void LoadRecipe(String^ fileName);
	/// <summary>
	/// Directly Set paratmers to vTool( Operator ).
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void SetParameters(String^ name, String^ value);
	/// <summary>
	///  Register all outputs observer.
	/// </summary>
	void RegisterAllOutputsObserver();
	/// <summary>
	/// Recipe start.
	/// </summary>
	void Start();
	/// <summary>
	/// Wait next output result.
	/// </summary>
	/// <param name="timeOut"></param>
	/// <returns></returns>
	bool WaitObject(UInt32 timeOut);
	/// <summary>
	/// Recipe stop.
	/// </summary>
	void Stop();
	/// <summary>
	/// Set input value by string.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void SetString(String^ name, String^ value);
	/// <summary>
	/// Set input value by boolean.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void SetBool(String^ name, bool value);
	/// <summary>
	/// Set input value by long.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void SetLong(String^ name, long value);
	/// <summary>
	/// Set input value by double.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="value"></param>
	void SetDouble(String^ name, double value);
	/// <summary>
	/// Set input value by image
	/// </summary>
	/// <param name="name"></param>
	/// <param name="img"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <param name="channels"></param>
	void SetImage(String^ name, cli::array<Byte>^ img, int w, int h, int channels);
	/// <summary>
	/// Get next output from queue.
	/// </summary>
	/// <returns></returns>
	bool NextOutput();
	/// <summary>
	/// Get image from output.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="imgW"></param>
	/// <param name="imgH"></param>
	/// <param name="imgC"></param>
	/// <returns></returns>
	cli::array< Byte >^ GetImage(String^ name, [Out] int% imgW, [Out] int% imgH, [Out] int% imgC);
	/// <summary>
	/// Get string from output.
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	String^ GetString(String^ name);
	/// <summary>
	/// Get boolean from output. 
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	bool GetBool(String^ name);
	/// <summary>
	/// Get long from output
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	int64_t GetLong(String^ name);
	/// <summary>
	/// Get double from output.
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	double GetDouble(String^ name);
	/// <summary>
	/// Get point from output.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void GetPointF(String^ name, [Out] double% x, [Out] double% y);
	/// <summary>
	/// Get rectangle from output.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <param name="a"></param>
	void GetRectangleF(String^ name, [Out] double% x, [Out] double% y, [Out] double% w, [Out] double% h, [Out] double% a);
	/// <summary>
	/// Get circle from output.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="r"></param>
	void GetCircleF(String^ name, [Out] double% x, [Out] double% y, [Out] double% r);
	/// <summary>
	/// Get ellipse from output.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="r1"></param>
	/// <param name="r2"></param>
	/// <param name="a"></param>
	void GetEllipseF(String^ name, [Out] double% x, [Out] double% y, [Out] double% r1, [Out] double% r2, [Out] double% a);
	/// <summary>
	/// Get line from output.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="x1"></param>
	/// <param name="y1"></param>
	/// <param name="x2"></param>
	/// <param name="y2"></param>
	void GetLineF(String^ name, [Out] double% x1, [Out] double% y1, [Out] double% x2, [Out] double% y2);
	/// <summary>
	/// Get string array from output.
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	cli::array< String^ >^ GetStringArray(String^ name);
	/// <summary>
	/// Get boolean array from output.
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	cli::array< bool >^ GetBoolArray(String^ name);
	/// <summary>
	/// Get long array from output.
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	cli::array< int64_t >^ GetLongArray(String^ name);
	/// <summary>
	/// Get double array from output.
	/// </summary>
	/// <param name="name"></param>
	/// <returns></returns>
	cli::array< double >^ GetDoubleArray(String^ name);
	/// <summary>
	/// Get point array from output.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	void GetPointFArray(String^ name, [Out] cli::array< double >^% x, [Out] cli::array< double >^% y);
	/// <summary>
	/// Get rectangle array from output.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="w"></param>
	/// <param name="h"></param>
	/// <param name="a"></param>
	void GetRectangleFArray(String^ name, [Out] cli::array< double >^% x, [Out] cli::array< double >^% y, [Out] cli::array< double >^% w, [Out] cli::array< double >^% h, [Out] cli::array< double >^% a);
	/// <summary>
	/// Get circle array from output.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="r"></param>
	void GetCircleFArray(String^ name, [Out] cli::array< double >^% x, [Out] cli::array< double >^% y, [Out] cli::array< double >^% r);
	/// <summary>
	/// Get ellipse array from output.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <param name="r1"></param>
	/// <param name="r2"></param>
	/// <param name="a"></param>
	void GetEllipseFArray(String^ name, [Out] cli::array< double >^% x, [Out] cli::array< double >^% y, [Out] cli::array< double >^% r1, [Out] cli::array< double >^% r2, [Out] cli::array< double >^% a);
	/// <summary>
	/// Get line array from output.
	/// </summary>
	/// <param name="name"></param>
	/// <param name="x1"></param>
	/// <param name="y1"></param>
	/// <param name="x2"></param>
	/// <param name="y2"></param>
	void GetLineFArray(String^ name, [Out] cli::array< double >^% x1, [Out] cli::array< double >^% y1, [Out] cli::array< double >^% x2, [Out] cli::array< double >^% y2);

protected:
	~vToolsDotNet();
private:
	vTools* tools;
	String_t ConvertToStringt(String^ value);
};