#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int A[MAXN + 1];
priority_queue<pii> pq;

void stabilize() {
  while (!pq.empty()) {
    auto [a, b] = pq.top();
    if (A[b] != a) {
      pq.pop();
      if (A[b]) pq.push({A[b], b});
    }
    else break;
  }
}

ll sumv = 0;
ll get_total() {
  stabilize();
  int maxv = pq.top().first;
  return sumv > 2 * maxv ? sumv / 2 : sumv - maxv;
}

vector<tuple<int, int, int>> ans;
void process(int i, int j, ll amt) {
  if (amt == 0 || i == j) return;
  A[i] -= amt; A[j] -= amt;
  sumv -= 2 * amt;
  ans.emplace_back(i, j, amt);
}

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) {
    cin >> A[i];
    pq.push({A[i], i});
    sumv += A[i];
  }

  int i = 1, j = 2;
  while (i <= N && j <= N) {
    if (A[i] == 0) {
      while (i <= N && A[i] == 0) ++i;
      j = i + 1;
      while (j <= N && A[j] == 0) ++j;
      continue;
    } else if (A[j] == 0) {
      while (j <= N && A[j] == 0) ++j;
      continue;
    }

    ll tot = get_total();
    int l = 0, r = min(A[i], A[j]) + 1;
    while (l < r) {
      int m = (l + r) / 2;

      A[i] -= m; A[j] -= m; sumv -= 2 * m;
      if (get_total() + m == tot) l = m + 1;
      else r = m;
      A[i] += m; A[j] += m; sumv += 2 * m;
      pq.push({A[i], i}); pq.push({A[j], j});
    }

    int avail = l - 1;
    process(i, j, avail);

    stabilize();
    int maxi = pq.top().second, amt = A[i];
    process(i, maxi, amt);
  }

  sort(ans.begin(), ans.end());
  vector<tuple<int, int, int>> ans2;
  for (auto t : ans) {
    if (ans2.empty()) ans2.push_back(t);
    else {
      auto [a, b, c] = t; auto [a2, b2, c2] = ans2.back();
      if (a == a2 && b == b2) ans2.back() = {a, b, c + c2};
      else ans2.push_back(t);
    }
  }

  cout << ans2.size() << '\n';
  for (auto [a, b, c] : ans2) cout << a << ' ' << b << ' ' << c << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
