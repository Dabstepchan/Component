#include "Components.h"

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

AdvEquationSolver::AdvEquationSolver()
{
    std::cout<<"AdvEquationSolver::AdvEquationSolver()"<<std::endl;
    refCount = 0;

    CoInitialize(NULL);

    IClassFactory* PCF = NULL;

    HRESULT resFactory = CoGetClassObject(Constants::CLSID_EquationSolver, CLSCTX_INPROC_SERVER, NULL, Constants::IID_IClassFactory, (void**) &PCF);

    if (!SUCCEEDED(resFactory))
    {
        std::cout<<"No factory"<<std::endl;
    }

    HRESULT resInstance = PCF->CreateInstance(NULL, Constants::IID_IEquationX, (void**) &iex);

    if (!SUCCEEDED(resInstance))
    {
        std::cout<<"No instance"<<std::endl;
    }

    HRESULT resQuery = iex->QueryInterface(Constants::IID_IEquationY, (void**) &iey);

    if (!SUCCEEDED(resQuery))
    {
        std::cout<<"No QueryInterface"<<std::endl;
    }

    PCF->Release();

    CoUninitialize();
}

HRESULT AdvEquationSolver::QueryInterface(const IID& iid, void** object)
{
    std::cout<<"AdvEquationSolver::QueryInterface"<<std::endl;

    if (iid == Constants::IID_IUnknown)
    {
        *object = (IUnknown*) (IEquationX*) this;
    }
    else if (iid == Constants::IID_IEquationX)
    {
        *object = static_cast<IEquationX*>(this);
    }
    else if (iid == Constants::IID_IEquationY)
    {
        *object = static_cast<IEquationY*>(this);
    }
    else if (iid == Constants2::IID_IEquationZ)
    {
        *object = static_cast<IEquationZ*>(this);
    }
    else
    {
        *object = NULL;
        return E_NOINTERFACE;
    }
    
    this->AddRef();
    return S_OK;
}

ULONG AdvEquationSolver::AddRef()
{
    refCount++;

    return refCount;
}

ULONG AdvEquationSolver::Release()
{
    refCount--;

    if (refCount == 0)
    {
        delete this;
    }
    
    return refCount;
}

HRESULT AdvEquationSolver::CreateSystem(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector, std::vector<std::vector<double>>& slauMatrix, std::vector<double>& slauVector)
{
    return iex->CreateSystem(matrix, vector, slauMatrix, slauVector);
}

HRESULT AdvEquationSolver::CalculateDeterminant(const std::vector<std::vector<double>>& matrix) 
{
    return iey->CalculateDeterminant(matrix);
}

HRESULT AdvEquationSolver::SolveSystemDecomposition(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector, std::vector<double>& solution)
{
    const int n = matrix.size();
    if (n == 0 || matrix[0].size() != n || vector.size() != n)
        return E_INVALIDARG;

    solution = vector;

    return S_OK;
}


AdvEquationSolver::~AdvEquationSolver()
{
    std::cout<<"AdvEquationSolver::~AdvEquationSolver()"<<std::endl;
    iex->Release();
    iey->Release();
}

// ---------------------------------------------------------------------------

AdvESolverClassFactory::AdvESolverClassFactory()
{
    std::cout<<"AdvESolverClassFactory::AdvESolverClassFactory()"<<std::endl;
    this->refCount = 0;
}

HRESULT AdvESolverClassFactory::QueryInterface(const IID& iid, void** object)
{
    std::cout<<"AdvESolverClassFactory::QueryInterface"<<std::endl;

    if (iid == Constants::IID_IClassFactory)
    {
        *object = (IUnknown*) (IClassFactory*) this;
    }
    else if (iid == Constants2::IID_IAdvESolverClassFactory)
    {
        *object = (IUnknown*) (IAdvESolverClassFactory*) this;
    }
    else
    {
        *object = NULL;
        return E_NOINTERFACE;
    }
    
    this->AddRef();
    return S_OK;
}

ULONG AdvESolverClassFactory::AddRef()
{
    refCount++;
    return refCount;
}

ULONG AdvESolverClassFactory::Release()
{
    refCount--;

    if (refCount == 0)
    {
        delete this;
    }
    
    return refCount;
}

HRESULT AdvESolverClassFactory::CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** object)
{
    std::cout<<"AdvESolverClassFactory::CreateInstance"<<std::endl;
    IUnknown* s = (IUnknown*) (IEquationX*) new AdvEquationSolver();

    HRESULT res = s->QueryInterface(iid, object);
    
    return res;
}

HRESULT AdvESolverClassFactory::CreateInstance(const IID& iid, void** object, int license[])
{
    std::cout<<"AdvESolverClassFactory::CreateInstance with license"<<std::endl;
    HRESULT res = E_NOTIMPL;

    if (license != NULL)
    {
        IUnknown* s = (IUnknown*) (IEquationX*) new AdvEquationSolver();

        res = s->QueryInterface(iid, object);
    }
    
    return res;
}

HRESULT AdvESolverClassFactory::LockServer(BOOL bLock)
{
    return S_OK;
}

AdvESolverClassFactory::~AdvESolverClassFactory()
{
    std::cout<<"AdvESolverClassFactory::~AdvESolverClassFactory()"<<std::endl;
}