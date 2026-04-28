#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int ob[MAX];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> ob[i];
  for (int i = 0; i < n; i += 2) ob[i] ^= 1;

  vector<int> streaks = {0};
  int li = ob[0], streak = 1;
  for (int i = 1; i < n; i++) {
    if (ob[i] == li) streak++;
    else {
      streaks.push_back(streak);
      streak = 1;
      li = ob[i];
    }
  }
  streaks.push_back(streak);
  streaks.push_back(0);

  int mlength = 0, sz = streaks.size() - 2;
  for (int i = 1; i <= sz; i++) mlength = max(mlength, streaks[i - 1] + streaks[i] + streaks[i + 1]);
  cout << mlength;
}
