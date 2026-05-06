#include <bits/stdc++.h>
using namespace std;
int main() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int n = rng() % 100 + 1;
    int m = rng() % 100 + 1;
    int Q = rng() % 20 + 1;

    cout << n << " " << m << "\n";

    vector<string> pattern(n);
    for (int i = 0; i < n; i++) {
        string row;
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) row += '.';
            else row += (rng()%5<3 ? '.' : '#');
        }
        pattern[i] = row;
        cout << row << "\n";
    }

    cout << Q << "\n";
    for (int i = 0; i < Q; i++) {
        long long r,c;
        while(1) {
        r = rng() % 2000000001LL - 1000000000LL;
        c = rng() % 2000000001LL - 1000000000LL;
        int x=(r%n+n)%n,y=(c%m+m)%m;
        if(pattern[x][y]=='.'&&r&&c) break;
        }

        cout << r << " " << c << "\n";
    }
}
