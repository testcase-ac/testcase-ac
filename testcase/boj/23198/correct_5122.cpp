#include <bits/stdc++.h>
using namespace std;
#define int long long
struct phone {
    int x, y, z, i;
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    vector<phone> v(N);
    for(int i = 0; i < N; i++) {
        cin >> v[i].x >> v[i].y >> v[i].z;
    }
    int x = 0, y = 0, z = 0, xy = 0, xz = 0, yz = 0, xyz = 0;
    for(int i = 0; i < N; i++) {
        x = max(x, v[i].x);
        y = max(y, v[i].y);
        z = max(z, v[i].z);
        xy = max(xy, v[i].x + v[i].y);
        xz = max(xz, v[i].x + v[i].z);
        yz = max(yz, v[i].y + v[i].z);
        xyz = max(xyz, v[i].x + v[i].y + v[i].z);
    }
    int ans2 = INT_MAX, ansi = 0;
    for(int i = 0; i < N; i++) {
        int ans = 0;
        ans = max(ans, x - v[i].x);
        ans = max(ans, y - v[i].y);
        ans = max(ans, z - v[i].z);
        ans = max(ans, xy - v[i].x - v[i].y);
        ans = max(ans, xz - v[i].x - v[i].z);
        ans = max(ans, yz - v[i].y - v[i].z);
        ans = max(ans, xyz - v[i].x - v[i].y - v[i].z);
        if(ans < ans2) {
            ans2 = ans;
            ansi = i + 1;
        }
    }
    cout << ans2 << " " << ansi;
}
