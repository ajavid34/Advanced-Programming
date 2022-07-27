#include "Recipes.hpp"
using namespace std;
vector<string> Recipe::read_recipe_input(istringstream& inputs){
	string temp;
	vector<string>info(5);
		inputs >> temp;
	if (temp != INGREDINTS_KEYWORD)
		throw Not_Found_Error();
	inputs >> info[0];
	inputs >> temp;
	if (temp != VEGETARIAN_KEYWORD)
		throw Not_Found_Error();
	inputs >> info[1];
	if (info[1]!= NO_KEYWORD && info[1] != YES_KEYWORD)
		throw Not_Found_Error();
	inputs >> temp;
	if (temp != MINUTES_TO_READY_KEYWORD)
		throw Not_Found_Error();
	inputs >> info[2];
	inputs >> temp;
	if (temp != TAGS_KEYWORD)
		throw Not_Found_Error();
	inputs >> info[3];
	inputs >> temp;
	if (temp != IMAGE_ADDRESS_KEYWORD)
		throw Not_Found_Error();
	inputs >> info[4];
	return info;
}
Recipe::Recipe(string title_, int id_, Chef* ch, istringstream& inputs) {
	vector<string>info;
	string temp;
	title = title_;
	id = id_;
	chef = ch;
	info = read_recipe_input(inputs);
	replace(info[0].begin(), info[0].end(), COMMA, ' ');
	stringstream line_stream(info[0]);	
	while (line_stream >> temp)
		ingredients.push_back(temp);
	if (info[1] == NO_KEYWORD)
		vegetarian_status = false;
	else
		vegetarian_status = true;
	minutes_to_ready = stoi(info[2]);
	replace(info[3].begin(), info[3].end(), COMMA, ' ');
	stringstream line_stream1(info[3]);	
	while (line_stream1 >> temp)
		tags.push_back(temp);
	image_address = info[4];
	cout << id << endl;
}
void Recipe::show_full_recipe() {
	cout << id << endl;
	cout << title << endl;
	cout << "vegetarian: ";
	if (vegetarian_status)
		cout << YES_KEYWORD << endl;
	else
		cout << NO_KEYWORD << endl;
	cout << "ingredients: [";
	for (int i = 0; i < ingredients.size(); i++) {
		if(i != ingredients.size() - 1)
			cout << ingredients[i] << ", ";
		else
			cout << ingredients[i] << "]" << endl;
	}
	cout << "minutes to ready: " << minutes_to_ready << endl;
	cout << "tags: [";
	for (int i = 0; i < tags.size(); i++) {
		if (i != tags.size() - 1)
			cout << tags[i] << ", ";
		else
			cout << tags[i] << "]" << endl;
	}
	cout.precision(1);
	cout << "rating: " << fixed << ceil(score * 10) / 10 << endl;
}
void Recipe::glimpse_recipe() {
	cout << id << " ";
	cout << title << " ";
	if (vegetarian_status)
		cout << YES_KEYWORD << " ";
	else
		cout << NO_KEYWORD << " ";
	cout << minutes_to_ready;
}
void Recipe::get_rated(double scr, O_User* user) {
	int index = find_voter_index(user->get_username());
	if (index != NOT_FOUND_INDEX)
		throw Bad_Request_Error();
	Voter votr(scr, user);
	voters.push_back(votr);
	calc_score();
}
void Recipe::calc_score() {
	double sum {0.0};
	for (int i = 0; i < voters.size(); i++)
		sum += voters[i].get_score();
	score = sum / voters.size();
}
void Recipe::change_rate(double scr, O_User* user) {
	int index = find_voter_index(user->get_username());
	if (index == NOT_FOUND_INDEX)
		throw Bad_Request_Error();
	voters[index].change_vote(scr);
	calc_score();
}
int Recipe::find_voter_index(string name) {
	for (int i = 0; i < voters.size(); i++)
		if (voters[i].get_name() == name)
			return i;
	return NOT_FOUND_INDEX;
}
bool Recipe::is_in_given_time_limit(int min_m, int max_m) {
	return (min_m <= minutes_to_ready && max_m >= minutes_to_ready);
}
bool Recipe::is_in_given_rate_limit(double min_r, double max_r) {
	return (min_r <= score && max_r >= score);
}
bool Recipe::has_tag(string tg) {
	for (int i = 0; i < tags.size(); i++)
		if (tags[i] == tg)
			return true;
	return false;
}
