#include <bits/stdc++.h>
using namespace std;
#define int long long

bool has_overlap(set<char> &s1, set<char> &s2) {
    for(char c: s1)
        if(s2.count(c))
            return true;
    return false;
}
bool check_is_cnt_equal(set<char> &st, vector<string> &v) {
    vector<int> cnt(26);
    for(string &s: v) {
        for(char c: s)
            cnt[c - 'A']++;
    }
    for(char c: st) {
        if(cnt[c - 'A'] != v.size() / st.size())
            return false;
    }
    return true;
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    vector<set<char>> v(N);
    vector<string> vst;
    for(int i = 0; i < M; i++) {
        string s;
        cin >> s;
        vst.push_back(s);
        for(int i = 0; i < N; i++) {
            set<char> &st = v[i];
            st.insert(s[i]);
        }
    }
    for(int i = 0; i < N; i++) {
        for(int j = i + 1; j < N; j++) {
            if(has_overlap(v[i], v[j])) {
                cout << "NO";
                return 0;
            }
        }
    }
    int t = 1;
    for(int i = 0; i < N; i++) {
        t *= v[i].size();
        if(t > 1e6) {
            cout << "NO";
            return 0;
        }
    }
    if(t != M) {
        cout << "NO";
        return 0;
    }
    for(int i = 0; i < N; i++) {
        if(!check_is_cnt_equal(v[i], vst)) {
            cout << "NO";
            return 0;
        }
    }
    set<string> strint_set(vst.begin(), vst.end());
    if(strint_set.size() != M) {
        cout << "NO";
        return 0;
    }
    cout << "YES\n";
    for(int i = 0; i < N; i++) {
        vector<char> ve(v[i].begin(), v[i].end());
        sort(ve.begin(), ve.end());
        for(char c: ve)
            cout << c;
        cout << '\n';
    }
}
