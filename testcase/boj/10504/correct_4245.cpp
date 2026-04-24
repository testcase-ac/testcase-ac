#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    int N;
    cin >> N;
    int b = 0;
    for(int a=2;; a++) {
        b += a-1;
        if(b > N) {
            printf("IMPOSSIBLE\n");
            return;
        }
        if((N - b) % a == 0) {
            int st = (N-b)/a;

            if(st <= 0) {
                continue;
            }
            printf("%d = ", N);

            for(int x=(N-b)/a; x < (N-b)/a+a; x++) {
                printf("%d", x);
                if(x != (N-b)/a+a-1) {
                    printf(" + ");
                }
            }
            printf("\n");
            return;
        }
    }
}

int main() {
    //ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}
