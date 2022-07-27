#ifndef FILTERS_H_
#define FILTERS_H_ "FILTERS_H_"
#include "Includes_And_Defines.hpp"
#include "Recipes.hpp"
#include "Errors.hpp"
class Filter {
public:
	Filter();
	virtual bool eligible_recipe(std::shared_ptr <Recipe> recipe);
	virtual void set_filter();
	void set_off() { state = false; }
protected:
	bool state{ false };
};
class Tag_Filter : public Filter {
public:
	Tag_Filter();
	bool eligible_recipe(std::shared_ptr <Recipe> recipe);
	void set_filter(std::string tg);
private:
	std::string tag;
};
class Veg_Filter : public Filter {
public:
	Veg_Filter();
	bool eligible_recipe(std::shared_ptr <Recipe> recipe);
	void set_filter();
	void set_not_veg();
	void set_off();
private:
	bool ops_state{ false };
};
class Time_to_Ready_Filter : public Filter {
public:
	Time_to_Ready_Filter();
	bool eligible_recipe(std::shared_ptr <Recipe> recipe);
	void set_filter(int min_m, int max_m);
private:
	int min_minutes{ 0 };
	int max_minutes{ 0 };
};
class Rate_Filter : public Filter {
public:
	Rate_Filter();
	bool eligible_recipe(std::shared_ptr <Recipe> recipe);
	void set_filter(double min_r, double max_r);
private:
	double min_rating{ 0.0 };
	double max_rating{ 0.0 };
};
#endif