#include <bits/stdc++.h>
using namespace std;
const int MX = 100003, LOGMX = 19;
int P[LOGMX][MX*2], k, cnt, arr[MX], K, acc;
char s[MX*2];
void rec(int d, int l, int r) {
    for(int i=l, j=l; i<r; i=j) {
        while(j < r && s[arr[i]+d] == s[arr[j]+d]) {
            if(s[arr[i]+d])
                acc++;
            if(acc == K) {
                for(int p=arr[i]; p<=arr[i]+d; p++) {
                    cout << s[p];
                }
                exit(0);
            }
            j++;
        }
        if(s[arr[i]+d])
            rec(d+1, i, j);
    }
}
int main() {
    cin >> s;
    int n = strlen(s);
    cin >> K;
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
    rec(0, 0, n);
    cout << -1;
}
