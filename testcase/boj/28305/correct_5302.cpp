#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef tree<int,null_type,less_equal<int>,rb_tree_tag,tree_order_statistics_node_update> set_t;

int N, T;
bool solve(vector<int> &A, int K) {
    set_t st;
    for(int t: A) {
        if(st.size() < K) {
            st.insert(max(t, T));
            continue;
        }
        auto it = st.find_by_order(st.size() - K); 
        int min_st = (*it) + 1;
        if(min_st > t) {
            return false;
        }
        st.insert(max(min_st + T - 1, t));
    }
    return true;
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> T;
    vector<int> A(N);
    for(int i=0; i<N; i++) {
        cin >> A[i];
    }
    sort(A.begin(), A.end());
    int l = 1, r = N;
    while(l < r) {
        int m = (l+r)/2;
        bool res = solve(A, m);
        if(res) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    cout << l;
}
