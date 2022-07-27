#include <iostream>
#include <vector>

using namespace std;

int find_max(vector <long>& h , int i)
{
    if (i == h.size() - 1)
        return i + 1;
    else if (h[i] > h[i + 1])
        return i + 1;
    else
        return find_max(h, i + 1);
}
int main()
{
    int n;
    cin >> n;
    vector <long> h(n);
    for (int i = 0; i < n; i++)
        cin >> h[i];
    cout << find_max(h, 0) << endl;
}
