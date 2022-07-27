#ifndef VOTER_H_
#define VOTER_H_ "VOTER_H_"
#include "Includes_And_Defines.hpp"
#include "Users.hpp"
class O_User;

class Voter {
public:
	Voter(double sc, O_User* user);
	double get_score();
	void change_vote(double new_vote);
	std::string get_name();
private:
	double user_score;
	O_User* voter_user;
};
#endif