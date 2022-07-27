
#ifndef APP_H
#define APP_H "APP_H"
#include "Defines.hpp"
#include "Permits.hpp"
#include "Form.hpp"

class App {
public:
    App(int argc, char* argv[]);
    void read_files(int argc, char* argv[]);
    void linking();
    void get_confirmation();
private:
    vector <CPermit> cpermits;
    vector <MPermit> mpermits;
    vector <OPermit> opermits;
    vector <Form> forms;
    Base_Permit* base_permit;
    vector<Permit*> permits;
};

#endif