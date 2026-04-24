#include <bits/stdc++.h>
using namespace std;

const int MX = 1e5+2;
pair<int, int> pos[MX];

struct comp {
    // return type bool, then operator(), then const qualifier
    bool operator()(int a, int b) const {
        return pos[a].first < pos[b].first;
    }
};

map<int, set<int, comp>> mpad, mpbc;
string arr;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k >> arr;
    for(int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        pos[i] = {x, y};
        mpad[y-x].insert(i);
        mpbc[y+x].insert(i);
    }
    int curr = 0, nxt, cx, cy;
    for(char c: arr) {
        tie(cx, cy) = pos[curr];
        nxt = curr;
        if(c == 'A') {
            auto &mp = mpad[cy-cx];
            auto it = next(mp.find(curr));
            if(it != mp.end())
                nxt = *it;
        } else if(c == 'B') {
            auto &mp = mpbc[cy+cx];
            auto it = next(mp.find(curr));
            if(it != mp.end())
                nxt = *it;
        } else if(c == 'C') {
            auto &mp = mpbc[cy+cx];
            auto it = mp.find(curr);
            if(it != mp.begin())
                nxt = *prev(it);
        } else {
            auto &mp = mpad[cy-cx];
            auto it = mp.find(curr);
            if(it != mp.begin())
                nxt = *prev(it);
        }
        if(nxt != curr) {
            mpad[cy-cx].erase(curr);
            mpbc[cy+cx].erase(curr);
            curr = nxt;
        }
    }
    tie(cx, cy) = pos[curr];
    cout << cx << ' ' << cy;
    return 0;
}
