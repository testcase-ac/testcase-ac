#include <bits/stdc++.h>
using namespace std;
#define int long long
bool is_prime(int t) {
    if(t < 2) {
        return false;
    }
    for(int i=2; i*i<=t; i++) {
        if(t % i == 0) {
            return false;
        }
    }
    return true;
}
vector<int> va, vb;
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int a, b;
    cin >> a >> b;
    vector<int> va = {a}, vb = {b};
    if(is_prime(a - 2)) {
        va.push_back(a-2);
    }
    if(is_prime(a + 2)) {
        va.push_back(a + 2);
    }
    if(is_prime(b - 2)) {
        vb.push_back(b-2);
    }
    if(is_prime(b + 2)) {
        vb.push_back(b + 2);
    }
    for(int i=0; i<va.size(); i++) {
        for(int j=0; j<vb.size(); j++) {
            if(is_prime(abs(va[i] - vb[j]))) {
                vector<int> ans;
                ans.push_back(va[0]);
                if(i == 1) {
                    ans.push_back(va[i]);
                }
                ans.push_back(vb[j]);
                if(j == 1) {
                    ans.push_back(vb[0]);
                }
                cout << ans.size() << '\n';
                for(int a: ans) {
                    cout << a << ' ';
                }
                return 0;
            } else if(is_prime(va[i] - 2) && is_prime(vb[j] - 2)) {
                vector<int> ans;
                ans.push_back(va[0]);
                if(i == 1) {
                    ans.push_back(va[i]);
                }
                ans.push_back(2);

                ans.push_back(vb[j]);
                if(j == 1) {
                    ans.push_back(vb[0]);
                }
                cout << ans.size() << '\n';
                for(int a: ans) {
                    cout << a << ' ';
                }
                return 0;
            }

        }
    }
    cout << -1;
}
