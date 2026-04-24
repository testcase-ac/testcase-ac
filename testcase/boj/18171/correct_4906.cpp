#include <bits/stdc++.h>
using namespace std;
const int MX = 4e5+4;
void getpi(string &p, vector<int> &pi) {
    int n = p.size();
    pi.resize(n);
    int j = 0;
    for(int i=1; i<n; i++) {
        while(j && p[j] != p[i])
            j = pi[j-1];
        if(p[j] == p[i])
            j++;
        pi[i] = j;
    }
}

int KMP(string &t, string &p) {
    vector<int> pi;
    getpi(p, pi);
    int n = t.size(), m = p.size(), j = 0;
    for(int i=0; i<n; i++) {
        while(j && p[j] != t[i])
            j = pi[j-1];
        if(p[j] == t[i]) {
            j++;
        }
        // printf("at i=%d, j=%d\n", i, j);
        if(i == n-1) {
            return j;
        }
        if(j == m) {
            j = pi[m-1];
        }
    }
    return -1;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    string s, rev;
    cin >> s;

    rev = s;
    reverse(rev.begin(), rev.end());

    int a = KMP(s, rev);
    cout << N - a << '\n';
}
