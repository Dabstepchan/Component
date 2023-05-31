#include "lib/interfaces.h"
#include "lib/interfaces2.h"
//#include "wrapper.h"
#include <objbase.h>

#include <vector>
#include <iostream>

const IID IID_NULL_ = {0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
IID Constants::IID_IUnknown = {0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
IID Constants::IID_IClassFactory = {0x00000100,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

IID Constants::IID_IEquationX = {0x00000001,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
IID Constants::IID_IEquationY = {0x00000002,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
IID Constants::IID_ClassFactory = {0x00000101,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
IID Constants::IID_IDispatch = {0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

//{4399E097-D19C-480D-90EE-1AA25B858D31}
CLSID Constants::CLSID_EquationSolver = {0x4399E097,0xD19C,0x480D,{0x90,0xEE,0x1A,0xA2,0x5B,0x85,0x8D,0x31}};

IID Constants2::IID_IAdvESolverClassFactory = {0x00000012,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
IID Constants2::IID_IEquationZ = {0x00000003,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};

//{4BFDC92A-A7F7-4491-AFC7-569C9555EF45}
CLSID Constants2::CLSID_AdvEquationSolver = {0x4BFDC92A,0xA7F7,0x4491,{0xAF,0xC7,0x56,0x9C,0x95,0x55,0xEF,0x45}};

int main()
{
    std::cout<<"Client main start"<<std::endl;

    CoInitialize(NULL);

    std::vector<std::vector<double>> matrix = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
    std::vector<double> vector = {1.0, 2.0, 3.0};
    std::vector<std::vector<double>> slauMatrix;
    std::vector<double> slauVector;

    CLSID CLSID_EquationSolver;
    {
        const wchar_t* progID = L"EQS.Application";

        HRESULT resCLSID = CLSIDFromProgID(progID, &CLSID_EquationSolver);
        
        if (!SUCCEEDED(resCLSID))
        {
            std::cout<<"NO CLSID"<<std::endl;
        }
    }

    IClassFactory* PCF = NULL;
    HRESULT resFactory = CoGetClassObject(Constants::CLSID_EquationSolver, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IClassFactory, (void**) &PCF);
    if (!SUCCEEDED(resFactory))
    {
        std::cout<<"No factory"<<std::endl;
    }

    IEquationX* iex = NULL;
    HRESULT resInstance = PCF->CreateInstance(NULL, Constants::IID_IEquationX, (void**) &iex);
    if (!SUCCEEDED(resInstance))
    {
        std::cout<<"No instance"<<std::endl;
    }

    IEquationY* iey = NULL;
    HRESULT resQuery = iex->QueryInterface(Constants::IID_IEquationY, (void**) &iey);
    if (!SUCCEEDED(resQuery))
    {
        std::cout<<"No query"<<std::endl;
    }

    iex->CreateSystem(matrix, vector, slauMatrix, slauVector);

    IDispatch* pDisp = NULL;
    HRESULT resQueryDisp = iex->QueryInterface(Constants::IID_IDispatch,(void**)&pDisp);
    if (!(SUCCEEDED(resQueryDisp)))
    {
        std::cout<<"No query dispatch";
    }

    DISPID dispid;
    int namesCount = 1;
    OLECHAR** names = new OLECHAR*[namesCount];
    OLECHAR* name = const_cast<OLECHAR*>(L"CalculateDeterminant");
    names[0] = name;
    HRESULT resID_Name = pDisp->GetIDsOfNames(
                                                IID_NULL_,
                                                names,
                                                namesCount,
                                                GetUserDefaultLCID(),
                                                &dispid
                                            );
    if (!(SUCCEEDED(resID_Name)))
    {
        std::cout<<"No id of name"<<std::endl;
    }
    else
    {
         DISPPARAMS dispparamsNoArgs = {
                                         NULL,
                                         NULL,
                                         0,
                                         0,
                                       };

        HRESULT resInvoke = pDisp->Invoke(
                                            dispid, // DISPID
                                            IID_NULL_,
                                            GetUserDefaultLCID(),
                                            DISPATCH_METHOD,
                                            &dispparamsNoArgs,
                                            NULL,
                                            NULL,
                                            NULL
                                        );
        if (!(SUCCEEDED(resInvoke)))
        {
          std::cout<<"No invoke"<<std::endl;
        }
      }

      PCF->Release();
      iex->Release();
      iey->Release();
      pDisp->Release();

    CoUninitialize();

    return 0;
}