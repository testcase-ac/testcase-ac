#include <bits/stdc++.h>
using namespace std;
vector<int> sort_cyclic_shifts(string &s) {
    int n = s.size();
    const int alphabet = 256;
    vector<int> p(n), c(n), cnt(max(n, alphabet)), pn(n), cn(n);
    // p[i] = location of ith suffix
    for(int i=0; i<n; i++)
        cnt[s[i]]++;
    for(int i=1; i<alphabet; i++)
        cnt[i] += cnt[i-1];
    for(int i=n-1; i>=0; i--)
        p[--cnt[s[i]]] = i;
    
    // c[i] = equivalnce class at location i
    c[p[0]] = 0;
    int classes = 1;
    for(int i=1; i<n; i++) {
        if(s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }

    for(int h=0; (1<<h)<n; h++) {
        // build pn
        for(int i=0; i<n; i++) {
            pn[i] = p[i] - (1<<h);
            if(pn[i] < 0)
                pn[i] += n;
        }
        // p[i]
        fill(cnt.begin(), cnt.end(), 0);
        for(int i=0; i<n; i++)
            cnt[c[i]]++;
        for(int i=1; i<classes; i++)
            cnt[i] += cnt[i-1];
        for(int i=n-1; i>=0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        
        // c[i]
        cn[p[0]] = 0;
        classes = 1;
        for(int i=1; i<n; i++) {
            pair<int, int> prv = {c[p[i]], c[(p[i] + (1<<h)) % n]},
                           nxt = {c[p[i-1]], c[(p[i-1] + (1<<h)) % n]};
            if(prv != nxt)
                classes++;
            cn[p[i]] = classes - 1;
        }
        swap(cn, c);
    }
    return p;
}
vector<int> lcp_construction(string const& s, vector<int> const& p) {
    int n = s.size(), k = 0;
    vector<int> rank(n), lcp(n-1);
    // rank[i] = order of suffix at ith location
    for(int i=0; i<n; i++) {
        rank[p[i]] = i;
    }
    for(int i=0; i<n; i++) {
        if(rank[i] == n-1) {
            k = 0;
            continue;
        }
        int j = p[rank[i] + 1];
        while(i+k < n && j+k < n && s[i+k] == s[j+k])
            k++;
        lcp[rank[i]] = k;
        if(k)
            k--;
    }
    return lcp;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    string a, b;
    cin >> a >> b;

    string total = a + "$" + b + "%";
#ifndef ONLINE_JUDGE
    printf("\n");
    printf("total is %s\n", total.c_str());
#endif
    auto p = sort_cyclic_shifts(total);
    auto lcp = lcp_construction(total, p);
#ifndef ONLINE_JUDGE
    printf("p   is ");
    for(int i: p)
        printf("%d ", i);
    printf("\n");
    printf("lcp is ");
    for(int i: lcp)
        printf("%d ", i);
    printf("\n");
#endif
    vector<int> idx(lcp.size());
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        return lcp[i] > lcp[j];
    });
    for(int i: idx) {
#ifndef ONLINE_JUDGE
        printf("i is %d\n", i);
#endif
        int len = lcp[i];
        if((p[i] < a.size()) == (p[i+1] < a.size()))
            continue;
        string ans = total.substr(p[i], len);
        cout << len << '\n' << ans;
        break;
    }
}
