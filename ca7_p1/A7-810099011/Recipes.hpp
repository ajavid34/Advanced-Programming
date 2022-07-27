#ifndef RECIPES_H_
#define RECIPES_H_ "RECIPES_H_"
#include "Includes_And_Defines.hpp"
#include "Users.hpp"
#include "Voter.hpp"
#include "Errors.hpp"
class Chef;
class Voter;
class O_User;
class Recipe {
public:
	Recipe(std::string title_, int id_, Chef* chef, std::istringstream& inputs);
	void show_full_recipe();
	void glimpse_recipe();
	std::string get_title() { return title; }
	int get_id() { return id; }
	void get_rated(double sc, O_User* user);
	void calc_score();
	int find_voter_index(std::string name);
	void change_rate(double sc, O_User* user);
	double get_score() { return score; }
	int get_num_voters() { return voters.size(); }
	bool has_tag(std::string);
	bool is_vegetarian() { return vegetarian_status; }
	bool is_in_given_time_limit(int min_m, int max_m);
	bool is_in_given_rate_limit(double min_r, double max_r);
private:
	std::vector<std::string> read_recipe_input(std::istringstream& inputs);
	std::string title;
	int id;
	double score{ 0.0 };
	std::vector<Voter> voters;
	bool vegetarian_status;
	std::vector <std::string> ingredients;
	int minutes_to_ready;
	std::vector <std::string> tags;
	std::string image_address;
	Chef* chef;
};
#endif