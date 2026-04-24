#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <utility>
using namespace std;
const int MX = 5e5+2, SQR = 707;
int a[MX], ans[MX], cnt[MX];
struct info{
    int l, r, i;
} qry[MX];
int cur;
void add(int t) {
    cnt[t]++;
    if(cnt[t] == 3) {
        cur--;
    } else if(cnt[t] == 2) {
        cur++;
    }
}
void sub(int t) {
    cnt[t]--;
    if(cnt[t] == 2) {
        cur++;
    } else if(cnt[t] == 1) {
        cur--;
    }
}
int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    int n, q;
    cin >> n >> q;
    for(int i=1; i<=n; i++)
        cin >> a[i];
    for(int i=0; i<q; i++) {
        cin >> qry[i].l >> qry[i].r;
        qry[i].i = i;
    }
    sort(qry, qry+q, [](auto a, auto b){
        return make_pair(a.l/SQR, a.r) < make_pair(b.l/SQR, b.r);
    });
    int l = 1, r = 0;
    for(int i=0; i<q; i++) {
        auto [ql, qr, qi] = qry[i];
        while(r < qr) {
            r++;
            add(a[r]);
        }
        while(l > ql) {
            l--;
            add(a[l]);
        }
        while(r > qr) {
            sub(a[r]);
            r--;
        }
        while(l < ql) {
            sub(a[l]);
            l++;
        }
        ans[qi] = cur;
    }
    for(int i=0; i<q; i++)
        cout << ans[i] << '\n';
}
