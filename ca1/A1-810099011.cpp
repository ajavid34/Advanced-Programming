#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void initialize(vector < vector <string> >& delivery_output, int s) 
{
	for (int i = 0; i < delivery_output.size(); i++) {
		for (int j = 0; j < s; j++) {
			delivery_output[i].push_back(" ");
		}
	}
}

int check_repeat(vector <int>& group, int row) 
{
	if (find(group.begin(), group.end(), row) != group.end())
		return 1;
	else
		return 0;
}

void final_check_print(vector < vector <string> >& std_id, vector < vector <string> >& delivery_output, vector < vector <int> >& where, int s)
{
	int a, b;
	for (int i = 0; i < delivery_output.size(); i++) {
		for (int j = 0; j < s; j++) {
			if (!delivery_output[i][j].compare(" ")) {
				a = rand() % std_id.size();
				while (check_repeat(where[i], a) != 0)
					a = rand() % std_id.size();
				b = rand() % 3;
				delivery_output[i][j] = std_id[a][b];
				where[i][j] = a;
			}
			cout << delivery_output[i][j] << ' ';
		}
		cout << endl;
	}
}

int main()
{
	int  k, a, s;
	int row, col;
	string temp;
	cin >> k >> a >> s;
	vector < vector <string> > std_id(k);
	vector < vector <string> > delivery_output(a);
	vector < vector <int> > where(a, vector <int>(s, -1));
	initialize(delivery_output, s);
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < 3; j++) {
			row = rand() % a;
			col = rand() % s;
			if (check_repeat(where[row], i) == 0 && !delivery_output[row][col].compare(" ")) {
				cin >> temp;
				std_id[i].push_back(temp);
				delivery_output[row][col] = std_id[i][j];
				where[row][col] = i;
			}
			else
				j--;
		}
	}
	cout << '\n' << endl;
	final_check_print(std_id ,delivery_output ,where ,s );
}
