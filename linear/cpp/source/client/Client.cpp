#include "lib/interfaces.h"
#include "lib/interfaces2.h"
#include "wrapper.h"
#include <objbase.h>

#include <vector>
#include <iostream>

IID Constants::IID_IUnknown = {0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
IID Constants::IID_IClassFactory = {0x00000100,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

IID Constants::IID_IEquationX = {0x00000001,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
IID Constants::IID_IEquationY = {0x00000002,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
IID Constants::IID_ClassFactory = {0x00000101,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};

//{4399E097-D19C-480D-90EE-1AA25B858D31}
CLSID Constants::CLSID_EquationSolver = {0x4399E097,0xD19C,0x480D,{0x90,0xEE,0x1A,0xA2,0x5B,0x85,0x8D,0x31}};

IID Constants2::IID_IAdvESolverClassFactory = {0x00000012,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
IID Constants2::IID_IEquationZ = {0x00000003,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};

//{4BFDC92A-A7F7-4491-AFC7-569C9555EF45}
CLSID Constants2::CLSID_AdvEquationSolver = {0x4BFDC92A,0xA7F7,0x4491,{0xAF,0xC7,0x56,0x9C,0x95,0x55,0xEF,0x45}};

int main()
{
    std::cout << "Client main start" << std::endl;

    try
    {
        std::cout << "Standard class factory" << std::endl;
        CEquationSolver solver;

        std::vector<std::vector<double>> matrix = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
        std::vector<double> vector = {1.0, 2.0, 3.0};
        std::vector<std::vector<double>> slauMatrix;
        std::vector<double> slauVector;

        HRESULT hr = solver.CreateSystem(matrix, vector, slauMatrix, slauVector);
        if (SUCCEEDED(hr))
        {
            std::cout << "SLAU Matrix:" << std::endl;
            for (const auto& row : slauMatrix)
            {
                for (const auto& element : row)
                {
                    std::cout << element << " ";
                }
                std::cout << std::endl;
            }

            std::cout << "SLAU Vector:" << std::endl;
            for (const auto& element : slauVector)
            {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
        else
        {
            std::cout << "Failed to create SLAU system" << std::endl;
        }

        hr = solver.CalculateDeterminant(matrix);
        if (SUCCEEDED(hr))
        {
            std::cout << "Determinant calculated successfully" << std::endl;
        }
        else
        {
            std::cout << "Failed to calculate determinant" << std::endl;
        }

        std::vector<double> solution;
        hr = solver.SolveSystemDecomposition(matrix, vector, solution);
        if (SUCCEEDED(hr))
        {
            std::cout << "Solution to the system:" << std::endl;
            for (const auto& element : solution)
            {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
        else
        {
            std::cout << "Failed to solve the system" << std::endl;
        }
    }
    catch (EEquationSolver& e)
    {
        std::cout << e.GetMessage() << std::endl;
    }

    return 0;
}