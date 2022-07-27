#include "Voter.hpp"
using namespace std;

Voter::Voter(double sc, O_User* user) {
	user_score = sc;
	voter_user = user;
}
double Voter::get_score() { return user_score; }
void Voter::change_vote(double new_vote) { user_score = new_vote; }
string Voter::get_name() { return voter_user->get_username(); }