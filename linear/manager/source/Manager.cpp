#include <windows.h>
#include <iostream>

using IID_ = int;
using CLSID_ = int;
using HRESULT_ = int;
using ULONG_ = int;

const int IID_IUnknown_ = 0;
const int IID_IX = 1;
const int IID_IY = 2;

const int CLSID_CServer = 1;
const int IID_IClassFactory_ = 100;
const int IID_ClassFactory = 101;
const int CLSID_ClassFactory = 1;

const int S_OK_ = 0;
const int E_NOINTERFACE_ = 1;
const int E_NOCOMPONENT_ = 2;

typedef HRESULT_ __stdcall (*FunctionType) (const CLSID_&, const IID_&, void**);

extern "C" HRESULT_ __stdcall __declspec(dllexport) CreateInstance(const CLSID_& clsid, const IID_& iid, void** object)
{
    return 0;
}

extern "C" HRESULT_ __stdcall __declspec(dllexport) GetClassObject(const CLSID_& clsid, const IID_& iid, void** object)
{
    const char* path;

    if (clsid == CLSID_ClassFactory)
    {
        path = "./manager/source/lib/server.dll";
    }
    else
    {
        return E_NOCOMPONENT_;
    }
    
    HINSTANCE h = LoadLibrary(path);

    if (!h)
    {
           std::cout<<"No dll!!!"<<std::endl;
    }

    FunctionType GCO=(FunctionType) GetProcAddress(h,"GetClassObject");

    if (!GCO)
    {
          std::cout << "No dll function" << std::endl;
    }

    return GCO(clsid, iid, object);
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            std::cout<<"DLL CONNECTED"<<std::endl;
            break;

        case DLL_PROCESS_DETACH:
            break;

        case DLL_THREAD_ATTACH:
            break;

        case DLL_THREAD_DETACH:
            break;
    }

    return TRUE;
}