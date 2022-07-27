#include "handlers.hpp"
#include "my_server.hpp"
#include <iostream>
#include "App.hpp"

using namespace std;

int main(int argc, char **argv) {
  App goodeats;
  map <string, User*> sessions;
  Status status;
	status.reset();
  try {
    MyServer server(5000);
    server.get("/login", new ShowLoginForm(&goodeats, &status, &sessions));
		server.get("/check_login", new CheckLogin(&goodeats, &status, &sessions));
		server.get("/", new ShowDynamicHome(&goodeats, &status, &sessions));
		server.get("/signup", new SignupForm(&goodeats, &status, &sessions));
		server.get("/check_signup", new CheckSignup(&goodeats, &status, &sessions));
		server.get("/home", new ShowLoggedinHome(&goodeats, &status, &sessions));
    server.get("/logout", new CheckLogout(&goodeats, &status, &sessions));
    server.get("/add_recipe", new AddRecipe(&goodeats, &status, &sessions));
    server.get("/recipe", new ShowRecipe(&goodeats, &status, &sessions));
    server.get("/delete_recipe", new DeleteRecipe(&goodeats, &status, &sessions));
    server.get("/rate", new RateRecipe(&goodeats, &status, &sessions));
    server.get("/reset_filters", new ResetFilters(&goodeats, &status, &sessions));
    server.get("/my_shelves", new ShowMyShelves(&goodeats, &status, &sessions));
    server.get("/add_shelves", new AddShelves(&goodeats, &status, &sessions));
    server.get("/shelves", new ShowShelves(&goodeats, &status, &sessions));
    server.get("/add_shelves_recipe", new AddShelvesRecipe(&goodeats, &status, &sessions));
    server.get("/delete_recipe_shelves", new DeleteRecipeShelves(&goodeats, &status, &sessions));
    server.setNotFoundErrPage("static/404.html");
    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  } catch(const invalid_argument& ia){
    cerr << "Invalid argument: " << ia.what() << '\n';
  } 
}
