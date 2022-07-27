#include "App.hpp"
#include "Errors.hpp"
using namespace std;
int main() {
	App goodeats;
	string command;
	int command_count;
	while (getline(cin,command)) {
		istringstream sstream(command);
		try {
			command_count = goodeats.count_words(command);
			goodeats.user_interface(sstream, command_count);
		}
		catch (Permission_Error& p) {
			cout << p.what();
		}
		catch (Bad_Request_Error& b) {
			cout << b.what();
		}
		catch (Not_Found_Error& n) {
			cout << n.what();
		}
	}
	return 0;
}