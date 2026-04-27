#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
int n, x[250250];
 
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> x[i];

    int ans = x[1]/2 + 1;
    for(int i=2;i<=n;i++) {
        if(x[i-1]+1 == x[i]) {
            cout << -1;
            return 0;
        }
        ans += (x[i]-x[i-1]-1)/2 + 1;
    }
    cout << ans;
}