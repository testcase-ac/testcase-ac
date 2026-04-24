#include <bits/stdc++.h>
using namespace std;
const int MX = 5e5+5;
long long ans[MX];
int enter[MX], event[MX];
struct good_set {
    priority_queue<int> pq, del_pq;

    void add(int x) {
        pq.push(x);
    }
    void remove(int x) {
        del_pq.push(x);
    }
    int size() {
        return pq.size() - del_pq.size();
    }
    int top() {
        while(pq.size() && del_pq.size() && pq.top() == del_pq.top()) {
            pq.pop();
            del_pq.pop();
        }
        return pq.top();
    }
};
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int Q;
    cin >> Q;
    map<int, pair<good_set, int>> mp;
    good_set mx_st;
    int enter_idx = 1;
    for(int i=1; i<=Q; i++) {
        int qry;
        cin >> qry;
        if(qry == 1) {
            int x;
            cin >> x;
            auto &[st, t] = mp[x];
            if(st.size() == 0) {
                mx_st.add(x);
            } else if(st.size() == 1) {
                // inc delayed points
                int cnt = event[i-1] - event[t];
                ans[st.top()] += cnt;

                // upd mx_st
                mx_st.remove(x);
            }
            st.add(enter_idx);
            t = i;
            enter[enter_idx++] = x;
        } else if(qry == 2) {
            int k;
            cin >> k;
            int x = enter[k];
            auto &[st, t] = mp[x];
            if(st.size() == 2) {
                mx_st.add(x);
            } else if(st.size() == 1) {
                // inc delayed points
                int cnt = event[i-1] - event[t];
                ans[st.top()] += cnt;

                // upd mx_st
                mx_st.remove(x);
            }
            st.remove(k);
            t = i;
        } else {
            int s;
            cin >> s;
            if(mx_st.size()) {
                auto &[st, t] = mp[mx_st.top()];
                ans[st.top()] += s;
            }
            event[i] = 1;
        }
        event[i] += event[i-1];
    }
    for(auto &[x, p]: mp) {
        auto &[st, t] = p;
        if(st.size() != 1) continue;
        int cnt = event[Q] - event[t];
        ans[st.top()] += cnt;
    }
    for(int i=1; i<enter_idx; i++) {
        cout << ans[i] << '\n';
    }
}
