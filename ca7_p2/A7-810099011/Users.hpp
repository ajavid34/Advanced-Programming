#ifndef USER_H_
#define USER_H_ "USER_H_"
#include "Includes_And_Defines.hpp"
#include "Recipes.hpp"
#include "Shelves.hpp"
#include "Sort_And_Find.hpp"
#include "Errors.hpp"
#include "Order.hpp"
class Ingredient;
class Order;
class User {
public:
	User(std::string username, std::string password);
	bool is_valid_password(std::string pass);
	bool is_valid_username(std::string name);
	std::string get_username();
	double get_credits();
	void add_credits(double money);
protected:
	std::string username;
	std::string password;
	double money{ 0.0 };
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
	void add_order(Order neworder);
	void view_orders();
private:
	std::vector <std::shared_ptr<Shelve> > shelves;
	std::vector <Order> orders;
};
class Supplier :public User {
public:
	Supplier(std::string username, std::string email, std::string password);
	bool is_valid_email(std::string email);
	bool is_already_posted(std::string title);
	void new_ingredient(std::shared_ptr<Ingredient> newing);
	void edit_ingredient(std::string title, double price, int count);
	void remove_ingredient(std::string title);
private:
	std::string email;
	std::vector<std::shared_ptr<Ingredient> > ingredients;
};
#endif