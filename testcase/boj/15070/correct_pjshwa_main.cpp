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
  int P[3] = {0, 1, 2};
  do {
    int ok = 1;
    for (int i = 0; i < 3; ++i) {
      int gs = P[i], ge = P[(i + 1) % 3];
      ok &= groups[gs].second >= groups[ge].first;
    }
    if (ok) {
      vector<tuple<int, int, int>> groups_i;
      for (int i = 0; i < 3; ++i) {
        groups_i.emplace_back(P[i], groups[P[i]].first, groups[P[i]].second);
      }
      sort(groups_i.begin(), groups_i.end());

      int p = 0;
      for (int i = 0; i < 3; ++i) {
        int w = get<1>(groups_i[i]);
        for (int j = 0; j < w; ++j) {
          G[B[p++]].push_back(i + 1);
        }
      }
      return true;
    }
  } while (next_permutation(P, P + 3));
  return false;
}

bool check(int l, int p1, int p2) {
  vector<pii> groups;
  groups.emplace_back(l + 1, B[l]);
  groups.emplace_back(p1 - l, B[p1]);
  groups.emplace_back(N - 1 - p1, B[N - 1]);
  if (check_int(groups)) return true;

  groups.clear();
  groups.emplace_back(l + 1, B[l]);
  groups.emplace_back(p2 - l, B[p2]);
  groups.emplace_back(N - 1 - p2, B[N - 1]);
  if (check_int(groups)) return true;

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

  int p1, p2;
  for (int l = 0; l < N; ++l) {
    p1 = l + B[l], p2 = N - 1 - B[l];
    if (p1 >= N) break;
    if (check(l, p1, p2)) {
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
