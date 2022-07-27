#include "Filters.hpp"
using namespace std;
Filter::Filter() {}
Tag_Filter::Tag_Filter() {}
Veg_Filter::Veg_Filter() {}
Time_to_Ready_Filter::Time_to_Ready_Filter() {}
Rate_Filter::Rate_Filter() {}
void Filter::set_filter() {}
void Tag_Filter::set_filter(string tg) { 
	state = true;
	tag = tg; 
}
void Veg_Filter::set_filter() { state = true;}
void Time_to_Ready_Filter::set_filter(int min_m, int max_m) {
	state = true;
	min_minutes = min_m;
	max_minutes = max_m;
}
void Rate_Filter::set_filter(double min_r, double max_r) {
	state = true;
	if (min_r < MIN_RATING || max_r > MAX_RATING)
		throw Bad_Request_Error();
	min_rating = min_r;
	max_rating = max_r;
}
bool Filter::eligible_recipe(shared_ptr <Recipe> recipe) { return true; }
bool Tag_Filter::eligible_recipe(shared_ptr <Recipe> recipe) {
	if (!state)
		return true;
	else
		return recipe->has_tag(tag);
}
bool Veg_Filter::eligible_recipe(shared_ptr <Recipe> recipe) {
	if (!state)
		return true;
	else
		return recipe->is_vegetarian();
}
bool Time_to_Ready_Filter::eligible_recipe(shared_ptr <Recipe> recipe) {
	if (!state)
		return true;
	else
		return recipe->is_in_given_time_limit(min_minutes, max_minutes);
}
bool Rate_Filter::eligible_recipe(shared_ptr <Recipe> recipe) {
	if (!state)
		return true;
	else
		return recipe->is_in_given_rate_limit(min_rating, max_rating);
}