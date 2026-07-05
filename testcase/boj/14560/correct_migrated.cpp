#include <iostream>
#include <array>
#include <vector>

using namespace std;
using i64 = long long;

array<i64, 30> p3, arr;

constexpr i64 INF = 1ll << 60;
vector<i64> comb_sorted(int l, int r) {
    vector<i64> poss, nposs;
    poss.reserve(p3[r-l+1]);
    nposs.reserve(p3[r-l+1]);
    poss = { 0 };
    for (int i = l; i <= r; i++) {
        int sz = poss.size();
        int nsz = sz * 3;
        i64 ai = arr[i];
        const i64* src = poss.data();
        int p0 = 0, p1 = 0, p2 = 0;
        nposs.resize(nsz);
        i64* dst = nposs.data();
        for (int j = 0; j < nsz; j++) {
            i64 v0 = p0 < sz ? src[p0] - ai : INF;
            i64 v1 = p1 < sz ? src[p1]      : INF;
            i64 v2 = p2 < sz ? src[p2] + ai : INF;

            if (v0 <= v1 && v0 <= v2) {
                dst[j] = v0;
                p0++;
            } else if (v1 <= v2) {
                dst[j] = v1;
                p1++;
            } else {
                dst[j] = v2;
                p2++;
            }
        }
        poss.swap(nposs);
        nposs.clear();
    }

    return poss;
}

int main() {
    p3[0] = 1ll; for (int i = 1; i < p3.size(); i++) { p3[i] = 3*p3[i-1]; }

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) { cin >> arr[i]; }
    i64 d;
    cin >> d;

    int m = n/2;

    vector<i64> lposs, rposs;
    lposs = comb_sorted(0, m-1);
    rposs = comb_sorted(m, n-1);

    i64 res = 0;
    int l = 0, r = 0;
    for (i64 x : lposs) {
        while (l < rposs.size() && rposs[l] < x-d) { l++; }
        while (r < rposs.size() && rposs[r] <= x+d) { r++; }
        res += r - l;
    }

    cout << res << "\n";

    return 0;
}
