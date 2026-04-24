#include <iostream>
#include <vector>
using namespace std;
vector<int> ways;
const int MX = 4000000;
int dp[MX], states[MX];
int main() {
    int m, k;
    cin >> m >> k;
    for(int i=0; i<k; i++) {
        int t;
        cin >> t;
        ways.push_back(t);
    }
    int mxw = ways.back();
    dp[0] = 0;
    //printf("%d ", 0);
    int start = -1, period = 0;
    for(int i=1; i<MX; i++) {
        for(int w: ways) {
            if(i-w >= 0 && !dp[i-w]) {
                dp[i] = 1;
                break;
            }
        }
        //printf("%d ", dp[i]);
        //if(i % 10 == 9)
        //    printf("\n");
        if(i >= mxw-1) {
            int bm = 0;
            for(int j=0; j<mxw; j++) {
                if(dp[i-j])
                    bm |= (1<<j);
            }
            if(states[bm]) {
                start = states[bm]+1;
                period = i - states[bm];
                goto end;
            } else
                states[bm] = i;
        }
    }
    end:;
    //printf("\nstart = %d, period = %d\n", start, period);
    int pcnt = (m-start+1) / period;
    m -= period * pcnt;
    //printf("pcnt=%d, m become %d\n", pcnt, m);
    int pp = 0, ans = 0;
    for(int i=start; i<start+period; i++)
        if(!dp[i])
            pp++;
    for(int i=1; i<=m; i++) {
        if(!dp[i])
            ans++;
    }
    cout << ans + pcnt * pp;
}
