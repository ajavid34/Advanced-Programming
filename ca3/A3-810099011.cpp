#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstring>
#define OUTPUT_MAP_NAME "out.ppm"

using namespace std;

const int max_num_of_neighbors = 4;
const int row_delta[max_num_of_neighbors] = { 1, 0, -1, 0 };
const int col_delta[max_num_of_neighbors] = { 0, 1, 0, -1 };

struct person {
	double happines{ 0.0 };
	char race{ ' ' };
	bool state{ true };
};
typedef vector <vector <person> > Society;

int line_count(string filename) {
	int number_of_lines = 0;
	string line;
	ifstream myfile(filename);
	while (getline(myfile, line))
		++number_of_lines;
	myfile.close();
	return number_of_lines;
}
int char_perline_count(string filename) {
	ifstream myfile(filename);
	string line;
	getline(myfile, line);
	myfile.close();
	return line.size();
}
Society read_map_file(string filename) {
	int num_of_lines = line_count(filename);
	int word_per_line = char_perline_count(filename);
	Society people(num_of_lines);
	person temp;
	ifstream places(filename);
	for (int i = 0; i < num_of_lines; i++) {
		for (int j = 0; j < word_per_line; j++) {
			places >> temp.race;
			people[i].push_back(temp);
		}
	}
	places.close();
	return people;
}

Society make_society(int argc, char* argv[]) {
	Society people;
	for (int i = 0; i < argc; i++)
		if (!strcmp(argv[i], "-f")) {
			people = read_map_file(argv[i + 1]);
		}
	return people;
}
bool is_valid_place(int new_row, int new_col, const Society& society) {
	if (new_row < 0 || new_row >= society.size() || new_col < 0 || new_col >= society[0].size())
		return 0;
	else
		return 1;
}
void update_agent_state(double blue, double red, person& agent, double happiness_threshold) {
	if (agent.race == 'B')
		agent.happines = blue / (blue + red);
	else
		agent.happines = red / (blue + red);
	if (agent.happines >= happiness_threshold)
		agent.state = false;
	else
		agent.state = true;
}
void measure_happiness(Society& society, double happiness_threshold) {
	for (int current_row = 0; current_row < society.size(); current_row++) {
		for (int current_col = 0; current_col < society[0].size(); current_col++) {
			int blue_num{ 0 };
			int red_num{ 0 };
			if (society[current_row][current_col].race == 'E')
				continue;
			for (int move = 0; move < max_num_of_neighbors; move++) {
				int new_row = current_row + row_delta[move];
				int new_col = current_col + col_delta[move];

				if (!is_valid_place(new_row, new_col, society))
					continue;
				else if (society[new_row][new_col].race == 'E') {
					if (society[current_row][current_col].race == 'B')
						blue_num++;
					else
						red_num++;
				}
				else if (society[new_row][new_col].race == 'B')
					blue_num++;
				else
					red_num++;
			}
			update_agent_state(1.0 * blue_num, 1.0 * red_num, society[current_row][current_col], happiness_threshold);
		}
	}

}
bool is_unstable(const Society& society) {
	for (int i = 0; i < society.size(); i++) {
		for (int j = 0; j < society[0].size(); j++) {
			if (society[i][j].race == 'E')
				continue;
			if (society[i][j].state)
				return true;
		}
	}
	return false;
}
void swap_place(person& a, person& b) {
	person temp;
	temp = a;
	a = b;
	b = temp;
}
bool is_available(person dest, person current) {
	if (dest.state && dest.race != current.race)
		return 1;
	else
		return 0;
}
void jump(Society& society) {
	for (int current_row = 0; current_row < society.size(); current_row++) {
		for (int current_col = 0; current_col < society[0].size(); current_col++) {
			if (society[current_row][current_col].race == 'E')
				continue;
			if (society[current_row][current_col].state) {
				while (true) {
					int dest_row = rand() % society.size();
					int dest_col = rand() % society[0].size();
					if (dest_row == current_row && dest_col == current_col)
						continue;
					if (is_available(society[dest_row][dest_col], society[current_row][current_col])) {
						swap_place(society[current_row][current_col], society[dest_row][dest_col]);
						break;
					}
				}
			}
		}
	}
}
void print_map(const Society& society) {
	for (int i = 0; i < society.size(); i++) {
		for (int j = 0; j < society[0].size(); j++) {
			cout << society[i][j].race;
		}
		cout << endl;
	}
	cout << endl;
}
void unhappy_count(const Society& society) {
	int count{ 0 };
	for (int i = 0; i < society.size(); i++) {
		for (int j = 0; j < society[0].size(); j++) {
			if (society[i][j].race == 'E')
				continue;
			if (society[i][j].state)
				count++;
		}
	}
	cout << count << endl;
}
void make_them_happy(Society& society, double happiness_threshold, int step_num) {
	measure_happiness(society, happiness_threshold);
	while (is_unstable(society) && step_num != 0) {
		jump(society);
		measure_happiness(society, happiness_threshold);
		step_num--;
	}
}
void ppm_file_map(const Society& society) {
	int dimx = society[0].size() * 100, dimy = society.size() * 100;
	ofstream ppm_file(OUTPUT_MAP_NAME, ios_base::out | ios_base::binary);
	ppm_file << "P6" << endl << dimx << ' ' << dimy << endl << "255" << endl;
	for (int i = 0; i < society.size(); i++) {
		for (size_t k = 0; k < 100; k++) {

			for (int j = 0; j < society[0].size(); j++) {
				for (size_t l = 0; l < 100; l++) {
					if (society[i][j].race == 'R')
						ppm_file << (char)(255) << (char)(0) << (char)(0);
					else if (society[i][j].race == 'B')
						ppm_file << (char)(0) << (char)(0) << (char)(255);
					else
						ppm_file << (char)(255) << (char)(255) << (char)(255);
				}
			}
		}
	}
}
void report(const Society& society) {
	unhappy_count(society);
	print_map(society);
	ppm_file_map(society);
}
int main(int argc, char* argv[]) {
	int step_num{ -1 };
	double happiness_threshold{ 0.3 };
	Society society = make_society(argc, argv);
	for (int i = 0; i < argc; i++) {
		if (!strcmp(argv[i], "-s"))
			step_num = stoi(argv[i + 1]);
		else if (!strcmp(argv[i], "-p"))
			happiness_threshold = 0.01 * stoi(argv[i + 1]);
	}
	make_them_happy(society, happiness_threshold, step_num);
	report(society);
	return 0;
}