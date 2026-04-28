#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

struct Actor {
  pii position = {0, 0};
  pii size = {0, 0};

  int parent_origin_x = 0, parent_origin_y = 0;
  int anchor_point_x = 0, anchor_point_y = 0;
  int color = 1;

  int id;
  vector<int> children;
  Actor() {}
  Actor(int id) : id(id) {}

  pii screen_position();
  void plot();
};

const int MAX = 5000, MAXZ = 50, INF = 0x3f3f3f3f;
int parent[MAX + 1], ci, W, H;
int board[MAXZ + 1][MAXZ + 1];
Actor actors[MAX + 1];
map<string, int> a2i;

void add_actor(string name) {
  int id = ci++;
  a2i[name] = id;
  actors[id] = Actor(id);
}

pii Actor::screen_position() {
  if (parent[id] == -1) {
    if (id == 0) return position;
    else return {INF, INF};
  }

  Actor& par = actors[parent[id]];
  auto [px, py] = par.screen_position();
  auto [sx, sy] = par.size;

  if (px == INF) return {INF, INF};

  int ox = px, oy = py;
  if (parent_origin_x) ox += sx;
  if (parent_origin_y) oy += sy;
  if (par.anchor_point_x) ox -= sx;
  if (par.anchor_point_y) oy -= sy;

  auto [cx, cy] = position;
  return {ox + cx, oy + cy};
}

void Actor::plot() {
  auto [x, y] = screen_position();
  auto [sx, sy] = size;

  int ax = x, ay = y;
  if (anchor_point_x) ax -= sx;
  if (anchor_point_y) ay -= sy;

  for (int i = max(0, -ax); i < sx; i++) {
    int x = ax + i;
    if (x >= W) break;

    for (int j = max(0, -ay); j < sy; j++) {
      int y = ay + j;
      if (y >= H) break;
      board[y][x] = color;
    }
  }
}

void dfs_plot(int id) {
  actors[id].plot();
  for (int child_id : actors[id].children) dfs_plot(child_id);
}

void solve() {
  int Q;
  cin >> W >> H >> Q;

  memset(parent, -1, sizeof(parent));
  add_actor("Window");
  actors[0].size = {W, H}; actors[0].color = 0;

  while (Q--) {
    string op;
    cin >> op;

    if (op == "New") {
      string name;
      cin >> name;
      add_actor(name);
    }
    if (op == "Add") {
      string par, name;
      cin >> par >> name;
      int pid = a2i[par], cid = a2i[name];
      if (parent[cid] != -1) {
        int parent_id = parent[cid];
        actors[parent_id].children.erase(
          find(actors[parent_id].children.begin(), actors[parent_id].children.end(), cid)
        );
      }
      parent[cid] = pid;
      actors[pid].children.push_back(cid);
    }
    if (op == "Remove") {
      string par, name;
      cin >> par >> name;
      int id = a2i[name], parent_id = a2i[par];
      if (parent[id] == parent_id) {
        parent[id] = -1;
        actors[parent_id].children.erase(
          find(actors[parent_id].children.begin(), actors[parent_id].children.end(), id)
        );
      }
    }
    if (op == "Unparent") {
      string name;
      cin >> name;
      int id = a2i[name];
      if (parent[id] != -1) {
        int pid = parent[id];
        actors[pid].children.erase(
          find(actors[pid].children.begin(), actors[pid].children.end(), id)
        );
        parent[id] = -1;
      }
    }
    if (op == "SetProperty") {
      string name, prop;
      cin >> name >> prop;
      int id = a2i[name];

      if (prop == "POSITION") cin >> actors[id].position.first >> actors[id].position.second;
      if (prop == "SIZE") cin >> actors[id].size.first >> actors[id].size.second;
      if (prop == "COLOR") cin >> actors[id].color;
      if (prop == "PARENT_ORIGIN") cin >> actors[id].parent_origin_x >> actors[id].parent_origin_y;
      if (prop == "ANCHOR_POINT") cin >> actors[id].anchor_point_x >> actors[id].anchor_point_y;
    }

    if (op == "GetProperty") {
      string name, prop;
      cin >> name >> prop;
      int id = a2i[name];

      if (prop == "POSITION") cout << actors[id].position.first << " " << actors[id].position.second << '\n';
      if (prop == "SIZE") cout << actors[id].size.first << " " << actors[id].size.second << '\n';
      if (prop == "COLOR") cout << actors[id].color << '\n';
      if (prop == "PARENT_ORIGIN") cout << actors[id].parent_origin_x << " " << actors[id].parent_origin_y << '\n';
      if (prop == "ANCHOR_POINT") cout << actors[id].anchor_point_x << " " << actors[id].anchor_point_y << '\n';
      if (prop == "SCREEN_POSITION") {
        auto [x, y] = actors[id].screen_position();

        if (x == INF) cout << "0 0\n";
        else cout << x << " " << y << '\n';
      }
    }
  }

  dfs_plot(0);
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      cout << board[i][j];
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
