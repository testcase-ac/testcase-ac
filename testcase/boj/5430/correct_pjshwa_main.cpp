#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

vector<string> split(string input, char delimiter) {
  vector<string> answer;
  stringstream ss(input);
  string temp;

  while (getline(ss, temp, delimiter)) answer.push_back(temp);
  return answer;
}

int main() {
  fast_io();

  int t;
  cin >> t;

  string ops, arrs;
  int n;

  while (t--) {
    cin >> ops >> n >> arrs;
    int sz = arrs.size(), csz = ops.size();
    auto arr = split(arrs.substr(1, sz - 2), ',');

    deque<string> darr;
    for (auto el : arr) darr.push_back(el);

    bool error = false, reversed = false;
    for (int i = 0; i < csz; i++) {
      if (ops[i] == 'R') reversed = !reversed;
      else {
        if (!n) {
          cout << "error\n";
          error = true;
          break;
        }
        if (reversed) darr.pop_back();
        else darr.pop_front();
        n--;
      }
    }

    if (error) continue;

    cout << '[';
    while (!darr.empty()) {
      if (reversed) {
        cout << darr.back();
        darr.pop_back();
      }
      else {
        cout << darr.front();
        darr.pop_front();
      }
      if (darr.size()) cout << ',';
    }
    cout << "]\n";
  }
}
