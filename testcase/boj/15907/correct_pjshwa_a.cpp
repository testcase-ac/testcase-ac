#include <iostream>
#include <vector>

using namespace std;

int N;
int touch[1000 + 1];

vector<int> prime;

int cnt[2000000];

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> touch[i];
    
    for (int i = 0; i < 2000000; i++) cnt[i] = 0;
    
    int temp0 = 0, temp1 = 0;
    for (int i = 1; i <= N; i++) {
        if (touch[i] % 2 == 0) temp0++;
        else temp1++;
    }
    
    int ans = max (temp0, temp1);
    
    for (int k = 3; k * (N / 2 - 1) <= touch[N]; k++) {
        for (int i = 1; i <= N; i++) {
            cnt[touch[i] % k]++;
            ans = max(ans, cnt[touch[i] % k]);
        }
        
        for (int i = 1; i <= N; i++) cnt[touch[i] % k]--;
        
        // N / 2 - 1 = 0 인 경우
        if (k > touch[N]) break;
    }
    
    cout << ans;
    
    return 0;
}
