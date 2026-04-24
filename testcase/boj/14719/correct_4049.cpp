#include <bits/stdc++.h>
using namespace std;
#define int long long

int arr[501][501];
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int R, C;
    cin >> R >> C;
    for(int i = 0; i < C; i++) {
        int t;
        cin >> t;
        for(int j = 0; j < t; j++) {
            arr[j][i] = 1;
        }
    }
    int ans = 0;
    for(int r = 0; r < R; r++) {
        for(int i = 0, j = 0; i < C; i = j) {
            while(j < C && arr[r][i] == arr[r][j]) {
                j++;
            }
            if((i != 0 && j != C && arr[r][i] == 0 && arr[r][j] == 1)) {
                ans += j - i;
            }
        }
    }
    cout << ans;
}
