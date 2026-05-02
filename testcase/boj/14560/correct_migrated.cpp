#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

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
        array<int, 3> ptr = { 0, 0, 0 };
        while (ptr[0] < sz || ptr[1] < sz || ptr[2] < sz) {
            array<i64, 3> val = { INF, INF, INF };
            if (ptr[0] < sz) { val[0] = poss[ptr[0]] - arr[i]; }
            if (ptr[1] < sz) { val[1] = poss[ptr[1]]         ; }
            if (ptr[2] < sz) { val[2] = poss[ptr[2]] + arr[i]; }
            
            int idx = min_element(val.begin(), val.end()) - val.begin();
            nposs.push_back(val[idx]);
            ptr[idx]++;
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
