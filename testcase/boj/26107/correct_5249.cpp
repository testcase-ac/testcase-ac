#include <bits/stdc++.h>
using namespace std;
#define int long long
using pii = pair<int,int>;

int get_idx(vector<int>& vals, int q) {
    return lower_bound(vals.begin(), vals.end(), q) - vals.begin();
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    vector<int> vals;
    vector<pii> segments(n);
    map<int,int> mp;
    for(int i=0; i<n; i++) {
        cin >> segments[i].first >> segments[i].second;
        vals.push_back(segments[i].first);
        vals.push_back(segments[i].second);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    vector<int> diffs(vals.size()-1);
    for(int i=1; i<vals.size(); i++) {
        diffs[i-1] = vals[i] - vals[i-1];
    }
    sort(segments.begin(), segments.end(), [](pii& a, pii& b) {
        if(a.second == b.second) {
            return a.first < b.first;
        }
        return a.second < b.second;
    });

    int l = 0, r = 0;
    for(int i=0; i<n; i++) {
        auto [s, e] = segments[i];
        if(s > r) {
            if(l > 0 || r > 0) {
                int li = get_idx(vals, l);
                int ri = get_idx(vals, r);
                for(int i=li; i<ri; i++) {
                    diffs[i] = 0;
                }
            }
            l = s;
            r = e;
        }
        else {
            l = min(l, s);
            r = max(r, e);
        }
    }
    int li = get_idx(vals, l);
    int ri = get_idx(vals, r);
    for(int i=li; i<ri; i++) {
        diffs[i] = 0;
    }
    
    vector<int> psums(diffs.size());
    psums[0] = diffs[0];
    for(int i=1; i<diffs.size(); i++) {
        psums[i] = psums[i-1] + diffs[i];
    }
    
    vector<int> queries(k+1);
    queries[0] = 1;
    for(int i=0; i<k; i++) {
        cin >> queries[i+1];
    }

    // for(auto diff: psums) {
    //     cout << diff << " ";
    // }
    // cout << "diffs\n";
    int ans = 0;
    for(int i=0; i<k; i++) {
        auto [s1, e1] = segments[queries[i]-1];
        auto [s2, e2] = segments[queries[i+1]-1];
        
        int i1 = get_idx(vals, s1), i2 = get_idx(vals, s2);
        // cout << vals[i1] << " " << vals[i2] << endl;
        if(i2 < i1)
            swap(i2, i1);
        
        ans += ((i2==0)?0:psums[i2-1]) - ((i1==0) ? 0:psums[i1-1]);
    }
    cout << ans;
}
