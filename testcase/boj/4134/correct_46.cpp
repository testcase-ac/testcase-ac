#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e5;
bool sieve[MX];
vector<int> primes;
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    for (int i = 2; i < MX; i++) {
        if (sieve[i]) continue;
        primes.push_back(i);
        for (int j = i * i; j < MX; j += i) {
            sieve[j] = true;
        }
    }
    int T;
    cin >> T;
    while(T--) {
        int N;
        cin >> N;
        if(N <= 2) {
            cout << "2\n";
            continue;
        }
        if(N % 2 == 0) N++;
        while(true) {
            bool flag = true;
            for(int t: primes) {
                if(t * t > N) break;
                if(N % t == 0) {
                    flag = false;
                    break;
                }
            }
            if(flag) {
                cout << N << '\n';
                break;
            }
            N += 2;
        }
    }
}
