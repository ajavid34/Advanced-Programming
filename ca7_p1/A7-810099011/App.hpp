#ifndef App_H_
#define App_H_ "App_H_"
#include "Includes_And_Defines.hpp"
#include "Users.hpp"
#include "Recipes.hpp"
#include "Shelves.hpp"
#include "Filters.hpp"
#include "Errors.hpp"
#include "Sort_And_Find.hpp"
class App {
public:
	App() {};
	void user_interface(std::istringstream& inputs, int command_count);
    int count_words(std::string const& str);
private:
	O_User* current_ouser{ NULL };
	Chef* current_chef{ NULL };
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
	void logout();
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
    template< typename T >
    void sort_users(std::vector <T* >& user);
	bool is_already_signup(std::string username);
	void rates(std::istringstream& inputs, std::string type, int command_count);
	int read_rates_input(std::istringstream& inputs);
	void reset_filters();
	void post_filter(std::istringstream& inputs, int command_count);
	void post_tag_filter(std::istringstream& inputs, int command_count);
	void post_time_filter(std::istringstream& inputs, int command_count);
	void post_rate_filter(std::istringstream& inputs, int command_count);
	bool is_passed_filters(const std::shared_ptr<Recipe>& recipe);
	O_User* find_ousers(std::string name);
	Chef* find_chefs(std::string name);
	std::vector <O_User*> users;
	std::vector <Chef*> chefs;
	std::vector <std::shared_ptr <Recipe> > recipes;
	std::vector <std::shared_ptr <Shelve> > shelves;
	int now_id_recipes{ 1 };
	int now_id_shelves{ 1 };
	Tag_Filter tag_filter;
	Veg_Filter veg_filter;
	Time_to_Ready_Filter time_filter;
	Rate_Filter rate_filter;
};
#endif