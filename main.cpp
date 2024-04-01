#include <iostream>
#include <cmath>
#include <functional>
#include <set>
#include <vector>
#include<micrograd.h>

using namespace std;



int main() {
    Value a= Value(4);
    Value b= Value(2);
    Value c = a * b ;
    cout << "a 4 loc = " << &a << endl;
    cout << "b 2 loc = " << &b << endl;
    cout << "c loc = " << &c << endl;
            cout << "-----------------" << endl;
    c.backward();
    cout << "Gradient of a after backward propagation: " << a.getGrad() << endl;
    cout << "c data = " << c.getValue() << endl;
    cout << "a grad = " << a.getGrad() << endl;
    cout << "b grad = " << b.getGrad() << endl;
    cout << "c grad = " << c.getGrad() << endl;
    cout<<1+3+4;
    return 0;
}
