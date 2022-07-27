#ifndef SORTANDFIND_H_
#define SORTANDFIND_H_ "SORTANDFIND_H_"
#include "Includes_And_Defines.hpp"
#include "Users.hpp"
#include "Recipes.hpp"
#include "Shelves.hpp"
class Recipe;
class Shelve;
std::shared_ptr <Recipe> find_recipe(int id, const std::vector <std::shared_ptr<Recipe> >& recipe);
int find_index_recipe(int id, const std::vector <std::shared_ptr<Recipe> >& recipe);
std::shared_ptr<Shelve> find_shelve(int id, const std::vector <std::shared_ptr<Shelve> >& shelves); 
void sort_recipes(std::vector <std::shared_ptr<Recipe> >& recipes);
void sort_shelves_id(std::vector <std::shared_ptr<Shelve> >& shelves);
#endif