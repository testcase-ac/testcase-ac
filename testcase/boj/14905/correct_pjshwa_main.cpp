#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

vector<int> ans;
bool able;

bool is_prime(ll n) {
  if (n <= 1) return false;
  if (n <= 3) return true;
  if (n % 2 == 0 || n % 3 == 0) return false;
  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) return false;
  }
  return true;
}

void solvek2(int N) {
  if (N >= 4) {
    for (int a = N / 2; a >= 2; a--) {
      if (is_prime(a) && is_prime(N - a)) {
        ans.push_back(a);
        ans.push_back(N - a);
        return;
      }
    }
  }
  able = 0;
}

void solvek3(int N, int K) {
  int diff;
  if (N & 1) diff = (K - 2) * 2 + 1;
  else diff = (K - 2) * 2;

  if (N < diff) able = 0;
  else {
    for (int i = 0; i < K - 3; i++) ans.push_back(2);
    ans.push_back(2 + (N & 1));
    solvek2(N - diff);
  }
}

int N;
void solve() {
  ans.clear();
  able = 1;

  solvek3(N, 4);

  if (able) {
    for (int e : ans) cout << e << ' ';
  }
  else cout << "Impossible.";
  cout << '\n';
}

int main() {
  fast_io();

  while (cin >> N) solve();
}
