#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

map<char, int> tally;
int kcnt, vplus, vminus;

void achar(int c) {
  if (tally[c] == 0) kcnt++;
  else if (tally[c] == -1) kcnt--;

  if (tally[c] >= 0) vplus++;
  else vminus--;
  tally[c]++;
}

void dchar(int c) {
  if (tally[c] == 1) kcnt--;
  else if (tally[c] == 0) kcnt++;

  if (tally[c] <= 0) vminus++;
  else vplus--;
  tally[c]--;
}

bool diff_by_one() {
  return kcnt == 2 && vplus == 1 && vminus == 1;
}

bool identical() {
  return kcnt == 0 && vplus == 0 && vminus == 0;
}

int main() {
  fast_io();

  string s;
  int t;
  cin >> s >> t;
  int ssz = s.size();

  while (t--) {
    string ti;
    cin >> ti;
    int tsz = ti.size();

    bool able = false;
    if (tsz > ssz) {
      tally.clear();
      kcnt = vplus = vminus = 0;
      for (int i = 0; i < ssz; i++) dchar(s[i]);
      for (int i = 0; i < ssz; i++) achar(ti[i]);
      able |= (diff_by_one() || identical());
      for (int i = ssz; i < tsz; i++) {
        dchar(ti[i - ssz]);
        achar(ti[i]);
        able |= (diff_by_one() || identical());
      }
    }
    else if (tsz == ssz) {
      tally.clear();
      kcnt = vplus = vminus = 0;
      for (int i = 0; i < ssz; i++) dchar(s[i]);
      for (int i = 0; i < ssz; i++) achar(ti[i]);
      able |= diff_by_one();
    }

    if (able) cout << "YES" << '\n';
    else cout << "NO" << '\n';
  }

}
