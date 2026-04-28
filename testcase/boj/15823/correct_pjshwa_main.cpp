#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int tally[500'001];
int kcnt;
int n, m;
int a[100'000];

void aval(int c) {
  if (tally[c] == 0) kcnt++;
  tally[c]++;
}

void dval(int c) {
  if (tally[c] == 1) kcnt--;
  tally[c]--;
}

bool do_search(int pack) {
  int cnt = 0, banned = 0;
  for (int i = 0; i < pack; i++) aval(a[i]);
  if (kcnt == pack) cnt++, banned = pack - 1;

  for (int i = pack; i < n; i++) {
    dval(a[i - pack]);
    aval(a[i]);

    if (banned) banned--;
    else if (kcnt == pack) cnt++, banned = pack - 1;
  }

  // cleanup
  for (int i = n - pack; i < n; i++) dval(a[i]);

  return cnt >= m;
}

int main() {
  fast_io();

  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> a[i];

  int left = 1, right = n + 1;
  int mid = (left + right) / 2;

  while (left < right) {
    if (do_search(mid)) left = mid + 1;
    else right = mid;
    mid = (left + right) / 2;
  }

  cout << mid - 1 << '\n';
}
