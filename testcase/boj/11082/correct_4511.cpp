#include <bits/stdc++.h>
using namespace std;
#define int long long

pair<int, int> simp(pair<int, int> b) {
    int g = gcd(b.first, b.second);
    return {b.first/g, b.second/g};
}
pair<int, int> add(pair<int, int> a, pair<int, int> b) {
    int num = a.first * b.second + b.first * a.second;
    int den = a.second * b.second;
    int g = gcd(num, den);
    return {num / g, den / g};
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin >> s;
    int num = 0, den = 1, rep = 0, repcnt = 1;
    bool apoint = 0, arep = 0;
    for(char c: s) {
        if(c == '.') {
            apoint = 1;
        } else if(c == '(') {
            arep = 1;
        } else if(c != ')') {
            if(!apoint) {
                num *= 10;
                num += c - '0';
            } else if(apoint && !arep) {
                num *= 10;
                den *= 10;
                num += c - '0';
            } else if(apoint && arep) {
                rep *= 10;
                rep += c - '0';
                repcnt *= 10;
            }
        }
    }
    repcnt -= 1;
    if(!rep) {
        auto [a, b] = simp({num, den});
        cout << a << '/' << b;
    } else {
        //printf("num = %d, den = %d, rep = %d, repcnt = %d\n", num, den, rep, repcnt);
        auto [a, b] = add({num, den}, {rep, repcnt * den});
        cout << a << '/' << b;
    }
}
