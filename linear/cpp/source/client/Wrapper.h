#pragma once

#include "lib/Interfaces.h"
#include "lib/Interfaces2.h"

#include <windows.h>
#include <iostream>

class EEquationSolver
{
    private:
        const char* msg;
    public:
        EEquationSolver(const char* msg);
        const char* GetMessage();
};

class CEquationSolver
{
    private:
        IEquationX* iex;
        IEquationY* iey;
        IEquationZ* iez;
        CEquationSolver(const CEquationSolver&) {};
        CEquationSolver& operator=(const CEquationSolver&) {return *this;};
    public:
        CEquationSolver();
        CEquationSolver(int license[]);

        virtual HRESULT __stdcall CreateSystem(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector, std::vector<std::vector<double>>& slauMatrix, std::vector<double>& slauVector);

        virtual HRESULT __stdcall CalculateDeterminant(const std::vector<std::vector<double>>& matrix);

        virtual HRESULT __stdcall SolveSystemDecomposition(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector, std::vector<double>& solution);

        ~CEquationSolver();
};