#include "Sort_And_Find.hpp"
using namespace std;
shared_ptr <Recipe> find_recipe(int id, const vector <shared_ptr<Recipe> >& recipe) {
	for (int i = 0; i < recipe.size(); i++)
		if (recipe[i]->get_id() == id)
			return recipe[i];
	return NULL;
}
int find_index_recipe(int id, const vector <shared_ptr<Recipe> >& recipe) {
	for (int i = 0; i < recipe.size(); i++)
		if (recipe[i]->get_id() == id)
			return i;
	return NOT_FOUND_INDEX;
}
shared_ptr<Shelve> find_shelve(int id, const vector <shared_ptr<Shelve> >& shelves) {
	for (int i = 0; i < shelves.size(); i++)
		if (shelves[i]->get_id() == id)
			return shelves[i];
	return NULL;
}
void sort_recipes(vector <shared_ptr<Recipe> >& recipes) {
	sort(recipes.begin(), recipes.end(), [](shared_ptr<Recipe> a, shared_ptr<Recipe> b) {
		return a->get_title() < b->get_title();
		});
}
void sort_shelves_id(vector <shared_ptr<Shelve> >& shelves) {
	sort(shelves.begin(), shelves.end(), [](shared_ptr<Shelve> a, shared_ptr<Shelve> b) {
		return a->get_id() < b->get_id();
		});
}