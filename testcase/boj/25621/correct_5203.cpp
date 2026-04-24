#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 1e9 + 7;
int k, overflow;
pair<char, int> get() {
    string s;
    cin >> s;
    char c = s[0];
    int x = atoi(s.c_str() + 1);
    return {c, x};
}
void apply(char c, int v) {
    if(c == '+') {
        k += v;
        if(k >= MOD) {
            k -= MOD;
            overflow++;
        }
    } else if(c == '-') {
        k -= v;
        if(k < 0) {
            if(overflow) {
                k += MOD;
                overflow--;
            } else {
                k = 0;
            }
        }
    } else if(c == '*') {
        k *= v;
        if(overflow < MOD || !v) {
            overflow *= v;
        }
        if(k >= MOD) {
            overflow += k / MOD;
            k %= MOD;
        }
    }
}

int pre_apply(char c, int v) {
    if(c == '+') {
        return k + v;
    } else if(c == '-') {
        return k - v;
    } else if(c == '*') {
        return k * v;
    }
    exit(-1);
}
pair<char, int> bad = {'*', 0};
pair<char, int> eq = {'*', 1};
bool is_p1_better(pair<char, int> p1, pair<char, int> p2) {
    if(p1 == bad)
        return false;
    if(p2 == bad)
        return true;
    if(p1 == eq) {
        return p2.first == '-';
    }
    if(p2 == eq) {
        return p1.first == '+';
    }
    if(p1.first == '*')
        return true;
    if(p1.first == '+' && p2.first == '-')
        return true;
    return false;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, K0;
    cin >> N >> K0;
    k = K0;
    for(int i = 0; i < N; i++) {
        pair<char, int> p1 = get(), p2 = get();
        if(p1.first == p2.first) {
            if(p1.first == '+' || p1.first == '*') {
                apply(p1.first, max(p1.second, p2.second));
            } else {
                apply(p1.first, min(p1.second, p2.second));
            }
        } else {  // different
            if(overflow) {
                if(is_p1_better(p1, p2)) {
                    apply(p1.first, p1.second);
                } else {
                    apply(p2.first, p2.second);
                }
            } else {
                int a1 = pre_apply(p1.first, p1.second);
                int a2 = pre_apply(p2.first, p2.second);
                if(a1 > a2) {
                    apply(p1.first, p1.second);
                } else {
                    apply(p2.first, p2.second);
                }
            }
        }
        // printf("k = %d, ov = %d after step %d\n", k, overflow, i + 1);
    }
    cout << k;
}
