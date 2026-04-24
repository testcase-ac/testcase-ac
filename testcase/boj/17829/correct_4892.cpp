#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<vector<int>> arr(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }
    while(arr.size() > 1) {
        int s = arr.size();
        vector<vector<int>> tmp(s / 2, vector<int>(s / 2));
        for(int i = 0; i < s / 2; i++) {
            for(int j = 0; j < s / 2; j++) {
                vector<int> v = {arr[i * 2][j * 2], arr[i * 2][j * 2 + 1], arr[i * 2 + 1][j * 2], arr[i * 2 + 1][j * 2 + 1]};
                sort(v.begin(), v.end());
                tmp[i][j] = v[2];
            }
        }
        arr = tmp;
    }
    cout << arr[0][0] << '\n';
}
