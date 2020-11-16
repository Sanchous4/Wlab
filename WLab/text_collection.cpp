#include <stack.h>
#include <text.h>
#include <fstream>
#include <stdio.h>
#include <text_collection.h>
#include <iostream>

using namespace std;

//Default constractor
text_collection::text_collection(){
    last = NULL;
    first = NULL;
    size = 0;
};

//Copy constractor
text_collection::text_collection(text_collection &stack){
    this->last=NULL;
    this->first=NULL;
    this->set_size(0);
    if(stack.get_last()){
        stack *object = stack.get_last();
        while(object.get_previous() != NULL){
            this->push_object(object);
            &object = object.get_previous();
        }
        this->push_object(object);
    }
};

//Setters
void text_collection::set_size(const size_t size){
    this->size = size;
};

void text_collection::set_last(stack& object){
    this->last = &object;
};

void text_collection::set_first(stack& object){
    this->first = &object;
};


//Getters
int text_collection::get_size(){
    return this->size;
};

stack *text_collection::get_last() const{
    if(this->last==NULL){
        cout << "Stack is empty" << endl;
        return NULL;
    }
    else
        return this->last;
};

stack *text_collection::get_first() const{
    if(this->first==NULL){
        cout << "Stack is empty" << endl;
        return NULL;
    }
    else
        return this->first;
};


//Доступ по итератору
stack *text_collection::get_by_index(int iterator){
    if(this->get_size()<=iterator){
        cout << "Iterartor out of stack size" << endl;
        exit(1);
    }
    else{
        stack *object = this->get_last();
        int len = this->get_size()-iterator-1;
        for(int i=0;i<len;i++){
            object=object->get_previous();
        }
        return object;
    }
};

;


//Add object to end of the stack and clear another stack
void text_collection::push_operation(stack &object, text_collection &change){
    if(this==&change)
    {
        cout << "Please use different undo and change stacks." << endl;
        exit(1);
    }
    stack *new_object;
    new_object= new stack(object);
    new_object->set_object(object.get_object());
    //If stack is empty, first is new object
    if (this->size == 0)
        this->first = new_object;
    //Previous value is last, last is new object
    new_object->set_previous(this->last);
    this->last = new_object;
    this->size++;
    cout << "Object with text: '" << this->last->get_object().get_text() << "' - added to the undo stack. Now it's length is: " << this->get_size() << endl;
    change.remove_all();
};


//Add text_collection object to stack
void text_collection::push(text_collection& push_stack){
       stack *last_object = push_stack.last;
       while(last_object->get_previous() != NULL){
           this->push_object(*last_object);
           last_object = last_object->get_previous();
       };
       this->push_object(*last_object);
};


//Remove stack object from the stack
stack *text_collection::pop()
{
    if(this->get_size()==0){
        cout << "No more operations to undo" << endl;
        return NULL;
    }
    else{
        if(this->get_size()>1)
        {
            stack *newLast = this->last->get_previous();
            stack *del=this->get_last();
            this->last = newLast;
            this->size = this->size - 1;
            return del;
        }
        else//It is required to make first NULL
        {
            stack *del=this->get_last();
            this->last = NULL;
            this->first = NULL;
            this->size = this->size - 1;
            return del;
        }
    }
}


//Remove the last object
void text_collection::remove(){
    stack *delet = pop();
    delete delet;
}


//Cancel operation
void text_collection::undo(text_collection& change_stack)
{
    stack *object = this->pop();
    if(object==NULL)
        cout << "Operation failed" << endl;
    else
    {
        cout << "Last object from stack with text: '" << object->get_object().get_text() << "' - deleted. Now it's length is: " << this->get_size() << " ." << endl;
        change_stack.push_object(*object);
    }
}



void text_collection::remove_all()
{
    if (this->size > 0){
        for(int i=this->get_size();i>0;i--){
            delete this->pop();
        }
        this->last = NULL;
        this->first = NULL;
    };
};


//Record to file
int text_collection::record_file(const string &fname)
{
    ofstream fout;
    fout.open(fname);

    for (int i = 0; i <int(this->size); i++)
    {
        text object = this->get_by_index(i)->get_object();
        fout <<  object.get_text() <<" " << object.get_poz() << " " << object.get_type() << endl;
    }
    fout.close();
    return 0;
};


//Read from file
int text_collection::output_file(const string &fname)
{
    string textt;
    size_t poz;
    string type;

    ifstream file(fname);

    //Clear stack
    if(this->size>0)  this->remove_all();

    while(file >> textt >> poz >> type)
    {
        auto text1 = new text(textt,poz,type);
        auto object = new stack(*text1);
        this->push_object(*object);
    }
    file.close();
    return 0;
};


//Checker for two stacks
bool text_collection::operator==(const text_collection& l)
{
    // Checker for size
    if(this->size != l.size)
        return false;

    stack *t1, *t2;
    t1 = get_last();
    t2 = l.get_last();

    // Checker for data
    while(t1 != NULL)
    {
        if (t1->get_object().get_text() != t2->get_object().get_text() && t1->get_object().get_poz() != t2->get_object().get_poz() && t1->get_object().get_type() != t2->get_object().get_type())
            return false;
        t1 = t1->get_previous();
        t2 = t2->get_previous();
    }
    return true;
}

//Display stack
int show_stack(text_collection& stack){
    int m = stack.get_size();
    stack *object = stack.get_last();
    cout << "Number  " << "Type      " << "Text              " << "Substring" << endl;
    for (int i=0; i < m; i++){
        string type;
        if (object->get_object().get_type() == "insert")
            type = "Insert";
        else
            type = "Delete";
        cout << i+1 << ".      " << type << "    " << object->get_object().get_text() << "             " << object->get_object().get_poz() << endl;
        object = object->get_previous();
    };
    return 0;
};
