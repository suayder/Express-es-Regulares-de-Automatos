#include "regularExpression.hpp"

int main(){

    RegularExpression rge = RegularExpression();
    string inputdata;
    getline(cin,inputdata);
    if(!rge.setInput(inputdata)){
        cout<<"Invalid Expression"<<endl;
    }
    else{
        cout<<"Valid Expression"<<endl;
        cout<<"Infixa: "<<rge.getInfixInput()<<endl;
        cout <<"Posfixa: " <<rge.getPostfixt()<<endl;
    }
    return 0;
}