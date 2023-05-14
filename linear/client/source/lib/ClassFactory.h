#pragma once

#include "EquationSolver.h"
#include "IClassFactory.h"

#include <iostream>

class ClassFactory : public IClassFactory_
{
    private:
        int a, b, c, d, e, refCount;
    public:
        ClassFactory();

        virtual HRESULT_ __stdcall QueryInterface(const IID_& iid, void** object);
        virtual HRESULT_ __stdcall AddRef();
        virtual HRESULT_ __stdcall Release();

        virtual HRESULT_ __stdcall CreateInstance(const IID_& iid, void** object);
        
        virtual HRESULT_ __stdcall CreateInstance(const IID_& iid, void** object, int license[]);

        ~ClassFactory();
};

BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);