#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <windows.h>
#include <string>
#include <cmath>

class Constants
{
    public:
     static IID IID_IUnknown;
     static IID IID_IClassFactory;

     static IID IID_IEquationX;
     static IID IID_IEquationY;
     static IID IID_ClassFactory;

     static CLSID CLSID_EquationSolver;
     static CLSID CLSID_ESolverClassFactory;
     static IID IID_IDispatch;
};

class IEquationX : public IUnknown
{
    public:
        virtual HRESULT __stdcall CreateSystem(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector, std::vector<std::vector<double>>& slauMatrix, std::vector<double>& slauVector) = 0;
};

class IEquationY : public IUnknown
{
    public:
        virtual HRESULT __stdcall CalculateDeterminant(const std::vector<std::vector<double>>& matrix) = 0;
};

class IEQClassFactory : public IUnknown
{
    public:
        virtual HRESULT __stdcall CreateInstance(const IID& iid, void** object, int license[]) = 0;
};

extern "C" HRESULT __stdcall __declspec(dllexport) DllGetClassObject(const CLSID& clsid, const IID& iid, void** object);