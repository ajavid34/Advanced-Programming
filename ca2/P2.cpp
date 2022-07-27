#include <iostream>
#include<vector>

using namespace std;

void generate_number(int i, int k,int n, vector<int>& output_num)
{
    if (n == 1){
        output_num.push_back(i);
        return;
    }
    if (i % 10 - k > -1)
        generate_number(10 * i + i % 10 - k, k, n - 1, output_num);

    if (k != 0) {
        if (i % 10 + k < 10)
            generate_number(10 * i + i % 10 + k, k, n - 1, output_num);
    }

}

void go_through_list(int i ,int k, int n, vector<int>& output_num)
{
    if (i > 0)
        go_through_list(i - 1, k, n, output_num);
    else
        return;
    generate_number(i, k, n, output_num);
}

int main()
{
    int k, n;
    cin >> n >> k;
    vector<int> output_num;
    go_through_list(9 ,k, n, output_num);
    for (int i = 0; i < output_num.size(); i++)
    {
        cout << output_num[i] << endl;
    }
}