#include "testlib.h"

#include <iterator>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Album {
    int parent;
    string name;
    set<string> photos;
    set<pair<string, int>> children;
};

string makeName(const string& prefix, int id) {
    string result = prefix;
    ++id;
    while (id > 0) {
        --id;
        result.push_back(char('a' + id % 26));
        id /= 26;
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(30, 120);
    int targetDepth = rnd.next(2, 5);
    int cur = 0;
    int albumId = 0;
    int photoId = 0;
    vector<Album> albums;
    vector<pair<string, string>> commands;
    albums.push_back({-1, "album", {}, {}});

    auto addCommand = [&](const string& op, const string& arg) {
        commands.push_back({op, arg});
    };

    auto currentChildren = [&]() -> vector<pair<string, int>> {
        return vector<pair<string, int>>(albums[cur].children.begin(), albums[cur].children.end());
    };

    auto currentPhotos = [&]() -> vector<string> {
        return vector<string>(albums[cur].photos.begin(), albums[cur].photos.end());
    };

    auto eraseAlbum = [&](auto&& self, int node) -> void {
        for (auto child : albums[node].children) {
            self(self, child.second);
        }
        albums[node].children.clear();
        albums[node].photos.clear();
    };

    auto removeChildByName = [&](const string& name) {
        auto it = albums[cur].children.lower_bound({name, -1});
        if (it == albums[cur].children.end() || it->first != name) {
            return;
        }
        int node = it->second;
        eraseAlbum(eraseAlbum, node);
        albums[cur].children.erase(it);
    };

    auto removeCurrentChildren = [&]() {
        for (auto child : albums[cur].children) {
            eraseAlbum(eraseAlbum, child.second);
        }
        albums[cur].children.clear();
    };

    for (int step = 0; step < n; ++step) {
        int mode = rnd.next(100);
        int depth = 0;
        for (int node = cur; node != 0 && node != -1; node = albums[node].parent) {
            ++depth;
        }

        if (mode < 24 || albums.size() <= 2) {
            string name;
            if (!albums[cur].children.empty() && rnd.next(100) < 25) {
                name = rnd.any(currentChildren()).first;
            } else {
                name = makeName("a", albumId++);
            }
            addCommand("mkalb", name);
            auto it = albums[cur].children.lower_bound({name, -1});
            if (it == albums[cur].children.end() || it->first != name) {
                int node = int(albums.size());
                albums.push_back({cur, name, {}, {}});
                albums[cur].children.insert({name, node});
            }
        } else if (mode < 43) {
            string name;
            if (!albums[cur].photos.empty() && rnd.next(100) < 30) {
                name = rnd.any(currentPhotos());
            } else {
                name = makeName("p", photoId++);
            }
            addCommand("insert", name);
            albums[cur].photos.insert(name);
        } else if (mode < 58) {
            string arg;
            int kind = rnd.next(4);
            if (kind == 0) {
                arg = "-1";
                if (!albums[cur].children.empty()) {
                    removeChildByName(albums[cur].children.begin()->first);
                }
            } else if (kind == 1) {
                arg = "1";
                if (!albums[cur].children.empty()) {
                    removeChildByName(prev(albums[cur].children.end())->first);
                }
            } else if (kind == 2) {
                arg = "0";
                removeCurrentChildren();
            } else {
                auto children = currentChildren();
                arg = children.empty() || rnd.next(100) < 30 ? makeName("missing", rnd.next(30))
                                                            : rnd.any(children).first;
                removeChildByName(arg);
            }
            addCommand("rmalb", arg);
        } else if (mode < 73) {
            string arg;
            int kind = rnd.next(4);
            if (kind == 0) {
                arg = "-1";
                if (!albums[cur].photos.empty()) {
                    albums[cur].photos.erase(albums[cur].photos.begin());
                }
            } else if (kind == 1) {
                arg = "1";
                if (!albums[cur].photos.empty()) {
                    albums[cur].photos.erase(prev(albums[cur].photos.end()));
                }
            } else if (kind == 2) {
                arg = "0";
                albums[cur].photos.clear();
            } else {
                auto photos = currentPhotos();
                arg = photos.empty() || rnd.next(100) < 30 ? makeName("ghost", rnd.next(30))
                                                           : rnd.any(photos);
                albums[cur].photos.erase(arg);
            }
            addCommand("delete", arg);
        } else {
            string arg;
            auto children = currentChildren();
            if (!children.empty() && depth < targetDepth && rnd.next(100) < 60) {
                auto child = rnd.any(children);
                arg = child.first;
                cur = child.second;
            } else if (cur != 0 && rnd.next(100) < 45) {
                arg = "..";
                cur = albums[cur].parent;
            } else if (rnd.next(100) < 25) {
                arg = "/";
                cur = 0;
            } else {
                arg = children.empty() || rnd.next(100) < 40 ? makeName("none", rnd.next(30))
                                                             : rnd.any(children).first;
                for (auto child : children) {
                    if (child.first == arg) {
                        cur = child.second;
                        break;
                    }
                }
            }
            addCommand("ca", arg);
        }
    }

    println(int(commands.size()));
    for (auto command : commands) {
        println(command.first, command.second);
    }

    return 0;
}
