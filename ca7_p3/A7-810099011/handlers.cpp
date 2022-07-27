#include "handlers.hpp"

using namespace std;

Response *SignupForm::callback(Request *req) {
  if (sessions->find(req->getSessionId()) != sessions->end())
      return Response::redirect("/home");
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  ostringstream body;
  body
  << form_html();
  if (status->used_username){
    body
    << already_signup_html();
    status->reset();
  }
  body
  << "</body>" << endl
  << "</html>" << endl;
  res->setBody(body.str());
  return res;
}

Response *ShowDynamicHome::callback(Request *req) {
  if (sessions->find(req->getSessionId()) != sessions->end())
    return Response::redirect("/home");
  else {
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    ostringstream body;
    body
    << not_login_home_page_html();
    if (status->has_logged_out){
      body
      << logout_html();
      status->reset();
    }
    body
    << "</body>" << endl
    << "</html>" << endl;
    res->setBody(body.str());
    return res;
  }
}

Response *CheckSignup::callback(Request *req) {
  string username = req->getQueryParam(USERNAME_KEYWORD);
  string password = req->getQueryParam(PASSWORD_KEYWORD);
  string password_copy = req->getQueryParam(PASSWORD_KEYWORD);
  string roll = req->getQueryParam(ROLL_KEYWORD);
  try {
    User* user = app->create_new_user(username, password_copy, roll);
    Response *res = Response::redirect("/home");
    res->setSessionId(username);
    sessions->insert(make_pair(username, user));
    return res;
	}
  catch (Bad_Request_Error& b) {
	  status->used_username = true;
    return Response::redirect("/signup");
  }
}
Response *ShowLoggedinHome::callback(Request *req){
  if (sessions->find(req->getSessionId()) == sessions->end())
      return Response::redirect("/");
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  ostringstream body;
  body << html_main_page(req);
  if (app->get_active_roll(sessions->find(req->getSessionId())->second->get_username()) == CHEF_KEYWORD)
    body << handle_chef(req);
  else
    body << handle_user(req);
  body
  << "</body>"
  << "</html>";
  res->setBody(body.str());
  return res;
}

Response *ShowLoginForm::callback(Request *req){
  if (sessions->find(req->getSessionId()) != sessions->end())
      return Response::redirect("/home");
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  ostringstream body;
  body
  << form_html();
  if (status->wrong_username_or_password){
    body
    << login_error_html();
    status->reset();
  }
  body
  << "</body>" << endl
  << "</html>" << endl;
  res->setBody(body.str());
  return res;
}
Response *CheckLogin::callback(Request *req){
  string username = req->getQueryParam(USERNAME_KEYWORD);
  string password = req->getQueryParam(PASSWORD_KEYWORD);
  status->used_username = app->is_already_signup(username) ? true :false ;
  try {
    Response *res = Response::redirect("/home");
    res->setSessionId(username);
    app->login_user(username,password);
    return res;
	}
  catch (Bad_Request_Error& b) {
    status->wrong_username_or_password = true;
    return Response::redirect("/login");
  }
}
Response *CheckLogout::callback(Request *req){
  Response *res = Response::redirect("/");
  res->setSessionId("");
  app->reset_filters_html();
  status->has_logged_out = true;
  return res;
}

