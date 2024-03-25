#include <iostream>
#include <cmath>
#include <functional>
#include <set>
#include <vector>

using namespace std;

class Value {
public:
    double data;
    double grad;
    set<Value*> prev;
    function<void()> backwardFunction;

    // Constructors
    Value() : data(0), grad(0), prev(), backwardFunction([](){ /* do nothing */ }) {}
    Value(double data, const initializer_list<Value*>& children = {})
        : data(data), grad(0), prev(children), backwardFunction([](){ /* do nothing */ }) {}

    // Getters
    double getGrad() const { return grad; }
    double getValue() const { return data; }

    // Operator overloadings
    Value operator+(Value& other) {
        Value out;
        out.data = this->data + other.data;
        cout << "assigning backward for +" << endl;
        out.backwardFunction = bind(&Value::backwardAdd, this, ref(other), ref(out));
        return out;
    }

    void backwardAdd(Value& other, Value& out) {
        cout << "running backward for +" << endl;
        cout << "Incrementing gradient of this (a): " << this->grad << " by " << out.grad << endl;
        this->grad += out.grad;
        cout << "Resulting gradient of this (a): " << this->grad << endl;
        cout << "Incrementing gradient of other (b): " << other.grad << " by " << out.grad << endl;
        other.grad += out.grad;
        cout << "Resulting gradient of other (b): " << other.grad << endl;
        // No need to modify 'out.grad' here
    }

    void backward() {
        cout << "vos" << endl;
        vector<Value*> topo;
        set<Value*> visited;
        const function<void(Value*)> buildTopo = [&](Value* v) {
            if (visited.count(v) == 0) {
                visited.insert(v);
                for (const auto child : v->prev) {
                    buildTopo(child);
                }
                topo.push_back(v);
            }
        };

        buildTopo(this);

        grad = 1;
        for (auto it = topo.rbegin(); it != topo.rend(); ++it) {
            cout << (*it)->data << endl;
            (*it)->backwardFunction();

        }
    }
};

int main() {
    Value a(4);
    Value b(2);
    Value c;
    cout << "-----------------" << endl;
    c = a + b + a;
    cout << "-----------------" << endl;
    cout << "Value of c after calculation: " << c.getValue() << endl;
    cout << "Gradient of a: " << a.getGrad() << endl;
    c.backward();
    cout << "Gradient of a after backward propagation: " << a.getGrad() << endl;
    cout << "c data = " << c.getValue() << endl;
    cout << "c grad = " << c.getGrad() << endl;
    cout << "a grad = " << a.getGrad() << endl;
    cout << "b grad = " << b.getGrad() << endl;
    return 0;
}
