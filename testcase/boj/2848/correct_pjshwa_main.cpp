#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

vector<int> graph[26];
int indegree[26];
bool used[26];
string words[100];
int main() {
  fast_io();

  int n, pt, sz, a, wsz1, wsz2, us = 0;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> words[i];
    sz = words[i].size();
    for (int j = 0; j < sz; j++) used[words[i][j] - 'a'] = 1;
  }

  for (int i = 0; i < n - 1; i++) {
    pt = 0;
    wsz1 = words[i].size();
    wsz2 = words[i + 1].size();
    while (pt < min(wsz1, wsz2) && words[i][pt] == words[i + 1][pt]) pt++;
    if (pt == wsz1) continue;
    if (pt == wsz2) {
      cout << "!\n";
      return 0;
    }

    graph[words[i][pt] - 'a'].push_back(words[i + 1][pt] - 'a');
    indegree[words[i + 1][pt] - 'a']++;
  }

  queue<int> q;
  for (int i = 0; i < 26; i++) {
    if (used[i]) {
      us++;
      if (!indegree[i]) q.push(i);
    }
  }

  vector<int> ans;
  bool flag = false;
  for (int i = 1; i <= us; i++) {
    if (q.empty()) {
      cout << "!\n";
      return 0;
    }

    if (q.size() > 1) flag = true;

    a = q.front();
    ans.push_back(a);
    q.pop();

    for (int dst : graph[a]) {
      if (!--indegree[dst]) q.push(dst);
    }
  }

  if (flag) cout << '?';
  else for (auto e : ans) cout << (char)(e + 'a');
  cout << '\n';
}
