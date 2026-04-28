#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX + 1], cnts[MAX + 1], bdno[MAX + 1];

void update_bdno(int pos, int no) {
  if (
    bdno[pos] &&
    (
      abs(bdno[pos] - pos) < abs(no - pos) ||
      (abs(bdno[pos] - pos) == abs(no - pos) && bdno[pos] < no)
    )
  ) return;
  bdno[pos] = no;
}

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];

  stack<int> s;
  for (int i = 1; i <= n; i++) {
    while (!s.empty() && a[s.top()] < a[i]) {
      update_bdno(s.top(), i);
      s.pop();
    }
    s.push(i);
  }
  while (!s.empty()) s.pop();

  for (int i = n; i >= 1; i--) {
    while (!s.empty() && a[s.top()] < a[i]) {
      update_bdno(s.top(), i);
      s.pop();
    }
    s.push(i);
  }
  while (!s.empty()) s.pop();

  for (int i = 1; i <= n; i++) {
    while (!s.empty() && a[s.top()] <= a[i]) {
      cnts[s.top()] += (s.size() - 1);
      s.pop();
    }
    s.push(i);
  }
  while (!s.empty()) cnts[s.top()] += (s.size() - 1), s.pop();

  for (int i = n; i >= 1; i--) {
    while (!s.empty() && a[s.top()] <= a[i]) {
      cnts[s.top()] += (s.size() - 1);
      s.pop();
    }
    s.push(i);
  }
  while (!s.empty()) cnts[s.top()] += (s.size() - 1), s.pop();

  for (int i = 1; i <= n; i++) {
    cout << cnts[i] << ' ';
    if (cnts[i]) cout << bdno[i];
    cout << '\n';
  }
}
