#include <bits/stdc++.h>
using namespace std;

const int MX = 1e6 + 5;

int a_ok[MX], b_ok[MX];

void mark(int v, int *ok, int val) {
    for(int i=1; i*i<=v; i++) {
        if(v % i == 0) {
            if(val == -1 || ok[i] == 0) {
                ok[i] = val;
            }
            if(val == -1 || ok[v / i] == 0) {
                ok[v / i] = val;
            }
        }
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);    
    int C, D;
    cin >> C >> D;
    for(int i=C; i<=D; i++) {
        string s;
        cin >> s;
        if(s == "Fizz") {
            mark(i, a_ok, 1);
            mark(i, b_ok, -1);
        } else if(s == "Buzz") {
            mark(i, a_ok, -1);
            mark(i, b_ok, 1);
        } else if(s == "FizzBuzz") {
            mark(i, a_ok, 1);
            mark(i, b_ok, 1);
        } else {
            mark(i, a_ok, -1);
            mark(i, b_ok, -1);
        }
    }
    int a = max_element(a_ok+1, a_ok+MX) - a_ok;
    int b = max_element(b_ok+1, b_ok+MX) - b_ok;
    cout << a << ' ' << b;
}
