#include "regularExpression.hpp"

RegularExpression::RegularExpression(){
    this->binaryOperators.insert('*');
    this->binaryOperators.insert('.');
    this->binaryOperators.insert('+');
    this->binaryOperators.insert('(');
    this->binaryOperators.insert(')');
}

bool RegularExpression::setInput(string input){
    this->infixInput = input;
    this->infixInput.erase(remove(this->infixInput.begin(), this->infixInput.end(), ' '), this->infixInput.end());
    if(this->convertPosfix())
        return this->check();
    else
        return false;
}
string RegularExpression::getInfixInput(){
    return this->infixInput;
}

string RegularExpression::getPostfixt(){
    return this->postfixt;
}

bool RegularExpression::convertPosfix(){
    stack<char> s;
    string aux;
    for(string::iterator it = this->infixInput.begin();it!=this->infixInput.end();++it){
        aux.push_back(*it);
        if(!(aux.back()=='\\' && this->binaryOperators.find(*(it+1))!=this->binaryOperators.end())){
            if((it+1) != this->infixInput.end()){
                    if(*it != '.' &&    *it!='+' && *it!='(' && *(it+1)!='+' && *(it+1)!='*' && *(it+1)!=')' && *(it+1)!='.'){
                    aux.push_back('.');
                }
            }
        }
    }
    this->infixInput.assign(aux);
    //cout<<this->infixInput<<endl;
    aux.clear();
    for(char op: this->infixInput){
        if(this->postfixt.back()=='\\' && this->binaryOperators.find(op)!=this->binaryOperators.end()){
            this->postfixt.push_back(op);
        }
        else{
            if(this->binaryOperators.find(op)==this->binaryOperators.end()){
                this->postfixt.push_back(op);
            }
            else{
                if(op=='('){
                    s.push(op);
                }
                else if(op==')'){
                    while(!s.empty() && s.top()!='('){
                        this->postfixt.push_back(s.top());
                        s.pop();
                    }
                    if(s.empty()) return false;
                    if(!s.empty() && s.top()=='(') s.pop();
                }
                else if(this->binaryOperators.find(op)!=this->binaryOperators.end()){
                    if(op=='.'){
                        while(!s.empty() && (s.top()=='*' || s.top()=='.')){
                            this->postfixt.push_back(s.top());
                            s.pop();
                        }
                    }
                    else if(op=='+'){
                        while(!s.empty() && (s.top()=='+' || s.top()=='.' || s.top()=='*')){
                            this->postfixt.push_back(s.top());
                            s.pop();
                        }
                    }
                    else if(op=='*'){
                        while(!s.empty() && s.top()=='*'){
                            this->postfixt.push_back(s.top());
                            s.pop();
                        }
                    }
                    s.push(op);
                }
            }
        }
    }
    while(!s.empty()){
        if(s.top()=='(') return false;
        this->postfixt.push_back(s.top());
        s.pop();
    }
    if(this->postfixt.empty()) this->postfixt.append("&");
    return true;
}

bool RegularExpression::check(){
    stack<string> stk;
    string op, op1, op2;    
    for(string::iterator it = this->postfixt.begin(); it!=this->postfixt.end(); ++it){
        op.assign(1,*it);
        if(*it=='\\' && this->binaryOperators.find(*(it+1))!=this->binaryOperators.end()){
            op.push_back(*(++it));
        }
        if(this->binaryOperators.find(op.front())==this->binaryOperators.end()){
            stk.push(op);
        }
        else{
            if(!stk.empty()){
                op2 = stk.top();
                stk.pop();
                if(op.front() == '*'){
                    stk.push(op2);
                }
                else{
                    if(!stk.empty()){
                        op1=stk.top();
                    }
                    else{
                        return false;
                    }
                }
            }
            else{
                return false;
            }
        }
    }
    stk.pop();
    if(stk.empty())
        return true;
    else
        return false;
}