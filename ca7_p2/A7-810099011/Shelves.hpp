#ifndef SHELVES_H_
#define SHELVES_H_ "SHELVES_H_"
#include "Includes_And_Defines.hpp"
#include "Users.hpp"
#include "Recipes.hpp"
#include "Sort_And_Find.hpp"
#include "Errors.hpp"
class O_User;
class Shelve {
public:
	Shelve(std::string name_, int id_, O_User* user_);
	void glimpse_shelve_recipes();
	void glimpse_shelve();
	void add_recipe(std::shared_ptr<Recipe> res);
	bool is_right_user(O_User* user_);
	std::string get_name();
	int get_id();
	void remove_recipe(int id_);
private:
	std::string name;
	int id;
	O_User* user;
	std::vector <std::shared_ptr<Recipe> > recipes;
};
#endif