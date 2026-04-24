#include <bits/stdc++.h>
using namespace std;
#define int long long
struct sphere {
    int r, x, y, z;
    void read() {
        cin >> r >> x >> y >> z;
    }
    double cap(double h) {
        return h * h * M_PI * (3 * r - h) / 3;
    }
    double volume() {
        return 4 * M_PI * r * r * r / 3;
    }
};
int N, S;
sphere arr[10000];

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> S;
    double total_vol = 0;
    for(int i = 0; i < N; i++) {
        arr[i].read();
        total_vol += arr[i].volume();
    }
    double desired = (1e15 - total_vol) / S;
    double lside = 0;
    vector<double> ans = {0};
    for(int s = 0; s < S - 1; s++) {
        double l = lside, r = 100000;
        while(r - l > 1e-10) {
            double mid = (l + r) / 2;
            double vol = (mid - lside) * 1e10 - total_vol;
            for(int i = 0; i < N; i++) {
                auto &sp = arr[i];
                if(lside > sp.z - sp.r) {
                    double h = min(lside - (sp.z - sp.r), sp.r * 2.0);
                    vol += sp.cap(h);
                }
                if(mid < sp.z + sp.r) {
                    double h = min(sp.z + sp.r - mid, sp.r * 2.0);
                    vol += sp.cap(h);
                }
            }
            if(vol > desired) {
                r = mid;
            } else {
                l = mid;
            }
        }
        ans.push_back(l);
        lside = l;
    }
    ans.push_back(100000);
    for(int i = 1; i < ans.size(); i++) {
        cout << fixed << setprecision(9) << (ans[i] - ans[i - 1]) / 1000 << '\n';
    }
}
