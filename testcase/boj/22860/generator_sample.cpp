#include "testlib.h"

#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(1, 12);
    int m = rnd.next(1, 24);

    vector<string> folder(n + 1);
    vector<int> parent(n + 1, -1);
    vector<string> path(n + 1);
    folder[0] = "main";
    path[0] = "main";

    for (int i = 1; i <= n; ++i) {
        folder[i] = "D" + to_string(i);
        if (mode == 0) {
            parent[i] = 0;
        } else if (mode == 1) {
            parent[i] = i - 1;
        } else if (mode == 2) {
            parent[i] = rnd.next(0, i - 1);
        } else {
            parent[i] = rnd.wnext(i, -2);
        }
        path[i] = path[parent[i]] + "/" + folder[i];
    }

    vector<pair<string, string>> folders;
    for (int i = 1; i <= n; ++i) {
        folders.push_back({folder[parent[i]], folder[i]});
    }
    shuffle(folders.begin(), folders.end());

    int fileNameCount = rnd.next(1, min(8, m));
    vector<string> fileNames;
    for (int i = 1; i <= fileNameCount; ++i) {
        fileNames.push_back("F" + to_string(i));
    }

    vector<set<string>> used(n + 1);
    vector<pair<string, string>> files;
    for (int i = 0; i < m; ++i) {
        int p = rnd.next(0, n);
        string name;
        for (int attempt = 0; attempt < 30; ++attempt) {
            name = rnd.any(fileNames);
            if (!used[p].count(name)) break;
            p = rnd.next(0, n);
        }
        if (used[p].count(name)) {
            name = "U" + to_string(i + 1);
        }
        used[p].insert(name);
        files.push_back({folder[p], name});
    }
    shuffle(files.begin(), files.end());

    int q = rnd.next(1, min(20, n + 1));
    vector<int> queryIds;
    queryIds.push_back(0);
    for (int i = 1; i <= n; ++i) {
        queryIds.push_back(i);
    }
    shuffle(queryIds.begin() + 1, queryIds.end());
    queryIds.resize(q);
    shuffle(queryIds.begin(), queryIds.end());

    println(n, m);
    for (const auto& [p, f] : folders) {
        println(p, f, 1);
    }
    for (const auto& [p, f] : files) {
        println(p, f, 0);
    }
    println(q);
    for (int id : queryIds) {
        println(path[id]);
    }

    return 0;
}
