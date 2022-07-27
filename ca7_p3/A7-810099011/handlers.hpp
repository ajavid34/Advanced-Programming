#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "server/server.hpp"
#include <iostream>
#include "App.hpp"

class GoodeatsHanler : public RequestHandler{
public:
	GoodeatsHanler(App* goodeats, Status* status_, std::map <std::string, User*>* sessions_){
        app = goodeats;
		status = status_;
		sessions = sessions_;
    }
protected:
	App* app;
	Status* status;
	std::map <std::string, User*>* sessions;
	std::string html_main_page(Request *req);
	std::string form_css();
};

class SignupForm : public GoodeatsHanler {
public:
	SignupForm(App* goodeats, Status* status_, std::map <std::string, User*>* sessions_) : 
	GoodeatsHanler (goodeats,status_,sessions_){};
	Response *callback(Request *req);
private:
	std::string form_html();
	std::string already_signup_html();
};

class ShowDynamicHome : public GoodeatsHanler {
public:
	ShowDynamicHome(App* goodeats, Status* status_, std::map <std::string, User*>* sessions_) : 
	GoodeatsHanler (goodeats,status_,sessions_){};
	Response *callback(Request *req);
private:
	std::string not_login_home_page_html();
	std::string logout_html();

};

class CheckSignup : public GoodeatsHanler {
public:
	CheckSignup(App* goodeats, Status* status_, std::map <std::string, User*>* sessions_): 
	GoodeatsHanler (goodeats,status_,sessions_){};
	Response *callback(Request *req);
private:

};

class ShowLoggedinHome : public GoodeatsHanler {
public:
	ShowLoggedinHome(App* goodeats, Status* status_, std::map <std::string, User*>* sessions_): 
	GoodeatsHanler (goodeats,status_,sessions_){};
	Response *callback(Request *req);
private:
	std::string add_recipe_chef_html();
	std::string handle_chef(Request *req);
	std::string handle_user(Request *req);
	void handle_filters(Request *req);
	std::string add_filter_user_html();
	std::string show_filters(Request *req);
};
class ShowLoginForm : public GoodeatsHanler {
public:
	ShowLoginForm(App* goodeats, Status* status_, std::map <std::string, User*>* sessions_): 
	GoodeatsHanler (goodeats,status_,sessions_){};
	Response *callback(Request *req);
private:
	std::string form_html();
	std::string login_error_html();
};
class CheckLogin : public GoodeatsHanler {
public:
	CheckLogin(App* goodeats, Status* status_, std::map <std::string, User*>* sessions_): 
	GoodeatsHanler (goodeats,status_,sessions_){};
	Response *callback(Request *req);
private:

};
class CheckLogout : public GoodeatsHanler {
public:
	CheckLogout(App* goodeats, Status* status_, std::map <std::string, User*>* sessions_): 
	GoodeatsHanler (goodeats,status_,sessions_){};
	Response *callback(Request *req);
private:

};
class AddRecipe : public GoodeatsHanler {
public:
	AddRecipe(App* goodeats, Status* status_, std::map <std::string, User*>* sessions_): 
	GoodeatsHanler (goodeats,status_,sessions_){};
	Response *callback(Request *req);
private:

  	void add_recipe(Request *req);
};
class ShowRecipe : public GoodeatsHanler {
public:
	ShowRecipe(App* goodeats, Status* status_, std::map <std::string, User*>* sessions_): 
	GoodeatsHanler (goodeats,status_,sessions_){};
	Response *callback(Request *req);
private:

};
class DeleteRecipe : public GoodeatsHanler {
public:
	DeleteRecipe(App* goodeats, Status* status_, std::map <std::string, User*>* sessions_): 
	GoodeatsHanler (goodeats,status_,sessions_){};
	Response *callback(Request *req);
private:

	void delete_recipe(Request *req);
};
class ResetFilters : public GoodeatsHanler {
public:
	ResetFilters(App* goodeats, Status* status_, std::map <std::string, User*>* sessions_): 
	GoodeatsHanler (goodeats,status_,sessions_){};
	Response *callback(Request *req);
private:

};
class RateRecipe : public GoodeatsHanler {
public:
	RateRecipe(App* goodeats, Status* status_, std::map <std::string, User*>* sessions_): 
	GoodeatsHanler (goodeats,status_,sessions_){};
	Response *callback(Request *req);
private:

	void rate(Request *req);
};
class ShowMyShelves : public GoodeatsHanler {
public:
	ShowMyShelves(App* goodeats, Status* status_, std::map <std::string, User*>* sessions_): 
	GoodeatsHanler (goodeats,status_,sessions_){};
	Response *callback(Request *req);
private:
	std::string handle_shelves(Request *req);
	std::string add_shelves_html();
};
class AddShelves : public GoodeatsHanler {
public:
	AddShelves(App* goodeats, Status* status_, std::map <std::string, User*>* sessions_): 
	GoodeatsHanler (goodeats,status_,sessions_){};
	Response *callback(Request *req);
private:
  	void add_shelves(Request *req);
};
class ShowShelves : public GoodeatsHanler {
public:
	ShowShelves(App* goodeats, Status* status_, std::map <std::string, User*>* sessions_): 
	GoodeatsHanler (goodeats,status_,sessions_){};
	Response *callback(Request *req);
private:
	std::string add_shelve_recipe(Request *req, int shelve_id);
	std::string add_shelve_recipe_html(int shelf_id);
};
class AddShelvesRecipe : public GoodeatsHanler {
public:
	AddShelvesRecipe(App* goodeats, Status* status_, std::map <std::string, User*>* sessions_): 
	GoodeatsHanler (goodeats,status_,sessions_){};
	Response *callback(Request *req);
private:

};
class DeleteRecipeShelves : public GoodeatsHanler {
public:
	DeleteRecipeShelves(App* goodeats, Status* status_, std::map <std::string, User*>* sessions_): 
	GoodeatsHanler (goodeats,status_,sessions_){};
	Response *callback(Request *req);
private:

};
Response* ErrorHandler(std::string massage);
#endif
