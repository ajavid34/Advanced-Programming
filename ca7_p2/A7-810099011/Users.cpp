#include "Users.hpp"
using namespace std;
bool User::is_valid_password(std::string pass) {
		if (pass == password)
			return true;
		else
			return false;
}
bool User::is_valid_username(std::string name) {
	if (name == username)
		return true;
	else
		return false;
}
string User::get_username() { return username; }
User::User(string name, string pass) {
	username = name;
	password = pass;
}
Chef::Chef(string username, string password) :User(username,password) {}
O_User::O_User(string username, string password) : User(username, password) {}
void Chef::calc_score() {
	double sum{ 0 };
	int count{ 0 };
	for (int i = 0; i < recipes.size(); i++) 
		if (recipes[i]->get_num_voters()) {
			sum += recipes[i]->get_score();
			count++;
		}
	if (count != 0)
		score = sum / count;
}
void Chef::glimpse_chef() {
	calc_score();
	cout << username << " ";
	cout.precision(1);
	cout << fixed << ceil(score * 10) / 10 << endl;
}
void Chef::full_show() {
	calc_score();
	cout << username << endl;
	cout.precision(1);
	cout << fixed << ceil(score * 10) / 10 << endl;
	cout << "recipes:" << endl;
	for (int i = 0; i < recipes.size(); i++) {
		recipes[i]->glimpse_recipe();
		cout.precision(1);
		cout << " " << fixed << ceil(recipes[i]->get_score() * 10) / 10 << endl;
	}
}
void Chef::view_recipes() {
	sort_recipes(recipes);
	for (int i = 0; i < recipes.size(); i++) {
		recipes[i]->show_full_recipe();
		cout << endl;
	}
}
void O_User::view_shelves(int limit) {
	sort_shelves_id(shelves);
	int size = min(limit, (int)shelves.size());
	for (int i = 0; i < size; i++)
		shelves[i]->glimpse_shelve();
	if (size == 0)
		cout << EMPTY_KEYWORD << endl;
}
void O_User::put_shelves_recipes(int shel_id, int rec_id, const shared_ptr<Recipe>& recipe) {
	shared_ptr<Shelve> shel = find_shelve(shel_id, shelves);
	if (shel == NULL)
		throw Permission_Error();
	shel->add_recipe(recipe);
}
void O_User::delete_shelves_recipes(int shel_id, int rec_id) {
	shared_ptr<Shelve> shel = find_shelve(shel_id, shelves);
	if (shel == NULL)
		throw Permission_Error();
	shel->remove_recipe(rec_id);
}
void Chef::remove_recipes(int id) {
	int index = find_index_recipe(id, recipes);
	if (index != NOT_FOUND_INDEX)
		recipes.erase(index + recipes.begin());
	else
		throw Permission_Error();
}
Supplier::Supplier(string username, string email_, string password) :User(username, password) { email = email_; }
bool Supplier::is_valid_email(string mail) {
	if (mail == email)
		return true;
	else
		return false;
}
void Supplier::new_ingredient(shared_ptr<Ingredient> newing) { ingredients.push_back(newing); }
void Supplier::edit_ingredient(string title, double pr, int cnt) {
	shared_ptr <Ingredient> ing = find_ingredient(title, this->username, ingredients);
	ing->edit(pr, cnt);
}
bool Supplier::is_already_posted(string title){
	shared_ptr <Ingredient> ing = find_ingredient(title, this->username, ingredients);
	if (ing == NULL)
		return false;
	else
		return true;
}
void Supplier::remove_ingredient(string title) {
	int index = find_index_ingredient(title, ingredients, this->username);
	ingredients.erase(index + ingredients.begin());
}
double User::get_credits() { return money; }
void User::add_credits(double mon) { money += mon; }

void O_User::add_order(Order neworder) { 
	orders.push_back(neworder);
	money -= neworder.get_price();
}
void O_User::view_orders() {
	for (int i = 0; i < orders.size(); i++) {
		cout << "====order_" << i + 1 << "====" << endl;
		cout << orders[i].get_recipe_id() << endl;
		orders[i].order_view();
	}
}