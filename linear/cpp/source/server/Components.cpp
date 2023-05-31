#include "Components.h"

IID Constants::IID_IUnknown = {0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};
IID Constants::IID_IClassFactory = {0x00000100,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

IID Constants::IID_IEquationX = {0x00000001,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
IID Constants::IID_IEquationY = {0x00000002,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
IID Constants::IID_ClassFactory = {0x00000101,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}};
IID Constants::IID_IDispatch = {0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};

//{4399E097-D19C-480D-90EE-1AA25B858D31}
CLSID Constants::CLSID_EquationSolver = {0x4399E097,0xD19C,0x480D,{0x90,0xEE,0x1A,0xA2,0x5B,0x85,0x8D,0x31}};

EquationSolver::EquationSolver()
{
    std::cout<<"EquationSolver::EquationSolver()"<<std::endl;
    refCount = 0;
    equationCount = 10;
}

HRESULT EquationSolver::QueryInterface(const IID& iid, void** object)
{
    std::cout<<"EquationSolver::QueryInterface"<<std::endl;
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
    else if (iid == Constants::IID_IDispatch)
    {
        *object = static_cast<IDispatch*>(this);
    }
    else
    {
        *object = NULL;
        return E_NOINTERFACE;
    }
    
    this->AddRef();
    return S_OK;
}

ULONG EquationSolver::AddRef()
{
    refCount++;

    return refCount;
}

ULONG EquationSolver::Release()
{
    refCount--;

    if (refCount == 0)
    {
        delete this;
    }
    
    return refCount;
}

HRESULT EquationSolver::CreateSystem(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector, std::vector<std::vector<double>>& slauMatrix, std::vector<double>& slauVector)
{
    const int n = matrix.size();
    if (n == 0 || matrix[0].size() != n || vector.size() != n)
        return E_INVALIDARG;

    slauMatrix = matrix;
    slauVector = vector;

    return S_OK;
}

HRESULT EquationSolver::CalculateDeterminant(const std::vector<std::vector<double>>& matrix) {
    const int n = matrix.size();
    if (n == 0 || matrix[0].size() != n)
        return E_INVALIDARG;

    return S_OK;
}

HRESULT EquationSolver::GetIDsOfNames(REFIID riid, LPOLESTR* rgszNames, UINT cNames, LCID lcid, DISPID* rgDispId)
{
    std::cout<<"EquationSolver::GetIDsOfNames"<<std::endl;

    if (cNames != 1) {return E_NOTIMPL;}

    if (wcscmp(rgszNames[0], L"CreateSystem") == 0)
    {
        rgDispId[0] = 1;
    }

    else if (wcscmp(rgszNames[0], L"CalculateDeterminant") == 0)
    {
        rgDispId[0] = 2;
    }

    else if (wcscmp(rgszNames[0], L"equationCount") == 0)
    {
        rgDispId[0] = 3;
    }

    else
    {
        return E_NOTIMPL;
    }

    return S_OK;
}

HRESULT EquationSolver::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pDispParams,VARIANT* pVarResult,
                                    EXCEPINFO* pExcepInfo, UINT* puArgErr)
{
    std::cout<<"EquationSolver:Invoke"<<std::endl;
    if (dispIdMember == 1)
    {
        if (pDispParams->cArgs != 4)
            return DISP_E_BADPARAMCOUNT;

        VARIANTARG* args = pDispParams->rgvarg;

        if (args[0].vt != (VT_ARRAY | VT_VARIANT) || args[1].vt != (VT_ARRAY | VT_VARIANT) ||
            args[2].vt != (VT_ARRAY | VT_VARIANT) || args[3].vt != (VT_ARRAY | VT_VARIANT))
            return DISP_E_TYPEMISMATCH;

        SAFEARRAY* matrixArray = args[0].parray;
        SAFEARRAY* vectorArray = args[1].parray;
        SAFEARRAY* slauMatrixArray = args[2].parray;
        SAFEARRAY* slauVectorArray = args[3].parray;

        return S_OK;
    }
    else if (dispIdMember == 2)
    {
        if (pDispParams->cArgs != 1)
            return DISP_E_BADPARAMCOUNT;

        VARIANTARG* args = pDispParams->rgvarg;

        if (args[0].vt != (VT_ARRAY | VT_VARIANT))
            return DISP_E_TYPEMISMATCH;

        SAFEARRAY* matrixArray = args[0].parray;

        if (wFlags == DISPATCH_PROPERTYGET)
        {
            if (pVarResult != NULL)
            {
                pVarResult->vt = VT_BOOL;
            }
        }

        return S_OK;
    }
    else if (dispIdMember == 3)
    {
        if ( (wFlags==DISPATCH_PROPERTYGET) || (wFlags==1) || (wFlags==3) )
       {
          if (pVarResult!=NULL)
          {
            pVarResult->vt = VT_INT;
            pVarResult->intVal = equationCount; 
          }
       }
       else if (wFlags==DISPATCH_PROPERTYPUT)
       {
          DISPPARAMS param = *pDispParams;
          VARIANT arg = (param.rgvarg)[0];
          VariantChangeType(&arg,&arg,0,VT_INT);
          equationCount = arg.intVal;
       }
       else
       {
         return E_NOTIMPL;
       }
    }
    else
    {
        return E_NOTIMPL;
    }

    return S_OK;
}

HRESULT EquationSolver::GetTypeInfoCount(UINT* pctinfo)
{
    return S_OK;
}

HRESULT EquationSolver::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo** ppTInfo)
{
    return S_OK;
}

EquationSolver::~EquationSolver()
{
    std::cout<<"EquationSolver::~EquationSolver()"<<std::endl;
}

// -----------------------------------------------------------------------------------------

ClassFactory::ClassFactory()
{
    std::cout<<"ClassFactory::ClassFactory()"<<std::endl;
    this->refCount = 0;
}

HRESULT ClassFactory::QueryInterface(const IID& iid, void** object)
{
    std::cout<<"ClassFactory::QueryInterface"<<std::endl;

    if (iid == Constants::IID_IClassFactory)
    {
        *object = (IUnknown*) (IClassFactory*) this;
    }
    else if (iid == Constants::IID_IClassFactory)
    {
        *object = (IUnknown*) (IClassFactory*) this;
    }
    else
    {
        *object = NULL;
        return E_NOINTERFACE;
    }
    
    this->AddRef();
    return S_OK;
}

ULONG ClassFactory::AddRef()
{
    refCount++;

    return refCount;
}

ULONG ClassFactory::Release()
{
    refCount--;

    if (refCount == 0)
    {
        delete this;
    }
    
    return refCount;
}

HRESULT ClassFactory::CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** object)
{
    std::cout<<"ClassFactory::CreateInstance"<<std::endl;

    if (pUnknownOuter != NULL)
    {
        return E_NOTIMPL;
    }

    IUnknown* s = (IUnknown*) (IEquationX*) new EquationSolver();

    HRESULT res = s->QueryInterface(iid, object);
    
    return res;
}

HRESULT ClassFactory::CreateInstance(const IID& iid, void** object, int license[])
{
    std::cout<<"ClassFactory::CreateInstance with license"<<std::endl;

    HRESULT res = E_NOTIMPL;

    if (license != NULL)
    {
        IUnknown* s = (IUnknown*) (IEquationX*) new EquationSolver();

        res = s->QueryInterface(iid, object);
    }
    
    return res;
}

HRESULT ClassFactory::LockServer(BOOL bLock)
{
    return S_OK;
}

ClassFactory::~ClassFactory()
{
    std::cout<<"ClassFactory::~ClassFactory()"<<std::endl;
}
