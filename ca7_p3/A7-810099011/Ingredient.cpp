#include "Ingredient.hpp"
using namespace std;
Ingredient::Ingredient(string title, Supplier* sup, double pr, int cnt, double packing) {
	name = title;
	supplier = sup;
	price = pr;
	count = cnt;
	packing_price = packing;
}
bool Ingredient::is_right_ingredient(string title, string supplier_name) {
	if (supplier_name != "") {
		if (title == name && supplier->is_valid_username(supplier_name))
			return true;
		else
			return false;
	}
	else
		return title == name;
}
void Ingredient::edit(double pr, int cnt) {
	price = pr;
	count = cnt;
}
vector <std::string> Recipe::get_ingredients_name() { return ingredients; }
string Ingredient::get_supplier_name() { return supplier->get_username(); }
string Ingredient::get_name() { return name; }
void Ingredient::get_sold() { 
	count--;
	supplier->add_credits(get_price());
}
void Ingredient::increase_one() { count++; }
double Ingredient::get_price() { return ((price + packing_price) * (1 - discount)); }
void Ingredient::set_discount(double dis = 0.1) { discount = dis; }
void Ingredient::set_off_discount() { discount = 0; }
Unique_Ingredient::Unique_Ingredient(shared_ptr <Ingredient> ing) {
	name = ing->get_name();
	ingredients.push_back(ing);
}
void Unique_Ingredient::add_to_ingredients(shared_ptr <Ingredient> ing) { ingredients.push_back(ing); }
string Unique_Ingredient::get_name() { return name; }
int Unique_Ingredient::get_count() {
	calc_count();
	return count;
}
int Ingredient::get_count() { return count; }
void Unique_Ingredient::remove_ingredients(shared_ptr <Ingredient> ing) {
	int index = find_index_ingredient(name, ingredients, ing->get_supplier_name());
	ingredients.erase(index + ingredients.begin());
}
void Unique_Ingredient::calc_count() {
	int cnt{ 0 };
	for (int i = 0; i < ingredients.size(); i++)
		cnt += ingredients[i]->get_count();
	count = cnt;
}
void Unique_Ingredient::check_discount() {
	calc_count();
	if (count >= 20 && discount_status == false) {
		for (int i = 0; i < ingredients.size(); i++)
			ingredients[i]->set_discount();
		discount_status = true;
	}
	else if (count < 20 && discount_status == true) {
		for (int i = 0; i < ingredients.size(); i++)
			ingredients[i]->set_off_discount();
		discount_status = false;
	}
	
}