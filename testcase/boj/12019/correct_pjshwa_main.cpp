#include <bits/stdc++.h>
using namespace std;

int n;
int dp[101][101][11];
int people[101];
int dirty_pf_sum[102];

int min_unpleasant(int day, int m, int last_cleaned_day) {
  if (day > n) return 0;

  if (dp[day][last_cleaned_day][m] == -1) {
    int unpleasant = min_unpleasant(day + 1, m, last_cleaned_day) + \
    (dirty_pf_sum[day - 1] - dirty_pf_sum[last_cleaned_day - 1]) * people[day];

    if (m) unpleasant = min(unpleasant, min_unpleasant(day + 1, m - 1, day));
    dp[day][last_cleaned_day][m] = unpleasant;
  }

  return dp[day][last_cleaned_day][m];
}

void trace(int day, int m, int last_cleaned_day) {
  if (day > n) return;

  if (
    (m && dp[day][last_cleaned_day][m] == dp[day + 1][day][m - 1]) ||
    (day == n && dp[day][last_cleaned_day][m] == 0)
  ) {
    cout << day - 1 << ' ';
    trace(day + 1, m - 1, day);
  }
  else {
    trace(day + 1, m, last_cleaned_day);
  }
}

int main(){
  int m;
  cin >> n >> m;

  if (n == m) {
    cout << "0\n";
    for (int i = 1; i <= n; i++) cout << i << ' ';
    cout << '\n';
    return 0;
  }

  memset(dp, -1, sizeof(dp));
  for (int i = 1; i <= n; i++) cin >> people[i];

  dirty_pf_sum[0] = 0;
  for (int i = 1; i <= n; i++) dirty_pf_sum[i] = dirty_pf_sum[i - 1] + people[i];

  cout << min_unpleasant(1, m, 1) << '\n';
  trace(1, m, 1);
  cout << '\n';
}
