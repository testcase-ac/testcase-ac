#include <bits/stdc++.h>

using namespace std;

int Xn, Yn, Wn;
string X, Y, W;

pair<vector<int>, vector<int>> common_pos(string X, int Xn) {
    vector<int> pref(Wn + 1), suff(Wn + 1);
    pref[0] = -1;
    for (int i = 1; i <= Wn; ++i) {
        pref[i] = pref[i - 1] + 1;
        while (X[pref[i]] != W[i - 1]) ++pref[i];
    }
    suff[0] = Xn;
    for (int i = 1; i <= Wn; ++i) {
        suff[i] = suff[i - 1] - 1;
        while (X[suff[i]] != W[Wn - i]) --suff[i];
    }
    return pair(pref, suff);
}

map<char, pair<int, int>> count_char;
int pos_char;

void add(char c, int v, int t) {
    auto &p = count_char[c];
    if (p.first && p.second) --pos_char;
    if (t == 1) p.first += v;
    else p.second += v;
    if (p.first && p.second) ++pos_char;
}

void solve() {
    count_char.clear();
    pos_char = 0;
    cin >> X >> Y >> W;
    Xn = X.length();
    Yn = Y.length();
    Wn = W.length();
    auto [X_pref, X_suff] = common_pos(X, Xn);
    auto [Y_pref, Y_suff] = common_pos(Y, Yn);
    int xs = 0, xe = -1, ys = 0, ye = -1;
    for (int i = 0; i <= Wn; ++i) {
        while (xe < X_suff[Wn - i] - 1) add(X[++xe], 1, 1);
        while (ye < Y_suff[Wn - i] - 1) add(Y[++ye], 1, 2);
        while (xs < X_pref[i] + 1) add(X[xs++], -1, 1);
        while (ys < Y_pref[i] + 1) add(Y[ys++], -1, 2);
        if (pos_char) return (void)printf("1\n");
    }
    printf("0\n");
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
