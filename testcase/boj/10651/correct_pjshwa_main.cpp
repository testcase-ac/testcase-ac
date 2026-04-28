#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

// ll T;
// struct Segment {
//   ll pos, spd;

//   Segment(ll pos, ll spd) : pos(pos), spd(spd) {}

//   const bool operator<(const Segment& rhs) const {
//     bool pos_cmp = pos < rhs.pos;
//     bool spd_cmp = spd < rhs.spd;

//     if (spd == rhs.spd) return pos_cmp;
//     if ((pos - rhs.pos) * (spd - rhs.spd) > 0) return pos_cmp;

//     assert(pos_cmp != spd_cmp);

//     if (spd_cmp) {
//       if (T * (rhs.spd - spd) >= (pos - rhs.pos)) return true;
//       else return false;
//     }
//     else {
//       if (T * (rhs.spd - spd) <= (pos - rhs.pos)) return false;
//       else return true;
//     }
//   }
// };

void solve() {
  int N, T;
  cin >> N >> T;

  vector<ll> A;
  for (int i = 0; i < N; i++) {
    ll pos, spd;
    cin >> pos >> spd;
    A.push_back(pos + spd * T);
  }

  vector<ll> L;
  L.push_back(A[N - 1]);

  for (int i = N - 2; i >= 0; i--) {
    auto next = A[i];

    if (L.back() <= next) L.push_back(next);
    else {
      auto it = upper_bound(L.begin(), L.end(), next);
      *it = next;
    }
  }

  cout << L.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
