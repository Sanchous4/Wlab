#ifndef TEXT_COLLECTION_H
#define TEXT_COLLECTION_H

#include <stack.h>
#include <text.h>
#include <fstream>
#include <stdio.h>
#include <iostream>

using namespace std;

class text_collection {
private:
    stack *last, *first;
    unsigned int size;
    stack *pop();
public:
    text_collection();
    text_collection(text_collection& stack);//Copy constructor
//Setters
    void set_size(const size_t size);
    void set_last(stack& object);
    void set_first(stack& object);
//Getters
    int get_size();
    stack *get_last() const;
    stack *get_first() const;
    stack *get_by_index(int iterator);//Доступ по иттератору
//Add or remove
    void push(text_collection& push_stack);//Добавить существующий text_collection обьект в стек
    void push_operation(stack& object, text_collection& change);//Создать новый обьект и добавить его в стек, очистить стек Redo
    void push_object(stack& object){//Push obj
        stack *new_object;
        new_object= new stack(object);
        new_object->set_object(object.get_object());
        //If stack is empty, first is new object
        if (this->size == 0){
            this->first = new_object;
        }
        //Previous value is last, last is new object
        new_object->set_previous(this->last);
        this->last = new_object;
        this->size++;
        cout << "Object with text: '" << this->last->get_object().get_text() << "' - added to the stack. Now it's length is: " << this->get_size() << endl;
    }//Создать новый обьект и добавить его в стек
    void undo(text_collection& change_stack);
    void remove();
    void remove_all();

//Create file and its ouput
    int record_file(const string &name);
    int output_file(const string &name);

//Checker of recorded file
    bool operator == (const text_collection&);
};

int show_stack(text_collection& stack);

#endif
