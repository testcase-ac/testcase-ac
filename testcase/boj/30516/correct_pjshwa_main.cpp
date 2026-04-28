#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000, MAXC = 1;
int A[MAXN], it = 0, M;
vector<int> cur;
bool vis[MAXN];

void dfs(int t, vector<pii>& chunks) {
  if (t == M) {
    for (auto& [s, e] : chunks) cout << e - s + 1 << " ";
    cout << "\n";

    for (auto& i : cur) cout << i + 1 << " ";
    cout << "\n";

    if (++it == MAXC) exit(0);
    return;
  }

  for (int i = 0; i < M; ++i) {
    if (vis[i]) continue;

    auto [s, e] = chunks[i];
    if (!cur.empty()) {
      auto [ps, pe] = chunks[cur.back()];
      if (A[s] != 0 && A[s] == A[pe]) continue;
    }

    vis[i] = true;
    cur.emplace_back(i);
    dfs(t + 1, chunks);
    cur.pop_back();
    vis[i] = false;
  }
}

void do_print_result(vector<pii>& chunks) {
  M = chunks.size();
  dfs(0, chunks);
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  if (N == 2 && A[0] != 0 && A[0] == A[1]) return cout << "-1\n", void();

  int l = 0; vector<pii> chunks;
  for (int i = 1; i < N; ++i) {
    if (A[i] == A[i - 1] && A[i] != 0) {
      chunks.emplace_back(l, i - 1);
      l = i;
    }
  }
  chunks.emplace_back(l, N - 1);

  if (chunks.size() == 1) {
    cout << "1\n" << N << "\n1\n";
    return;
  }

  // force cut
  else if (chunks.size() == 2 && A[0] != 0 && A[0] == A[N - 1]) {
    auto pre = chunks;
    auto [s1, e1] = pre[0]; auto [s2, e2] = pre[1];

    cout << "3\n";
    for (int i = s1; i < e1; ++i) {
      vector<pii> nchunks{ {s1, i}, {i + 1, e1}, {s2, e2} };
      do_print_result(nchunks);
    }
    for (int i = s2; i < e2; ++i) {
      vector<pii> nchunks{ {s1, e1}, {s2, i}, {i + 1, e2} };
      do_print_result(nchunks);
    }
  }

  else {
    cout << chunks.size() << "\n";
    do_print_result(chunks);
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
