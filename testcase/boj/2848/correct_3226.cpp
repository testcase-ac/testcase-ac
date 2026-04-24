#include <bits/stdc++.h>
using namespace std;
#define int long long
int adj[26][26], indeg[26], used[26];
string arr[100];
char get_at(int t, int p) {
    return p < arr[t].size() ? arr[t][p] : '*';
}

void process(int l, int r, int p) {
    if(r - l <= 1) {
        return;
    }
    // printf("%d %d %d\n", l, r, p);
    for(int i = l, j = l; i < r; i = j) {
        while(j < r && get_at(i, p) == get_at(j, p)) {
            j++;
        }
        if(j != r && get_at(i, p) != '*' && get_at(j, p) != '*') {
            adj[get_at(i, p) - 'a'][get_at(j, p) - 'a'] = 1;
            // printf("addedge: %c %c\n", get_at(i, p), get_at(j, p));
        }
        if(j != r && get_at(i, p) != '*' && get_at(j, p) == '*') {
            cout << "!";
            exit(0);
        }
        // printf("i = %d, j = %d, get_at = %c\n", i, j, get_at(i, p));
        if(get_at(i, p) != '*')
            process(i, j, p + 1);
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
        for(char c: arr[i]) {
            used[c - 'a'] = 1;
        }
    }
    process(0, n, 0);
    queue<int> que;
    int used_cnt = 0;
    for(int i = 0; i < 26; i++) {
        used_cnt += used[i];
    }
    for(int i = 0; i < 26; i++) {
        if(used[i]) {
            for(int j = 0; j < 26; j++) {
                if(adj[i][j]) {
                    indeg[j]++;
                }
            }
        }
    }
    for(int i = 0; i < 26; i++) {
        if(indeg[i] == 0 && used[i]) {
            que.push(i);
        }
    }
    bool is_multiple = false;
    vector<int> ans;
    while(que.size()) {
        if(que.size() > 1) {
            // printf("multiple\n");
            is_multiple = true;
        }
        int cur = que.front();
        // printf("cur = %c\n", cur + 'a');
        que.pop();
        ans.push_back(cur);
        for(int i = 0; i < 26; i++) {
            if(adj[cur][i]) {
                indeg[i]--;
                if(indeg[i] == 0) {
                    que.push(i);
                }
            }
        }
    }
    if(ans.size() < used_cnt)
        return !(cout << "!");
    else if(is_multiple)
        return !(cout << "?");
    else {
        for(auto i: ans) {
            cout << (char)(i + 'a');
        }
    }
}
