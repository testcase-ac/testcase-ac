#include <bits/stdc++.h>
using namespace std;
#define int long long
struct point {
    int x, y;
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<point> A(N);
    for(int i=0; i<N; i++) {
        cin >> A[i].x >> A[i].y;
    }
    int ans = 0;
    for(int i=0; i<N; i++) {
        vector<pair<int, int>> slopes;
        for(int j=i+1; j<N; j++) {
            int dx = A[j].x - A[i].x;
            int dy = A[j].y - A[i].y;
            if(dx < 0) {
                dx = -dx;
                dy = -dy;
            }
            int g = __gcd(dx, dy);
            dx /= g;
            dy /= g;
            slopes.push_back({dx, dy});
        }
        sort(slopes.begin(), slopes.end());
        ans += unique(slopes.begin(), slopes.end()) - slopes.begin();
    }
    cout << ans*2 << '\n';
}
