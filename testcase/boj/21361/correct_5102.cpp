#include <bits/stdc++.h>
using namespace std;
#define int long long
int R, C, L;
char arr[2002][2002], cmd[2002];
map<char, pair<int, int>> mp = {
    {'v', {1, 0}},
    {'^', {-1, 0}},
    {'>', {0, 1}},
    {'<', {0, -1}}
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> R >> C >> L;
    cin >> cmd;
    for(int r=0; r<R; r++) {
        cin >> arr[r];
    }
    int tr, tc;
    for(int r=0; r<R; r++) {
        for(int c=0; c<C; c++) {
            if(arr[r][c] == 'O') {
                tr = r, tc = c;
                break;
            }
        }
    }
    int ans = 1;
    for(int l=0; l<L; l++) {
        char c = cmd[l];
        auto [dr, dc] = mp[c];
        while(arr[tr + dr][tc + dc] != '#') {
            tr += dr;
            tc += dc;
            if(arr[tr][tc] == '.') {
                arr[tr][tc] = 'O';
                ans++;
            }
        }
    }
    cout << ans;
}
