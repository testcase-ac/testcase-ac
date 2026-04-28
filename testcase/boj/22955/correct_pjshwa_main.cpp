#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tll = tuple<ll, ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
const ll INF = 1e14;
char board[MAX + 1][MAX + 1];
vector<tll> graph[MAX + 1][MAX + 1];
ll cdist[MAX + 1][MAX + 1];
pair<int, int> from[MAX + 1][MAX + 1];
int n, m;

void dijk(int si, int sj) {
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cdist[i][j] = INF;
  cdist[si][sj] = 0;

  priority_queue<tll, vector<tll>, greater<tll>> pq;
  pq.push({0, si, sj});

  while (!pq.empty()) {
    auto [wi, ui, uj] = pq.top();
    pq.pop();

    if (wi > cdist[ui][uj]) continue;

    for (auto &t : graph[ui][uj]) {
      auto [vi, vj, di] = t;
      if (cdist[vi][vj] > di + wi) {
        cdist[vi][vj] = di + wi;
        from[vi][vj] = {ui, uj};
        pq.push({cdist[vi][vj], vi, vj});
      }
    }
  }
}

void solve() {
  cin >> n >> m;
  for (int i = 0; i < n; i++) cin >> board[i];

  int si, sj, ei, ej;
  for (int i = n - 1; i >= 0; i--) for (int j = 0; j < m; j++) {
    if (board[i][j] == 'D' || board[i][j] == 'X') continue;
    if (board[i][j] == 'C') si = i, sj = j;
    if (board[i][j] == 'E') ei = i, ej = j;
    if (j > 0 && board[i][j - 1] != 'D') graph[i][j].push_back({i, j - 1, 1});
    if (j < m - 1 && board[i][j + 1] != 'D') graph[i][j].push_back({i, j + 1, 1});
    if (i > 0 && board[i][j] == 'L' && board[i - 1][j] != 'D' && board[i - 1][j] != 'X') {
      graph[i][j].push_back({i - 1, j, 5});
      graph[i - 1][j].push_back({i, j, 5});
    }
    int k = i - 1;
    while (k >= 0 && board[k][j] == 'X') {
      graph[k][j].push_back({i, j, 10});
      k--;
    }
  }

  dijk(si, sj);

  // if (cdist[ei][ej] != INF) {
  //   auto [ci, cj] = pair<int, int>(ei, ej);
  //   cout << "pi: " << ei << " pj: " << ej << endl;
  //   while (ci != si || cj != sj) {
  //     auto [pi, pj] = from[ci][cj];
  //     cout << "pi: " << pi << " pj: " << pj << endl;
  //     ci = pi, cj = pj;
  //   }
  // }

  if (cdist[ei][ej] == INF) cout << "dodo sad\n";
  else cout << cdist[ei][ej] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

// TC Random Generator
// loop do
//   n, m = 4, 4
//   a = 4.times.map do |i|
//     4.times.map do
//       i == 3 ? 'DFL'[rand(3)] : 'DFXL'[rand(4)]
//     end.join
//   end
//   si, sj = rand(4), rand(4)
//   ei, ej = rand(4), rand(4)
//   a[si][sj] = 'C'
//   a[ei][ej] = 'E'
//   next if si == ei && sj == ej
//   File.write('in', "#{n} #{m}\n#{a.join("\n")}")
//   res1 = `./22955 < in`.chomp
//   res2 = `./22955-a < in`.chomp
//   p res1
//   break unless res1 == res2
// end

