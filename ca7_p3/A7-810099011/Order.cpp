#include "Order.hpp"

using namespace std;

bool Order::is_right_ingredient(string name, const shared_ptr<Ingredient>& ing, double price) {
	if (ing->get_name() == name && (ing->get_price() < price || price == -1.0) && ing->get_count() > 0)
		return true;
	else
		return false;
}
shared_ptr<Ingredient> Order::find_best_ingredient(string name, const vector <shared_ptr<Ingredient> >& all_ings) {
	double price = -1.0;
	shared_ptr<Ingredient> chosen_ing{ NULL };
	for (int i = 0; i < all_ings.size(); i++)
		if (is_right_ingredient(name, all_ings[i], price)) {
			price = all_ings[i]->get_price();
			chosen_ing = all_ings[i];
		}
	return chosen_ing;
}
Order::Order(shared_ptr<Recipe> rec, const vector <shared_ptr<Ingredient> >& all_ings, double user_money) {
	recipe_id = rec->get_id();
	vector <shared_ptr<Ingredient> > selected_ings;
	vector<string> ing_names = rec->get_ingredients_name();
	shared_ptr<Ingredient> temp;
	for (int i = 0; i < ing_names.size(); i++) {
		temp = find_best_ingredient(ing_names[i], all_ings);
		int index = find_supplier_orders(temp->get_supplier_name());
		if (index == NOT_FOUND_INDEX)
			order_recipe.push_back(Supplier_Order(temp));
		else
			order_recipe[index].add_ingredient(temp);
		selected_ings.push_back(temp);
	}
	calc_price();
	if (user_money < total_price)
		throw Bad_Request_Error();
	all_sold(selected_ings);
	sort_order();
}
void Order::all_sold(const vector <shared_ptr<Ingredient> >& sel_ings) {
	for (int i = 0; i < sel_ings.size(); i++)
		sel_ings[i]->get_sold();
}
Supplier_Order::Supplier_Order(shared_ptr<Ingredient> ing) {
	ingredients.push_back(*ing);
	supplier_name = ing->get_supplier_name();
}
string Supplier_Order::get_supplier_name() { return supplier_name; }
void Supplier_Order::add_ingredient(shared_ptr<Ingredient> ing) { ingredients.push_back(*ing); }
int Order::find_supplier_orders(string name) {
	for (int i = 0; i < order_recipe.size(); i++) 
		if (order_recipe[i].get_supplier_name() == name)
			return i;
	return NOT_FOUND_INDEX;
}
double Supplier_Order::get_price() { 
	total_price = calc_price_order(ingredients);
	return total_price;
}
void Order::calc_price() { total_price = calc_price_order(order_recipe); }
double Order::get_price() { return total_price; }
void Order::order_view() {
	for (int i = 0; i < order_recipe.size(); i++)
		order_recipe[i].view();
	cout << floor(total_price) << endl;
}
void Supplier_Order::view() {
	cout << supplier_name << " ";
	for (int i = 0; i < ingredients.size(); i++)
		cout << ingredients[i].get_name() << " ";
	cout << endl;
}
void Order::sort_order() {
	sort(order_recipe.begin(), order_recipe.end(), [](Supplier_Order a, Supplier_Order b) {
		return a.get_supplier_name() < b.get_supplier_name();
		});
	for (int i = 0; i < order_recipe.size(); i++) 
		order_recipe[i].sort_ingredients();
}
void Supplier_Order::sort_ingredients() {
	sort(ingredients.begin(), ingredients.end(), [](Ingredient a, Ingredient b) {
		return a.get_name() < b.get_name();
		});
}
int Order::get_recipe_id() { return recipe_id; }
template< typename T >
double calc_price_order(vector <T>& thing) {
	double pr{ 0 };
	for (int i = 0; i < thing.size(); i++)
		pr += thing[i].get_price();
	return pr;
}