#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N; cin.ignore();

  map<string, string> by_name;
  for (int i = 0; i < N; ++i) {
    string name, party;
    getline(cin, name); getline(cin, party);
    by_name[name] = party;
  }
  
  int M; cin >> M; cin.ignore();
  map<string, int> votes_by_party;
  while (M--) {
    string vote; getline(cin, vote);
    if (by_name.count(vote)) ++votes_by_party[vote];
  }
  if (votes_by_party.empty()) {
    cout << "tie\n";
    return;
  }

  vector<pair<int, string>> votes;
  for (auto& [party, vote] : votes_by_party) votes.emplace_back(vote, party);
  sort(votes.begin(), votes.end(), greater<>());

  if (votes.size() >= 2 && votes[0].first == votes[1].first) cout << "tie\n";
  else cout << by_name[votes[0].second] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
