#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    double h, r, da, dw;
    cin >> h >> r >> da >> dw;
    cout << fixed << setprecision(10) << h * sqrt(da) / (sqrt(da) + sqrt(dw)); 
}
