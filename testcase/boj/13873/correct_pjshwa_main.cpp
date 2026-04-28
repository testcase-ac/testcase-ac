#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int P[MAX];

void solve() {
  int N, K;
  cin >> N >> K;

  int cnt = 0, sum = 0, tot = 0;
  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 0; i < N; i++) {
    cin >> P[i];
    if (cnt == K) {
      pq.push(P[i]);
      sum += P[i];
      cnt = 0;
    }
    else {
      cnt++;
      if (pq.size()) {
        sum += P[i];
        pq.push(P[i]);
        sum -= pq.top();
        pq.pop();
      }
    }
    tot += P[i];
  }

  cout << tot - sum << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
