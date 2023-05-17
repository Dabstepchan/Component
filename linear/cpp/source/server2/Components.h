#pragma once

#include "Interfaces2.h"
#include "lib/interfaces.h"

class AdvEquationSolver: public IEquationX, public IEquationY, public IEquationZ
{
    private:
        int refCount;
        IEquationX* iex;
        IEquationY* iey;
    public:
        AdvEquationSolver();
        
        virtual HRESULT __stdcall QueryInterface(const IID& iid, void** object);
        virtual ULONG __stdcall AddRef();
        virtual ULONG __stdcall Release();

        virtual HRESULT __stdcall CreateSystem(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector, std::vector<std::vector<double>>& slauMatrix, std::vector<double>& slauVector);
        virtual HRESULT __stdcall CalculateDeterminant(const std::vector<std::vector<double>>& matrix);
        virtual HRESULT __stdcall SolveSystemDecomposition(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector, std::vector<double>& solution);

        ~AdvEquationSolver();
};

class AdvESolverClassFactory : public IClassFactory, public IAdvESolverClassFactory
{
    private:
        int refCount;
    public:
        AdvESolverClassFactory();

        virtual HRESULT __stdcall QueryInterface(const IID& iid, void** object);
        virtual ULONG __stdcall AddRef();
        virtual ULONG __stdcall Release();

        virtual HRESULT __stdcall CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** object);
        virtual HRESULT __stdcall CreateInstance(const IID& iid, void** object, int license[]);

        virtual HRESULT __stdcall LockServer(BOOL bLock);

        ~AdvESolverClassFactory();
};