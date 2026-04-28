#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

unordered_map<string, int> friend_to_index;
int fc = 0;

int f_index(string f) {
  auto found = friend_to_index.find(f);
  if (friend_to_index.end() == found) {
    friend_to_index.insert({f, fc});
    return fc++;
  }
  else return found->second;
}

const int MAX = 1e6, INF = 1e9 + 7;
vector<int> graph[MAX];
int cdist[MAX];

int main() {
  fast_io();

  int n, m, Q;
  cin >> n >> m;
  while (m--) {
    string s, t;
    cin >> s >> t;
    int si = f_index(s), ti = f_index(t);
    graph[si].push_back(ti);
  }

  cin >> Q;
  while (Q--) {
    string s, t;
    cin >> s >> t;
    int si = f_index(s), ti = f_index(t);

    queue<int> q;

    fill(cdist, cdist + n, INF);
    q.push(si);
    cdist[si] = 0;

    while (!q.empty()) {
      int cur = q.front();
      q.pop();

      for (int nxt : graph[cur]) {
        if (cdist[nxt] > cdist[cur] + 1) {
          cdist[nxt] = cdist[cur] + 1;
          q.push(nxt);
        }
      }
    }

    int res1 = cdist[ti];

    fill(cdist, cdist + n, INF);
    q.push(ti);
    cdist[ti] = 0;

    while (!q.empty()) {
      int cur = q.front();
      q.pop();

      for (int nxt : graph[cur]) {
        if (cdist[nxt] > cdist[cur] + 1) {
          cdist[nxt] = cdist[cur] + 1;
          q.push(nxt);
        }
      }
    }

    int res2 = cdist[si];
    
    if (res1 != INF && res2 == INF) cout << s;
    else if (res1 == INF && res2 != INF) cout << t;
    else cout << "gg";
    cout << ' ';
  }

  cout << '\n';
}
