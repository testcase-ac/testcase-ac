#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
int A[MAXN], B[MAXN], N;
vector<int> G[MAXN + 1];

bool check_int(vector<pii>& groups) {
  for (auto& [w, _] : groups) {
    if (w <= 0) return false;
  }

  int P[3] = {0, 1, 2};
  do {
    int ok = 1;
    for (int i = 0; i < 3; ++i) {
      int gs = P[i], ge = P[(i + 1) % 3];
      ok &= groups[gs].second <= groups[ge].first;
    }
    if (ok) {
      int off[3] = {0, 0, 0};
      for (int i = 1; i < 3; ++i) {
        off[i] = off[i - 1] + groups[i - 1].first;
      }

      for (int i = 0; i < 3; ++i) {
        int w = groups[P[i]].first;
        for (int j = 0; j < w; ++j) {
          G[B[j + off[P[i]]]].push_back(i + 1);
        }
      }
      return true;
    }
  } while (next_permutation(P, P + 3));
  return false;
}

bool check(int l, int p1, int p2, int p3) {
  vector<pii> groups;
  for (int u : {p1, p2, p3}) {
    if (u < 0 || u >= N) continue;
    groups.clear();
    groups.emplace_back(l + 1, B[l]);
    groups.emplace_back(u - l, B[u]);
    groups.emplace_back(N - 1 - u, B[N - 1]);
    if (check_int(groups)) return true;
  }
  return false;
}

void construct_ans() {
  for (int i = 0; i < N; ++i) {
    int l = G[A[i]].back(); cout << l;
    G[A[i]].pop_back();
  }
  cout << '\n';
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
    B[i] = A[i];
  }
  sort(B, B + N);

  for (int l = 0; l < N; ++l) {
    int p1 = l + B[l], p2 = N - 1 - B[l], p3 = l + B[N - 1];
    if (check(l, p1, p2, p3)) {
      cout << "YES\n";
      return construct_ans();
    }
  }
  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
