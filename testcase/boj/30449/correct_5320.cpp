#include <bits/stdc++.h>
using namespace std;
#define int long long
struct frac {
    int a, b;
    bool operator<(frac f) const {
        return a * f.b < b * f.a;
    }
};
bool ok[5001][5001];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    vector<frac> v = {{0, 1}, {1, 1}};
    for(int i=0; i<=n; i++) {
        ok[i][1] = 1;
    }
    for(int a=1; a<=n; a++) {
        ok[a][1] = 1;
        for(int b=2; b<a; b++) {
            ok[a][b] = ok[b][a%b];
        }
    }
    for(int b=1; b<=n; b++) {
        for(int a=1; a<b; a++) {
            if(ok[b][a])
                v.push_back({a, b});
        }
    }
    nth_element(v.begin(), v.begin() + k - 1, v.end());
    cout << v[k-1].a << ' ' << v[k-1].b << '\n';
}
