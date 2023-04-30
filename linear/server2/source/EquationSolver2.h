#ifndef EQUATIONSOLVER_H_INCLUDED
#define EQUATIONSOLVER_H_INCLUDED
#include <Windows.h>

using IID_ = int;
using CLSID_ = int;
using HRESULT_ = int;
using ULONG_ = int;


const int IID_IUnknown_ = 0;
const int IID_IX = 1;
const int IID_IY = 2;

const int CLSID_CServer = 1;
const int IID_IClassFactory_ = 100;
const int IID_ClassFactory = 101;
const int CLSID_ClassFactory = 1;

const int S_OK_ = 0;
const int E_NOINTERFACE_ = 1;
const int E_NOCOMPONENT_ = 2;

class IUnknown_ {
public:
    virtual HRESULT_ __stdcall QueryInterface(const IID_& iid, void** ppv) = 0;
    virtual ULONG_ __stdcall AddRef() = 0;
    virtual ULONG_ __stdcall Release() = 0;
};

HRESULT_ __stdcall CreateInstance(const CLSID_& clsid, const IID_& iid, void** object);
HRESULT_ __stdcall GetClassObject(const CLSID_& clsid, const IID_& iid, void** object);

class IEquationX : public IUnknown_ {
public:
    virtual HRESULT_ __stdcall Fx2() = 0;
};

class IEquationY : public IUnknown_ {
public:
    virtual HRESULT_ __stdcall Fy2() = 0;
};

class EquationSolver : public IEquationX, public IEquationY {
private:
    int a, b, c, d, e, refCount;
public:
    EquationSolver();
    virtual HRESULT_ __stdcall QueryInterface(const IID_& iid, void** ppv);
    virtual ULONG_ __stdcall AddRef();
    virtual ULONG_ __stdcall Release();
    virtual HRESULT_ __stdcall Fx2();
    virtual HRESULT_ __stdcall Fy2();
};

#endif // EQUATIONSOLVER_H_INCLUDED
