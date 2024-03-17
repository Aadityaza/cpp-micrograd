#include<iostream>
#include<cmath> // Include cmath header for pow function

using namespace std;

class Value {
public:
    double data;
    double prev;
    double grad=0;
    
    Value(){
        // Default constructor, no need for any action
    }

    Value(double data){
        this->data = data;
    }
    Value operator+(const Value& other) {
        Value result;
        result.data = this->data + other.data;
        return result;
    }
    Value operator-(const Value& other) {
        Value result;
        result.data = this->data - other.data;
        return result;
    }
    
    Value operator*(const Value& other) {
        Value result;
        result.data = this->data * other.data;
        return result;
    }
    Value operator^(const Value& other) {
        Value result;
        result.data = pow(this->data, other.data);
        return result;
    }
    Value relu(){
        if(data < 0){
            return Value(0);
        }
        else{
            return *this;
        }
    }
    void disp(){
        cout << data<<endl;
    }
};

int main(){
    Value* a = new Value(4);
    a->disp();
    Value* b = new Value(4);
    b->disp();
    Value* c = new Value();
*c = *a  - *b;  // Add the values pointed to by a and b
    c->disp();
    return 0;
}
