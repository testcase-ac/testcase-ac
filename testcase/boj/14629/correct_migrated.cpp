#include <bits/stdc++.h>
using namespace std;

bool used[10];
long long n, ans;

void bt(long long x) {
    if (abs(x - n) < abs(ans - n)) ans = x;
    else if (abs(x - n) == abs(ans - n)) ans = min(ans, x);
    for (int i = 0; i < 10; i++) {
        if (!used[i]) {
            used[i] = 1;
            bt(x * 10 + i);
            used[i] = 0;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin >> n;
    bt(0);
    cout << ans;
}
