#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int N, Q;
void solve() {
  vector<string> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];

  while (Q--) {
    int x; cin >> x;
    ll d = 1, cnt = N, pw = N;
    while (x > cnt) {
      pw *= N; cnt += ++d * pw;
    }
    x -= (cnt - d * pw + 1);

    int w = x / d, off = x % d;
    vector<int> word;
    while (w > 0) word.push_back(w % N), w /= N;
    while ((int)word.size() < d) word.push_back(0);
    reverse(word.begin(), word.end());
    cout << A[word[off]] << '\n';
  }
}

int main() {
  fast_io();

  int f = 1;
  while (cin >> N >> Q) {
    if (N == 0 && Q == 0) break;
    if (f) f = 0;
    else cout << '\n';
    solve();
  }
}
