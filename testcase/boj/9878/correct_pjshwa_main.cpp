#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  priority_queue<int, vector<int>, greater<int>> eventT, eventD;
  int e;
  cin >> e;
  while (e--) {
    string op;
    int val;
    cin >> op >> val;
    if (op == "T") eventT.push(val);
    if (op == "D") eventD.push(val);
  }
  eventD.push(1000);

  int inv_speed = 1;
  double ctime = 0, cdist = 0, speed = 1;
  while (!eventT.empty() && !eventD.empty()) {
    int ndist = eventD.top();
    int ntime = eventT.top();

    if (speed * (ntime - ctime) <= ndist - cdist) {
      cdist += speed * (ntime - ctime);
      ctime = ntime;
      eventT.pop();
    }
    else {
      ctime += (ndist - cdist) / speed;
      cdist = ndist;
      eventD.pop();
    }

    inv_speed++;
    speed = 1.0 / inv_speed;
  }

  while (!eventT.empty()) {
    int ntime = eventT.top();
    cdist += speed * (ntime - ctime);
    ctime = ntime;
    eventT.pop();

    inv_speed++;
    speed = 1.0 / inv_speed;
  }

  while (!eventD.empty()) {
    int ndist = eventD.top();
    ctime += (ndist - cdist) / speed;
    cdist = ndist;
    eventD.pop();

    inv_speed++;
    speed = 1.0 / inv_speed;
  }

  cout << (int)round(ctime) << '\n';
}
