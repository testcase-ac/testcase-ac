#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

struct Folder {
    string name;
    int parent = -1;
    bool alive = true;
    vector<int> children;
    set<string> childNames;
    set<string> files;
};

string folderName(int id) {
    return "D" + to_string(id);
}

string fileName(int id) {
    return "F" + to_string(id);
}

bool isAncestor(const vector<Folder>& folders, int ancestor, int node) {
    for (int cur = node; cur != -1; cur = folders[cur].parent) {
        if (cur == ancestor) return true;
    }
    return false;
}

string pathOf(const vector<Folder>& folders, int node) {
    vector<string> parts;
    for (int cur = node; cur != -1; cur = folders[cur].parent) {
        parts.push_back(folders[cur].name);
    }
    reverse(parts.begin(), parts.end());

    string path = parts[0];
    for (int i = 1; i < (int)parts.size(); ++i) {
        path += "/" + parts[i];
    }
    return path;
}

vector<int> aliveFolders(const vector<Folder>& folders, bool includeRoot) {
    vector<int> result;
    for (int i = includeRoot ? 0 : 1; i < (int)folders.size(); ++i) {
        if (folders[i].alive) result.push_back(i);
    }
    return result;
}

void moveContents(vector<Folder>& folders, int source, int destination) {
    for (const string& file : folders[source].files) {
        folders[destination].files.insert(file);
        folders[destination].childNames.insert(file);
    }
    folders[source].files.clear();

    vector<int> children = folders[source].children;
    folders[source].children.clear();
    for (int child : children) {
        folders[destination].children.push_back(child);
        folders[destination].childNames.insert(folders[child].name);
        folders[child].parent = destination;
    }

    int parent = folders[source].parent;
    vector<int>& siblings = folders[parent].children;
    siblings.erase(remove(siblings.begin(), siblings.end(), source), siblings.end());
    folders[parent].childNames.erase(folders[source].name);

    folders[source].parent = -1;
    folders[source].alive = false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int folderCount = rnd.next(3, 12);
    int fileCount = rnd.next(3, 18);
    int fileNameKinds = rnd.next(2, min(fileCount + folderCount, 12));

    vector<Folder> folders(folderCount + 1);
    folders[0].name = "main";
    vector<tuple<string, string, int>> entries;

    for (int id = 1; id <= folderCount; ++id) {
        folders[id].name = folderName(id);
        int parent = rnd.next(0, id - 1);
        folders[id].parent = parent;
        folders[parent].children.push_back(id);
        folders[parent].childNames.insert(folders[id].name);
        entries.push_back({folders[parent].name, folders[id].name, 1});
    }

    for (int id = 0; id < fileCount; ++id) {
        vector<pair<int, string>> candidates;
        for (int parent = 0; parent <= folderCount; ++parent) {
            for (int nameId = 0; nameId < fileNameKinds; ++nameId) {
                string name = fileName(nameId);
                if (!folders[parent].childNames.count(name)) {
                    candidates.push_back({parent, name});
                }
            }
        }
        auto [parent, name] = rnd.any(candidates);
        folders[parent].files.insert(name);
        folders[parent].childNames.insert(name);
        entries.push_back({folders[parent].name, name, 0});
    }

    shuffle(entries.begin(), entries.end());

    vector<pair<string, string>> moves;
    int moveLimit = rnd.next(0, min(10, folderCount));
    for (int step = 0; step < moveLimit; ++step) {
        vector<pair<int, int>> candidates;
        vector<int> sources = aliveFolders(folders, false);
        vector<int> destinations = aliveFolders(folders, true);
        for (int source : sources) {
            for (int destination : destinations) {
                if (source == destination) continue;
                if (isAncestor(folders, source, destination)) continue;
                candidates.push_back({source, destination});
            }
        }
        if (candidates.empty()) break;

        auto [source, destination] = rnd.any(candidates);
        moves.push_back({pathOf(folders, source), pathOf(folders, destination)});
        moveContents(folders, source, destination);
    }

    vector<string> queries;
    int queryCount = rnd.next(1, 10);
    vector<int> queryCandidates = aliveFolders(folders, true);
    for (int i = 0; i < queryCount; ++i) {
        queries.push_back(pathOf(folders, rnd.any(queryCandidates)));
    }

    println(folderCount, fileCount);
    for (const auto& [parent, name, isFolder] : entries) {
        println(parent, name, isFolder);
    }
    println((int)moves.size());
    for (const auto& [source, destination] : moves) {
        println(source, destination);
    }
    println((int)queries.size());
    for (const string& query : queries) {
        println(query);
    }

    return 0;
}
