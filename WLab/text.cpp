#include <text.h>
#include <string>


using namespace std;

text::text(string text, size_t index, string value) {
    this->textI = text;
    size_t len = text.length();
    if (len > index)
        this->index = index;
    else
        this->index = 0;
    if (value == "delete")
        this->type = false;
    else
        this->type = true;

}

text::text(const text& i) {
    this->textI = i.textI;
    this->index = i.index;
    this->type = i.type;
}

text::text() {
    this->textI = "";
    this->index = 0;
    this->type = true;
}

const string& text::get_text()
{
    return this->textI;
}

int text::getindex() const
{
    return this->index;
}

const string text::get_type()
{
    if (this->type == true)
        return "insert";
    else
    {
        if (this->type == false)
            return "delete";
        else
            return "none";
    }
}


void text::set_text(string value)
{
    this->textI = value;
}

void text::set_type(string value)
{
    if (value == "insert")
        this->type = true;
    else
        if (value == "delete")
            this->type = false;
}

void text::set_index(size_t value)
{
    size_t text_len = this->textI.length();
    if (value >= 0 && text_len > value)
        this->index = value;
    else
        this->index = 0;

}


