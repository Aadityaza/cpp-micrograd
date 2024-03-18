#include<iostream>
#include<cmath> 
#include <functional>
#include<set>

using namespace std;

class Value {
public:
    double data;
    double grad;
    set<Value*> prev;
    function<void()> backward;
    
    
    Value(){
        // Default constructor, no need for any action
    }
    double getGrad() {
        return grad;
    }
    double getValue() {
        return data;
    }

    Value(double data, initializer_list<Value*> children = {}) 
    : data(data), grad(0), prev(children) {}

    Value operator+( Value& other) {
        Value out;
        out.data = this->data + other.data;
        out.backward =[this,&out,&other](){
            this->grad += out.grad;
            other.grad += out.grad;
        };
        return out;
    }
    
    Value operator-( Value& other) {
        Value out;
        out.data = this->data - other.data;
        out.backward =[this,&out,&other](){
            this->grad += out.grad;
            other.grad -= out.grad;
        };
        return out;
    }
    
    Value operator*( Value& other) {
        Value out;
        out.data = this->data * other.data;
        out.backward =[this,&out,&other](){
            this->grad += other.data * out.grad;
            other.grad += this->data * out.grad;
        };
        return out;
    }
    
    Value operator^(const Value& other) {
        Value out;
        out.data = pow(this->data, other.data);
        out.backward =[this,&out,&other](){
            this->grad += other.data * pow(this->data, other.data - 1) * out.grad;
        };
        return out;
    }
    
    Value relu(){
        if(data < 0){
            return Value(0);
        }
        else{
            return *this;
        }
    }
    
};

int main(){
    Value* a = new Value(4);
    cout<<"Grag"<<a->getGrad()<<endl;
    Value* b = new Value(4);
    cout<<b->getValue()<<endl;
    Value* c = new Value();
    cout<<b->getValue()<<endl;
    *c = *a + *b;  
    cout<<c->getGrad();           
    return 0;
}
