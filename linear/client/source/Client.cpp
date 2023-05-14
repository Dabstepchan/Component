#include "lib/EquationSolver.h"
#include "lib/IClassFactory.h"
#include "lib/ClassFactory.h"

#include <iostream>

using namespace std;

int main() {
    try
    {
    std::cout<<"My Class Factory"<<std::endl;
    int license[]{1, 2, 3};
    ClassFactory* ICL = NULL;
    HRESULT_ res = GetClassObject(CLSID_ClassFactory, IID_IClassFactory_, (void**) &ICL);
    if (res == E_NOCOMPONENT_)
    {
        cout << "Error: Unsupported component";
    }
    else if (res == E_NOINTERFACE_)
    {
        cout << "Error: Unsupported interface";
    }
    else if (res != S_OK_)
    {
        cout << "Error: Unknown error";
    }
    IEquationX* iex = NULL;
    res = ICL->CreateInstance(IID_IX, (void**) &iex, license);

    if (res != S_OK_)
    {
        cout << "Error: wrong license";
    }

    IEquationY* iey = NULL;
    res = iex->QueryInterface(IID_IY, (void**) &iey);
    if (res != S_OK_)
    {
        iex->Release();
        if (res == E_NOINTERFACE_)
        {
            cout << "Error: Unsupported interface";
        }
        else
        {
            cout << "Error: Unknown error";
        }
    }

    ICL->Release();
    }
    catch (...)
    {
        cout << "Client::Main::Unknown error while application running" << endl;
        return 0;
    }
}
