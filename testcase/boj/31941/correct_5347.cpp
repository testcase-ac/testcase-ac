#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T, N, L, K;
    cin >> T >> N >> L >> K;
    vector<int> len_type;
    vector<int> dtime(N), safe(K);
    for (int i = 0; i < N; i++) {
        cin >> dtime[i];
        if(i) {
            int len = dtime[i] - dtime[i-1] - 1;
            if(len) {
                len_type.push_back(len);
            }
        }
    }
    int len = dtime[0] + T - dtime[N-1] - 1;
    if(len) {
        len_type.push_back(len);
    }
    for (int i = 0; i < K; i++) {
        cin >> safe[i];
        if(i) {
            int len = safe[i] - safe[i-1] - 1;
            if(len) {
                len_type.push_back(len);
            }
        }
    }
    sort(len_type.begin(), len_type.end());
    len_type.erase(unique(len_type.begin(), len_type.end()), len_type.end());
    auto compress = [&](int x) {
        return lower_bound(len_type.begin(), len_type.end(), x) - len_type.begin();
    };
    vector<vector<int>> mst(len_type.size() * 2);
    for(int i=1; i<N; i++) {
        len = dtime[i] - dtime[i-1] - 1;
        if(len) {
            int clen = compress(len);
            mst[clen + len_type.size()].push_back(dtime[i-1]+1);
        }
    }
    len = dtime[0] + T - dtime[N-1] - 1;
    if(len) {
        int clen = compress(len);
        mst[clen + len_type.size()].push_back((dtime[N-1]+1) % T);
    }

    for(int i=len_type.size(); i<len_type.size()*2; i++) {
        sort(mst[i].begin(), mst[i].end());
    }
    for(int i=len_type.size()-1; i>=1; i--) { // error 1: no building
        auto &v1 = mst[i], &v2 = mst[i*2], &v3 = mst[i*2+1];
        v1.reserve(v2.size() + v3.size());
        int a = 0, b = 0;
        while(a < v2.size() && b < v3.size()) {
            if(v2[a] < v3[b]) {
                v1.push_back(v2[a++]);
            } else {
                v1.push_back(v3[b++]);
            }
        }
        while(a < v2.size()) {
            v1.push_back(v2[a++]);
        }
        while(b < v3.size()) {
            v1.push_back(v3[b++]);
        }
    }

    len = dtime[0] + T - dtime[N-1] - 1;
    if(len) {
        int clen = compress(len);
        mst[clen + len_type.size()].push_back((dtime[N-1]+1) % T);
    }
    // x다음으로 작은 거 찾기.. lower_bound
    function<int(int, int)> query = [&](int l, int x) {
        int r = len_type.size() * 2;
        l += len_type.size();
        int res = INF;
        while(l < r) {
            if(l & 1) {
                auto it = upper_bound(mst[l].begin(), mst[l].end(), x);
                if(it != mst[l].end()) {
                    res = min(res, *it);
                }
                l++;
            }
            if(r & 1) {
                r--;
                auto it = upper_bound(mst[r].begin(), mst[r].end(), x);
                if(it != mst[r].end()) {
                    res = min(res, *it);
                }
            }
            l /= 2, r /= 2;
        }
        return res;
    };
    int ctime_nmod = 0;
    for(int i=0; i<K-1; i++) {
        int len = safe[i+1] - safe[i] - 1;
        // printf("at ctime = %lld, going to %lld\n", ctime_nmod, safe[i+1]);
        if(!len) {
            ctime_nmod++;
            continue;
        }
        int ctime = ctime_nmod % T;
        // find loc in dtime, check if possible
        auto it = upper_bound(dtime.begin(), dtime.end(), ctime);
        int remain_time;
        if(it == dtime.end()) {
            it = dtime.begin();
            remain_time = *it + T - ctime - 1;
        } else {
            remain_time = *it - ctime - 1;
        }
        if(remain_time >= len) {
            ctime_nmod += len + 1; // error 2: forget to add 1
            continue;
        }
        // if not possible, search in mst for next possible
        int clen = compress(len);
        int next_time = query(clen, ctime);
        int wait_time;
        if(next_time == INF) {
            next_time = query(clen, -1);
            if(next_time == INF) {
                return !(cout << "What is that map newbie...");
            }
            wait_time = next_time + T - ctime;
        } else {
            wait_time = next_time - ctime;
        }
        ctime_nmod += len + wait_time;
    }
    cout << ctime_nmod << '\n';
}
