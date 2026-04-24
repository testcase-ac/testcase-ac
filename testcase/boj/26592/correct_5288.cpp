#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        double A, B;
        cin >> A >> B;
        double ans = 2 * A / B;
        printf("The height of the triangle is %.2f units\n", ans);
    }
}
