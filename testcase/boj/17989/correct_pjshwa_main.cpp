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

int main() {
  fast_io();

  int n, m, k;
  cin >> n >> m >> k;
  cin.ignore();
  priority_queue<pair<string, int>, vector<pair<string, int>>, greater<pair<string, int>>> pq;
  pq.push({"Jane Eyre", k});

  for (int i = 0; i < n; i++) {
    string line;
    getline(cin, line);
    auto arr = split(line.substr(1), '"');
    string book = arr[0];
    int page = stoi(arr[1].substr(1));
    pq.push({book, page});
  }

  vector<tuple<int, string, int>> v;
  for (int i = 0; i < m; i++) {
    string line;
    getline(cin, line);
    auto arr = split(line, '"');
    int stime = stoi(arr[0]);
    string book = arr[1];
    int page = stoi(arr[2].substr(1));
    v.push_back({stime, book, page});
  }
  sort(v.begin(), v.end());

  long long ctime = 0;
  int vi = 0;
  while (!pq.empty()) {
    while (vi < m && ctime >= get<0>(v[vi])) {
      pq.push({get<1>(v[vi]), get<2>(v[vi])});
      vi++;
    }

    auto [book, page] = pq.top();
    pq.pop();

    ctime += page;
    if (book == "Jane Eyre") return cout << ctime << '\n', 0;
  }
}
