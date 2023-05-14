#include "EquationSolver.h"
#include <iostream>

EquationSolver::EquationSolver() {
    //initialize variables
    a = 10;
    b = 20;
    c = 100;
    d = 200;
    e = 300;
    refCount = 0;
}

HRESULT_ __stdcall EquationSolver::QueryInterface(const IID_& iid, void** ppv) {
    if (iid == IID_IUnknown_ || iid == IID_IX || iid == IID_IY) {
        *ppv = static_cast<IEquationX*>(this);
        AddRef();
        return S_OK_;
    } else {
        *ppv = nullptr;
        return E_NOINTERFACE_;
    }
}

ULONG_ __stdcall EquationSolver::AddRef() {
    refCount++;
    return refCount;
}

ULONG_ __stdcall EquationSolver::Release() {
    refCount--;
    if (refCount == 0)
    {
        delete this;
    }
    
    return refCount;
}

HRESULT_ __stdcall EquationSolver::Fx1() {
    // First equation: a + b = c
    c = a + b;
    return S_OK_;
}

HRESULT_ __stdcall EquationSolver::Fy1() {
    // Third equation: b - a = e
    e = b - a;
    return S_OK_;
}

