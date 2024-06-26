#ifndef MICROGRAD_H
#define MICROGRAD_H


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
    set<Value*> prev ={};
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
        out.prev = {this, &other};
        out.backwardFunction = [this, &out, &other]() {
            this->grad += out.grad; ;
            other.grad += out.grad; ;
        };
        return out;
        }
    Value operator-( Value& other) {
        Value out;
        out.data = this->data - other.data;
        out.backwardFunction =[this,&out,&other](){
            this->grad += out.grad;
            other.grad -= out.grad;
        };
        return out;
    }
    
    Value operator*( Value& other) {
        Value out;
        out.data = this->data * other.data;
        out.backwardFunction =[this,&out,&other](){
            this->grad += other.data * out.grad;
            other.grad += this->data * out.grad;
        };
        return out;
    } 
    
    Value operator^(const Value& other) {
        Value out;
        out.data = pow(this->data, other.data);
        out.backwardFunction =[this,&out,&other](){
            this->grad += other.data * pow(this->data, other.data - 1) * out.grad;
        };
        return out;
    }
    Value relu(){
        Value out;
        data < 0 ?out.data = 0:out.data=data;
        out.backwardFunction =[this, &out]() {
            grad += (out.data > 0) ? out.grad : 0.0;
        };
        return out;

    }
    Value sigmoid() {
    Value out;
    out.data = 1.0 / (1.0 + exp(-data));
    out.backwardFunction = [this, &out]() {
        double temp = out.data * (1 - out.data);
        grad += temp * out.grad;
    };
    return out;
}

    void backward() {
        vector<Value*> topo;
        set<Value*> visited;
        const function<void(Value*)> buildTopo = [&](Value* v) {
            if (visited.count(v) == 0) {
                visited.insert(v);
                for (const auto child : v->prev) {
                    cout << "child: "<<*child << endl;
                    buildTopo(child);
                }
                topo.push_back(v);
            }
        };
        buildTopo(this);

        this->grad = 1;
            for (auto node : topo) {
            }
        for (auto it = topo.rbegin(); it != topo.rend(); ++it) {
            (*it)->backwardFunction();
        }
    }
};

#endif