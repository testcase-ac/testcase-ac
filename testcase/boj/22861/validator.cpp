#include "testlib.h"

#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string name;
    int parent = -1;
    bool alive = true;
    map<string, int> folders;
    set<string> files;
};

vector<string> splitPath(const string& path) {
    vector<string> parts;
    string current;
    for (char ch : path) {
        if (ch == '/') {
            parts.push_back(current);
            current.clear();
        } else {
            current.push_back(ch);
        }
    }
    parts.push_back(current);
    return parts;
}

int resolvePath(const vector<Node>& nodes, const string& path) {
    vector<string> parts = splitPath(path);
    ensuref(!parts.empty() && parts[0] == "main", "path must start with main: %s", path.c_str());
    int cur = 0;
    for (int i = 1; i < (int)parts.size(); ++i) {
        ensuref(!parts[i].empty(), "empty path component in path: %s", path.c_str());
        ensuref((int)parts[i].size() <= 10, "path component is too long in path: %s", path.c_str());
        for (char ch : parts[i]) {
            ensuref(('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z') || ('0' <= ch && ch <= '9'),
                    "path component has invalid character in path: %s", path.c_str());
        }
        auto it = nodes[cur].folders.find(parts[i]);
        ensuref(it != nodes[cur].folders.end(), "folder path does not exist: %s", path.c_str());
        cur = it->second;
        ensuref(nodes[cur].alive, "folder path uses deleted folder: %s", path.c_str());
    }
    return cur;
}

bool isAncestor(const vector<Node>& nodes, int ancestor, int node) {
    for (int cur = node; cur != -1; cur = nodes[cur].parent) {
        if (cur == ancestor) return true;
    }
    return false;
}

void moveContents(vector<Node>& nodes, int source, int destination) {
    ensuref(source != 0, "cannot move and delete main folder");
    for (const string& file : nodes[source].files) {
        nodes[destination].files.insert(file);
    }
    nodes[source].files.clear();

    vector<pair<string, int>> children(nodes[source].folders.begin(), nodes[source].folders.end());
    nodes[source].folders.clear();
    for (auto [name, child] : children) {
        auto existing = nodes[destination].folders.find(name);
        if (existing == nodes[destination].folders.end()) {
            nodes[destination].folders[name] = child;
            nodes[child].parent = destination;
        } else {
            moveContents(nodes, child, existing->second);
        }
    }

    int parent = nodes[source].parent;
    ensuref(parent != -1, "source folder has no parent: %s", nodes[source].name.c_str());
    nodes[parent].folders.erase(nodes[source].name);
    nodes[source].parent = -1;
    nodes[source].alive = false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();

    vector<Node> nodes(1);
    nodes[0].name = "main";
    map<string, int> folderId;
    folderId["main"] = 0;

    struct Entry {
        string parent;
        string name;
        int c;
    };
    vector<Entry> entries;
    int folderEntries = 0;
    int fileEntries = 0;
    for (int i = 0; i < n + m; ++i) {
        string p = inf.readToken("[A-Za-z0-9]{1,10}", "P");
        inf.readSpace();
        string f = inf.readToken("[A-Za-z0-9]{1,10}", "F");
        inf.readSpace();
        int c = inf.readInt(0, 1, "C");
        inf.readEoln();

        ensuref(f != "main", "main is reserved as the root folder name");
        entries.push_back({p, f, c});
        if (c == 1) {
            ++folderEntries;
            ensuref(!folderId.count(f), "duplicate folder name: %s", f.c_str());
            folderId[f] = (int)nodes.size();
            nodes.push_back(Node{f});
        } else {
            ++fileEntries;
        }
    }
    ensuref(folderEntries == n, "expected %d folder entries, found %d", n, folderEntries);
    ensuref(fileEntries == m, "expected %d file entries, found %d", m, fileEntries);

    for (const Entry& entry : entries) {
        auto parentIt = folderId.find(entry.parent);
        ensuref(parentIt != folderId.end(), "parent folder is not defined: %s", entry.parent.c_str());
        int parent = parentIt->second;

        // CHECK: A folder and file with the same name under one parent would make filesystem-style paths ambiguous.
        ensuref(!nodes[parent].files.count(entry.name), "duplicate child name under folder %s: %s",
                entry.parent.c_str(), entry.name.c_str());
        ensuref(!nodes[parent].folders.count(entry.name), "duplicate child name under folder %s: %s",
                entry.parent.c_str(), entry.name.c_str());

        if (entry.c == 1) {
            int child = folderId[entry.name];
            ensuref(child != parent, "folder cannot be its own parent: %s", entry.name.c_str());
            nodes[child].parent = parent;
            nodes[parent].folders[entry.name] = child;
        } else {
            nodes[parent].files.insert(entry.name);
        }
    }

    vector<int> state(nodes.size(), 0);
    auto dfs = [&](auto&& self, int v) -> void {
        ensuref(state[v] != 1, "initial folder tree contains a cycle at %s", nodes[v].name.c_str());
        if (state[v] == 2) return;
        state[v] = 1;
        for (const auto& [name, child] : nodes[v].folders) {
            self(self, child);
        }
        state[v] = 2;
    };
    dfs(dfs, 0);
    for (int i = 1; i < (int)nodes.size(); ++i) {
        ensuref(state[i] == 2, "folder is not reachable from main: %s", nodes[i].name.c_str());
    }

    int k = inf.readInt(0, 1000, "K");
    inf.readEoln();
    for (int i = 0; i < k; ++i) {
        string a = inf.readToken("[A-Za-z0-9/]{4,11004}", "A");
        inf.readSpace();
        string b = inf.readToken("[A-Za-z0-9/]{4,11004}", "B");
        inf.readEoln();

        int source = resolvePath(nodes, a);
        int destination = resolvePath(nodes, b);
        ensuref(source != destination, "move source and destination are the same: %s", a.c_str());
        ensuref(!isAncestor(nodes, source, destination), "A is an ancestor of B for move %d", i + 1);
        moveContents(nodes, source, destination);
    }

    int q = inf.readInt(1, 1000, "Q");
    inf.readEoln();
    for (int i = 0; i < q; ++i) {
        string query = inf.readToken("[A-Za-z0-9/]{4,11004}", "query");
        inf.readEoln();
        resolvePath(nodes, query);
    }

    inf.readEof();
}
