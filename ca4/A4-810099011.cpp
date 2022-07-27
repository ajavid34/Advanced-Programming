#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
class Person;

class Station {
public:
	Station(string name, int taffy_price);
	string get_name() { return name; }
	int get_price() { return taffy_price; }
private:
	int taffy_price;
	string name;
};

class Train {
public:
	Train(Station* start_station, Station* dest_station, int travel_time, int break_time, int id);
	void add_train_passenger(Person* people) { passengers.push_back(people); }
	void delete_passengers();
	string get_status() { return last_status; }
	void show_info(int time);
	Station* get_start_station() { return current_station; }
	Station* get_dest_station() { return dest_station; }
	void update_change(int time);
	int get_estimate(int t);
	void change_way();
	int get_id() { return id; }
	void update_passengers_change(vector <Person>& people);
private:
	Station* dest_station{ NULL };
	Station* start_station{ NULL };
	int break_time;
	int travel_time;
	int id;
	int last_change_time{ 0 };
	vector <Person*> passengers;
	Station* current_station{ NULL };
	string last_status{ "resting" };
};

class Person {
public:
	Person(int taffy_per_hour, int id);
	void add_station(Station* station) { trip_stations.push_back(station); }
	void catch_train(Train* train);
	bool is_arrived();
	void get_of_train();
	void buy_taffy(){ taffy_spent += taffy_per_hour * (trip_stations[num_current_station]->get_price()); }
	void show_info();
	string get_current_station_name() { return trip_stations[num_current_station]->get_name(); }
	string get_next_station_name() { return trip_stations[num_current_station + 1]->get_name(); }
	string get_status() { return last_status; }
	bool is_right_train(Train train);
	int get_current_train_id();
private:
	int taffy_per_hour;
	int taffy_spent{ 0 };
	int id;
	int num_current_station{ 0 };
	Train* current_train{ NULL };
	vector <Station*> trip_stations;
	string last_status{ "in station" };
};
Person::Person(int th, int id_) {
	taffy_per_hour = th;
	id = id_ + 1;
}
Station::Station(string name_, int tafpr) {
	name = name_;
	taffy_price = tafpr;
}
Train::Train(Station* start, Station* dest, int trtime, int brtime, int id_) {
	start_station = start;
	dest_station = dest;
	travel_time = trtime;
	break_time = brtime;
	id = id_ + 1;
	current_station = start;
}
void Train::update_change(int time) {
	last_change_time = time;
	if (!last_status.compare("resting"))
		last_status = "moving";
	else
		last_status = "resting";
}
int Train::get_estimate(int t) {
	if (!last_status.compare("resting"))
		return abs(t - last_change_time - break_time);
	else
		return abs(t - last_change_time - travel_time);
}
void Train::change_way() {
	Station* temp = dest_station;
	dest_station = start_station;
	start_station = temp;
	current_station = start_station;
}
void Person::catch_train(Train* train) {
	current_train = train;
	last_status = "on train";
}
bool Person::is_right_train(Train train) {
	if (!train.get_start_station()->get_name().compare(get_current_station_name()) &&
		!train.get_dest_station()->get_name().compare(get_next_station_name()))
		return true;
	else
		return false;
}
void Train::delete_passengers() {
	while (passengers.size() != 0) {
		passengers[passengers.size() - 1]->get_of_train();
		passengers.pop_back();
	}
}
void Train::show_info(int t) {
	cout << "status : "<< last_status << endl;
	cout << "estimated remaining time : " << get_estimate(t) << endl;
	cout << "next station : " << dest_station->get_name() << endl;
	cout << "passengers count : " << passengers.size() << endl;
}
void Person::show_info() {
	cout << "status : " << last_status << endl;
	cout << "spent : " << taffy_spent << endl;
	if (current_train == NULL)
		cout << "current station " << get_current_station_name() << endl;
	else
		cout << "current train " << current_train->get_id() << endl;
}
bool Person::is_arrived() {
	if (!get_next_station_name().
		compare(trip_stations[trip_stations.size() - 1]->get_name()))
		return true;
	else
		return false;
}
void Person::get_of_train() {
	if (is_arrived())
		last_status = "arrived";
	else
		last_status = "in station";
	num_current_station++;
	current_train = NULL;
}
int Person::get_current_train_id() {
	if (current_train != NULL)
		return current_train->get_id();
	else
		return -1;
}
void Train::update_passengers_change(vector <Person>& people) {
	for (int i = 0; i < passengers.size(); i++) 
		for (int j = 0; j < people.size(); j++) 
			if (people[j].get_current_train_id() == id)
				passengers[i] = &people[j];
}
void take_train(vector <Person>& people, Train& train) {
	for (int i = 0; i < people.size(); i++) {
		if (!people[i].get_status().compare("in station")) {
			if (people[i].is_right_train(train)) {
				people[i].catch_train(&train);
				train.add_train_passenger(&people[i]);
			}
		}
	}
}
void do_next_train_step(vector <Train>& trains, int time) {
	for (int i = 0; i < trains.size(); i++) {
		if (!trains[i].get_status().compare("resting") && trains[i].get_estimate(time) == 0) {
			trains[i].update_change(time);
		}
		else if (!trains[i].get_status().compare("moving") && trains[i].get_estimate(time) == 0) {
			trains[i].update_change(time);
			trains[i].delete_passengers();
			trains[i].change_way();
		}
	}
}
void check_all_activities(vector <Person>& people, vector <Train>& trains, int time) {
	for (int i = 0; i < trains.size(); i++) {
		if (!trains[i].get_status().compare("resting"))
			take_train(people, trains[i]);
	}
	for (int i = 0; i < people.size(); i++)
		if (!people[i].get_status().compare("in station"))
			people[i].buy_taffy();
	do_next_train_step(trains, time);
}
bool is_all_arrived(vector <Person>& people) {
	for (int i = 0; i < people.size(); i++) {
		if (abs(people[i].get_status().compare("arrived")))
			return false;
	}
	return true;
}
Station* find_station(vector <Station>& stations, string station_name) {
	for (int i = 0; i < stations.size(); i++)
		if (!station_name.compare(stations[i].get_name()))
			return &stations[i];
}
void add_passenger(vector <Person>& people, vector <Station>& stations) {
	int taffy_addiction;
	string temp;
	cin >> taffy_addiction;
	people.push_back(Person(taffy_addiction, people.size()));
	getline(cin, temp);
	istringstream iss(temp, istringstream::in);
	string station_name;
	while (iss >> station_name) 
		people[people.size() - 1].add_station(find_station(stations, station_name));
}
void add_station(vector <Station>& stations) {
	int taffy_price;
	string temp;
	cin >> temp;
	cin >> taffy_price;
	stations.push_back(Station(temp, taffy_price));
}
void add_train(vector <Train>& trains, vector <Station>& stations) {
	string temp;
	int break_time;
	int travel_time;
	cin >> temp;
	Station* start = find_station(stations, temp);
	cin >> temp;
	Station* dest = find_station(stations, temp);
	cin >> travel_time;
	cin >> break_time;
	trains.push_back(Train(start, dest, travel_time, break_time, trains.size()));
}
void finish(vector <Person>& people, vector <Train>& trains, int& time) {
	while (!is_all_arrived(people)) {
		time += 1;
		check_all_activities(people, trains, time);
	}
}
void advance_time(vector <Person>& people, vector <Train>& trains, int& time) {
	int time_advance;
	cin >> time_advance;
	while (time_advance > 0) {
		time += 1;
		check_all_activities(people, trains, time);
		time_advance--;
	}
}
void update_train_passengers(vector <Person>& people, vector <Train>& trains) {
	for (int i = 0; i < trains.size(); i++)
		trains[i].update_passengers_change(people);
}
void user_interface(string inner, vector <Person>& people, vector <Train>& trains, vector <Station>& stations, int& time) {
	string temp;
		if (!inner.compare("add_passenger")) {
			add_passenger(people, stations);
			if (time > 0)
				update_train_passengers(people,trains);
			cout << "OK\n";
		}
		else if (!inner.compare("add_station")){
			add_station(stations);
			cout << "OK\n";
		}
		else if (!inner.compare("add_train")) {
			add_train(trains, stations);
			cout << "OK\n";
		}
		else if (!inner.compare("advance_time")) {
			advance_time(people, trains, time);
			cout << "OK\n";
		}
		else if (!inner.compare("finish")) {
			finish(people, trains, time);
			cout << "OK\n";
		}
		else if (!inner.compare("show_passenger_info")) {
			int id;
			cin >> id;
			people[id - 1].show_info();
		}
		else if (!inner.compare("show_train_info")) {
			int id;
			cin >> id;
			trains[id - 1].show_info(time);
		}
}
int main() {
	int time{ 0 };
	string inner;
	vector <Person> people;
	vector <Train> trains;
	vector <Station> stations;
	while (cin >> inner) {
		user_interface(inner, people, trains, stations, time);
	}
}