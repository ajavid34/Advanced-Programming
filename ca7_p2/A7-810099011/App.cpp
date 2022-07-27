#include "App.hpp"
using namespace std;

void App::user_interface(istringstream& inputs, int command_count) {
	string command_type;
	inputs >> command_type;
	if (!command_type.compare(POST_COMMANDS))
		post_commands(inputs, command_count);
	else if (!command_type.compare(GET_COMMANDS))
		get_commands(inputs, command_count);
	else if (!command_type.compare(DELETE_COMMANDS))
		delete_commands(inputs, command_count);
	else if (!command_type.compare(PUT_COMMANDS))
		put_commands(inputs, command_count);
	else
		throw Bad_Request_Error();
}
void App::post_commands(istringstream& inputs, int command_count) {
	string temp;
	inputs >> temp;
	if (!temp.compare(SIGNUP_COMMAND))
		signup(inputs, command_count);
	else if (!temp.compare(LOGIN_COMMAND))
		login(inputs, command_count);
	else if (!temp.compare(LOGOUT_COMMAND))
		logout();
	else if (!temp.compare(RATINGS_COMMAND))
		rates(inputs, POST_COMMANDS, command_count);
	else if (!temp.compare(SHELVES_KEYWORD))
		post_shelve(inputs, command_count);
	else if (!temp.compare(RECIPES_KEYWORD))
		post_recipes(inputs, command_count);
	else if (!temp.compare(FILTERS_COMMAND))
		post_filter(inputs, command_count);
	else if (!temp.compare(SIGNUP_SUPPLIER_COMMAND))
		supplier_signup(inputs, command_count);
	else if (!temp.compare(OFFERS_COMMAND))
		post_offers(inputs, command_count);
	else if (!temp.compare(ORDERS_COMMAND))
		post_orders(inputs, command_count);
	else
		throw Bad_Request_Error();
}
void App::put_commands(istringstream& inputs, int command_count) {
	string temp;
	inputs >> temp;
	if (!temp.compare(RATINGS_COMMAND))
		rates(inputs, PUT_COMMANDS, command_count);
	else if (!temp.compare(SHELVES_RECIPES_KEYWORD))
		put_shelves_recipes(inputs, command_count);
	else if (!temp.compare(OFFERS_COMMAND))
		put_offers(inputs, command_count);
	else if (!temp.compare(CREDITS_COMMAND))
		put_credits(inputs, command_count);
	else
		throw Bad_Request_Error();
}
void App::logout() {
	if (current_chef == NULL && current_ouser == NULL && current_supplier == NULL)
		throw Permission_Error();
	if (current_ouser != NULL)
		reset_filters();
	current_chef = NULL;
	current_ouser = NULL;
	current_supplier = NULL;
	cout << OK_KEYWORD << endl;
}
void App::read_post_shelve_input(istringstream& inputs){
	string temp;
	inputs >> temp;
	if (temp != QUESTION_MARK)
		throw Not_Found_Error();
	inputs >> temp;
	if (temp != NAME_KEYWORD)
		throw Not_Found_Error();
}
void App::post_shelve(istringstream& inputs, int command_count) {
	string temp;
	string name;
	if (current_ouser == NULL)
		throw Permission_Error();
	if (command_count != POST_SHELVES_COMMAND_SIZE)
		throw Bad_Request_Error();
	read_post_shelve_input(inputs);
	inputs >> name;
	shared_ptr<Shelve> newshelv(make_shared<Shelve>(name, now_id_shelves, current_ouser));
	shelves.push_back(newshelv);
	current_ouser->new_shelves(newshelv);
	now_id_shelves++;
}
bool App::is_already_signup(string name, string email = "") {
	Supplier* sp1{ NULL };
	Supplier* sp2{ NULL };
	Chef* ch{ NULL };
	O_User* us{ NULL };
	ch = find_chefs(name);
	us = find_ousers(name);
	sp2 = find_name_supplier(name);
	if (email != "")
		sp1 = find_email_supplier(email);
	if (sp1 != NULL || sp2 != NULL || us != NULL || ch != NULL)
		return true;
	else
		return false;
}
vector<string> App::read_signup_input(istringstream& inputs){
	vector<string> info(3);
	string temp;
	inputs >> temp;
	if (temp != QUESTION_MARK)
		throw Not_Found_Error();
	inputs >> temp;
	if (temp != USERNAME_KEYWORD)
		throw Not_Found_Error();
	inputs >> info[0];
	inputs >> temp;
	if (temp != PASSWORD_KEYWORD)
		throw Not_Found_Error();
	inputs >> info[1];
	inputs >> temp;
	if (temp != TYPE_KEYWORD)
		throw Not_Found_Error();
	inputs >> info[2];
	return info;
}
void App::signup(istringstream& inputs, int command_count) {
	vector<string> info;
	if (current_chef != NULL || current_ouser != NULL)
		throw Bad_Request_Error();
	if (command_count != SIGNUP_COMMAND_SIZE)
		throw Bad_Request_Error();
	info = read_signup_input(inputs);
	if (is_already_signup(info[0]))
		throw Bad_Request_Error();
	if (!info[2].compare(CHEF_KEYWORD)) {
		current_chef = new Chef(info[0], info[1]);
		chefs.push_back(current_chef);
	}
	else if (!info[2].compare(USER_KEYWORD)) {
		current_ouser = new O_User(info[0], info[1]);
		users.push_back(current_ouser);
	}
	else
		throw Not_Found_Error();
	cout << OK_KEYWORD << endl;
}
vector<string> App::read_login_input(istringstream& inputs){
	vector<string> info(2);
	string temp;
	inputs >> temp;
	if (temp != USERNAME_KEYWORD && temp != EMAIL_KEYWORD)
		throw Not_Found_Error();
	inputs >> info[0];
	inputs >> temp;
	if (temp != PASSWORD_KEYWORD)
		throw Not_Found_Error();
	inputs >> info[1];
	return info;
}
int App::choice_user(istringstream& inputs) {
	string identifier;
	string temp;
	inputs >> temp;
	if (temp != QUESTION_MARK)
		throw Not_Found_Error();
	stringstream::pos_type pos = inputs.tellg();
	inputs >> identifier;
	if (identifier == EMAIL_KEYWORD) {
		inputs.clear();
		inputs.seekg(pos, inputs.beg);
		return 1;
	}
	else {
		inputs.clear();
		inputs.seekg(pos, inputs.beg);
		return 0;
	}
}
void App::login(istringstream& inputs, int command_count) {
	vector<string> info;
	if (current_chef != NULL || current_ouser != NULL)
		throw Bad_Request_Error();
	if (command_count != LOGIN_COMMAND_SIZE)
		throw Bad_Request_Error();
	if (choice_user(inputs)) {
		info = read_login_input(inputs);
		current_supplier = find_email_supplier(info[0]);
		check_login(info[1]);
	}
	else {
		info = read_login_input(inputs);
		current_ouser = find_ousers(info[0]);
		current_chef = find_chefs(info[0]);
		check_login(info[1]);
	}
	cout << OK_KEYWORD << endl;
}
void App::check_login(string password){
	if (current_ouser != NULL) {
		if (!current_ouser->is_valid_password(password)) {
			current_ouser = NULL;
			throw Bad_Request_Error();
		}
	}
	else if (current_chef != NULL) {
		if (!current_chef->is_valid_password(password)) {
			current_chef = NULL;
			throw Bad_Request_Error();
		}
	}
	else if (current_supplier != NULL) {
		if (!current_supplier->is_valid_password(password)) {
			current_supplier = NULL;
			throw Bad_Request_Error();
		}
	}
	else
		throw Bad_Request_Error();
}
int App::read_get_recipes_id_input(istringstream& inputs){
	string temp;
	int id;
	inputs >> temp;
	if (temp != ID_KEYWORD)
		throw Not_Found_Error();
	inputs >> id;
	return id;
}
void App::get_recipes_id(istringstream& inputs, int command_count) {
	int id;
	if (current_ouser == NULL)
		throw Permission_Error();
	if (command_count != GET_RECIPE_ID_COMMAND_SIZE)
		throw Bad_Request_Error();
	id = read_get_recipes_id_input(inputs);
	shared_ptr <Recipe> recipe = find_recipe(id,recipes);
	if (recipe == NULL)
		throw Not_Found_Error();
	else
		recipe->show_full_recipe();
}
int App::choice_command(istringstream& inputs) {
	string identifier;
	stringstream::pos_type pos = inputs.tellg();
	inputs >> identifier;
	if (identifier == QUESTION_MARK)
		return 1;
	else {
		inputs.clear();
		inputs.seekg(pos, inputs.beg);
		return 0;
	}
}
string App::read_get_chef_username_input(istringstream& inputs){
	string temp;
	inputs >> temp;
	if (temp != CHEF_USERNAME_KEYWORD)
		throw Not_Found_Error();
	inputs >>temp;
	return temp;
}
void App::get_chef_username(istringstream& inputs, int command_count) {
	string name;
	if (current_ouser == NULL)
		throw Permission_Error();
	if (command_count != GET_CHEF_USERNAME_COMMAND_SIZE)
		throw Bad_Request_Error();
	name = read_get_chef_username_input(inputs);
	Chef* chef = find_chefs(name);
	if (chef == NULL)
		throw Not_Found_Error();
	else
		chef->full_show();
}
void App::get_all_chefs() {
	if (current_ouser == NULL)
		throw Permission_Error();
	sort_users<Chef>(chefs);
	for (int i = 0; i < chefs.size(); i++)
		chefs[i]->glimpse_chef();
}
void App::get_all_users() {
	if (current_ouser == NULL)
		throw Permission_Error();
	sort_users<O_User>(users);
	for (int i = 0; i < users.size(); i++)
		if (users[i] != current_ouser)
			cout << users[i]->get_username() << endl;
	if (users.size() == 1)
		cout << EMPTY_KEYWORD << endl;
}
void App::get_commands(istringstream& inputs, int command_count) {
	string temp;
	inputs >> temp;
	if (!temp.compare(RECIPES_KEYWORD)) {
		if (choice_command(inputs))
			get_recipes_id(inputs, command_count);
		else
			get_recipes();
	}
	else if (!temp.compare(SHELVES_RECIPES_KEYWORD))
		get_shelves(inputs, command_count);
	else if (!temp.compare(CHEFS_KEYWORD)) {
		if (choice_command(inputs))
			get_chef_username(inputs, command_count);
		else
			get_all_chefs();
	}
	else if (!temp.compare(USERS_KEYWORD))
		get_all_users();
	else if (!temp.compare(MY_RECIPES_KEYWORD))
		current_chef->view_recipes();
	else if (!temp.compare(SHELVES_KEYWORD))
		get_user_shelves(inputs, command_count);
	else if (!temp.compare(CREDITS_COMMAND))
		get_credits();
	else if (!temp.compare(ORDERS_COMMAND))
		get_orders();
	else
		throw Bad_Request_Error();
}
string App::read_post_recipes_input(istringstream& inputs){
	string temp;
	inputs >> temp;;
	if (temp != QUESTION_MARK)
		throw Not_Found_Error();
	inputs >> temp;
	if (temp != TITLE_KEYWORD)
		throw Not_Found_Error();
	inputs >> temp;
	return temp;
}
void App::post_recipes(istringstream& inputs, int command_count) {
	string title;
	if (current_chef == NULL)
		throw Permission_Error();
	if (command_count != POST_RECIPES_COMMAND_SIZE)
		throw Bad_Request_Error();
	title = read_post_recipes_input(inputs);
	shared_ptr<Recipe> newrecip (make_shared <Recipe>(title, now_id_recipes,current_chef, inputs));
	recipes.push_back(newrecip);
	current_chef->new_recipes(newrecip);
	now_id_recipes++;
}
void App::delete_commands(istringstream& inputs, int command_count){
	string temp;
	inputs >> temp;
	if (!temp.compare(RECIPES_KEYWORD))
		delete_recipes(inputs, command_count);
	else if (!temp.compare(SHELVES_RECIPES_KEYWORD))
		delete_shalves_recipes(inputs, command_count);
	else if (!temp.compare(FILTERS_COMMAND)) {
		reset_filters();
		cout << OK_KEYWORD << endl;
	}
	else if (!temp.compare(OFFERS_COMMAND))
		delete_offers(inputs, command_count);
	else
		throw Bad_Request_Error();
}
int App::read_delete_recipes_input(istringstream& inputs){
	string temp;
	int id;
	inputs >> temp;
	if (temp != QUESTION_MARK)
		throw Not_Found_Error();
	inputs >> temp;
	if (temp != ID_KEYWORD)
		throw Not_Found_Error();
	inputs >> id;
	return id;
}
void App::delete_recipes(istringstream& inputs, int command_count) {
	int id;
	if (current_chef == NULL)
		throw Permission_Error();
	if (command_count != DELETE_RECIPES_COMMAND_SIZE)
		throw Bad_Request_Error();
	id = read_delete_recipes_input(inputs);
	int index = find_index_recipe(id,recipes);
	current_chef->remove_recipes(id);
	recipes.erase(index + recipes.begin());
	cout << OK_KEYWORD << endl;
}
O_User* App::find_ousers(string name) {
	for (int i = 0; i < users.size(); i++) 
		if (users[i]->is_valid_username(name))
			return users[i];
	return NULL;
}
Chef* App::find_chefs(string name) {
	for (int i = 0; i < chefs.size(); i++)
		if (chefs[i]->is_valid_username(name))
			return chefs[i];
	return NULL;
}
bool App::is_passed_filters(const shared_ptr<Recipe>& recipe) {
	if (tag_filter.eligible_recipe(recipe) && veg_filter.eligible_recipe(recipe)
		&& time_filter.eligible_recipe(recipe) && rate_filter.eligible_recipe(recipe))
		return true;
	else
		return false;
}
void App::get_recipes() {
	int count{ 0 };
	if (current_ouser == NULL)
		throw Permission_Error();
	sort_recipes(recipes);
	for (auto x : recipes) 
		if (is_passed_filters(x)) {
			x->glimpse_recipe();
			cout << endl;
			count++;
		}
	if (count == 0)
		cout << EMPTY_KEYWORD << endl;
}
int App::read_rates_input(istringstream& inputs){
	string temp;
	int id;
	inputs >> temp;
	if (temp != QUESTION_MARK)
		throw Not_Found_Error();
	inputs >> temp;
	if (temp != RECIPE_ID_KEYWORD)
		throw Not_Found_Error();
	inputs >> id;
	inputs >> temp;
	if (temp != SCORE_KEYWORD)
		throw Not_Found_Error();
	return id;
}
void App::rates(istringstream& inputs, string type, int command_count) {
	int id;
	double score;
	shared_ptr<Recipe> recipe;
	if (current_ouser == NULL)
		throw Permission_Error();
	if (command_count != RATES_COMMAND_SIZE)
		throw Bad_Request_Error();
	id = read_rates_input(inputs);
	recipe = find_recipe(id, recipes);
	if (recipe == NULL)
		throw Not_Found_Error();
	inputs >> score;
	if (score > MAX_RATING || score < MIN_RATING)
		throw Bad_Request_Error();
	if (type == POST_COMMANDS)
		recipe->get_rated(score, current_ouser);
	else if (type == PUT_COMMANDS) 
		recipe->change_rate(score, current_ouser);
	cout << OK_KEYWORD << endl;
}
string App::read_get_user_shelves_input(istringstream& inputs){
	string username,temp;
	inputs >> temp;
	if (temp != QUESTION_MARK)
		throw Not_Found_Error();
	inputs >> temp;
	if (temp != USERNAME_KEYWORD)
		throw Not_Found_Error();
	inputs >> username;
	inputs >> temp;
	if (temp != LIMIT_KEYWORD)
		throw Not_Found_Error();
	return username;
}
void App::get_user_shelves(istringstream& inputs, int command_count) {
	string username;
	O_User* user;
	int limit;
	if (current_ouser == NULL)
		throw Permission_Error();
	if (command_count != GET_USER_SHELVES_COMMAND_SIZE)
		throw Bad_Request_Error();
	username = read_get_user_shelves_input(inputs);
	inputs >> limit;
	user = find_ousers(username);
	if (user == NULL)
		throw Not_Found_Error();
	user->view_shelves(limit);
}
vector<int> App::read_put_shelves_recipes_input(istringstream& inputs){
	string temp;
	vector<int> info(2);
	inputs >> temp;
	if (temp != QUESTION_MARK)
		throw Not_Found_Error();
	inputs >> temp;
	if (temp != SHELF_ID_KEYWORD)
		throw Not_Found_Error();
	inputs >> info[0];
	inputs >> temp;
	if (temp != RECIPE_ID_KEYWORD)
		throw Not_Found_Error();
	inputs >> info[1];
	return info;
}
void App::put_shelves_recipes(istringstream& inputs, int command_count) {
	vector<int> info;
	if (current_ouser == NULL)
		throw Permission_Error();
	if (command_count != PUT_SHELVES_RECIPES_COMMAND_SIZE)
		throw Bad_Request_Error();
	info = read_put_shelves_recipes_input(inputs);
	shared_ptr<Recipe> rec = find_recipe(info[1], recipes);
	if (rec == NULL)
		throw Not_Found_Error();
	current_ouser->put_shelves_recipes(info[0], info[1], rec);
	cout << OK_KEYWORD << endl;
}
int App::read_get_shelves_input(istringstream& inputs){
	int shel_id;
	string temp;
	inputs >> temp;
	if (temp != QUESTION_MARK)
		throw Not_Found_Error();
	inputs >> temp;
	if (temp != SHELF_ID_KEYWORD)
		throw Not_Found_Error();
	inputs >> shel_id;
	return shel_id;
}
void App::get_shelves(istringstream& inputs, int command_count) {
	int shel_id;
	shared_ptr<Shelve> shel;
	if (current_ouser == NULL)
		throw Permission_Error();
	if (command_count != GET_SHELVES_RECIPES_COMMAND_SIZE)
		throw Bad_Request_Error();
	shel_id = read_get_shelves_input(inputs);
	shel = find_shelve(shel_id, shelves);
	if (shel == NULL)
		throw Not_Found_Error();
	shel->glimpse_shelve_recipes();
}
vector<int> App::read_delete_shelves_recipes_input(istringstream& inputs){
	string temp;
	vector<int> info(2);
	inputs >> temp;
	if (temp != QUESTION_MARK)
		throw Not_Found_Error();
	inputs >> temp;
	if (temp != SHELF_ID_KEYWORD)
		throw Not_Found_Error();
	inputs >> info[0];
	inputs >> temp;
	if (temp != RECIPE_ID_KEYWORD)
		throw Not_Found_Error();
	inputs >> info[1];
	return info;
}
void App::delete_shalves_recipes(istringstream& inputs, int command_count) {
	vector<int> info;
	if (current_ouser == NULL)
		throw Permission_Error();
	if (command_count != DELETE_SHEVES_RECIPES_COMMAND_SIZE)
		throw Bad_Request_Error();
	info = read_delete_shelves_recipes_input(inputs);
	shared_ptr<Shelve> shel = find_shelve(info[0], shelves);
	if (shel == NULL)
		throw Not_Found_Error();
	current_ouser->delete_shelves_recipes(info[0], info[1]);
	cout << OK_KEYWORD << endl;
}
void App::post_filter(istringstream& inputs, int command_count) {
	string temp;
	if (current_ouser == NULL)
		throw Permission_Error();
	inputs >> temp;
	if (temp != QUESTION_MARK)
		throw Not_Found_Error();
	inputs >> temp;
	if (!temp.compare(TAG_KEYWORD))
		post_tag_filter(inputs, command_count);
	else if (!temp.compare(VEGETARIAN_KEYWORD)) {
		veg_filter.set_filter();
		cout << OK_KEYWORD << endl;
	}
	else if (!temp.compare(MIN_MINUTES_KEYWORD))
		post_time_filter(inputs, command_count);
	else if (!temp.compare(MIN_RATING_KEYWORD))
		post_rate_filter(inputs, command_count);
	else
		throw Bad_Request_Error();
}
void App::post_tag_filter(istringstream& inputs, int command_count) {
	string tag;
	if (command_count != TAG_FILTER_COMMAND_SIZE)
		throw Bad_Request_Error();
	inputs >> tag;
	tag_filter.set_filter(tag);
	cout << OK_KEYWORD << endl;
}
void App::post_time_filter(istringstream& inputs, int command_count) {
	string temp;
	if (command_count != TIME_FILTER_COMMAND_SIZE)
		throw Bad_Request_Error();
	int min, max;
	inputs >> min; 
	inputs >> temp;
	if (temp != MAX_MINUTES_KEYWORD)
		throw Not_Found_Error();
	inputs >> max;
	if (min > max)
		throw Bad_Request_Error();
	time_filter.set_filter(min, max);
	cout << OK_KEYWORD << endl;
}
void App::post_rate_filter(istringstream& inputs, int command_count) {
	string temp;
	if (command_count != RATES_FILTER_COMMAND_SIZE)
		throw Bad_Request_Error();
	double min, max;
	inputs >> min;
	inputs >> temp;
	if (temp != MAX_RATING_KEYWORD)
		throw Not_Found_Error();
	inputs >> max;
	if (max > MAX_RATING || min < MIN_RATING || max < MIN_RATING || min > MAX_RATING)
		throw Bad_Request_Error();
	if (min > max)
		throw Bad_Request_Error();
	rate_filter.set_filter(min, max);
	cout << OK_KEYWORD << endl;
}
void App::reset_filters() {
	if (current_ouser == NULL)
		throw Permission_Error();
	tag_filter.set_off();
	veg_filter.set_off();
	time_filter.set_off();
	rate_filter.set_off();
}
int App::count_words(string const& str) {
	stringstream stream(str);
	return distance(istream_iterator<string>(stream), istream_iterator<string>());
}
template< typename T >
void App::sort_users(vector <T* >& user) {
	sort(user.begin(), user.end(), [](User* a, User* b) {
		return a->get_username() < b->get_username();
		});
}
vector<string> App::read_supplier_signup_input(istringstream& inputs) {
	vector<string> info(3);
	string temp;
	inputs >> temp;
	if (temp != QUESTION_MARK)
		throw Not_Found_Error();
	inputs >> temp;
	if (temp != NAME_KEYWORD)
		throw Not_Found_Error();
	inputs >> info[0];
	inputs >> temp;
	if (temp != EMAIL_KEYWORD)
		throw Not_Found_Error();
	inputs >> info[1];
	inputs >> temp;
	if (temp != PASSWORD_KEYWORD)
		throw Not_Found_Error();
	inputs >> info[2];
	return info;

}
Supplier* App::find_name_supplier(string name) {
	for (int i = 0; i < suppliers.size(); i++)
		if (suppliers[i]->is_valid_username(name))
			return suppliers[i];
	return NULL;
}
Supplier* App::find_email_supplier(string email) {
	for (int i = 0; i < suppliers.size(); i++)
		if (suppliers[i]->is_valid_email(email))
			return suppliers[i];
	return NULL;
}
void App::supplier_signup(istringstream& inputs, int command_count) {
	vector<string> info;
	if (current_chef != NULL || current_ouser != NULL || current_supplier != NULL)
		throw Bad_Request_Error();
	if (command_count != SIGNUP_SUPPLIER_COMMAND_SIZE)
		throw Bad_Request_Error();
	info = read_supplier_signup_input(inputs);
	if (is_already_signup(info[0], info[1]))
		throw Bad_Request_Error();
	current_supplier = new Supplier(info[0], info[1], info[2]);
	suppliers.push_back(current_supplier);
	cout << OK_KEYWORD << endl;
}
vector<string> App::read_offers_input(istringstream& inputs, string type) {
	vector<string>info(4);
	string temp;
	inputs >> temp;
	if (temp != QUESTION_MARK)
		throw Not_Found_Error();
	inputs >> temp;
	if (temp != INGREDINT_KEYWORD)
		throw Not_Found_Error();
	inputs >> info[0];
	inputs >> temp;
	if (temp != PRICE_KEYWORD)
		throw Not_Found_Error();
	inputs >> info[1];
	inputs >> temp;
	if (temp != COUNT_KEYWORD)
		throw Not_Found_Error();
	inputs >> info[2];
	if (type == POST_COMMANDS) {
		inputs >> temp;
		if (temp != PACKAGING_KEYWORD)
			throw Not_Found_Error();
		inputs >> info[3];
	}
	return info;
}
void App::post_offers(istringstream& inputs, int command_count) {
	vector<string>info;
	if (current_supplier == NULL)
		throw Permission_Error();
	if (command_count != POST_OFFERS_COMMAND_SIZE)
		throw Bad_Request_Error();
	info = read_offers_input(inputs, POST_COMMANDS);
	if (current_supplier->is_already_posted(info[0]))
		throw Bad_Request_Error();
	shared_ptr<Ingredient> newing (make_shared <Ingredient>(info[0], current_supplier, stold(info[1]), stoi(info[2]), stold(info[3])));
	ingredients.push_back(newing);
	current_supplier->new_ingredient(newing);
	add_unique_ingredients(info[0], newing);
	check_discount_state();
	cout << OK_KEYWORD << endl;
}
void App::add_unique_ingredients(string name, shared_ptr <Ingredient> ing) {
	for (int i = 0; i < unique_ingredients.size(); i++)
		if (name == unique_ingredients[i].get_name()) {
			unique_ingredients[i].add_to_ingredients(ing);
			return;
		}
	unique_ingredients.push_back(Unique_Ingredient(ing));
}

