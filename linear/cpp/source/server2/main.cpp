#include "Components.h"

extern "C" HRESULT __stdcall __declspec(dllexport) DllGetClassObject(const CLSID& clsid, const IID& iid, void** object)
{
    std::cout<<"Global GetClassObject"<<std::endl;

    IUnknown* s = NULL;

    if (clsid == Constants2::CLSID_AdvEquationSolver)
    {
        s = (IUnknown*) (IClassFactory*) new AdvESolverClassFactory();
    }
    else
    {
        *object = NULL;
        return E_NOTIMPL;
    }

    s->AddRef();
    HRESULT res = s->QueryInterface(iid, object);
    s->Release();
    
    return S_OK;
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            std::cout<<"AdvEquationSolver dll connected!"<<std::endl;
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}