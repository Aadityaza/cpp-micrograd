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
    // Overloaded << operator to print Value objects
    friend std::ostream& operator<<(std::ostream& os, const Value& v) {
        os << "Value(data=" << v.data << ", grad=" << v.grad << ")";
        return os;
    }
    // Getters
    double getGrad() const { return grad; }
    double getValue() const { return data; }

    // Operator overloadings
    Value operator+( Value& other) {
        Value out;
        out.data = this->data + other.data;
        out.backwardFunction = [this, &out, &other]() {
            // During backpropagation
            cout << "location of this inside operator+ : " << this << endl;
            cout << "location of out inside operator+ : " << &out << endl;
            cout << "location of other inside operator+ : " << &other << endl;
            cout << "running backward for +" << endl;
            // Calculate the contribution of this node (a) to the output gradient
            double this_grad_contribution = out.grad;  // out.grad holds the gradient from previous node
            cout << "Incrementing gradient of this (a): " << this->grad << " by " << this_grad_contribution << endl;
            this->grad += this_grad_contribution;
            cout << "Resulting gradient of this (a): " << this->grad << endl;

            // Calculate the contribution of other node (b) to the output gradient (usually same as this)
            double other_grad_contribution = this_grad_contribution;  // Assuming equal contribution from both operands
            cout << "Incrementing gradient of other (b): " << other.grad << " by " << other_grad_contribution << endl;
            other.grad += other_grad_contribution;
            cout << "Resulting gradient of other (b): " << other.grad << endl;
        };
        cout << "backward of +" << endl;
        return out;
        }

    void backward() {
        cout << "hello" << endl;
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

        // Set the gradient of the output node to 1
        this->grad = 1;

        cout << "address of this : " << this << endl;
        for (auto it = topo.rbegin(); it != topo.rend(); ++it) {
            cout << "yeta hera ta " << (*it)->grad << endl;
            cout << "address of it : " << *it << endl;
            (*it)->backwardFunction();
        }
    }
};

int main() {
    Value a= Value(4);
    Value b= Value(2);
    cout << "-----------------" << endl;
    Value c = a + b +a;
    cout << "address of c : "<<&c  << endl;
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
