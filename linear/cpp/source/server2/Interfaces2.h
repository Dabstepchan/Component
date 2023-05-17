#pragma once

#include <string>
#include <vector>
#include "windows.h"
#include <iostream>
#include <objbase.h>

class Constants2
{
    public:
     static IID IID_IAdvESolverClassFactory;
     static IID IID_IEquationZ;

     static CLSID CLSID_AdvEquationSolver;
};

class IEquationZ : public IUnknown
{
    public:
        virtual HRESULT __stdcall SolveSystemDecomposition(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector, std::vector<double>& solution) = 0;
};

class IAdvESolverClassFactory : public IUnknown
{
    public:
        virtual HRESULT __stdcall CreateInstance(const IID& iid, void** object, int license[]) = 0;
};

extern "C" HRESULT __stdcall __declspec(dllexport) DllGetClassObject(const CLSID& clsid, const IID& iid, void** object);
