#ifndef USER_H_
#define USER_H_ "USER_H_"
#include "Includes_And_Defines.hpp"
#include "Recipes.hpp"
#include "Shelves.hpp"
#include "Sort_And_Find.hpp"
#include "Errors.hpp"
class User {
public:
	User(std::string username, std::string password);
	bool is_valid_password(std::string pass);
	bool is_valid_username(std::string name);
	std::string get_username();
protected:
	std::string username;
	std::string password;
};
class Chef :public User {
public:
	Chef(std::string username, std::string password);
	void new_recipes(std::shared_ptr<Recipe> newrecip) { recipes.push_back(newrecip); }
	void view_recipes();
	void calc_score();
	void glimpse_chef();
	void full_show();
	void remove_recipes(int id);
private:
	std::vector <std::shared_ptr<Recipe> > recipes;
	double score{ 0.0 };
};
class O_User :public User {
public:
	O_User(std::string username, std::string password);
	void new_shelves(std::shared_ptr<Shelve> newshelve) { shelves.push_back(newshelve); }
	void view_shelves(int limit);
	void put_shelves_recipes(int shel_id, int rec_id, const std::shared_ptr<Recipe>& recipes);
	void delete_shelves_recipes(int shel_id, int rec_id);
private:
	std::vector <std::shared_ptr<Shelve> > shelves;
};
#endif