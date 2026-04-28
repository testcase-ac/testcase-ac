#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6;
int a[MAX];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  int mv = 0;
  for (int mini = 1; mini <= 8; mini++) {
    int maxi = mini + 2, streak = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] >= mini && a[i] <= maxi) streak++;
      else {
        mv = max(mv, streak);
        streak = 0;
      }
    }
    mv = max(mv, streak);
  }
  cout << mv;
}
