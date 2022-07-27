#ifndef ORDER_H_
#define ORDER_H_ "ORDER_H_"
#include "Includes_And_Defines.hpp"
#include "Ingredient.hpp"
#include "Recipes.hpp"
#include "Errors.hpp"
class Supplier_Order {
public:
	Supplier_Order(std::shared_ptr<Ingredient> ingredient);
	void add_ingredient(std::shared_ptr<Ingredient> ingredient);
	std::string get_supplier_name();
	double get_price();
	void sort_ingredients();
	void view();
private:
	std::string supplier_name;
	std::vector<Ingredient> ingredients;
	double total_price;
};

class Order {
public:
	Order(std::shared_ptr<Recipe> rec, const std::vector<std::shared_ptr<Ingredient> >& all_ingredients, double user_money);
	void order_view();
	double get_price();
	int get_recipe_id();
private:
	std::vector <Supplier_Order> order_recipe;
	double total_price;
	int find_supplier_orders (std::string name);
	void calc_price();
	std::shared_ptr<Ingredient> find_best_ingredient(std::string title, const std::vector<std::shared_ptr<Ingredient> >& all_ingredients);
	bool is_right_ingredient(std::string name, const std::shared_ptr<Ingredient>& ingredient, double price);
	void sort_order();
	void all_sold(const std::vector<std::shared_ptr<Ingredient> >& some_ingredients);
	int recipe_id;
};
template< typename T >
double calc_price_order(std::vector <T>& thing);
#endif