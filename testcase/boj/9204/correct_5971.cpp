#include <bits/stdc++.h>
using namespace std;
#define int long long
pair<int, int> read() {
    string s;
    cin >> s;
    int t;
    cin >> t;
    return {(int)(s[0] - 'A') + 1, t};
}
void output(pair<int, int> pr) {
    cout << (char)(pr.first + 'A' - 1) << " " << pr.second << ' ';
}
bool on_same_diag(pair<int, int> pr1, pair<int, int> pr2) {
    auto diff1 = pr1.first - pr2.first, diff2 = pr1.second - pr2.second;
    auto sum1 = pr1.first + pr1.second, sum2 = pr2.first + pr2.second;
    return diff1 == diff2 || sum1 == sum2;
}
bool is_valid(pair<int, int> pr) {
    return 1 <= pr.first && pr.first <= 8 && 1 <= pr.second && pr.second <= 8;
}
void solve() {
    auto pos1 = read(), pos2 = read();
    if((pos1.first + pos1.second) % 2 != (pos2.first + pos2.second) % 2) {
        cout << "Impossible\n";
        return;
    }
    if(pos1 == pos2) {
        cout << "0 ";
        output(pos1);
        return;
    }
    if(on_same_diag(pos1, pos2)) {
        cout << "1 ";
        output(pos1);
        output(pos2);
        cout << '\n';
    } else {
        for(int i = -7; i <= 7; i++) {
            pair<int, int> mid1 = {pos1.first + i, pos1.second + i};
            if(is_valid(mid1)) {
                if(on_same_diag(mid1, pos2)) {
                    cout << "2 ";
                    output(pos1);
                    output(mid1);
                    output(pos2);
                    cout << '\n';
                    return;
                }
            }

            pair<int, int> mid2 = {pos1.first + i, pos1.second - i};
            if(is_valid(mid2)) {
                if(on_same_diag(mid2, pos2)) {
                    cout << "2 ";
                    output(pos1);
                    output(mid2);
                    output(pos2);
                    cout << '\n';
                    return;
                }
            }
        }
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--)
        solve();
}
