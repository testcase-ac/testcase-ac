#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<vector<char>> rot(vector<vector<char>> v) {
    int R = v.size(), C = v[0].size();
    vector<vector<char>> w(C, vector<char>(R));
    for(int r=0; r<R; r++) {
        for(int c=0; c<C; c++) {
            w[c][R-r-1] = v[r][c];
        }
    }
    return w;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int R, C;
    cin >> R >> C;
    vector<vector<char>> arr(R, vector<char>(C));
    for(int r=0; r<R; r++) {
        string s;
        cin >> s; // ?
        for(int c=0; c<C; c++) {
            arr[r][c] = s[c];
        }
    }
    for(int i=0; i<4; i++) {
        bool ok = 1;
        for(char c: arr[0]) {
            if(c == '.') {
                ok = 0;
            }
        }
        for(int r=1; r<arr.size(); r++) {
            for(int c=0; c<arr[0].size(); c++) {
                if(arr[r][c] == '#' && arr[r-1][c] == '.') {
                    ok = 0;
                }
            }
        }
        if(ok) {
            cout << arr.size() << ' ' << (arr[0].size() + 1) << '\n';
            for(auto &v: arr) {
                for(char c: v) {
                    cout << (c == '.' ? '#' : '.');
                }
                cout << '#';
                cout << '\n';
            }
            return 0;
        }
        arr = rot(arr);
    }
    cout << "impossible";
}
