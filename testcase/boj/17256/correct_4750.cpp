#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int ax, ay, az, cx, cy, cz;
    cin >> ax >> ay >> az >> cx >> cy >> cz;
    cout << cx - az << ' ' << cy / ay << ' ' << cz - ax;
}
