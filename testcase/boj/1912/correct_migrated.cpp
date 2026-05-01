#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <map>
using namespace std;
int ns[300001];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> ns[i];
    }
    int temp = ns[0];
    int ans = ns[0];
    for (int i = 1; i < n; i++)
    {
        temp = max(ns[i], temp + ns[i]);
        ans = max(ans, temp);
    }
    cout << ans;
    return 0;
}
