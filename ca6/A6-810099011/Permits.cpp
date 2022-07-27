#include "Permits.hpp"

Permit::Permit(string input) {
    string temp;
    istringstream iss(input, istringstream::in);
    getline(iss, organ_name, COMMA);
    getline(iss, temp, COMMA);
    getline(iss, permit_name, COMMA);
    getline(iss, temp, COMMA);
    getline(iss, manager_name, COMMA);
    getline(iss, ceo_name, COMMA);
    istringstream reqs(temp, istringstream::in);
    while (getline(reqs, temp, SEPRATE_REQ))
        req_names.push_back(temp);
}
Base_Permit::Base_Permit(string input) :Permit(input){
    sign_type = input.at(input.find(COMMA) + 1);
}
CPermit::CPermit(string input) : Permit(input) {}
OPermit::OPermit(string input) : Permit(input) {}
MPermit::MPermit(string input) : Permit(input) {}

void Permit::create_relation(vector <Permit*>& all_permits, vector <Form>& all_forms) {
    for (int i = 0; i < req_names.size(); i++) {
        if (req_names[i].at(0) == FORM_START) {
            req_forms.push_back(find_form_reqs(all_forms, req_names[i]));
            print_seq.push_back(FORM_START + to_string(req_forms.size()));
        }
        else if (req_names[i].at(0) == PERMIT_START) {
            req_permits.push_back(find_permit_reqs(all_permits, req_names[i]));
            print_seq.push_back(PERMIT_START + to_string(req_permits.size()));
        }
    }
}
Form* Permit::find_form_reqs(vector <Form>& all_forms, string req_name) {
    for (int k = 0; k < all_forms.size(); k++)
        if (!req_name.compare(all_forms[k].get_form_name()))
            return &all_forms[k];
    return NULL;
}
Permit* Permit::find_permit_reqs(vector <Permit*>& all_permits, string req_name) {
    for (int j = 0; j < all_permits.size(); j++) 
        if (!req_name.compare(all_permits[j]->get_permit_name())) 
            return all_permits[j];
    return NULL;
}
string Permit::get_permit_name() { return permit_name; }
bool Permit::is_confirmed() { return confirm_state; }
bool Base_Permit::start_print() { return confirm_state; }

int Permit::confirm_form(string form_name) {
    for (int i = 0; i < req_forms.size(); i++) {
        if (!form_name.compare(req_forms[i]->get_form_name())) {
            req_forms[i]->get_confirm();
            return 1;
        }
    }
    return 0;
}
void Permit::confirm_check() {
    for (int i = 0; i < req_permits.size(); i++) {
        req_permits[i]->confirm_check();
        if (!req_permits[i]->is_confirmed())
            return;
    }
    for (int i = 0; i < req_forms.size(); i++)
        if (!req_forms[i]->is_confirmed())
            return;
    confirm_state = true;
}

void Permit::print_sign() {}
void MPermit::print_sign() {
    cout << manager_name;
}
void CPermit::print_sign() {
    cout << ceo_name;
}
void OPermit::print_sign() {
    cout << organ_name;
}
void Base_Permit::print_sign() {
    if (sign_type == M_TYPE_PERMIT)
        cout << manager_name;
    else if (sign_type == C_TYPE_PERMIT)
        cout << ceo_name;
    else if (sign_type == O_TYPE_PERMIT)
        cout << organ_name;
}
void Permit::print(int space) {
    print_space(space);
    cout << "Name: " << permit_name << endl;
    print_space(space);
    cout << "This permit consists of: {";
    for (int i = 0; i < print_seq.size(); i++) {
        cout << endl;
        print_space(SPACE_NUMBER + space);
        cout << "#" << i + 1<< endl;
        if (print_seq[i].at(0) == FORM_START) {
            req_forms[(int)(print_seq[i].at(1) - 49)]->print(SPACE_NUMBER + space);
        }
        else if (print_seq[i].at(0) == PERMIT_START) {
            req_permits[(int)(print_seq[i].at(1) - 49)]->print(SPACE_NUMBER + space);
        }
    }
    cout << endl;
    print_space(space);
    cout << "}" << endl;
    print_space(space);
    cout << "Signature: ";
    print_sign();
}