#ifndef INGREDIENT_H_
#define INGREDIENT_H_ "INGREDIENT_H_"
#include "Includes_And_Defines.hpp"
#include "Users.hpp"
class Supplier;
class Ingredient {
public:
	Ingredient(std::string title, Supplier* supplier, double price, int count, double packing);
	void set_discount(double discount);
	void set_off_discount();
	std::string get_supplier_name();
	bool is_right_ingredient(std::string title, std::string supplier_name);
	void edit(double price, int count);
	std::string get_name();
	double get_price();
	void get_sold();
	void increase_one();
	int get_count();
private:
	std::string name;
	int count{ 0 };
	double price{ 0.0 };
	double packing_price{ 0.0 };
	double discount{ 0.0 };
	Supplier* supplier;
};

class Unique_Ingredient {
public:
	Unique_Ingredient(std::shared_ptr <Ingredient> ingredient);
	void add_to_ingredients(std::shared_ptr <Ingredient> ingredient);
	void remove_ingredients(std::shared_ptr <Ingredient> ingredient);
	std::string get_name();
	int get_count();
	void check_discount();
private:
	std::vector <std::shared_ptr <Ingredient> > ingredients;
	std::string name;
	int count;
	void calc_count();
	bool discount_status{ false };
};
#endif