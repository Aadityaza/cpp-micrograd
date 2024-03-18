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
    
    
    Value(): grad(0), prev() {}
    
    Value(double data, initializer_list<Value*> children = {}) 
    : data(data), grad(0), prev(children) {}

    
    double getGrad() {
        return grad;
    }
    double getValue() {
        return data;
    }

    

    Value operator+( Value& other) {
        Value out;
        out.data = this->data + other.data;
        out.backward =[this,&out,&other](){
            this->grad += out.grad;
            other.grad += out.grad;
        };
        cout<<"backward of +"<<endl;
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

int main() {
    // Creating object 'a' with value 4
    Value a(4);
    Value b(9);
    Value c; 

    c = (a + b) *a;  
    cout << "Value of c after calculation: " << c.getValue() << endl;

    // Printing gradient of 'a'
    cout << "Gradient of a: " << a.getGrad() << endl;

    // Performing backward propagation
    c.backward();     
    cout << "Gradient of a after backward propagation: " << a.getGrad() << endl;    

    return 0;
}

