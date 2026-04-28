#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

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

vector<int> cards[10];
vector<pii> ops[10];

void solve() {
  int n, c;
  cin >> n >> c;

  vector<int> perm;
  for (int i = 0, o, j; i < n; i++) {
    cin >> o;
    while (o--) {
      cin >> j;
      perm.push_back(i);
      cards[i].push_back(j - 1);
    }
  }

  cin.ignore();
  for (int i = 0; i < c; i++) {
    string op;
    getline(cin, op);

    for (string oi : split(op, ',')) {
      auto oarg = split(oi, ' ');
      if (oarg[0] == "ADD") ops[i].emplace_back(0, (int)oarg[1][0]);
      if (oarg[0] == "DEL") ops[i].emplace_back(1, stoi(oarg[1]));
    }
  }

  set<string> ans;
  do {
    int cpos[10];
    memset(cpos, 0, sizeof(cpos));

    string s = "";
    bool able = true;
    for (int i = 0; i < perm.size(); i++) {
      int card = cards[perm[i]][cpos[perm[i]]];
      cpos[perm[i]]++;

      for (auto [op, arg] : ops[card]) {
        if (op == 0) s += (char)arg;
        if (op == 1) {
          if (arg < s.size()) s.erase(s.begin() + arg);
          else {
            able = false;
            break;
          }
        }
      }
      if (!able) break;
    }

    if (able) s == "" ? ans.insert("EMPTY") : ans.insert(s);
    else ans.insert("ERROR");
  } while (next_permutation(perm.begin(), perm.end()));

  for (string s : ans) cout << s << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
