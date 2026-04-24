#include <bits/stdc++.h>
using namespace std;
int sieve[200];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    for(int i=2; i<200; i++) {
        if(sieve[i]) {
            continue;
        }
        for(int j=i*i; j<200; j+=i) {
            sieve[j] = 1;
        }
    }
    vector<int> primes;
    for(int i=2; i<200; i++) {
        if(!sieve[i]) {
            primes.push_back(i);
        }
    }
    set<int> sm;
    for(int i=0; i<primes.size(); i++) {
        for(int j=i; j<primes.size(); j++) {
            sm.insert(primes[i] + primes[j]);
        }
    }
    int N;
    cin >> N;
    while(N--) {
        int a;
        cin >> a;
        cout << (sm.count(a) ? "Yes" : "No") << '\n';
    }
}
