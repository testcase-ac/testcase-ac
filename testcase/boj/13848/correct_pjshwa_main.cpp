#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 52, MAXV = 13;
int cnt[MAX], ans[MAX], N;

bool r(int i, int s) {
  if (i == N) return true;

  for (int x = 1; x <= MAXV; x++) {
    if (s % x || cnt[x] == 0) continue;

    cnt[x]--;
    ans[i] = x;
    if (r(i + 1, s - x)) return true;
    cnt[x]++;
  }

  return false;
}

void solve() {
  memset(cnt, 0, sizeof(cnt));

  int s = 0;
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    cnt[x]++;
    s += x;
  }

  if (r(0, s)) {
    for (int i = N - 1; i >= 0; i--) cout << ans[i] << ' ';
    cout << '\n';
  }
  else cout << "No\n";
}

int main() {
  fast_io();

  while (cin >> N) {
    if (N == 0) break;
    solve();
  }
}
