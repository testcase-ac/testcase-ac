#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;

int main() {
    int n;
    cin >> n;
    vector<pii> v;
    for(int i=0; i<n; i++) {
        int x, y;
        cin >> x >> y;
        if(y < 0)
            y += 360;
        v.push_back({x,y*2});
    }
    vector<bool> chk(720);
    for(int i=0; i<n; i++) {
        int y1 = v[i].second, y2 = v[(i+1)%n].second;
        if(y1 > y2) swap(y1, y2);
        // printf("y1 = %d, y2 = %d\n", y1, y2);
        if(y2 - y1 < 360) {
            // printf("chk %d - %d\n", y1, y2);
            for(int y=y1; y<=y2; y++) {
                chk[y] = 1;
            }
        } else if(y2 - y1 > 360) {
            // printf("chk %d - %d, %d - %d\n", y2, 720, 0, y1);
            for(int y=y2; y<720; y++) {
                chk[y] = 1;
            }
            for(int y=0; y<=y1; y++) {
                chk[y] = 1;
            }
        } else {
            return !(cout << "yes");
        }
    }
    for(int y=0; y<720; y++) {
        if(!chk[y]) {
            return !(cout << "no " << fixed << setprecision(1) << ((double)(y >= 360 ? y - 720 : y) / 2));
        }
    }
    cout << "yes";
}
