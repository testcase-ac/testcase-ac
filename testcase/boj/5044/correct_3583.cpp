#include <bits/stdc++.h>
using namespace std;
vector<int> sort_cyclic_shifts(vector<int>& s) {
    int n = s.size();
    vector<int> p(n), c(n), cnt(n);
    // 0th iteration: sort by first character
    for (int i = 0; i < n; i++)
        cnt[s[i]]++;
    for (int i = 1; i < n; i++)
        cnt[i] += cnt[i-1];
    for (int i = 0; i < n; i++)
        p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }
    // remaining iterations: sort by 2^h-th cyclic shift
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++)
            cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}
vector<int> lcp_construction(vector<int> const& s, vector<int> const& p) {
    int n = s.size();
    vector<int> rank(n, 0);
    for (int i = 0; i < n; i++)
        rank[p[i]] = i;

    int k = 0;
    vector<int> lcp(n-1, 0);
    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = p[rank[i] + 1];
        while (i + k < n && j + k < n && s[i+k] == s[j+k])
            k++;
        lcp[rank[i]] = k;
        if (k)
            k--;
    }
    return lcp;
}
map<string, int> token_mp;
vector<int> parse_file() {
    int N;
    string line;
    vector<int> lines;
    while(getline(cin, line)) {
        if(line == "***END***")
            break;
        int hashed = 0;
        string stripped;
        int st = 0, ed = line.size();
        while(st < ed && line[st] == ' ')
            st++;
        while(ed > st && line[ed-1] == ' ')
            ed--;
        for(int i=st; i<ed; i++) {
            if(i > st && line[i] == ' ' && line[i-1] == ' ')
                continue;
            stripped.push_back(line[i]);
        }
        if(stripped.empty())
            continue;
        if(token_mp.count(stripped) == 0)
            token_mp[stripped] = token_mp.size() + 1;
        lines.push_back(token_mp[stripped]);
    }
    return lines;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;
    if(N == 0) {
        return !(cout << "0\n");
    }
    vector<pair<string, vector<int>>> files;
    for(int i=0; i<N; i++) {
        string s;
        cin >> s;
        files.push_back({s, parse_file()});
    }
    vector<int> mine = parse_file();
    token_mp.clear();
    vector<int> lenacc;
    for(auto &[s, v]: files) {
        if(lenacc.empty()) {
            lenacc.push_back(v.size());
        } else {
            lenacc.push_back(lenacc.back() + v.size() + 1);
        }
    }

    vector<int> all;
    for(int i=0; i<N; i++) {
        all.insert(all.end(), files[i].second.begin(), files[i].second.end());
        all.push_back(0);
    }
    all.insert(all.end(), mine.begin(), mine.end());
    all.push_back(all.size());
    vector<int> p = sort_cyclic_shifts(all);
    vector<int> lcp = lcp_construction(all, p);
    vector<int> best_match(files.size());
    // p
    int cur = 0;
    for(int i=0; i<p.size(); i++) {
        if(p[i] > lenacc.back()) {
            cur = INT_MAX;
        } else {
            if(i)
                cur = min(cur, lcp[i-1]);
            if(all[p[i]] == 0)
                continue;
            int idx = lower_bound(lenacc.begin(), lenacc.end(), p[i]) - lenacc.begin();
            best_match[idx] = max(best_match[idx], cur);
        }
    }
    cur = 0;
    for(int i=p.size()-1; i>=0; i--) {
        if(p[i] > lenacc.back()) {
            cur = INT_MAX;
        } else {
            if(i < lcp.size())
                cur = min(cur, lcp[i]);
            if(all[p[i]] == 0)
                continue;
            int idx = lower_bound(lenacc.begin(), lenacc.end(), p[i]) - lenacc.begin();
            best_match[idx] = max(best_match[idx], cur);
        }
    }
    int ans = *max_element(best_match.begin(), best_match.end());
    cout << ans << ' ';
    if(ans > 0) {
        for(int i=0; i<best_match.size(); i++) {
            if(best_match[i] == ans) {
                cout << files[i].first << ' ';
            }
        }
    }
}
