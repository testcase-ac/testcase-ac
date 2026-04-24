#include <bits/stdc++.h>
using namespace std;
#define int long long

int a[300][300];
vector<int> values;
vector<pair<int, int>> indexes;

void rotate_rec(int r1, int r2, int c1, int c2) {
    if(r1 > r2 || c1 > c2) return;
    values.clear();
    indexes.clear();
    for(int r = r1; r <= r2; r++) {
        indexes.push_back({r, c1});
    }
    for(int c = c1 + 1; c <= c2; c++) {
        indexes.push_back({r2, c});
    }
    for(int r = r2 - 1; r >= r1; r--) {
        indexes.push_back({r, c2});
    }
    for(int c = c2 - 1; c >= c1 + 1; c--) {
        indexes.push_back({r1, c});
    }
    for(auto [r, c]: indexes) {
        values.push_back(a[r][c]);
    }
    rotate(values.begin(), values.end() - 1, values.end());
    for(int i = 0; i < values.size(); i++) {
        a[indexes[i].first][indexes[i].second] = values[i];
    }
    rotate_rec(r1 + 1, r2 - 1, c1 + 1, c2 - 1);
}
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int R, C, K;
    cin >> R >> C >> K;
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cin >> a[i][j];
        }
    }
    while(K--) {
        rotate_rec(0, R - 1, 0, C - 1);
    }
    for(int i = 0; i < R; i++) {
        for(int j = 0; j < C; j++) {
            cout << a[i][j] << " ";
        }
        cout << '\n';
    }
}
