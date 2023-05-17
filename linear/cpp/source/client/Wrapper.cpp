#include "Wrapper.h"

EEquationSolver::EEquationSolver(const char* msg)
{
    this->msg = msg;
}

const char* EEquationSolver::GetMessage()
{
    return msg;
}

CEquationSolver::CEquationSolver()
{
    CoInitialize(NULL);

    IClassFactory* ICF = NULL;

    HRESULT resFactory = CoGetClassObject(Constants2::CLSID_AdvEquationSolver, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IClassFactory, (void**) &ICF);

    if (!SUCCEEDED(resFactory))
    {
        throw EEquationSolver("No factory");
    }

    HRESULT resInstance = ICF->CreateInstance(NULL, Constants::IID_IEquationX, (void**) &iex);

    if (!SUCCEEDED(resInstance))
    {
        throw EEquationSolver("No instance");
    }

    HRESULT resQuery = iex->QueryInterface(Constants::IID_IEquationY, (void**) &iey);

    if (!SUCCEEDED(resQuery))
    {
        throw EEquationSolver("No QueryInterface");
    }

    HRESULT resQuery2 = iey->QueryInterface(Constants2::IID_IEquationZ, (void**) &iez);

    if (!SUCCEEDED(resQuery2))
    {
        throw EEquationSolver("No QueryInterface 2");
    }

    ICF->Release();
}

CEquationSolver::CEquationSolver(int license[])
{
    CoInitialize(NULL);

    IClassFactory* ICF = NULL;

    HRESULT resFactory = CoGetClassObject(Constants2::CLSID_AdvEquationSolver, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IClassFactory, (void**) &ICF);

    if (!SUCCEEDED(resFactory))
    {
        throw EEquationSolver("No factory");
    }

    HRESULT resInstance = ICF->CreateInstance(NULL, Constants::IID_IEquationX, (void**) &iex);

    if (!SUCCEEDED(resInstance))
    {
        throw EEquationSolver("Wrong license");
    }

    HRESULT resQuery = iex->QueryInterface(Constants::IID_IEquationY, (void**) &iey);

    if (!SUCCEEDED(resQuery))
    {
        throw EEquationSolver("No QueryInterface");
    }

    HRESULT resQuery2 = iey->QueryInterface(Constants2::IID_IEquationZ, (void**) &iez);

    if (!SUCCEEDED(resQuery2))
    {
        throw EEquationSolver("No QueryInterface 2");
    }

    ICF->Release();
}

HRESULT __stdcall CEquationSolver::CreateSystem(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector, std::vector<std::vector<double>>& slauMatrix, std::vector<double>& slauVector)
{
    return iex->CreateSystem(matrix, vector, slauMatrix, slauVector);
}

HRESULT __stdcall CEquationSolver::CalculateDeterminant(const std::vector<std::vector<double>>& matrix)
{
    return iey->CalculateDeterminant(matrix);
}

HRESULT __stdcall CEquationSolver::SolveSystemDecomposition(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector, std::vector<double>& solution)
{
    return iez->SolveSystemDecomposition(matrix, vector, solution);
}

CEquationSolver::~CEquationSolver()
{
    iex->Release();
    iey->Release();
    iez->Release();
    
    CoUninitialize();
}
