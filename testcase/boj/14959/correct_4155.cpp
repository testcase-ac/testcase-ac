#include <bits/stdc++.h>
using namespace std;
#define int long long
void getpi(vector<int> &p, vector<int> &pi) {
    int n = p.size();
    pi.resize(n);
    int j = 0;
    for(int i = 1; i < n; i++) {
        while(j && p[j] != p[i])
            j = pi[j - 1];
        if(p[j] == p[i])
            j++;
        pi[i] = j;
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> pi;
    vector<int> p(n);
    for(int i = 0; i < n; i++) {
        cin >> p[i];
    }
    reverse(p.begin(), p.end());
    getpi(p, pi);
    int mx_i = max_element(pi.begin(), pi.end()) - pi.begin();
    int real_i = n - mx_i - 1;
    cout << real_i << ' ' << (n - (real_i + pi[mx_i]));
}
