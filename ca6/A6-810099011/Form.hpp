
#ifndef FORM_H
#define FORM_H "FORM_H"
#include "Defines.hpp"
class Form {
public:
    Form(string input);
    void print(int space);
    string get_form_name();
    void get_confirm();
    bool is_confirmed();
private:
    bool confirm_state{ false };
    string name;
    string content;
};
#endif