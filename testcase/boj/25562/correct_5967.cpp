#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    cout << ((N*(N-1))/2) << '\n';
    for(int i=0; i<N; i++) {
        cout << (1<<i) << ' ';
    }
    cout << '\n';
    cout << (N-1) << '\n';
    for(int i=0; i<N; i++) {
        cout << i+1 << ' ';
    }
}
