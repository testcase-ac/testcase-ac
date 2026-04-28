#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>

const int INF = 0x3f3f3f3f;

int main() {
  int nodes_cnt, roads_cnt;
  std::cin >> nodes_cnt >> roads_cnt;

  int start_node = 1, end_node = nodes_cnt;

  std::vector<std::pair<int, int>> adj_graph[nodes_cnt + 1];
  std::vector<int> reverse_adj_graph[nodes_cnt + 1];
  for (int i = 0; i < roads_cnt; ++i) {
    int from, to, weight;
    std::cin >> from >> to >> weight;

    // minimize negative value of weight = maximize weight
    adj_graph[from].emplace_back(to, -weight);

    // will use to mark all nodes that can reach the end node
    reverse_adj_graph[to].emplace_back(from);
  }

  std::vector<bool> src_reachable(nodes_cnt + 1, false);
  std::vector<bool> dest_reachable(nodes_cnt + 1, false);

  {
    std::queue<int> bfs_queue;
    std::bitset<101> visited;

    visited.reset();
    bfs_queue.push(start_node); visited[start_node] = true;
    while (!bfs_queue.empty()) {
      int v = bfs_queue.front(); bfs_queue.pop();
      src_reachable[v] = true;

      for (auto& [u, _] : adj_graph[v]) {
        if (visited[u]) continue;

        bfs_queue.push(u); visited[u] = true;
      }
    }

    visited.reset();
    bfs_queue.push(end_node); visited[end_node] = true;
    while (!bfs_queue.empty()) {
      int v = bfs_queue.front(); bfs_queue.pop();
      dest_reachable[v] = true;

      for (int u : reverse_adj_graph[v]) {
        if (visited[u]) continue;

        bfs_queue.push(u); visited[u] = true;
      }
    }
  }

  std::vector<int> cdist(nodes_cnt + 1, INF), prev(nodes_cnt + 1, -1);
  cdist[start_node] = 0;

  for (int iter = 1; iter <= nodes_cnt; ++iter) {
    for (int from = 1; from <= nodes_cnt; ++from) {

      for (auto& [to, weight] : adj_graph[from]) {

        if (cdist[from] != INF && cdist[to] > cdist[from] + weight) {

          cdist[to] = cdist[from] + weight;
          prev[to] = from;

          // has a negative cycle && affects route from start to end
          if (iter == nodes_cnt && src_reachable[to] && dest_reachable[to]) {
            std::cout << "-1\n";
            return 0;
          }

        }

      }

    }
  }

  int trace_node = end_node;
  std::stack<int> trajectory;

  while (trace_node != -1) {
    trajectory.push(trace_node);
    trace_node = prev[trace_node];
  }

  while (!trajectory.empty()) {
    std::cout << trajectory.top() << ' ';
    trajectory.pop();
  }
  std::cout << '\n';

}
