#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string S;
int N;

void solve_neg() {
  for (int i = N - 1; i >= 1; --i) {
    if (S[i] == '9') continue;
    ++S[i];
    return cout << S << '\n', void();
  }

  cout << "-1";
  for (int i = 1; i < N; ++i) cout << "9";
  cout << '\n';
}

void solve() {
  N = S.size();
  if (S[0] == '-') return solve_neg();

  int avail = 9 - (S[N - 1] - '0'), i;
  for (i = N - 2; i >= 0; --i) {
    int cur = S[i] - '0';
    if (cur > (i == 0) && avail >= 2) break;
    avail += 9 - cur;
  }

  if (i < 0) {
    int sum = 1;
    for (char c : S) sum += c - '0';
    if (sum > 9 * N - 9) {
      // Case 1
      string T = "";
      while (sum) {
        int cur = min(9, sum);
        sum -= cur;
        T += cur + '0';
      }
      reverse(T.begin(), T.end());
      cout << '-' << T << '\n';
    }
    else {
      // Case 2
      for (int j = 0; j < N - 1; ++j) {
        int cur = min(9, sum);
        sum -= cur;
        cout << cur;
      }
      cout << '\n';
    }
  }
  else {
    // Case 3
    --S[i]; int f = 2;
    sort(S.begin() + i + 1, S.end(), greater<char>());
    for (int j = i + 1; j < N; ++j) {
      while (f && S[j] < '9') --f, ++S[j];
    }
    cout << S << '\n';
  }
}

int main() {
  fast_io();

  while (cin >> S) {
    if (S == "END") break;
    solve();
  }
}
