#ifndef SORTANDFIND_H_
#define SORTANDFIND_H_ "SORTANDFIND_H_"
#include "Includes_And_Defines.hpp"
#include "Users.hpp"
#include "Recipes.hpp"
#include "Shelves.hpp"
#include "Ingredient.hpp"
class Recipe;
class Shelve;
class Ingredient;
std::shared_ptr <Recipe> find_recipe(int id, const std::vector <std::shared_ptr<Recipe> >& recipe);
std::shared_ptr <Ingredient> find_ingredient(std::string name, std::string supplier_name, const std::vector <std::shared_ptr<Ingredient> >& ingredient);
int find_index_recipe(int id, const std::vector <std::shared_ptr<Recipe> >& recipe);
int find_index_ingredient(std::string name, const std::vector <std::shared_ptr<Ingredient> >& ingredient, std::string supplier_name = "");
std::shared_ptr<Shelve> find_shelve(int id, const std::vector <std::shared_ptr<Shelve> >& shelves); 
void sort_recipes(std::vector <std::shared_ptr<Recipe> >& recipes);
void sort_shelves_id(std::vector <std::shared_ptr<Shelve> >& shelves);
#endif