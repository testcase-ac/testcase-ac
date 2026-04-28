#include <bits/stdc++.h>
#define x first
#define y second
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using namespace std;

typedef long long ll;
typedef pair<int, int> p;
typedef pair<int, p> pp;

int n, k, a[111], b[111];
int dst[111][1<<10];

int main(){
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> k;
    for(int i=1; i<=n; i++) cin >> a[i];
    for(int i=1; i<=n; i++) cin >> b[i];
    for(int i=1; i<=n; i++) a[i] ^= b[i];
    
    memset(dst, 0x3f, sizeof dst);
    priority_queue<pp> pq; pq.emplace(0, p(1, 0)); dst[1][0] = 0;
    while(pq.size()){
        int cst = -pq.top().x;
        int idx = pq.top().y.x, bit = pq.top().y.y;
        pq.pop();
        if(cst > dst[idx][bit]) continue;
        
        if(bit % 2 == a[idx] && idx+k-1 < n){
            if(dst[idx+1][bit>>1] > dst[idx][bit]){
                dst[idx+1][bit>>1] = dst[idx][bit];
                pq.emplace(-dst[idx+1][bit>>1], p(idx+1, bit>>1));
            }
        }
        int inv = bit;
        for(int i=0; i<k; i++) inv ^= (1 << i);
        for(int i=0; i<k; i++){
            int nxt = inv ^ (1 << i);
            if(dst[idx][nxt] > dst[idx][bit] + 1){
                dst[idx][nxt] = dst[idx][bit] + 1;
                pq.emplace(-dst[idx][nxt], p(idx, nxt));
            }
            if(a[idx] != nxt % 2 || idx+k-1 == n) continue;
            if(dst[idx+1][nxt>>1] > dst[idx][bit] + 1){
                dst[idx+1][nxt>>1] = dst[idx][bit] + 1;
                pq.emplace(-dst[idx+1][nxt>>1], p(idx+1, nxt>>1));
            }
        }
    }
    int ed = 0, base = n-k+1;
    for(int i=0; i<k; i++) ed |= (a[base+i] << i);
    if(dst[base][ed] < 1e9) cout << dst[base][ed];
    else cout << -1;
}