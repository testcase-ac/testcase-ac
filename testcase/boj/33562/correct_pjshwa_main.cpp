#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

vector<string> split(const string &str, string delim) {
  vector<string> tokens;

  string::size_type start = 0;
  string::size_type end = 0;

  while ((end = str.find(delim, start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));
    start = end + delim.size();
  }

  tokens.push_back(str.substr(start));
  return tokens;
}

struct Segment {
  char shape, color;
  int is_segment;

  Segment() : is_segment(0) {}
  Segment(char shape, char color) : shape(shape), color(color), is_segment(1) {}

  string to_string() {
    if (is_segment) return string(1, shape) + color;
    else return "--";
  }
};

struct Shape {
  Segment segments[4];

  void init_shape(string shape_str) {
    assert(shape_str.size() == 8);
    for (int i = 0; i < 4; ++i) {
      char shape = shape_str[i * 2];
      char color = shape_str[i * 2 + 1];
      if (shape != '-') segments[i] = Segment(shape, color);
    }
  }

  int is_shape() {
    for (int i = 0; i < 4; i++) {
      if (segments[i].is_segment) return 1;
    }
    return 0;
  }

  void rotate() {
    Segment tmp = segments[3];
    for (int i = 3; i > 0; i--) {
      segments[i] = segments[i - 1];
    }
    segments[0] = tmp;
  }

  int is_combinable(Shape& other) {
    for (int i = 0; i < 4; i++) {
      if (segments[i].is_segment && other.segments[i].is_segment) return 0;
    }
    return 1;
  }

  Shape combine(Shape& other) {
    Shape ret;
    for (int i = 0; i < 4; i++) {
      if (segments[i].is_segment) ret.segments[i] = segments[i];
      else ret.segments[i] = other.segments[i];
    }
    return ret;
  }

  void color(char new_color) {
    for (int i = 0; i < 4; i++) {
      if (segments[i].is_segment) segments[i].color = new_color;
    }
  }

  string to_string() {
    string ret = "";
    for (int i = 0; i < 4; i++) {
      ret += segments[i].to_string();
    }
    return ret;
  }
};

struct ShapeX {
  vector<Shape> shapes;

  pair<ShapeX, ShapeX> divide() {
    ShapeX a, b;
    for (auto shape : shapes) {
      a.shapes.push_back(shape);
      b.shapes.push_back(shape);
    }

    for (auto& shape : a.shapes) {
      for (int i = 0; i < 2; ++i) {
        shape.segments[i].is_segment = 0;
      }
    }
    for (auto& shape : b.shapes) {
      for (int i = 2; i < 4; ++i) {
        shape.segments[i].is_segment = 0;
      }
    }

    vector<Shape> new_shapes_a, new_shapes_b;
    for (auto shape : a.shapes) if (shape.is_shape()) new_shapes_a.push_back(shape);
    for (auto shape : b.shapes) if (shape.is_shape()) new_shapes_b.push_back(shape);
    a.shapes = new_shapes_a;
    b.shapes = new_shapes_b;
    return {a, b};
  }

  void rotate(int k) {
    for (auto& shape : shapes) {
      for (int i = 0; i < k; ++i) {
        shape.rotate();
      }
    }
  }

  int is_shape_x() {
    return shapes.size() > 0;
  }

  ShapeX combine(ShapeX& other) {
    int Z = shapes.size(), oZ = other.shapes.size();
    for (int si = 0;; ++si) {
      int ok = 1;
      for (int j = 0; j < oZ; ++j) for (int k = si + j; k < Z; ++k) {
        if (!shapes[k].is_combinable(other.shapes[j])) ok = 0;
      }
      if (!ok) continue;

      ShapeX ret = ShapeX();
      for (auto shape : shapes) ret.shapes.push_back(shape);
      for (int j = 0; j < oZ; ++j) {
        if (si + j < Z) {
          ret.shapes[si + j] = shapes[si + j].combine(other.shapes[j]);
        } else {
          ret.shapes.push_back(other.shapes[j]);
        }
      }
      while (ret.shapes.size() > 4) ret.shapes.pop_back();
      return ret;
    }
    return ShapeX();
  }
  
  void color(char new_color) {
    for (auto& shape : shapes) {
      shape.color(new_color);
    }
  }

  void print() {
    if (!is_shape_x()) return cout << "None\n", void();

    int Z = shapes.size();
    for (int i = 0; i < Z; ++i) {
      cout << shapes[i].to_string();
      if (i < Z - 1) cout << ':';
      else cout << '\n';
    }
  }
};

const int MAXN = 100;
ShapeX registry[MAXN + 1];

void solve() {
  int N, Q; cin >> N >> Q;
  for (int i = 1; i <= N; ++i) {
    string shape_str; cin >> shape_str;
    vector<string> tokens = split(shape_str, ":");
    for (auto& token : tokens) {
      registry[i].shapes.push_back(Shape());
      registry[i].shapes.back().init_shape(token);
    }
  }
  while (Q--) {
    int op, i, j; string kstr; cin >> op >> i >> j >> kstr;
    if (op == 1) {
      int k = stoi(kstr);
      if (!registry[i].is_shape_x()) {
        registry[j] = ShapeX();
        registry[k] = ShapeX();
        continue;
      }
      auto [a, b] = registry[i].divide();
      registry[j] = a;
      registry[k] = b;
    }
    if (op == 2) {
      int k = stoi(kstr);
      if (!registry[i].is_shape_x()) {
        registry[j] = ShapeX();
        continue;
      }
      registry[j] = registry[i];
      registry[j].rotate(k);
    }
    if (op == 3) {
      int k = stoi(kstr);
      if (!registry[i].is_shape_x() || !registry[j].is_shape_x()) {
        registry[k] = ShapeX();
        continue;
      }
      auto shape = registry[i].combine(registry[j]);
      registry[k] = shape;
    }
    if (op == 4) {
      if (!registry[i].is_shape_x()) {
        registry[j] = ShapeX();
        continue;
      }
      registry[j] = registry[i];
      registry[j].color(kstr[0]);
    }
  }

  // for (int i = 1; i <= 100; ++i) {
  //   if (registry[i].is_shape_x()) {
  //     cout << i << ": ";
  //     registry[i].print();
  //   }
  // }

  registry[100].print();
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
