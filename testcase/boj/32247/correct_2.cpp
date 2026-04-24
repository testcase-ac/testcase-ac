#include <bits/stdc++.h>
using namespace std;
#define int long long
struct info {
    int c, x, h;
    void read(){
        cin >> c >> x >> h;
    }
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    vector<info> v(M);
    for(auto &i: v)
        i.read();
    sort(v.begin(), v.end(), [&](info a, info b){
        return a.x < b.x;
    });
    int curx = 0, curh = 0;
    for(auto &i: v) {
        int dist = i.x - curx;
        curh -= dist;
        if(i.c == 1 && !(curh < i.h)) {
            return !(cout << "adios");
        }
        if(i.c == 0) {
            curh = max(i.h + 1, curh);
        }
        curx = i.x;
        // printf("curx = %lld, curh = %lld\n", curx, curh);
    }
    // printf("before last, curx = %lld, curh = %lld\n", curx, curh);
    int dist = N - curx;
    curh -= dist;
    if(curh > 0) {
        cout << "adios";
    } else {
        cout << "stay";
    }
}
