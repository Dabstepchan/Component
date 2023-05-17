#pragma once

#include "Interfaces.h"

class EquationSolver : public IEquationX, public IEquationY
{
    private:
        int refCount;
    public:
        EquationSolver();
        
        virtual HRESULT __stdcall QueryInterface(const IID& iid, void** object);
        virtual ULONG __stdcall AddRef();
        virtual ULONG __stdcall Release();

        virtual HRESULT __stdcall CreateSystem(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector, std::vector<std::vector<double>>& slauMatrix, std::vector<double>& slauVector);
        virtual HRESULT __stdcall CalculateDeterminant(const std::vector<std::vector<double>>& matrix);
        ~EquationSolver();
};

class ClassFactory : public IClassFactory, public IEQClassFactory
{
    private:
        int refCount;
    public:
        ClassFactory();

        virtual HRESULT __stdcall QueryInterface(const IID& iid, void** object);
        virtual ULONG __stdcall AddRef();
        virtual ULONG __stdcall Release();

        virtual HRESULT __stdcall CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** object);
        virtual HRESULT __stdcall CreateInstance(const IID& iid, void** object, int license[]);

        virtual HRESULT __stdcall LockServer(BOOL bLock);

        ~ClassFactory();
};