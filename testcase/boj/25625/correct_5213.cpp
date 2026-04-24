#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int x, y;
    cin >> x >> y;
    if(y < x)
        y += x;
    else
        y -= x;
    cout << y;
}
