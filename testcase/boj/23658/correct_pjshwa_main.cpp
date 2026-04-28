#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 64;
bool vis[MAX];
vector<int> cur;
int n, mlen = 1;
int goal[7] = {0, 2, 3, 5, 8, 14, 27};

string to_binary(unsigned int u, int num_of_bits) { 
  string a = "";
  int t = pow(2, num_of_bits);   // t is the max number that can be represented

  for(t; t>0; t = t/2)           // t iterates through powers of 2
    if(u >= t){                // check if u can be represented by current value of t
        u -= t;
        a += "1";               // if so, add a 1
    }
    else {
        a += "0";               // if not, add a 0
    }

  return a ;                     // returns string
}

void dfs(int v) {
  if (cur.size() == goal[n]) {
    cout << cur.size() << '\n';
    for (int i = 0; i < cur.size(); ++i) {
      cout << to_binary(cur[i], n - 1) << '\n';
    }
    exit(0);
  }

  for (int b = 0; b < n; b++) {
    int f = 1, t = v ^ (1 << b);
    if (vis[t]) continue;

    for (int p : cur) {
      if (p != v && __builtin_popcount(p ^ t) == 1) f = 0;
    }
    if (!f) continue;

    cur.push_back(t);
    vis[t] = 1;
    mlen = max(mlen, (int)cur.size());

    dfs(t);

    vis[t] = 0;
    cur.pop_back();
  }
}

void solve() {
  cin >> n;

  int s = 0;
  cur.push_back(s);
  vis[s] = 1;
  dfs(s);
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}