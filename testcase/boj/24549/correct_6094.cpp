#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define ll long long
#define eps 1e-7
#define all(x) ((x).begin()),((x).end())
#define usecppio ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
#define int ll
using pii = pair<int, int>;
const int MX = 302;
int arr[MX][MX];
int N, M, K;
void mark(int x, int y) {
    if(1 <= x && x <= N && 1 <= y && y <= M) {
        arr[x][y] = 1;
    }
}
int dx[] = {-3, -3, -2, -2, 2, 2, 3, 3}, dy[] = {2,-2,3,-3,3,-3,2,-2};
#define vi vector<int>
bool dfs(int a, int L, vector<vi> &g, vi &btoa, vi &A, vi &B) {
    if(A[a] != L) return 0;
    A[a] = -1;
    for(int b: g[a]) if(B[b] == L+1) {
        B[b] = 0;
        if(btoa[b] == -1 || dfs(btoa[b], L+1, g, btoa, A, B)) {
            return btoa[b] = a, 1;
        }
    }
    return 0;
}

int hopcroft(vector<vi> &g, vi& btoa) {
    int res = 0;
    vi A(g.size()), B(btoa.size()), cur, next;
    while(true) {
        fill(A.begin(), A.end(), 0);
        fill(B.begin(), B.end(), 0);
        cur.clear();
        for(int a: btoa) if(a != -1) A[a] = -1;
        for(int a=0; a<g.size(); a++) if(A[a] == 0) cur.push_back(a);
        for(int lay=1;;lay++) {
            bool islast = 0;
            next.clear();
            for(int a: cur) for(int b: g[a]) {
                if(btoa[b] == -1) {
                    B[b] = lay;
                    islast = 1;
                }
                else if(btoa[b] != a && !B[b]) {
                    B[b] = lay;
                    next.push_back(btoa[b]);
                }
            }
            if(islast) break;
            if(next.empty()) return res;
            for(int a: next) A[a] = lay;
            cur.swap(next);
        }
        for(int a=0; a<g.size(); a++) {
            res += dfs(a, 0, g, btoa, A, B);
        }
    }
}



vector<int> mis(vector<vector<int>> &g, int n, int m) {
    vector<int> match(m, -1);
    int res = hopcroft(g, match);
    vector<bool> lfound(n, true), seen(m);
    for(int it: match) if(it != -1) lfound[it] = false;
    vector<int> q, cover;
    for(int i=0; i<n; i++) {
        if(lfound[i]) q.push_back(i);
    }
    while(q.size()) {
        int i = q.back(); q.pop_back();
        lfound[i] = 1;
        for(int e: g[i]) {
            if(!seen[e] && match[e] != -1) {
                seen[e] = true;
                q.push_back(match[e]);
            }
        }
    }
    for(int i=0; i<n; i++) {
        if(lfound[i]) cover.push_back(i);
    }
    for(int i=0; i<m; i++) {
        if(!seen[i]) cover.push_back(n+i);
    }
   // assert(cover.size() == n+m-res);
    return cover;
}
int32_t main()
{
    cin >> N >> M >> K;
    vector<pii> soldiers(K);
    for(int i=0; i<K; i++) {
        int x, y;
        cin >> x >> y;
        soldiers[i] = {x, y};
        arr[x][y] = 1;
        mark(x-1, y);
        mark(x, y+1);
        mark(x+1, y);

        for(int j=0; j<8; j++) {
            int tx = x + dx[j], ty = y + dy[j];
            mark(tx, ty);
        }
    }
    map<pii, int> odd_mp;
    map<pii, int> even_mp;
    map<int, pii> inv_mp;
    for(int x=1; x<=N; x++) {
        for(int y=1; y<=M; y++) {
            if(!arr[x][y]) {
                // printf("x = %d, y = %d is ok\n", x, y);
                if((x+y)%2) {
                    odd_mp[{x, y}] = odd_mp.size();
                } else {
                    even_mp[{x, y}] = even_mp.size();
                }
            }
        }
    }
    for(auto [pr, num]: odd_mp) {
        inv_mp[num] = pr;
    }
    for(auto [pr, num]: even_mp) {
        inv_mp[num + odd_mp.size()] = pr;
    }
    // printf("odd mp = %d, even mp = %d\n", odd_mp.size(), even_mp.size());
    vector<vector<int>> adj(odd_mp.size());
    for(auto [pr, num]: odd_mp) {
        auto [x, y] = pr;
        for(int i=0; i<8; i++) {
            int tx = x + dx[i], ty = y + dy[i];
            if(even_mp.count({tx, ty})) {
                int num2 = even_mp[{tx, ty}];
                adj[num].push_back(num2);
            }
        }
    }
    vector<int> btoa(even_mp.size(), -1);
    vector<int> st = mis(adj, odd_mp.size(), even_mp.size());
    cout << st.size() << '\n';
    for(auto t: st) {
        auto pr = inv_mp[t];
        cout << pr.first << ' ' << pr.second << '\n';
    }
}
