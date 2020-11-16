#ifndef TEXT_H
#define TEXT_H
#include "string"

using namespace std;

class text{
    private:
        string textI;
        unsigned int index;
        bool type;
    public:
        text(string text,unsigned int index, string type);//
        text(const text& i);//
        text();

        const string& get_text();
        int get_poz() const;
        const string get_type();

        void set_text(string value);
        void set_poz(unsigned int value);
        void set_type(string value);
        void set_index(size_t value);
        int getindex() const;
};

#endif
