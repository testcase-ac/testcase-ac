#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  map<pair<int, int>, int> traj;

  int xi, yi, g;
  for (int i = 0; i < n; i++) {
    cin >> xi >> yi;
    if (xi == 0) yi /= abs(yi);
    else if (yi == 0) xi /= abs(xi);
    else {
      g = __gcd(abs(xi), abs(yi));
      xi /= g;
      yi /= g;
    }

    auto found = traj.find({xi, yi});
    if (found != traj.end()) found->second++;
    else traj.insert({{xi, yi}, 1});
  }

  int mv = 0;
  for (auto iter = traj.begin(); iter != traj.end(); iter++) mv = max(mv, iter->second);
  cout << mv << '\n';
}