string ShowLoggedinHome::handle_chef(Request *req){
  ostringstream body;
  body 
  << add_recipe_chef_html()
  << app->show_chef_recipe(sessions->find(req->getSessionId())->second->get_username());
  return body.str();
}
Response *AddRecipe::callback(Request *req){
  if (sessions->find(req->getSessionId()) == sessions->end())
        return Response::redirect("/");
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  add_recipe(req);
  return res = Response::redirect("/home");
}
void AddRecipe::add_recipe(Request *req){
  string title= req->getQueryParam(TITLE_KEYWORD);
	string ingredients= req->getQueryParam(INGREDINTS_KEYWORD);
	string tags= req->getQueryParam(TAGS_KEYWORD);
  string img= req->getQueryParam(IMAGE_ADDRESS_KEYWORD);
  string veg= req->getQueryParam(VEGETARIAN_KEYWORD);
  int time= stoi(req->getQueryParam(MINUTES_TO_READY_KEYWORD));
  app->add_recipe(sessions->find(req->getSessionId())->second->get_username(),title,ingredients,tags,img,veg,time);
}
Response *ShowRecipe::callback(Request *req){
  if (sessions->find(req->getSessionId()) == sessions->end())
    return Response::redirect("/");
  try {int rec_id = stoi(req->getQueryParam(ID_KEYWORD));
    ostringstream body;
    body
    << app->show_recipe_id_html(rec_id,sessions->find(req->getSessionId())->second->get_username(), status);
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    res->setBody(body.str());
    status->reset();
  return res;
  } catch (Not_Found_Error& n) {
  	return ErrorHandler(n.what());
  }
}
Response* DeleteRecipe::callback(Request *req){
  if (sessions->find(req->getSessionId()) == sessions->end())
    return Response::redirect("/");
  try{
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    delete_recipe(req);
    return res = Response::redirect("/home");
  } catch (Not_Found_Error& n) {
		return ErrorHandler(n.what());
	}
}
void DeleteRecipe::delete_recipe(Request *req){
  int rec_id = stoi(req->getQueryParam(ID_KEYWORD));
  app->delete_recipe_id(sessions->find(req->getSessionId())->second->get_username(),rec_id);
}
string ShowLoggedinHome::handle_user(Request *req){
  ostringstream body;
  handle_filters(req);
  body << show_filters(req)
  << app->show_all_recipes_html();
  return body.str();
}
string ShowLoggedinHome::show_filters(Request *req){
  ostringstream body;
  body 
  << add_filter_user_html();
  if (status->wrong_filter) {
    body << "<p>&#10060 Filter was Not Successful.</p>";
    status->wrong_filter = false;
  }
  else if (status->en_filter) {
    body << "<p>&#9989 Filter was Successful.</p>";
    status->en_filter = false;
  }
  return body.str();
}
void ShowLoggedinHome::handle_filters(Request *req){
  if (req->getQueryParam(MIN_RATING_KEYWORD) != "" && req->getQueryParam(MAX_RATING_KEYWORD) != ""){
    int min_star = stoi(req->getQueryParam(MIN_RATING_KEYWORD));
    int max_star = stoi(req->getQueryParam(MAX_RATING_KEYWORD));
    if (min_star > max_star)
      status->wrong_filter = true;
    else {
      app->set_filters(RATINGS_COMMAND,min_star,max_star);
      status->en_filter = true;
    }
  }
  if (req->getQueryParam(MIN_MINUTES_KEYWORD) != "" && req->getQueryParam(MAX_MINUTES_KEYWORD) != "") {
    int min_time = stoi(req->getQueryParam(MIN_MINUTES_KEYWORD));
    int max_time = stoi(req->getQueryParam(MAX_MINUTES_KEYWORD));
    if (min_time > max_time)
      status->wrong_filter = true;
    else {
      app->set_filters(TIME_KEYWORD,min_time,max_time);
      status->en_filter = true;
    }
  }
  if (req->getQueryParam(VEGETARIAN_KEYWORD) == YES_KEYWORD){
    app->set_filters(VEGETARIAN_KEYWORD);
    status->en_filter = true;
  }
  if (req->getQueryParam(VEGETARIAN_KEYWORD) == NO_KEYWORD){
    app->set_filters(NOT_VEGETARIAN_FILTER_KEYWORD);
    status->en_filter = true;
  }
}
Response *ResetFilters::callback(Request *req){
  if (sessions->find(req->getSessionId()) == sessions->end())
        return Response::redirect("/");
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  app->reset_filters_html();
  return res = Response::redirect("/home");
}
Response *RateRecipe::callback(Request *req){
  if (sessions->find(req->getSessionId()) == sessions->end())
        return Response::redirect("/");
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  rate(req);
  ostringstream address;
  address << "/recipe" << "?" << "id=" << req->getQueryParam(ID_KEYWORD);
  return res = Response::redirect(address.str());
}
void RateRecipe::rate(Request *req){
  int rec_id = stoi(req->getQueryParam(ID_KEYWORD));
  int rate = stoi(req->getQueryParam(RATINGS_COMMAND));
  app->rate_recipe_id(sessions->find(req->getSessionId())->second->get_username(),rec_id, rate, status);
}
Response *ShowMyShelves::callback(Request *req){
  if (sessions->find(req->getSessionId()) == sessions->end())
    return Response::redirect("/");
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  ostringstream body;
  body << html_main_page(req);
  body << handle_shelves(req)
  << "</body>"
  << "</html>";
  res->setBody(body.str());
  return res;
}
string ShowMyShelves::handle_shelves(Request *req){
  ostringstream body;
  body 
  << add_shelves_html()
  << app->show_user_shelves(sessions->find(req->getSessionId())->second->get_username());
  return body.str();
}
Response *AddShelves::callback(Request *req){
  if (sessions->find(req->getSessionId()) == sessions->end())
        return Response::redirect("/");
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  add_shelves(req);
  return res = Response::redirect("/my_shelves");
}
void AddShelves::add_shelves(Request *req){
  string title= req->getQueryParam(TITLE_KEYWORD);
  app->add_shelve(sessions->find(req->getSessionId())->second->get_username(),title);
}
Response *ShowShelves::callback(Request *req){
  if (sessions->find(req->getSessionId()) == sessions->end())
      return Response::redirect("/");
  try {
    int sh_id = stoi(req->getQueryParam(ID_KEYWORD));
    ostringstream body;
    body << html_main_page(req);
    body << add_shelve_recipe(req,sh_id);
    body << app->show_shelve_id_html(sh_id);
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    res->setBody(body.str());
    status->reset();
    return res;
  } catch (Not_Found_Error& n) {
		return ErrorHandler(n.what());
	}
}
string ShowShelves::add_shelve_recipe(Request *req,int sh_id){
  ostringstream body;
  body 
  << add_shelve_recipe_html(sh_id);
  if (status->wrong_add_rec_to_shelve) {
    body << "<p>&#10060 Add Chosen Recipe was Not Successful.</p>";
    status->wrong_filter = false;
  }
  if (status->add_rec_to_shelve) {
    body << "<p>&#9989 Recipe Added to Shelf Successfully..</p>";
    status->add_rec_to_shelve = false;
  }
  body << "<br /> <br />"
  << "</div>" << endl;
  return body.str();
}
Response *AddShelvesRecipe::callback(Request *req){
  if (sessions->find(req->getSessionId()) == sessions->end())
        return Response::redirect("/");
  int id_rec= stoi(req->getQueryParam("id_to_add"));
  int id_shel= stoi(req->getQueryParam("id_shelve"));
  try{
    app->add_recipe_shelve(sessions->find(req->getSessionId())->second->get_username(),id_rec,id_shel);
    status->add_rec_to_shelve = true;
  }
  catch (Bad_Request_Error& b){
    status->wrong_add_rec_to_shelve = true;
  }
  catch (Not_Found_Error& n) {
			status->wrong_add_rec_to_shelve = true;
	}
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  ostringstream address;
  address << "/shelves" << "?" << "id=" << id_shel;
  return res = Response::redirect(address.str());
}
Response *DeleteRecipeShelves::callback(Request *req){
  if (sessions->find(req->getSessionId()) == sessions->end())
        return Response::redirect("/");
  int id_rec= stoi(req->getQueryParam("id"));
  int id_shel= stoi(req->getQueryParam("id_shelve"));
  app->delete_recipe_shelve_html(sessions->find(req->getSessionId())->second->get_username(),id_rec,id_shel);
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  ostringstream address;
  address << "/shelves" << "?" << "id=" << id_shel;
  return res = Response::redirect(address.str());
}
Response* ErrorHandler(string massage) {
  Response* res = new Response;
  res->setHeader("Content-Type", "text/html");
  ostringstream body;
  body 
  << "<!DOCTYPE html>"
  << "<style>"
  << "* {box-sizing: border-box;font-family: Verdana, Geneva, Tahoma, sans-serif;}"
  << ".button {background-color: white;border: "
  << "2px solid green;color: black;padding: 15px 32px;text-align: center;text-decoration: black;display: inline-block;font-size: 16px;}"
  << "a:hover {background-color: lightgreen;}"
  << ".message {margin: 0;position: absolute;top: 50%;left: 50%;margin-right: -50%;"
  << "transform: translate(-50%, -50%);text-align: center;font-size: 30px;}"
  << "</style>"
  << "<body>"
  << "<div class=\"message\">"
  << "<p>Oops! An Error Occured While Handling Your Request</p>"
  << "<p>[Error Code: 500, Message: "
  << massage
  << "]</p><a href=\"/\" class=\"button\">Back To Home</a>"
  << "</div></body></html>";
  res->setBody(body.str());
  return res;
}
string ShowShelves::add_shelve_recipe_html(int sh_id){
  ostringstream body;
  body 
  << "</div>"
  << "<br /> <br />"
  << "<form action='/add_shelves_recipe' method='get'>" << endl
  << "<input name='id_to_add' type='number' placeholder='ID Recipe You Want Add' , required/>" << "<br />" << endl
  << "<input type='hidden' id='cust' name='id_shelve' value='" << sh_id << "'>"
  << "<br /> <br />"
  << "<button type='submit' class='button1'>Add Recipe</button>"
  << "<br /> <br />"
  << "</form>" << endl;
  return body.str();
}
string ShowMyShelves::add_shelves_html(){
  ostringstream body;
  body 
  << "</div>"
  << "<br /> <br />"
  << "<form action='/add_shelves' method='get'>" << endl
  << "<input name='title' type='text' placeholder='Title' , required/>" << "<br />" << endl
  << "<br /> <br />"
  << "<button type='submit' class='button1'>Add Shelf</button>"
  << "<br /> <br />"
  << "</form>" << endl
  << "</div>" << endl;
  return body.str();
}
string ShowLoggedinHome::add_filter_user_html(){
  ostringstream body;
  body 
  << "<form action='/home'>"
  << "<label for='quantity_min' style='color:tomato;'>Rating Filter  </label>"
  << "<input type='number' id='quantity_min' name='min_rating' min='1' max='5' placeholder='minimum rating (1 to 5)'>"
  << "<input type='number' id='quantity_max' name='max_rating' min='1' max='5' placeholder='maximum rating (1 to 5)'>"
  << "<br /> <br />"
  << "<label for='q_min' style='color:tomato;'>Time Filter  </label>"
  << "<input type='number' id='q_min' name='min_minutes' min='1' placeholder='(minimum time to ready)'>"
  << "<input type='number' id='q_max' name='max_minutes' min='1' placeholder='(maximum time to ready)'>"
  << "<br /> <br />"
  << "<label class='container' for='Yes'>Show Only Vegetarian Recipe<br>" << "<br />" << endl
  << "<input type='radio' id='Yes' name='vegetarian' value='Yes'>" << "<br />" << endl
  << "<span class='radio_class'></span></label>"
  << "<label class='container' for='No'>Show Only Not Vegetarian Recipe<br>" << "<br />" << endl
  << "<input type='radio' id='No' name='vegetarian' value='No'>" << "<br />" << endl
  << "<span class='radio_class'></span></label>"
  << "<button type='submit' class='button1'>Filter</button>"
  << "</form>"
  << "<form action='/reset_filters'>"
  << "<input type='submit' class='button11' value='Reset All Filters' />"
  << "</form>";
  return body.str();
}
string ShowLoggedinHome::add_recipe_chef_html(){
  ostringstream body;
  body
  << "</div>"
  << "<br /> <br />"
  << "<form action='/add_recipe' method='get'>" << endl
  << "<input name='title' type='text' placeholder='Title' , required/>" << "<br />" << endl
  << "<input name='ingredients' type='text' placeholder='Ingredients' , required/>" << "<br />" << endl
  << "<input name='tags' type='text' placeholder='Tags' , required/>" << "<br />" << endl
  << "<input name='image_address' type='text' placeholder='Image Address' , required/>" << "<br />" << endl
  << "<input name='minutes_to_ready' type='number' placeholder='Minutes to Ready' min='0', required/>" << "<br />" << endl
  << "<label  class='container' for='Yes'>Vegetarian Recipe<br>" << "<br />" << endl
  << "<input type='radio' id='Yes' name='vegetarian' value='Yes' checked>" << "<br />" << endl
  << "<span class='radio_class'></span></label>"
  << "<label  class='container' for='No'> Not Vegetarian Recipe<br>" << "<br />" << endl
  << "<input type='radio' id='No' name='vegetarian' value='No'>" << "<br />" << endl
  << "<span class='radio_class'></span></label>"
  << "<button type='submit' class='button1'>Add Recipe</button>"
  << "<br /> <br />"
  << "</form>" << endl
  << "</div>" << endl;
  return body.str();
}
string ShowLoginForm::login_error_html(){
  ostringstream body;
  body
  << "<div style='background-color:tomato;color:white;padding:1px;'>"
  << "<p>&#10071 Username/Password incorrect.</p>" << endl
  << "</div>"
  << "<br />";
  return body.str();
}
string ShowLoginForm::form_html(){
  ostringstream body;
  body
  << "<html>" << endl
  << "<head><title>Login Form</title>" << endl
  << "<style>"
  << form_css()
  << "</head>"
  << "<body style='background-color: orange; text-align: center;'>" << endl
  << "<div style='background-color:tomato;color:white;padding:1px;'>"
  << "<h1>Please fill the form below</h1>" << endl
  << "</div>"
  << "<br /> <br />"
  << "<form action='/check_login' method='get'>" << endl
  << "<input name='username' type='text' placeholder='Username' , required/>" << "<br />" << endl
  << "<br /> <br />" << endl
  << "<input name='password' type='text' placeholder='Password' , required/>" << "<br />" << endl
  << "<button class='button1' type='submit' >Login!</button>" << endl
  << "</form>" << endl
  << "<br /> <br />" << endl
  << "<form action='/signup' method='get'>" << endl
  << "<button class='button1' type='submit' >Don't Have Account ?, Signup First</button>" << endl
  << "</form>" << endl
  << "</div>" << endl;
  return body.str();
}
string ShowDynamicHome::logout_html(){
  ostringstream body;
  body
  << "<br /> <br /> <br />" << endl
  << "<div style='background-color:tomato;color:white;padding:1px;'>"
  << "<p>&#9989 Logout Successful.</p>" << endl
  << "</div>";
  return body.str();
}
string ShowDynamicHome::not_login_home_page_html(){
  ostringstream body;
  body
  << "<html>" << endl
  << "<head><title>Login or Signup Required</title>" << endl
  << "<style>"
  << "a:link, a:visited {"
  << "background-color: tomato;"
  << "color: white;"
  << "padding: 15px 25px;"
  << "text-align: center;"
  << "text-decoration: none;"
  << "display: inline-block;"
  << "}"
  << "a:hover, a:active {"
  << "background-color: red;"
  << "}"
  << "img{"
  << "border-radius: 50px;"
  << "}"
  << "</style>"
  << "</head>"
  << "<body style='background-color: orange; text-align: center;'>" << endl
  << "<img src= "<< '"' << "https://i.pinimg.com/originals/73/86/c6/7386c6649d14ba4620953a5afc827a37.jpg" << '"' << "alt='Goodeats' />"<< endl
  << "<br /> <br />" << endl
  << "<h1>Welcome to Goodeats!</h1>" << endl
  << "<h2>You need to login first!</h2>" << endl
  << "<br /> <br />" << endl
  << "<a href='/login'>Login</a>" << endl
  << "<br /> <br />" << endl
  << "<a href='/signup'>Signup</a>" << endl;
  return body.str();
}
string SignupForm::already_signup_html(){
  ostringstream body;
  body
  << "<br /> <br />"
  << "<div style='background-color:tomato;color:white;padding:1px;'>"
  << "<p>&#10071 Username already taken.</p>" << endl
  << "</div>"
  << "<br />"
  << "<br /> <br />" << endl
  << "<form action='/login' method='get'>" << endl
  << "<button class='button1' type='submit' >If You Have Account ,Click Here To Login</button>" << endl
  << "</form>" << endl;
  return body.str();
}
string SignupForm::form_html(){
  ostringstream body;
  body
  << "<html>" << endl
  << "<head><title>Signup Form</title>" << endl
  << form_css()
  << "</head>"
  << "<body style='background-color: orange; text-align: center;'>" << endl
  << "<div style='background-color:tomato;color:white;padding:1px;'>"
  << "<h1>Please fill the form below</h1>" << endl
  << "</div>"
  << "<br /> <br />"
  << "<form action='/check_signup' method='get'>" << endl
  << "<input name='username' type='text' placeholder='Username', required />" << "<br />" << endl
  << "<br /> <br />"
  << "<input name='password' type='text' placeholder='Password', required />" << "<br />" << endl
  << "<br /> <br />"
  << "<br /> <br />"
  << "<div class='wrapper'>"
  << "<input type='radio' name='roll' id='chef' value='chef' checked>"
  << "<input type='radio' name='roll' id='user' value='user'>"
  << "<label for='chef' class='option chef'>"
  << "<div class='dot'></div>"
  << "<span>Chef</span>"
  << "</label>"
  << "<label for='user' class='option user'>"
  << "  <div class='dot'></div>"
  << "  <span>User</span>"
  << " </label>"
  << "</div>"
  << "<br /> <br />"
  << "<br /> <br />"
  << "<div class='form-group'>"
  << "<button type='submit' class='button1'>Signup!</button>"
  << "</div>" << endl
  << "</form>" << endl
  << "</div>" << endl;
  return body.str();
}
string GoodeatsHanler::form_css(){
  ostringstream body;
  body
  << "<style>"
  << "a:link, a:visited {"
  << "background-color: tomato;"
  << "color: white;"
  << "padding: 15px 25px;"
  << "text-align: center;"
  << "text-decoration: none;"
  << "display: inline-block;"
  << "}"
  << "a:hover, a:active {"
  << "background-color: red;"
  << "}"
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
  << "   .wrapper{"
  << "   display: inline-flex;"
  << "   background: orange;"
  << "   height: 100px;"
  << "   width: 300px;"
  << "   align-items: center;"
  << "   justify-content: space-evenly;"
  << "   border-radius: 5px;"
  << "   padding: 20px 15px;"
  << "   box-shadow: 5px 5px 30px rgba(0,0,0,0.2);"
  << " }"
  << " .wrapper .option{"
  << "   background: #fff;"
  << "   height: 100%;"
  << "   width: 100%;"
  << "   display: flex;"
  << "   align-items: center;"
  << "   justify-content: space-evenly;"
  << "   margin: 0 10px;"
  << "   border-radius: 5px;"
  << "   cursor: pointer;"
  << "   padding: 0 10px;"
  << "   border: 2px solid lightgrey;"
  << "   transition: all 0.3s ease;"
  << " }"
  << " .wrapper .option .dot{"
  << "   height: 20px;"
  << "   width: 20px;"
  << "   background: #d9d9d9;"
  << "   border-radius: 50%;"
  << "   position: relative;"
  << " }"
  << " .wrapper .option .dot::before{"
  << "   position: absolute;"
  << "   content: '';"
  << "   top: 4px;"
  << "   left: 4px;"
  << "   width: 12px;"
  << "   height: 12px;"
  << "   background: #0069d9;"
  << "   border-radius: 50%;"
  << "   opacity: 0;"
  << "   transform: scale(1.5);"
  << "   transition: all 0.3s ease;"
  << " }"
  << " input[type='radio']{"
  << "   display: none;"
  << " }"
  << " #chef:checked:checked ~ .chef,"
  << " #user:checked:checked ~ .user{"
  << "   border-color: #0069d9;"
  << "   background: #0069d9;"
  << " }"
  << " #chef:checked:checked ~ .chef .dot,"
  << " #user:checked:checked ~ .user .dot{"
  << "   background: #fff;"
  << " }"
  << " #chef:checked:checked ~ .chef .dot::before,"
  << " #user:checked:checked ~ .user .dot::before{"
  << "   opacity: 1;"
  << "   transform: scale(1);"
  << " }"
  << " .wrapper .option span{"
  << "   font-size: 20px;"
  << "   color: #808080;"
  << " }"
  << " #chef:checked:checked ~ .chef span,"
  << " #user:checked:checked ~ .user span{"
  << "   color: #fff;"
  << " }"
  << "input[type=text]{"
  << "width: 40%;"
  << "padding: 12px 20px;"
  << "margin: 8px 0;"
  << "box-sizing: border-box;"
  << "border: 2px solid red;"
  << "border-radius: 4px; }"
  << "</style>";
  return body.str();
}
string GoodeatsHanler::html_main_page(Request *req){
  ostringstream body;
  body
  << "<!DOCTYPE html>"
  << "<html>"
  << "<head>"
  << "<title> Home </title>"
  << "<style>"
  << "ul {"
  << "list-style-type: none;"
  << "margin: 0;"
  << "padding: 0;"
  << "overflow: hidden;"
  << "background-color: orange;"
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
  << "</style>"
  << "</head>"
  << "<body>"
  << "<ul>"
  << "<li><a href='/home'>Home</a></li>";
  if (app->get_active_roll(sessions->find(req->getSessionId())->second->get_username()) == "user")
    body << "<li><a href='/my_shelves'>My Shelves</a></li>";
  body
  << "<li style='float:right'><a class='active' href='/logout'>&#128100 Logout "
  << sessions->find(req->getSessionId())->second->get_username() << "</a></li>"
  << "</ul>"
  << "</body>"
  << "</html>"
  << "<!DOCTYPE html>"
  << "<html>"
  << "<head>"
  << "<style>"
  << "div.gallery {"
  << "margin: 5px;"
  << "border: 1px solid #ccc;"
  << "float: left;"
  << "width: 300px;"
  << "border-radius: 2px;"
  << "}"
  << "div.gallery:hover {"
  << "border: 1px solid #777;"
  << "}"
  << "div.gallery img {"
  << "width: 300px;"
  << "height: 300px;"
  << "object-fit :cover;"
  << "border-radius: 2px;"
  << "}"
  << "div.desc {"
  << "padding: 10px;"
  << "text-align: center;"
  << "}"
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
  << ".button11 {"
  << "width: 300px;"
  << "background-color: yellow;"
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
  << ".button11:hover {"
  << "background-color: DarkGreen;"
  << "color: white;"
  << "}"
  << "input[type=text],input[type=number]{"
  << "width: 15%;"
  << "padding: 6px 10px;"
  << "margin: 3px 0;"
  << "box-sizing: border-box;"
  << "border: 2px solid red;"
  << "border-radius: 4px; }"
  << ".container {"
  << "position: relative;"
  << "padding-left: 30px;"
  << "margin-bottom: 10px;"
  << "cursor: pointer;"
  << "font-size: 14px;"
  << "}"
  << ".container input {"
  << "position: absolute;"
  << "opacity: 0;"
  << "}"
  << ".radio_class {"
  << "position: absolute;"
  << "top: 0;"
  << "left: 0;"
  << "height: 20px;"
  << "width: 20px;"
  << "background-color: LightGray;"
  << "border-radius: 25%;"
  << "}"
  << ".container:hover input ~ .radio_class {"
  << "background-color: orange;"
  << "}"
  << ".container input:checked ~ .radio_class {"
  << "background-color: tomato;"
  << "}"
  << ".container .radio_class:after {"
  << "top: 10px;"
  << "left: 10px;"
  << "width: 10px;"
  << "height: 10px;"
  << "border-radius: 80%;"
  << "background: orange;"
  <<  "}"
  << "</style>"
  << "</head>"
  << "<body>";
  return body.str();
}