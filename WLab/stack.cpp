#include <stack.h>
#include <text.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <stdio.h>

using namespace std;

stack::stack(text &stack){ //constructor of initialization
    set_object(stack);
    set_previous(NULL);
};

stack::stack(stack &other){
    text *stack_text;
    stack_text = new text(other.get_object()) ;
    this->set_object(other.get_object());
    this->set_previous(other.get_previous());
};

void stack::set_previous(stack *stack){//setters for previous object
    this->previous = stack;
};

void stack::set_object(text &object){//setters for previous object
    this->object = object;
};

text &stack::get_object(){//getters for object
    return this->object;
};

stack *stack::get_previous() const{//getters for privious stack object
    return this->previous;
};





