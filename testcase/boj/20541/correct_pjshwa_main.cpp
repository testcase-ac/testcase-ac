#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;

int new_it = 0;
struct Album {
  string name;
  set<string> photos;
  set<pair<string, int>> child_albums;
};
Album albums[MAXN];
int parent[MAXN];

struct Stat {
  int removed_albums_count;
  int removed_photos_count;
} stat;

void init_stat() {
  stat = {0, 0};
}

void erase_album(int i) {
  ++stat.removed_albums_count;
  stat.removed_photos_count += albums[i].photos.size();

  for (auto [name, idx] : albums[i].child_albums) {
    erase_album(idx);
  }

  albums[i] = {"", {}, {}};
  parent[i] = -1;
}

void rmalb(int i, string& album_name) {
  if (albums[i].child_albums.empty()) return;

  if (album_name == "-1") {
    auto it = albums[i].child_albums.begin();
    auto [name, idx] = *it;
    erase_album(idx);
    albums[i].child_albums.erase(it);
  }
  else if (album_name == "0") {
    for (auto [name, idx] : albums[i].child_albums) {
      erase_album(idx);
    }
    albums[i].child_albums.clear();
  }
  else if (album_name == "1") {
    auto it = prev(albums[i].child_albums.end());
    auto [name, idx] = *it;
    erase_album(idx);
    albums[i].child_albums.erase(it);
  }
  else {
    auto it = albums[i].child_albums.lower_bound({album_name, -1});
    if (it != albums[i].child_albums.end() && it->first == album_name) {
      auto [name, idx] = *it;
      erase_album(idx);
      albums[i].child_albums.erase(it);
    }
  }
}

void delete_photo(int i, string& photo_name) {
  if (albums[i].photos.empty()) return;

  if (photo_name == "-1") {
    albums[i].photos.erase(albums[i].photos.begin());
    ++stat.removed_photos_count;
  }
  else if (photo_name == "0") {
    stat.removed_photos_count += albums[i].photos.size();
    albums[i].photos.clear();
  }
  else if (photo_name == "1") {
    albums[i].photos.erase(prev(albums[i].photos.end()));
    ++stat.removed_photos_count;
  }
  else {
    auto it = albums[i].photos.find(photo_name);
    if (it != albums[i].photos.end()) {
      albums[i].photos.erase(it);
      ++stat.removed_photos_count;
    }
  }
}

void solve() {
  int N; cin >> N;
  albums[new_it++] = {"album", {}, {}};

  memset(parent, -1, sizeof(parent));

  int cur = 0;
  for (int i = 0; i < N; ++i) {
    string op; cin >> op;
    if (op == "mkalb") {
      string S; cin >> S;

      auto it = albums[cur].child_albums.lower_bound({S, -1});
      if (it != albums[cur].child_albums.end() && it->first == S) {
        cout << "duplicated album name\n";
      }
      else {
        albums[cur].child_albums.insert({S, new_it});
        albums[new_it] = {S, {}, {}};
        parent[new_it] = cur;
        ++new_it;
      }
    }
    if (op == "rmalb") {
      string S; cin >> S;
      init_stat();
      rmalb(cur, S);
      cout << stat.removed_albums_count << ' ' << stat.removed_photos_count << '\n';
    }
    if (op == "insert") {
      string S; cin >> S;
      if (albums[cur].photos.count(S)) cout << "duplicated photo name\n";
      else albums[cur].photos.insert(S);
    }
    if (op == "delete") {
      string S; cin >> S;
      init_stat();
      delete_photo(cur, S);
      cout << stat.removed_photos_count << '\n';
    }
    if (op == "ca") {
      string S; cin >> S;
      if (S == "..") {
        if (cur != 0) cur = parent[cur];
      }
      else if (S == "/") cur = 0;
      else {
        auto it = albums[cur].child_albums.lower_bound({S, -1});
        if (it != albums[cur].child_albums.end() && it->first == S) {
          cur = it->second;
        }
      }
      cout << albums[cur].name << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
