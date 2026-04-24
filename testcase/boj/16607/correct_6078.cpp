#include <bits/stdc++.h>
using namespace std;
map<char, pair<int,int>> mp = {
    {'L', {-1, 0}},
    {'R', {1, 0}},
    {'U', {0, 1}},
    {'D', {0, -1}},
};
bool is_reverse(char a, char b) {
    if(a > b)
        swap(a, b);
    return (a == 'L' && b == 'R') || (a == 'D' && b == 'U');
}
struct point {
    int x, y;
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin >> s;
    vector<point> blocks, pos;
    int x = 0, y = 0;
    for(int i=0; i<s.size(); i++) {
        int step = (1<<i);
        auto [dx, dy] = mp[s[i]];
        if(i >= 2 && is_reverse(s[i], s[i-1]) && s[i] == s[i-2]) {
            x = pos[i-2].x;
            y = pos[i-2].y;
        } else {
            x += dx * step;
            y += dy * step;
            blocks.push_back({x + dx, y + dy});
        }
        pos.push_back({x, y});
    }
    int sz = s.size();
    if(sz >= 3 && is_reverse(s[sz-1], s[sz-2]) && s[sz-1] == s[sz-3]) {
        return !(cout << "impossible");
    }
    cout << -x << ' ' << -y << '\n';
    cout << blocks.size() << '\n';
    for(auto [bx, by]: blocks) {
        cout << bx - x << ' ' << by - y << '\n';
    }
}
