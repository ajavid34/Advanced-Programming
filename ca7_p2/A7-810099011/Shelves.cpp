#include "Shelves.hpp"
using namespace std;
Shelve::Shelve(string name_, int id_, O_User* user_) {
		name = name_;
		user = user_;
		id = id_;
		cout << id << endl;
	}
void Shelve::glimpse_shelve_recipes() {
	for (int i = 0; i < recipes.size(); i++) {
		recipes[i]->glimpse_recipe();
		cout << endl;
	}
}
void Shelve::glimpse_shelve() {
	cout << id << " ";
	cout << name << endl;
}
void Shelve::add_recipe(std::shared_ptr<Recipe> res) {
	recipes.push_back(res); 
}
bool Shelve::is_right_user(O_User* user_) {
	if (user == user_)
		return true;
	else
		return false;
}
string Shelve::get_name() { return name; }
int Shelve::get_id() { return id; }
void Shelve::remove_recipe(int rec_id) {
	int index = find_index_recipe(rec_id,recipes);
	if (index != NOT_FOUND_INDEX)
		recipes.erase(index + recipes.begin());
	else
		throw Bad_Request_Error();
}