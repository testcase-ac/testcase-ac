#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, X;
    cin >> N >> X;
    if(X > N * 26 || X < N) {
        return !(cout << "!");
    }
    string s;
    while(s.size() < N) {
        int remain = N - s.size();
        if(X > remain * 26) {
            return !(cout << "!");
        }
        int req = max(X - (remain - 1) * 26, 1ll);
        s.push_back('A' + req - 1);
        X -= req;
    }
    cout << s;
}
