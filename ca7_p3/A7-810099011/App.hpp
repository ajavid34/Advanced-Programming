#ifndef App_H_
#define App_H_ "App_H_"
#include "Includes_And_Defines.hpp"
#include "Users.hpp"
#include "Recipes.hpp"
#include "Shelves.hpp"
#include "Filters.hpp"
#include "Errors.hpp"
#include "Sort_And_Find.hpp"
#include "Order.hpp"
#include "Ingredient.hpp"
class App {
public:
	App() {};
	void user_interface(std::istringstream& inputs, int command_count);
    int count_words(std::string const& str);
	User* create_new_user(std::string username, std::string password, std::string roll);
	std::string get_active_roll(std::string name);
	bool is_already_signup(std::string username, std::string email = "");
	void login_user(std::string, std::string);
	std::string show_chef_recipe(std::string username);
	void add_recipe(std::string,std::string,std::string,std::string,std::string,std::string,int );
	std::string show_recipe_id_html(int id, std::string username, Status* status);
	void delete_recipe_id(std::string username,int id);
	std::string show_all_recipes_html();
	void set_filters(std::string type, int min = 0, int max = 0);
	void rate_recipe_id(std::string username,int id, int rate, Status* status);
	std::string show_user_shelves(std::string username);
	void add_shelve(std::string username,std::string title);
	std::string show_shelve_id_html(int id);
	void add_recipe_shelve(std::string username,int id_recipe, int id_shelve);
	void reset_filters_html();
	void delete_recipe_shelve_html(std::string username,int id_recipe, int id_shelve);
private:
	O_User* current_ouser{ NULL };
	Chef* current_chef{ NULL };
	Supplier* current_supplier{ NULL };
	void get_commands(std::istringstream& inputs, int command_count);
	void post_commands(std::istringstream& inputs, int command_count);
	void delete_commands(std::istringstream& inputs, int command_count);
	void put_commands(std::istringstream& inputs, int command_count);
	void post_recipes(std::istringstream& inputs, int command_count);
	std::string read_post_recipes_input(std::istringstream& inputs);
	void signup(std::istringstream& inputs, int command_count);
	std::vector<std::string> read_signup_input(std::istringstream& inputs);
	void login(std::istringstream& inputs, int command_count);
	void check_login(std::string pass);
	std::vector<std::string> read_login_input(std::istringstream& inputs);
	void delete_recipes(std::istringstream& inputs, int command_count);
	int read_delete_recipes_input(std::istringstream& inputs);
	void post_shelve(std::istringstream& inputs, int command_count);
	void read_post_shelve_input(std::istringstream& inputs);
	void get_recipes();
	void get_recipes_id(std::istringstream& inputs, int command_count);
	int read_get_recipes_id_input(std::istringstream& inputs);
	std::string read_get_user_shelves_input(std::istringstream& inputs);
	void get_user_shelves(std::istringstream& inputs, int command_count);
	int read_get_shelves_input(std::istringstream& inputs);
	void get_shelves(std::istringstream& inputs, int command_count);
	std::vector<int> read_put_shelves_recipes_input(std::istringstream& inputs);
	void put_shelves_recipes(std::istringstream& inputs, int command_count);
	std::vector<int> read_delete_shelves_recipes_input(std::istringstream& inputs);
	void delete_shalves_recipes(std::istringstream& inputs, int command_count);
	int choice_command(std::istringstream& inputs);
	void get_chef_username(std::istringstream& inputs, int command_count);
	std::string read_get_chef_username_input(std::istringstream& inputs);
	void get_all_chefs();
	void get_all_users();
	void reset_filters();
    template< typename T >
    void sort_users(std::vector <T* >& user);
	std::string chef_show_recipe_page(int id);
	std::string user_show_recipe_page(int id);
	void rates(std::istringstream& inputs, std::string type, int command_count);
	int read_rates_input(std::istringstream& inputs);
	void post_filter(std::istringstream& inputs, int command_count);
	void post_tag_filter(std::istringstream& inputs, int command_count);
	void post_time_filter(std::istringstream& inputs, int command_count);
	void post_rate_filter(std::istringstream& inputs, int command_count);
	bool is_passed_filters(const std::shared_ptr<Recipe>& recipe);
	O_User* find_ousers(std::string name);
	Chef* find_chefs(std::string name);
	Supplier* find_email_supplier(std::string email);
	Supplier* find_name_supplier(std::string name);
	void supplier_signup(std::istringstream& inputs, int command_count);
	std::vector<std::string> read_supplier_signup_input(std::istringstream& inputs);
	int choice_user(std::istringstream& inputs);
	void post_offers(std::istringstream& inputs, int command_count);
	std::vector<std::string> read_offers_input(std::istringstream& inputs, std::string type);
	void put_offers(std::istringstream& inputs, int command_count);
	void delete_offers(std::istringstream& inputs, int command_count);
	std::string read_delete_offers_input(std::istringstream& inputs);
	void put_credits(std::istringstream& inputs, int command_count);
	void get_credits();
	double read_put_credits_input(std::istringstream& inputs);
	void post_orders(std::istringstream& inputs, int command_count);
	int read_post_order_input(std::istringstream& inputs);
	void get_orders();
	bool are_all_ingredient_exist(std::shared_ptr <Recipe> recipe);
	void add_unique_ingredients(std::string name, std::shared_ptr <Ingredient> ingredient);
	void delete_unique_ingredients(std::string name, std::shared_ptr <Ingredient> ingredient);
	bool is_exist_ingredient(std::string name); 
	void check_discount_state();
	void logout();
	std::vector <O_User*> users;
	std::vector <Chef*> chefs;
	std::vector <Supplier*> suppliers;
	std::vector <std::shared_ptr <Recipe> > recipes;
	std::vector <std::shared_ptr <Shelve> > shelves;
	std::vector <std::shared_ptr <Ingredient> > ingredients;
	std::vector <Unique_Ingredient> unique_ingredients;
	int now_id_recipes{ 1 };
	int now_id_shelves{ 1 };
	Tag_Filter tag_filter;
	Veg_Filter veg_filter;
	Time_to_Ready_Filter time_filter;
	Rate_Filter rate_filter;
};
#endif