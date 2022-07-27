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

string Recipe::get_img(){ return image_address; }
string Recipe::get_veg(){
	if (vegetarian_status)
		return "Yes";
	else
		return "No";
}
string Recipe::glimpse_recipe_html(int shel_id){
	ostringstream body;
    if (title.size() >= 30){
        title = title.substr(0, 28) + "...";
    }
    body
    << "<style>"
    << ".button1 {"
    << "width: 300px;"
    << "background-color: tomato;"
    << "border: none;"
    << "color: white;"
    << "padding: 16px 32px;"
    << "text-align: center;"
    << "text-decoration: none;"
    << "display: inline-block;"
    << "font-size: 16px;"
    << "transition-duration: 0.4s;"
    << "cursor: pointer;"
    << "}"
    << ".button1:hover {"
    << "background-color: red;"
    << "color: white;"
    << "}"
    << "</style>";
    body << "<div class='gallery'>"
    << "<img src=" << '"' << image_address << '"' << "alt='Recipe_img' width='60' height='40'>";
	body.precision(1);
	body
    << "<div class='desc' style='font-size:15px'> &#127828 " << title << "<br /> &#11088 " << fixed << ceil(score * 10) / 10 << "<br />&#127807 " 
	<< get_veg() << "<br />&#128338 " << minutes_to_ready 
	<< "<br /> &#128240 " << id << "</div>"
    << "<form action='/recipe' method='get'>"
    << "<input type='hidden' id='custid' name='id' value='" << id << "'>"
    << "<div class='form-group'>"
    << "<button type='submit' class='button1'>Read More</button> </form>";
	if (shel_id != NOT_FOUND_INDEX)
		body << shalves_req_html(shel_id);
    body << "  </div> </div> ";
    return body.str();
}
string Recipe::shalves_req_html(int shel_id){
	ostringstream body;
	body
	<< "<br /> <br />"
	<< "<form action='/delete_recipe_shelves' method='get'>"
    << "<input type='hidden' id='cust' name='id_shelve' value='" << shel_id << "'>"
	<< "<input type='hidden' id='custid' name='id' value='" << id << "'>"
    << "<div class='form-group'>"
    << "<button type='submit' class='button1'>Delete Recipe</button>"
    << "</div> </form>";
	return body.str();
}
Recipe::Recipe(string name,string ings,string tgs,string img_add,string veg,int min_to_ready, int id_,Chef* ch){
	string temp;
	title = name;
	replace(ings.begin(), ings.end(), COMMA, ' ');
	stringstream line_stream(ings);	
	while (line_stream >> temp)
		ingredients.push_back(temp);
	replace(tgs.begin(), tgs.end(), COMMA, ' ');
	stringstream line_stream1(tgs);	
	while (line_stream1 >> temp)
		tags.push_back(temp);
	image_address = img_add;
	if (veg == NO_KEYWORD)
		vegetarian_status = false;
	else
		vegetarian_status = true;
	minutes_to_ready = min_to_ready;
	id = id_;
	chef = ch;
}
string Recipe::show_full_recipe_html(string username){
	ostringstream body;
    body
	<< header_recipe_page()
    << "<body>"
    << "<ul>"
    << "<li><a href='/home'>Home</a></li>";
	if (username != chef->get_username())
    	body << "<li><a href='/my_shelves'>My Shelves</a></li>";
	body
    << "<li style='float:right'><a class='active' href='/logout'>&#128100 Logout "
    << username << "</a></li>"
    << "</ul>"
    << "<br /> <br />";
	body
    << "<div class='gallery'>"
    << "<img src=" << '"' << image_address << '"' << "alt='Recipe_img' width='360' height='360'>"
    << "</div>"
    << "<div style='background-color:tomato;color:white;padding:20px;'>"
    << "<h1>" << title << "</h1>"
	<< "<h3>" << "ID" << "</h3>"
	<< "<h4>" << id << "</h4>"
	<< "<h3>" << "Vegegetarian" << "</h3>"
	<< "<p>" << get_veg() << "</p>"
	<< "<h3>" << "Time to Ready" << "</h3>"
	<< "<p>" << minutes_to_ready << "</p>"
	<< "<h3>" << "Chef" << "</h3>"
    << "<p>" << chef->get_username() << "</p>"
	<< "<h3>" << "Tags" << "</h3>"
	<< "<p> [";
	for (int i = 0; i < tags.size(); i++) {
		if (i != tags.size() - 1)
			body << tags[i] << ", ";
		else
			body << tags[i] << "]" << endl;
	}
	body << "</p>"
	<< "<h3>" << "Ingredients" << "</h3>"
	"<p> [";
	for (int i = 0; i < ingredients.size(); i++) {
		if(i != ingredients.size() - 1)
			body << ingredients[i] << ", ";
		else
			body << ingredients[i] << "]" << endl;
	}
	body << "</p>"
	<< "<h3>" << "Score" << "</h3>";
	body.precision(1);
	body
	<< "<p>" << fixed << ceil(score * 10) / 10 << "</p>";
	int rd_score = round(score);
	for (int i = 0; i < rd_score; i++)
		body << "<span class='fa fa-star checked'></span>";
	for (int i = 0; i < (5 - rd_score); i++)
		body << "<span class='fa fa-star'></span>";
    return body.str();
}
string Recipe::header_recipe_page(){
	ostringstream body;
    body
    << "<!DOCTYPE html>"
    << "<html>"
    << "<head> <title>Recipe</title>"
	<< "<link rel='stylesheet' href='https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css'>"
    << "<style>"
    << "ul {"
    << "list-style-type: none;"
    << "margin: 0;"
    << "padding: 0;"
    << "overflow: hidden;"
    << "background-color: orange;"
    << "}"
    << ".button1 {"
    << "width: 300px;"
    << "background-color: Chartreuse;"
    << "border: none;"
    << "color: black;"
    << "padding: 16px 32px;"
    << "text-align: center;"
    << "text-decoration: none;"
    << "display: inline-block;"
    << "font-size: 16px;"
    << "transition-duration: 0.4s;"
    << "cursor: pointer;"
    << "}"
    << ".button1:hover {"
    << "background-color: DarkGreen;"
    << "color: white;"
    << "}"
    << "li {"
    << "float: left;"
    << "}"
    << "li a {"
    << "display: block;"
    << "color: white;"
    << "text-align: center;"
    << "padding: 14px 16px;"
    << "text-decoration: none;"
    << "}"
    << "li a:hover:not(.active) {"
    << "background-color: tomato;"
    << "}"
    << ".active {"
    << "background-color: tomato;"
    << "}"
	<< ".checked {"
  	<< "color: yellow;"
	<< "}"
	<< "img {"
	<< "width='400'"
	<< "height='380'"
	<< "object-fit :cover;"
    << "border-radius: 2px;"
	<< "}"
    << "</style>"
    << "</head>";
	return body.str();
}