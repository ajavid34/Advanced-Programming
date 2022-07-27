
#ifndef PERMITS_H
#define PERMITS_H "PERMITS_H"
#include "Defines.hpp"
#include "Form.hpp"
class Permit {
public:
    Permit(string input);
    void print(int space = 0);
    void confirm_check();
    void create_relation(vector <Permit*>& permits, vector <Form>& forms);
    string get_permit_name();
    int confirm_form(string form_name);
    bool is_confirmed();
    virtual void print_sign();
protected:
    Permit* find_permit_reqs(vector <Permit*>& permits, string req_name);
    Form* find_form_reqs(vector <Form>& forms, string req_name);
    vector <Form* > req_forms;
    vector <Permit* > req_permits;
    vector <string> req_names;
    vector <string> print_seq;
    bool confirm_state{ false };
    string organ_name;
    string permit_name;
    string manager_name;
    string ceo_name;
};

class Base_Permit :public Permit {
public:
    Base_Permit(string input);
    bool start_print();
    void print_sign();
private:
    char sign_type;
};
class MPermit :public Permit {
public:
    MPermit(string input);
    void print_sign();
private:
};
class CPermit :public Permit {
public:
    CPermit(string input);
    void print_sign();
private:
};
class OPermit :public Permit {
public:
    OPermit(string input);
    void print_sign();
private:
};
#endif