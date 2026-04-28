#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

vector<int> Fail(const string& s) {
    const int n = s.size(); vector<int> f(n);
    for (int i = 1, j = 0; i < n; i++) {
        while (j && s[i] != s[j]) j = f[j - 1];
        if (s[i] == s[j]) f[i] = ++j;
    }
    return f;
}

vector<int> KMP(const string& a, const string& b) { // a[i], ...가 b인 i들을 반환
    const int n = a.size(), m = b.size();
    vector<int> ret, f = Fail(b);
    for (int i = 0, j = 0; i < n; i++) {
        while (j && a[i] != b[j]) j = f[j - 1];
        if (a[i] == b[j] && ++j == m) {
            ret.push_back(i - m + 1);
            j = f[j - 1];
        }
    }
    return ret;
}

int main() {
    fastio;
    string a, b; getline(cin, a); getline(cin, b);
    auto v = KMP(a, b);
    cout << v.size() << '\n';
    for (auto i : v) cout << i + 1 << ' ';
    cout << '\n';
}
