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

void KMP(vector<int> &t, vector<int> &p, vector<int> &ans) {
    vector<int> pi;
    getpi(p, pi);
    int n = t.size(), m = p.size(), j = 0;
    for(int i = 0; i < n; i++) {
        while(j && p[j] != t[i])
            j = pi[j - 1];
        if(p[j] == t[i])
            j++;
        if(j == m) {
            ans.push_back(i - m + 1);
            j = pi[m - 1];
        }
    }
}
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for(int i = 0; i < n; i++) {
        cin >> b[i];
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    vector<int> adiff(2 * n - 1), bdiff(n - 1);
    auto getA = [&](int i) {
        if(i >= n)
            return a[i - n] + 360000;
        return a[i];
    };
    for(int i = 0; i < 2 * n - 1; i++) {
        adiff[i] = getA(i + 1) - getA(i);
    }
    for(int i = 0; i < n - 1; i++) {
        bdiff[i] = b[i + 1] - b[i];
    }
    vector<int> ans;
    KMP(adiff, bdiff, ans);
    cout << (ans.size() ? "possible" : "impossible");
}
