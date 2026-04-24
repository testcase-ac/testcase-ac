#include <bits/stdc++.h>
using namespace std;
#define int long long
int arr[200001];
set<pair<int, int>> st;
void chk_merge(auto it) {
    auto nxt = next(it);
    if(nxt == st.end()) return;
    if(nxt->first == it->second + 1) {
        // printf("  * insert %d %d, erase %d %d / %d %d\n", it->first, nxt->second, it->first, it->second, nxt->first, nxt->second);
        st.erase(nxt);
        st.erase(it);
        st.insert({it->first, nxt->second});
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    for(int i=1; i<=N; i++) {
        cin >> arr[i];
    }
    for(int i=1, j=1; i<=N; i=j) {
        while(j <= N && arr[j] - arr[i] == j - i) {
            j++;
        }
        st.insert({arr[i], arr[j-1]});
        // printf("insert %d %d\n", arr[i], arr[j-1]);
    }
    int q;
    cin >> q;
    while(q--) {
        int tidx;
        cin >> tidx;
        int t = arr[tidx];
        // printf("chk %d\n", t);
        auto nxt = st.lower_bound({t, INT_MAX});
        auto it = prev(nxt);
        auto [fst, snd] = *it;
        
        st.erase(it);
        if(fst == t) {
            auto it = st.insert({fst+1, snd+1}).first;
            // printf("  insert %d %d\n", fst+1, snd+1);
            chk_merge(it);
        } else if(snd == t) {
            st.insert({fst, snd-1});
            // printf("  insert %d %d\n", fst, snd-1);
            auto it = st.insert({snd+1, snd+1}).first;
            // printf("  insert %d %d\n", snd+1, snd+1);
            chk_merge(it);
        } else {
            st.insert({fst, t-1});
            // printf("  insert %d %d\n", fst, t-1);
            auto it = st.insert({t+1, snd+1}).first;
            // printf("  insert %d %d\n", t+1, snd+1);
            chk_merge(it);
        }

        arr[tidx] = snd+1;
        cout << snd+1 << '\n';
    }
}
