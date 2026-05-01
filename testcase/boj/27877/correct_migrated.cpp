#include <iostream>
#include <array>
#include <algorithm>

using namespace std;
using i64 = long long;

constexpr i64 MOD = 998244353;

array<i64, 15'000'000> ofact, efact;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ofact[0] = 1; efact[0] = 2;
    for (int i = 1; i < ofact.size(); i++) {
        ofact[i] = ofact[i-1]*(2*i+1) % MOD;
        efact[i] = efact[i-1]*(2*i+2) % MOD;
    }

    i64 n;
    cin >> n;
    if (n == 1) {
        cout << "1\n";
    } else if (n < 14) {
        cout << "-1\n";
    } else {
        i64 res = 9676800;
        i64 sz = 6;
        bool odd = true;
        i64 i = 13;

        while (true) {
            if (i+sz > n) { break; }
            res = res*(odd ? ofact : efact)[sz-1] % MOD;
            i += sz;
            
            int nsz = odd ? sz : sz+2;
            sz = nsz;
            odd = !odd;
        }

        res = res*(odd ? ofact : efact)[n-i] % MOD;
        cout << res << "\n";
    }

    return 0;
}
