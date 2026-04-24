#include <bits/stdc++.h>
using namespace std;
#define int long long

int arr[1000];
int dp[1000];

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        switch(c) {
            case 'B':
                arr[i] = 0;
                break;
            case 'O':
                arr[i] = 1;
                break;
            case 'J':
                arr[i] = 2;
                break;
        }
    }
    for (int i = 1; i < n; i++) {
        dp[i] = 1e9;
        for(int j = 0; j < i; j++) {
            if(arr[i] == (arr[j] + 1) % 3) {
                dp[i] = min(dp[i], (j-i) * (j-i) + dp[j]);
            }
        }
    }
    cout << (dp[n-1] == 1e9 ? -1 : dp[n-1]);
}
