#include <iostream>
#include <assert.h>
#include <stack.h>
#include <text.h>
#include <fstream>
#include <stdio.h>
#include <text_collection.h>

using namespace std;

int main()
{
    //Class text
     text test_txt("phone", 2, "insert" );
     assert(test_txt.get_text() == "phone");
     assert(test_txt.get_poz() == 2);
     assert(test_txt.get_type() == "insert");

     stack test_stack(test_txt);

     // Default constructors
     text_collection test_cl_stack;
     assert(test_cl_stack.get_last()==NULL);
     assert(test_cl_stack.get_first()==NULL);
     assert(test_cl_stack.get_size()==0);

     // Remove and add
     assert(test_cl_stack.get_size() == 0);
     test_cl_stack.push_object(test_stack);
     assert(test_cl_stack.get_size() == 1);
     test_cl_stack.remove();
     assert(test_cl_stack.get_size() == 0);

     test_cl_stack.push_object(test_stack);
     test_cl_stack.push_object(test_stack);

     //Copy constructors and remove all
     text_collection stack2(test_cl_stack);
     assert(test_cl_stack == stack2);
     assert(test_cl_stack.get_size() == 2);
     stack2.remove_all();
     bool check = test_cl_stack == stack2;
     assert(check==false);
     assert(stack2.get_size() == 0);

     //Show stack
     assert(show_stack(test_cl_stack) == 0);


     //Record and read file
     assert(test_cl_stack.record_file("file1.txt") == 0);
     text_collection test_cl_stack_out;
     assert(test_cl_stack_out.output_file("file1.txt") == 0);
     show_stack(test_cl_stack_out);
     assert(test_cl_stack == test_cl_stack_out); // Проверка на равенство записанной в файл и полученной из файла коллекцией

    return 0;
}
