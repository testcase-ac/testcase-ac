#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
int a[MAX];
pair<int, int> c[MAX + 1];
int main() {
  fast_io();

  int N, T, D, K;
  string op;
  cin >> N >> T;
  for (int i = 0; i < T; i++) cin >> a[i];

  queue<pair<int, pair<string, int>>> op_queue;
  for (int i = 0; i < T; i++) {
    cin >> D >> op;
    if (op == "next") K = 0;
    else cin >> K;
    op_queue.push({D, {op, K}});
  }

  map<int, int> cards_player_map;
  pair<string, int> opK;
  for (int i = 0; i < T; i++) {
    int player = a[i];
    if (c[player].first == 0) {
      tie(D, opK) = op_queue.front();
      tie(op, K) = opK;
      op_queue.pop();

      if (op == "acquire") {
        if (cards_player_map.count(K) && cards_player_map[K] != 0) c[player] = {K, D};
        else cards_player_map[K] = player;
      }
      else if (op == "release") cards_player_map[K] = 0;
    }
    else {
      tie(K, D) = c[player];
      if (!cards_player_map.count(K) || cards_player_map[K] == 0) {
        c[player] = {0, 0};
        cards_player_map[K] = player;
      }
    }
    cout << D << '\n';
  }

}
