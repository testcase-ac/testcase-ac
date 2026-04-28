#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

struct Student {
  int d;
  vector<int> a;

  bool operator<(const Student& rhs) const {
    return d < rhs.d;
  }
};

const int MAX = 1e5;
vector<Student> ss;
int acnt[31], ck, ak;

int main() {
  fast_io();

  int n, k, D;
  cin >> n >> k >> D;
  ss.resize(n);

  for (int i = 0; i < n; i++) {
    int m;
    cin >> m >> ss[i].d;
    ss[i].a.resize(m);
    for (int j = 0; j < m; j++) cin >> ss[i].a[j];
  }
  sort(ss.begin(), ss.end());

  int rp = 0, maxe = 0;
  for (int al : ss[0].a) acnt[al]++;
  for (int lp = 0; lp < n; lp++) {
    while (rp < n - 1 && ss[lp].d + D >= ss[rp + 1].d) {
      rp++;
      for (int al : ss[rp].a) acnt[al]++;
    }
    int pcnt = rp - lp + 1, ck = 0, ak = 0;
    for (int i = 1; i <= k; i++) {
      if (acnt[i]) ck++;
      if (acnt[i] == pcnt) ak++;
    }
    maxe = max(maxe, pcnt * (ck - ak));

    for (int al : ss[lp].a) acnt[al]--;
  }

  cout << maxe;
}
