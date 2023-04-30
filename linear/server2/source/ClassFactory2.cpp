#include "ClassFactory2.h"
#include "EquationSolver2.h"

ClassFactory::ClassFactory()
{
    this->a = 10;
    this->b = 20;
    this->c = 100;
    this->d = 200;
    this->e = 300;
    this->refCount = 0;
}

HRESULT_ ClassFactory::QueryInterface(const IID_& iid, void** object)
{
    std::cout<<"ClassFactory::QueryInterface"<<std::endl;

    if (iid == IID_IClassFactory_)
    {
        *object = (IUnknown_*) (IClassFactory_*) this;
    }
    else if (iid == IID_ClassFactory)
    {
        *object = (IUnknown_*) (ClassFactory*) this;
    }
    else
    {
        *object = NULL;
        return E_NOINTERFACE_;
    }
    
    this->AddRef();
    return S_OK_;
}

HRESULT_ ClassFactory::AddRef()
{
    refCount++;
    return refCount;
}

HRESULT_ ClassFactory::Release()
{
    refCount--;

    if (refCount == 0)
    {
        delete this;
    }
    
    return refCount;
}

HRESULT_ ClassFactory::CreateInstance(const IID_& iid, void** object)
{
    std::cout<<"ClassFactory::CreateInstance"<<std::endl;
    IUnknown_* s = (IUnknown_*)(IEquationX*)new EquationSolver();

    s->AddRef();
    HRESULT_ res = s->QueryInterface(iid, object);
    s->Release();
    
    return res;
}

HRESULT_ ClassFactory::CreateInstance(const IID_& iid, void** object, int license[])
{
    std::cout<<"ClassFactory::CreateInstance with license"<<std::endl;
    HRESULT_ res = E_NOCOMPONENT_;

    if (license != NULL)
    {
        IUnknown_* s = (IUnknown_*)(IEquationY*)new EquationSolver();

        s->AddRef();
        res = s->QueryInterface(iid, object);
        s->Release();
    }
    
    return res;
}

ClassFactory::~ClassFactory()
{
    std::cout<<"ClassFactory::~ClassFactory()"<<std::endl;
}

HRESULT_ __stdcall CreateInstance(const CLSID_& clsid, const IID_& iid, void** object)
{
    std::cout<<"Global CreateInstance"<<std::endl;

    IClassFactory_* s = NULL;
    HRESULT_ res = GetClassObject(clsid, IID_IClassFactory_, (void**) &s);

    if (res == S_OK_)
    {
        if (iid == IID_IX)
        {
            IEquationX* iex = NULL;

            res = s->CreateInstance(iid, (void**) &iex);
            *object = (IUnknown_*) (IEquationX*) iex;
        }
        else if (iid == IID_IY)
        {
            IEquationY* iey = NULL;

            res = s->CreateInstance(iid, (void**) &iey);
            *object = (IUnknown_*) (IEquationY*) iey;
        }
    }
    else
    {
        std::cout<<"Global CreateInstance ERROR "<<res<<std::endl;
    }
   
    return res;
}

HRESULT_ __stdcall GetClassObject(const CLSID_& clsid, const IID_& iid, void** object)
{
    std::cout<<"Global GetClassObject"<<std::endl;

    IUnknown_* s = NULL;

    if (clsid == CLSID_ClassFactory)
    {
        s = (IUnknown_*) (IClassFactory_*) new ClassFactory();
    }
    else
    {
        *object = NULL;
        return E_NOCOMPONENT_;
    }

    s->AddRef();
    HRESULT_ res = s->QueryInterface(iid, object);
    s->Release();
    
    return S_OK_;
}

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
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