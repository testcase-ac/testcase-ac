#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void replace_all(std::string& source, const std::string from, const std::string to) {
  std::string newString;
  newString.reserve(source.length());  // avoids a few memory allocations

  std::string::size_type lastPos = 0;
  std::string::size_type findPos;

  while (std::string::npos != (findPos = source.find(from, lastPos))) {
    newString.append(source, lastPos, findPos - lastPos);
    newString += to;
    lastPos = findPos + from.length();
  }

  // Care for the rest after last occurrence
  newString += source.substr(lastPos);

  source.swap(newString);
}

void solve() {
  string s;
  cin >> s;

  set<string> u;
  queue<string> q;
  q.push(s);
  u.insert(s);

  while (!q.empty()) {
    string x = q.front();
    q.pop();

    if (x == "ABC") return cout << "Yes\n", void();

    for (int i = 0; i < 3; i++) {
      string f = "";
      bool able = true;
      for (int j = 0; j < x.size(); j++) {
        if (j + 2 < x.size() && x[j] == 'A' && x[j + 1] == 'B' && x[j + 2] == 'C') {
          f += 'A' + i, j += 2;
        }
        else if (x[j] == 'A' + i) able = false;
        else f += x[j];
      }

      if (able && !u.count(f)) u.insert(f), q.push(f);
    }
  }

  cout << "No\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
