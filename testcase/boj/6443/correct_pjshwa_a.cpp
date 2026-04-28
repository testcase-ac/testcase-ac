#include <bits/stdc++.h>
using namespace std;

int n;
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    while (n--)
    {
        string str;
        cin >> str;

        sort(str.begin(), str.end());
        do
        {
            cout << str << "\n";
        } while (next_permutation(str.begin(), str.end()));
    }
    return 0;
}
