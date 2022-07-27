#include "Form.hpp"

Form::Form(string input) {
    string temp;
    istringstream iss(input, istringstream::in);
    getline(iss, name, COMMA);
    getline(iss, content);
}
void Form::print(int space) {
    print_space(space);
    cout << "Name: " << name << endl;
    print_space(space);
    cout << "Content: " << content;
}
string Form::get_form_name() { return name; }
void Form::get_confirm() { confirm_state = true; }
bool Form::is_confirmed() { return confirm_state; }