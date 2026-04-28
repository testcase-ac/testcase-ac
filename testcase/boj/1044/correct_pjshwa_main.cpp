#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 36, BIAS = 18;
int N;
ll A[MAXN], B[MAXN], dif;

map<ll, string> u1[MAXN + 1];
vector<int> cur; string ans;

void update_ans(ll cdif, string t) {
  if (ans.empty() || dif > cdif) {
    ans = t;
    dif = cdif;
  }
  else if (dif == cdif) {
    ans = min(ans, t);
  }
}

void dfs1(int i, int s, ll acc) {
  if (i == N / 2) {
    string r = "";
    for (int j = 0; j < N / 2; ++j) {
      r += cur[j] == 1 ? '1' : '2';
      r += ' ';
    }
    s += BIAS;
    if (!u1[s].count(acc) || u1[s][acc] > r) u1[s][acc] = r;
  }
  else {
    cur.push_back(1);
    dfs1(i + 1, s + 1, acc + A[i]);
    cur.pop_back();

    cur.push_back(2);
    dfs1(i + 1, s - 1, acc - B[i]);
    cur.pop_back();
  }
}

void dfs2(int i, int s, ll acc) {
  if (i == N) {
    string r = "";
    for (int j = 0; j < N / 2; ++j) {
      r += cur[j] == 1 ? '1' : '2';
      r += ' ';
    }

    s += BIAS;
    auto it = u1[s].upper_bound(-acc);

    if (it != u1[s].end()) {
      string t = it->second + r;
      update_ans(abs(acc + it->first), t);
    }
    if (it != u1[s].begin()) {
      --it;
      string t = it->second + r;
      update_ans(abs(acc + it->first), t);
    }
  }
  else {
    cur.push_back(1);
    dfs2(i + 1, s - 1, acc + A[i]);
    cur.pop_back();

    cur.push_back(2);
    dfs2(i + 1, s + 1, acc - B[i]);
    cur.pop_back();
  }
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 0; i < N; ++i) cin >> B[i];

  dfs1(0, 0, 0);
  dfs2(N / 2, 0, 0);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
