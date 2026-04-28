#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int PL[MAX + 10], PR[MAX + 10];

void solve() {
  int N, Q; string S;
  cin >> N >> Q >> S;

  stack<char> s;
  for (int i = 0; i < N; i++) {
    PL[i + 1] = PL[i];

    char c = S[i];
    while (!s.empty() && s.top() > c) s.pop();

    if (!s.empty() && s.top() == c) continue;
    else s.push(c), PL[i + 1]++;
  }

  s = stack<char>();
  for (int i = N - 1; i >= 0; i--) {
    PR[i + 1] = PR[i + 2];

    char c = S[i];
    while (!s.empty() && s.top() > c) s.pop();

    if (!s.empty() && s.top() == c) continue;
    else s.push(c), PR[i + 1]++;
  }

  while (Q--) {
    int l, r;
    cin >> l >> r;
    cout << PL[l - 1] + PR[r + 1] << '\n';
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
