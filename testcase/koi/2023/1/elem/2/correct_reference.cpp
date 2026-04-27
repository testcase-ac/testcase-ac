#include <iostream>
#include <algorithm>
using namespace std;
 
const int INF = 1e9;
 
int n, k, x[111], y[111];

int max_dist(int i, int j, int k) {
    int re = 0;
    for(int u=0;u<n;u++)
        re = max(re, min({abs(x[i]-x[u])+abs(y[i]-y[u]), abs(x[j]-x[u])+abs(y[j]-y[u]), abs(x[k]-x[u])+abs(y[k]-y[u])}));
    return re;
}

int main(){
    cin >> n >> k;
    for(int i=0;i<n;i++) cin >> x[i] >> y[i];
    
    int ans = INF;
    if(k == 1) {
        for(int i=0;i<n;i++)
            ans = min(ans, max_dist(i, i, i));
    } else if(k == 2) {
        for(int i=0;i<n;i++)
            for(int j=i;j<n;j++)
                ans = min(ans, max_dist(i, j, j));
    } else {
        for(int i=0;i<n;i++)
            for(int j=i;j<n;j++)
                for(int k=j;k<n;k++)
                    ans = min(ans, max_dist(i, j, k));
    }
    cout << ans;
}