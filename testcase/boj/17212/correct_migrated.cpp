#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n;
    cin >> n;

    vector<int> v{0, 1, 1, 2, 2, 1, 2, 1};
    for (int i = 7; i < n; i++) v.push_back(min(v[i], min(v[i-1], min(v[i-4], v[i-6]))) + 1);

    cout << v[n];
    return 0;
}
