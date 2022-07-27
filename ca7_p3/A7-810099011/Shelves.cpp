#include "Shelves.hpp"
using namespace std;
Shelve::Shelve(string name_, int id_, O_User* user_) {
		name = name_;
		user = user_;
		id = id_;
		cout << id << endl;
	}
void Shelve::glimpse_shelve_recipes() {
	for (int i = 0; i < recipes.size(); i++) {
		recipes[i]->glimpse_recipe();
		cout << endl;
	}
}
void Shelve::glimpse_shelve() {
	cout << id << " ";
	cout << name << endl;
}
void Shelve::add_recipe(std::shared_ptr<Recipe> res) {
	recipes.push_back(res); 
}
bool Shelve::is_right_user(O_User* user_) {
	if (user == user_)
		return true;
	else
		return false;
}
string Shelve::get_name() { return name; }
int Shelve::get_id() { return id; }
void Shelve::remove_recipe(int rec_id) {
	int index = find_index_recipe(rec_id,recipes);
	if (index != NOT_FOUND_INDEX)
		recipes.erase(index + recipes.begin());
	else
		throw Bad_Request_Error();
}
string Shelve::glimpse_shelve_html(){
		ostringstream body;
    if (name.size() >= 30){
        name = name.substr(0, 28) + "...";
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
    << "</style>"
    << "<div class='gallery'>"
    << "<img src=" << '"' << "https://cdn2.vectorstock.com/i/1000x1000/25/01/food-products-on-shop-shelf-supermarket-shopping-vector-23292501.jpg" 
	<< '"' << "alt='Recipe_img' width='60' height='40'>"
    << "<div class='desc' style='font-size:15px'> &#127869 " << name 
	<< "<br /> &#128240 " << id << "</div>"
    << "<form action='/shelves' method='get'>"
    << "<input type='hidden' id='custid' name='id' value='" << id << "'>"
    << "<div class='form-group'>"
    << "<button type='submit' class='button1'>Read More</button>"
    << "  </div> </div> </form>";
    return body.str();
}
string Shelve::show_full_shelve_html(){
	ostringstream body;
	body 
	<< "<div style='background-color:tomato;color:white;padding:20px;'>"
    << "<h1>" << name << "</h1>"
	<< "<h3>" << "ID" << "</h3>"
	<< "<h4>" << id << "</h4></div>";
	for (int i = 0; i < recipes.size(); i++)
		body << recipes[i]->glimpse_recipe_html(id);
	return body.str();
}