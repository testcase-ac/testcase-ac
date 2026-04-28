#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

vector<string> split(string input, char delimiter) {
  vector<string> answer;
  stringstream ss(input);
  string temp;

  while (getline(ss, temp, delimiter)) answer.push_back(temp);
  return answer;
}

int ts2ep(string s) {
  auto su = split(s, ':');
  if (su.size() == 3) return stoi(su[0]) * 3600 + stoi(su[1]) * 60 + stoi(su[2]);
  else return stoi(su[0]) * 3600 + stoi(su[1]) * 60;
}

string ep2ts(int ep) {
  int h = ep / 3600;
  int m = (ep % 3600) / 60;
  int s = ep % 60;
  stringstream ss;
  ss << setfill('0') << setw(2) << h << ':' << setw(2) << m << ':' << setw(2) << s;
  return ss.str();
}

int stn2idx(string s) {
  return stoi(s.substr(1)) - 210;
}

int cost(int sidx) {
  if (sidx == 0 || sidx == 12 || sidx == 15 || sidx == 28 || sidx == 40 || sidx == 46 || sidx == 56) return 180;
  if (sidx == 10 || sidx == 11 || sidx == 35 || sidx == 39) return 240;
  if (sidx == 37) return 300;
  return 120;
}

set<int> start_times[100];

void solve() {
  string sstr;
  cin >> sstr;

  int ctime = ts2ep(sstr);

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    string us, vs, ust;
    cin >> us >> vs >> ust;
    int u = stn2idx(us), v = stn2idx(vs);
    int usv = ts2ep(ust);

    int dt = 0;
    for (int i = u; i < v; i++) {
      start_times[i].insert(usv + dt);
      dt += (cost(i) + 20);
    }
  }

  int cstn = 15;
  while (cstn < 62) {
    auto it = start_times[cstn].lower_bound(ctime);
    if (it == start_times[cstn].end()) return cout << "-1\n", void();
    ctime = *it + cost(cstn);
    cstn++;
  }

  if (ctime < 86400) cout << ep2ts(ctime) << '\n';
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
