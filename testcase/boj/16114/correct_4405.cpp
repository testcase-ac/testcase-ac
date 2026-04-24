#include <bits/stdc++.h>
#define rep(i,n) for(int i=0; i<(n); i++)
#define sz(x) ((int)(x).size())
#define ll long long
using namespace std;

int main() {
    int x, n;
    cin >> x >> n;
    if(n == 1) {
        x = -x;
        n = 0;
    }
    if(n&1) return !(cout << "ERROR");
    n /= 2;
    if(x <= n) return !(cout << 0);
    if(n == 0) return !(cout << "INFINITE");
    int ans = 0;
    while((x -= n) > 0) {
        ans++;
    }
    cout << ans;
}
