#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6 + 1;
bool p[MAX + 1];
vector<int> hprimes, R;

int N;
void solve() {
  cout << N << ' ';
  cout << upper_bound(R.begin(), R.end(), N) - R.begin() << '\n';
}

int main() {
  fast_io();

  for (int i = 5; i <= MAX; i += 4) {
    if (p[i]) continue;
    hprimes.push_back(i);

    for (int j = i * 5; j <= MAX; j += i * 4) {
      p[j] = true;
    }
  }

  set<ll> u;
  for (int i = 0; i < hprimes.size(); i++) {
    for (int j = i; j < hprimes.size(); j++) {
      if ((ll)hprimes[i] * hprimes[j] > MAX) break;
      u.insert((ll)hprimes[i] * hprimes[j]);
    }
  }
  R = vector<int>(u.begin(), u.end());

  while (cin >> N) {
    if (N == 0) break;
    solve();
  }
}
