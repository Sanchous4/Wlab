#ifndef STACK_H
#define STACK_H

#include <text.h>
#include <fstream>
#include <stdio.h>

class stack {
private:
    stack *previous;
    text object;

public:
    stack(text& object);
    stack(stack &object);
//Setters
    void set_previous(stack *stack);
    void set_object(text& object);
//Getters
    text& get_object();
    stack *get_previous() const;
};

#endif
