#include <iostream>
#include <vector>

const int POSSIBLE_MOVES = 4;
const int row_delta[POSSIBLE_MOVES] = { 1, 0, -1, 0 };
const int col_delta[POSSIBLE_MOVES] = { 0, 1, 0, -1 };

using namespace std;

void initialize(vector < vector <int> >& fillplace) {
    for (int i = 0; i < fillplace.size(); i++) {
        for (int j = 0; j < fillplace[0].size(); j++) {
            fillplace[i][j] = -1;
        }
    }
}
void print(vector <vector <int>>& output_way) {
    for (int i = output_way.size() - 1; i >= 0; i--) {
        if (output_way[i].size() != 0) {
            for (int j = 0; j < output_way[i].size(); j++) {
                cout << output_way[i][j] << " ";
            }
            return;
        }
    }
}
bool find_tour(int move_no, int current_row, int current_col, vector <vector<int> >& places, vector <vector<int> >& fillplace,
    vector <vector<int> >& output_way, int max_move) {

    if (move_no == max_move)
        return true;

    for (int move = 0; move < POSSIBLE_MOVES; move++) {
        int new_row = current_row + row_delta[move];
        int new_col = current_col + col_delta[move];

        if (new_row < 0 || new_row >= places.size() || new_col < 0 || new_col >= places[0].size() ||
            abs(places[new_row][new_col] - places[current_row][current_col]) != 1)
            continue;

        if (fillplace[new_row][new_col] != -1)
            continue;

        fillplace[new_row][new_col] = move_no + 1;
        output_way[max_move - 1].push_back(places[new_row][new_col]);
        if (find_tour(move_no + 1, new_row, new_col, places, fillplace, output_way, max_move))
            return true;
        fillplace[new_row][new_col] = -1;
        if (output_way[max_move - 1].size() > 1)
            output_way[max_move - 1].pop_back();
    }
    return false;
}

void solve(vector <vector<int> >& places, vector <vector<int> >& fillplace, vector <vector<int> >& output_way) {
    int i;
    bool founded_size;
    for (int k = 0; k < places[0].size() * places.size(); k++) {
        founded_size = 0;
        for (int j = 0; j < places.size(); j++) {
            for (i = 0; i < places[0].size(); i++) {
                fillplace[j][i] = 1;
                output_way[k].push_back(places[j][i]);
                if (find_tour(1, j, i, places, fillplace, output_way, k + 1)) {
                    initialize(fillplace);
                    founded_size = 1;
                    break;
                }
                else {
                    output_way[k].pop_back();
                    fillplace[j][i] = -1;
                }
            }
            if (founded_size)
                break;
        }
    }
    print(output_way);
}

int main() {
    int n, m;
    cin >> n >> m;
    vector <vector<int> > places(m, vector <int>(n, -1));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> places[i][j];
        }
    }
    vector <vector<int> > fillplace(m, vector <int>(n, -1));
    vector <vector<int> > output_way( n * m );
    solve(places, fillplace, output_way);
    cout << endl;
    return 0;
}