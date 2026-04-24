#include <bits/stdc++.h>
using namespace std;
#define int long long
struct point {
    int x, y, k;
};
int C[100000], N, K, L;
point arr[1000000];
multiset<int> group_xs[100000];
// get valid x range for group k
pair<int, int> get_xlxr(int k) {
    auto &ms = group_xs[k];
    int c = C[k];
    if(!c) {
        int ed = ms.empty() ? L+1 : *ms.begin();
        return {0ll, ed};
    }
    while(ms.size() > c+1) {
        ms.erase(prev(ms.end()));
    }
    if(ms.size() < c) {
        return {0ll, 0ll};
    } else if(ms.size() == c) {
        return {*ms.rbegin() + 1, L+1};
    } else if(ms.size() == c+1) {
        return {(*next(ms.rbegin()))+1, *ms.rbegin()};
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> L >> K;
    for(int i=0; i<K; i++)
        cin >> C[i];
    
    cin >> N;

    for(int i=0; i<N; i++) {
        int x, y, k;
        cin >> x >> y >> k;
        k--;
        arr[i] = {x, y, k};
    }
    sort(arr, arr+N, [&](point a, point b) {return a.y < b.y;});
    multiset<int> xls, xrs;
    for(int i=0; i<K; i++) {
        auto [xl, xr] = get_xlxr(i);
        xls.insert(xl);
        xrs.insert(xr);
    }
    int last_y = 0, ans = 0;
    auto chk = [&](int cur_y) {
        int ydiff = cur_y - last_y;
        int dist = max(*xrs.begin() - *xls.rbegin(), 0ll);
        ans += dist * ydiff;
    };
    for(int i=0, j=0; i<N; i=j) {
        chk(arr[i].y);

        int mn_x = L+2;
        while(j < N && arr[j].y == arr[i].y) {
            auto [x, y, k] = arr[j];
            auto [xl, xr] = get_xlxr(k);
            xls.erase(xls.find(xl));
            xrs.erase(xrs.find(xr));
            group_xs[k].insert(x);
            auto [nxl, nxr] = get_xlxr(k);
            xls.insert(nxl);
            xrs.insert(nxr);
            mn_x = min(mn_x, x);
            j++;
        }
        ans += max(min(*xrs.begin(), mn_x) - *xls.rbegin(), 0ll);
        last_y = arr[i].y + 1;
    }
    chk(L+1);

    cout << ans;
}
