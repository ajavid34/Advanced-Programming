#include "App.hpp"
App::App(int argc, char* argv[]) {
    read_files(argc, argv);
    base_permit->confirm_check();
    while (!base_permit->start_print()) {
        get_confirmation();
        base_permit->confirm_check();
    }
    base_permit->print();
}
void App::read_files(int argc, char* argv[]) {
    string name_permit_file;
    string name_form_file;
    for (int i = 0; i < argc; i++) {
        if (strstr(argv[i], FILE_FORMAT)) {
            name_permit_file = argv[i];
            name_form_file = argv[i + 1];
            break;
        }
    }
    ifstream permit_file(name_permit_file);
    string temp;
    getline(permit_file, temp);
    for (int i = 0; getline(permit_file, temp); i++) {
        if (i == 0) {
            base_permit = new Base_Permit(temp);
        }
        else if (temp.at(temp.find(COMMA) + 1) == M_TYPE_PERMIT)
            mpermits.push_back(MPermit(temp));
        else if (temp.at(temp.find(COMMA) + 1) == O_TYPE_PERMIT)
            opermits.push_back(OPermit(temp));
        else if (temp.at(temp.find(COMMA) + 1) == C_TYPE_PERMIT)
            cpermits.push_back(CPermit(temp));
    }
    permit_file.close();
    ifstream form_file(name_form_file);
    getline(form_file, temp);
    while (getline(form_file, temp)) {
        forms.push_back(Form(temp));
    }
    form_file.close();
    for (int i = 0; i < cpermits.size(); i++)
        permits.push_back(&cpermits[i]);
    for (int i = 0; i < mpermits.size(); i++)
        permits.push_back(&mpermits[i]);
    for (int i = 0; i < opermits.size(); i++)
        permits.push_back(&opermits[i]);
    linking();
}
void App::linking() {
    base_permit->create_relation(permits, forms);
    for (int i = 0; i < permits.size(); i++)
        permits[i]->create_relation(permits, forms);
}
void App::get_confirmation() {
    string temp;
    string form_name;
    cin >> temp >> form_name;
    if (base_permit->confirm_form(form_name))
        return;
    else
        for (int i = 0; i < permits.size(); i++)
            if (permits[i]->confirm_form(form_name))
                return;
}