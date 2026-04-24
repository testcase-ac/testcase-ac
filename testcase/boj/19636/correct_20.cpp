#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int W0, L0, T;
    int D, L, A;
    cin >> W0 >> L0 >> T >> D >> L >> A;
    int diff = L - A - L0;
    int exp_noch = W0 + diff * D;
    if(exp_noch <= 0) {
        cout << "Danger Diet\n";
    } else {
        cout << exp_noch << ' ' << L0 << '\n';
    }

    int B = L0, exp = W0;
    for(int d=1; d<=D; d++) {
        diff = L - A - B;
        exp += diff;
        B += (abs(diff) > T ? (diff > 0 ? diff/2 : (diff-1)/2) : 0ll);
        if(exp <= 0 || B <= 0) {
            return !(cout << "Danger Diet\n");
        }
    }
    if(exp <= 0) {
        cout << "Danger Diet\n";
    } else {
        cout << exp << ' ' << B << ' ';
        int diff = L0 - B;
        if(diff > 0) {
            cout << "YOYO";
        } else {
            cout << "NO";
        }
    }
}
