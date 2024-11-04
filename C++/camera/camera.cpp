// camera/main.cpp
/*
    Sample demonstrating how to use and parameterize the Camera vTool (no license required).
    Note: The Recipe Code Generator of the pylon Viewer allows you to generate
          sample code to use your vTool recipe in your development environment.
*/
// Include files to use the pylon API.
#include <pylon/PylonIncludes.h>
#ifdef PYLON_WIN_BUILD
#  include <pylon/PylonGUI.h>
#endif
// Extend the pylon API for using pylon data processing
#include <pylondataprocessing/PylonDataProcessingIncludes.h>
// The sample uses the std::list
#include <list>

// Namespaces for using pylon objects
using namespace Pylon;
using namespace Pylon::DataProcessing;

// Namespace for using cout
using namespace std;

// Number of images to be grabbed
static const uint32_t c_countOfImagesToGrab = 100;

int main(int /*argc*/, char* /*argv*/[])
{
    // The exit code of the sample application.
    int exitCode = 0;

    // Enable the pylon camera emulator for grabbing images from disk
    // by setting the necessary environment variable.
#if defined(PYLON_WIN_BUILD)
    _putenv("PYLON_CAMEMU=1");
#elif defined(PYLON_UNIX_BUILD)
    setenv("PYLON_CAMEMU", "1", true);
#endif

    // Before using any pylon methods, the pylon runtime must be initialized.
    PylonInitialize();

    try
    {
        TCHAR tRoot[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, tRoot);
        wstring wRoot(&tRoot[0]);
        string recipePath(wRoot.begin(), wRoot.end());
        recipePath += "\\camera.precipe";
        // This object is used for collecting the output data.
        // If placed on the stack it must be created before the recipe
        // so that it is destroyed after the recipe.
        CGenericOutputObserver resultCollector;
        // Create a recipe representing a design created using
        // the pylon Viewer Workbench.
        CRecipe recipe;

        // Load the recipe file.
        // Note: PYLON_DATAPROCESSING_CAMERA_RECIPE is a string
        // created by the CMake build files.
        recipe.Load(recipePath.c_str());

        // For demonstration purposes only
        // Let's check the Pylon::CDeviceInfo properties of the camera we are going to use.
        // Basler recommends using the DeviceClass and the UserDefinedName to identify a camera.
        // The UserDefinedName is taken from the DeviceUserID parameter that you can set in the pylon Viewer's Features pane.
        // Note: USB cameras must be disconnected and reconnected or reset to provide the new DeviceUserID.
        // This is due to restrictions defined by the USB standard.
        cout << "Properties used for selecting a camera device" << endl;
        CIntegerParameter devicePropertySelector =
            recipe.GetParameters().Get(IntegerParameterName("MyCamera/@vTool/DevicePropertySelector"));
        if (devicePropertySelector.IsWritable())
        {
            CStringParameter deviceKey = recipe.GetParameters().Get(StringParameterName("MyCamera/@vTool/DevicePropertyKey"));
            CStringParameter deviceValue = recipe.GetParameters().Get(StringParameterName("MyCamera/@vTool/DevicePropertyValue"));
            for (int64_t i = devicePropertySelector.GetMin(); i <= devicePropertySelector.GetMax(); ++i)
            {
                devicePropertySelector.SetValue(i);
                cout << deviceKey.GetValue() << "=" << deviceValue.GetValue() << endl;
            }
        }
        else
        {
            cout << "The first camera device found is used." << endl;
        }

        // For demonstration purposes only
        // Print available parameters.
        {
            cout << "Parameter names before allocating resources" << endl;
            StringList_t parameterNames = recipe.GetParameters().GetAllParameterNames();
            for (const auto& name : parameterNames)
            {
                cout << name << endl;
            }
        }

        // Allocate the required resources. This includes the camera device.
        recipe.PreAllocateResources();

        // For demonstration purposes only
        cout << "Selected camera device:" << endl;
        cout << "ModelName=" << recipe.GetParameters().Get(StringParameterName("MyCamera/@vTool/SelectedDeviceModelName")).GetValueOrDefault("N/A") << std::endl;
        cout << "SerialNumber=" << recipe.GetParameters().Get(StringParameterName("MyCamera/@vTool/SelectedDeviceSerialNumber")).GetValueOrDefault("N/A") << std::endl;
        cout << "VendorName=" << recipe.GetParameters().Get(StringParameterName("MyCamera/@vTool/SelectedDeviceVendorName")).GetValueOrDefault("N/A") << std::endl;
        cout << "UserDefinedName=" << recipe.GetParameters().Get(StringParameterName("MyCamera/@vTool/SelectedDeviceUserDefinedName")).GetValueOrDefault("N/A") << std::endl;
        // StringParameterName is the type of the parameter.
        // MyCamera is the name of the vTool.
        // Use @vTool if you want to access the vTool parameters.
        // Use @CameraInstance if you want to access the parameters of the CInstantCamera object used internally.
        // Use @DeviceTransportLayer if you want to access the transport layer parameters.
        // Use @CameraDevice if you want to access the camera device parameters.
        // Use @StreamGrabber0 if you want to access the camera device parameters.
        // SelectedDeviceUserDefinedName is the name of the parameter.

        // For demonstration purposes only
        // Print available parameters after allocating resources. Now we can access the camera parameters.
        {
            cout << "Parameter names after allocating resources" << endl;
            StringList_t parameterNames = recipe.GetParameters().GetAllParameterNames();
            for (const auto& name : parameterNames)
            {
                cout << name << endl;
            }
        }


        // For demonstration purposes only
        // Print available output names.
        StringList_t outputNames;
        recipe.GetOutputNames(outputNames);
        for (const auto& outputName : outputNames)
        {
            cout << "Output found: " << outputName << std::endl;
        }

        // Register the helper object for receiving all output data.
        recipe.RegisterAllOutputsObserver(&resultCollector, RegistrationMode_Append);

        // Start the processing. The recipe is triggered internally
        // by the camera vTool for each image.
        recipe.Start();

        int count = 0;
        bool testImage1 = true;
        CEnumParameter testImageSelector = recipe.GetParameters().Get(EnumParameterName("MyCamera/@CameraDevice/TestImageSelector|MyCamera/@CameraDevice/TestPattern"));
        for (uint32_t i = 0; i < c_countOfImagesToGrab; ++i)
        {
            if (resultCollector.GetWaitObject().Wait(5000))
            {
                CVariantContainer result = resultCollector.RetrieveResult();
                CVariant imageVariant = result["Image"];
				
                if (!imageVariant.HasError())
                {
                    // Access the image data.
                    auto image = imageVariant.ToImage();
                    cout << "SizeX: " << image.GetWidth() << endl;
                    cout << "SizeY: " << image.GetHeight() << endl;
                    const uint8_t* pImageBuffer = static_cast<uint8_t*>(image.GetBuffer());
                    cout << "Gray value of first pixel: " << static_cast<uint32_t>(pImageBuffer[0]) << endl << endl;

#ifdef PYLON_WIN_BUILD
                    DisplayImage(1, image);
#endif
                }
                else
                {
                    cout << "An error occurred in processing: " << imageVariant.GetErrorDescription() << endl;
                }

                ++count;

                // Now let's change a parameter every 10 images
                // while grabbing is active.
                if (0 == count % 10)
                {
                    testImage1 = !testImage1;
                    if (testImage1)
                    {
                        testImageSelector.SetValue("Testimage1");
                    }
                    else
                    {
                        testImageSelector.SetValue("Testimage2");
                    }
                }
            }
            else
            {
                throw RUNTIME_EXCEPTION("Result timeout");
            }
        }

        // Stop the processing.
        recipe.Stop();

        // Optionally, deallocate resources.
        recipe.DeallocateResources();
    }
    catch (const GenericException& e)
    {
        // Error handling.
        cerr << "An exception occurred." << endl << e.GetDescription() << endl;
        exitCode = 1;
    }

    // Comment the following two lines to disable waiting on exit.
    cerr << endl << "Press enter to exit." << endl;
    while (cin.get() != '\n')
        ;

    // Releases all pylon resources.
    PylonTerminate();

    return exitCode;
}