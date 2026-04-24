#include <bits/stdc++.h>
#define int long long
using namespace std;
int K, M, N;
vector<int> multiply(vector<int> &a, vector<int> &b) {
    set<int> res;
    for(int i: a) {
        for(int j: b) {
            res.insert((i*j)%M);
        }
    }
    vector<int> v(res.begin(), res.end());
    return v;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> K >> M >> N;
    vector<int> mult(N), res = {1};
    for(int &t: mult) {
        cin >> t;
    }
    while(K) {
        if(K&1) {
            res = multiply(res, mult);
        }
        mult = multiply(mult, mult);
        K /= 2;
    }
    for(int t: res)
        cout << t << ' ';
}
