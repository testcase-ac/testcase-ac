#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 30, INF = 2e18;
ll c[MAXN + 10][MAXN + 10]; //capacity
ll f[MAXN + 10][MAXN + 10]; //flow
ll d[MAXN + 10][MAXN + 10]; //dist
ll prv[MAXN + 10], dist[MAXN + 10];
bool inque[MAXN + 10];

// https://justicehui.github.io/ps/2019/03/23/BOJ11408/
struct MCMF {
  vector<int> g[MAXN + 10]; //graph
  int n, source, sink;

  MCMF(){
    init(n);
  }

  MCMF(int n, int source, int sink){
    init(n); setSource(source); setSink(sink);
  }

  void init(int _n){
    n = _n+1;
    source = sink = -1;
    memset(c, 0, sizeof c);
    memset(d, 0, sizeof d);
    memset(f, 0, sizeof f);
  }

  void setSource(int s){
    source = s;
  }

  void setSink(int t){
    sink = t;
  }

  void addEdge(int s, int e, ll cap, ll dist){
    g[s].push_back(e); c[s][e] = cap; d[s][e] = dist;
    g[e].push_back(s); c[e][s] = 0; d[e][s] = -dist;
  }

  ll mcmf(){
    ll minCost = 0;
    while(1){
      memset(prv, -1, sizeof prv);
      memset(inque, 0, sizeof inque);
      fill(dist, dist + n, INF);
      queue<int> q;
      dist[source] = 0;
      inque[source] = 1;
      q.push(source);

      while(q.size()){
        int now = q.front(); q.pop(); inque[now] = 0;
        for(auto nxt : g[now]){
          if(c[now][nxt] - f[now][nxt] > 0 && dist[nxt] > dist[now] + d[now][nxt]){
            dist[nxt] = dist[now] + d[now][nxt];
            prv[nxt] = now;
            if(!inque[nxt]){
              q.push(nxt);
              inque[nxt] = 1;
            }
          }
        }
      }
      if(prv[sink] == -1) break;
      ll flow = INF;
      for(int i=sink; i!=source; i=prv[i]){
        flow = min(flow, c[prv[i]][i] - f[prv[i]][i]);
      }
      for(int i=sink; i!=source; i=prv[i]){
        minCost += flow * d[prv[i]][i];
        f[prv[i]][i] += flow;
        f[i][prv[i]] -= flow;
      }
    }
    return minCost;
  }
};

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int S = 10, T = 11;
  MCMF flow(T, S, T);

  ll N, A[3], B[3]; cin >> N;
  for (int i = 0; i < 3; ++i) {
    cin >> A[i];
    flow.addEdge(S, i, A[i], 0);
  }
  for (int i = 0; i < 3; ++i) {
    cin >> B[i];
    flow.addEdge(i + 3, T, B[i], 0);
  }
  for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) {
    ll cost; cin >> cost;
    flow.addEdge(i, j + 3, INF, -cost);
  }
  cout << -flow.mcmf() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
