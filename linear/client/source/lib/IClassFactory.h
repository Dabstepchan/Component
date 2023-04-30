#pragma once

#include "EquationSolver.h"

class IClassFactory_ : public IUnknown_
{
    public:
        virtual HRESULT_ __stdcall CreateInstance(const IID_& iid, void** object) = 0;
};