#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int X;
    cin >> X;
    vector<int> ans;
    for(int i = 1; i * i + i < X; i++) {
        if((X - i) % i == 0) {
            int b = (X - i) / i;
            if(b > i) {
                ans.push_back(b);
            } else {
                break;
            }
        }
    }
    for(int i = 2; i < min(X, 31700LL); i++) {
        vector<int> tmp;
        int x = X;
        while(x) {
            tmp.push_back(x % i);
            x /= i;
        }
        bool ok = 1;
        for(int i = 0; i < tmp.size(); i++) {
            if(tmp[i] != tmp[tmp.size() - i - 1]) {
                ok = 0;
                break;
            }
        }
        if(ok) {
            ans.push_back(i);
        }
    }
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());
    for(int i = 0; i < ans.size(); i++) {
        cout << ans[i] << '\n';
    }
}
