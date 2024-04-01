#include <iostream>
#include <cmath>
#include <functional>
#include <set>
#include <vector>
#include "micrograd.h"

using namespace std;


int main() {
    Value a= Value(-4);
    Value b= Value(2);
    Value c = a.relu();

    c.backward();
    cout << "c data = " << c.getValue() << endl;
    cout << "a grad = " << a.getGrad() << endl;
    // cout << "b grad = " << b.getGrad() << endl;
    cout << "c grad = " << c.getGrad() << endl;

    return 0;
}
