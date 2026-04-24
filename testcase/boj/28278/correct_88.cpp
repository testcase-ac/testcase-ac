#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    stack<int> stk;
    while(N--) {
        int t;
        cin >> t;
        if(t == 1) {
            int x;
            cin >> x;
            stk.push(x);
        } else if(t == 2) {
            if(stk.size()) {
                cout << stk.top() << '\n';
                stk.pop();
            } else {
                cout << -1 << '\n';
            }
        } else if(t == 3) {
            cout << stk.size() << '\n';
        } else if(t == 4) {
            cout << (stk.size() ? 0 : 1) << '\n';
        } else {
            if(stk.size()) {
                cout << stk.top() << '\n';
            } else {
                cout << -1 << '\n';
            }
        }
    }
}
