#pragma once
#include <pylon/PylonIncludes.h>
#include <pylondataprocessing/PylonDataProcessingIncludes.h>
using namespace Pylon;
using namespace Pylon::DataProcessing;
class ResultData
{
public:
	ResultData();
	CPylonImage image;
	StringList_t decodedBarcodes;
	bool hasError;
	String_t errorMessage;
};