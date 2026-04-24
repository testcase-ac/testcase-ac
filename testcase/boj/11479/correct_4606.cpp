#include <bits/stdc++.h>
using namespace std;
const int MX = 1e6, LOGMX = 21;
int P[LOGMX][MX*2], arr[MX], k, cnt;
int lcp(int a, int b) {
    int ret = 0;
    for(int t=k-1; t>=0; t--) {
        if(P[t][a] == P[t][b]) {
            a += 1 << t;
            b += 1 << t;
            ret += 1 << t;
        }
    }
    return ret;
}
int main() {
    string s;
    cin >> s;
    int n = s.size();
    for(int i=0; i<n; i++) {
        P[0][i] = s[i];
        arr[i] = i;
    }
    auto f = [&](int a, int b) {
        return tie(P[k-1][a], P[k-1][a+cnt]) < tie(P[k-1][b], P[k-1][b+cnt]);
    };
    for(k=1, cnt=1; cnt<n; k++, cnt*=2) {
        sort(arr, arr+n, f);
        P[k][arr[0]] = 1;
        for(int i=1; i<n; i++) {
            P[k][arr[i]] = P[k][arr[i-1]];
            if(f(arr[i-1], arr[i]))
                P[k][arr[i]]++;
        }
    }
    long long ans = 1ll*n*(n+1)/2;
    for(int i=0; i<n-1; i++) {
        ans -= lcp(arr[i], arr[i+1]);
    }
    cout << ans;
}