void App::put_offers(istringstream& inputs, int command_count) {
	vector<string>info;
	if (current_supplier == NULL)
		throw Permission_Error();
	if (command_count != PUT_OFFERS_COMMAND_SIZE)
		throw Bad_Request_Error();
	info = read_offers_input(inputs, PUT_COMMANDS);
	if (!current_supplier->is_already_posted(info[0]))
		throw Bad_Request_Error();
	current_supplier->edit_ingredient(info[0], stold(info[1]), stoi(info[2]));
	check_discount_state();
	cout << OK_KEYWORD << endl;
}
string App::read_delete_offers_input(istringstream& inputs) {
	string temp;
	inputs >> temp;
	if (temp != QUESTION_MARK)
		throw Not_Found_Error();
	inputs >> temp;
	if (temp != INGREDINT_KEYWORD)
		throw Not_Found_Error();
	inputs >> temp;
	return temp;
}
void App::delete_offers(istringstream& inputs, int command_count) {
	string title;
	if (current_supplier == NULL)
		throw Permission_Error();
	if (command_count != DELETE_OFFERS_COMMAND_SIZE)
		throw Bad_Request_Error();
	title = read_delete_offers_input(inputs);
	if (current_supplier->is_already_posted(title)) {
		int index = find_index_ingredient(title, ingredients, current_supplier->get_username());
		current_supplier->remove_ingredient(title);
		delete_unique_ingredients(title, ingredients[index]);
		ingredients.erase(index + ingredients.begin());
	}
	else
		throw Bad_Request_Error();
	check_discount_state();
	cout << OK_KEYWORD << endl;
}
void App::delete_unique_ingredients(string name, shared_ptr <Ingredient> ing) {
	for (int i = 0; i < unique_ingredients.size(); i++)
		if (name == unique_ingredients[i].get_name()) {
			unique_ingredients[i].remove_ingredients(ing);
			return;
		}
}
void App::get_credits() {
	double money;
	if (current_ouser == NULL && current_supplier == NULL)
		throw Permission_Error();
	else if (current_supplier == NULL)
		money = current_ouser->get_credits();
	else
		money = current_supplier->get_credits();
	cout << floor(money) << endl;
}
double App::read_put_credits_input(istringstream& inputs) {
	string temp;
	double money;
	inputs >> temp;
	if (temp != QUESTION_MARK)
		throw Not_Found_Error();
	inputs >> temp;
	if (temp != MONEY_KEYWORD)
		throw Not_Found_Error();
	inputs >> money;
	return money;
}
void App::put_credits(istringstream& inputs, int command_count) {
	double money;
	if (current_ouser == NULL)
		throw Permission_Error();
	if (command_count != PUT_CREDITS_COMMAND_SIZE)
		throw Bad_Request_Error();
	money = read_put_credits_input(inputs);
	current_ouser->add_credits(money);
	cout << OK_KEYWORD << endl;
}
int App::read_post_order_input(istringstream& inputs) {
	string temp;
	int id;
	inputs >> temp;
	if (temp != QUESTION_MARK)
		throw Not_Found_Error();
	inputs >> temp;
	if (temp != RECIPE_ID_KEYWORD)
		throw Not_Found_Error();
	inputs >> id;
	return id;
}
void App::post_orders(istringstream& inputs, int command_count) {
	shared_ptr<Recipe> recipe;
	if (current_ouser == NULL)
		throw Permission_Error();
	if (command_count != POST_ORDERS_COMMAND_SIZE)
		throw Bad_Request_Error();
	int rec_id = read_post_order_input(inputs);
	recipe = find_recipe(rec_id, recipes);
	if (recipe == NULL)
		throw Not_Found_Error();
	if (!are_all_ingredient_exist(recipe))
		throw Not_Found_Error();
	Order neworder(recipe, ingredients, current_ouser->get_credits());
	current_ouser->add_order(neworder);
	check_discount_state();
	neworder.order_view();
}
void App::get_orders() {
	if (current_ouser == NULL)
		throw Permission_Error();
	current_ouser->view_orders();
}
bool App::are_all_ingredient_exist(shared_ptr <Recipe> recipe) {
	vector <string> ing_names = recipe->get_ingredients_name();
	for (int i = 0; i < ing_names.size(); i++)
		if (!is_exist_ingredient(ing_names[i]))
			return false;
	return true;
}
bool App::is_exist_ingredient(string name) {
	for (int i = 0; i < unique_ingredients.size(); i++) {
		if (name == unique_ingredients[i].get_name())
			return (unique_ingredients[i].get_count() > 0);
	}
	return false;
}
void App::check_discount_state() {
	for (int i = 0; i < unique_ingredients.size(); i++)
		unique_ingredients[i].check_discount();
}