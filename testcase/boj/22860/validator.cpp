#include "testlib.h"

#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

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

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const string namePattern = "[a-zA-Z0-9]{1,10}";
    const string pathPattern = "[a-zA-Z0-9/]{1,11010}";

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();

    set<string> folders;
    folders.insert("main");
    map<string, map<string, int>> childFolders;
    map<string, set<string>> childFiles;

    int folderCount = 0;
    int fileCount = 0;
    for (int i = 0; i < n + m; ++i) {
        string parent = inf.readToken(namePattern, "P");
        inf.readSpace();
        string child = inf.readToken(namePattern, "F");
        inf.readSpace();
        int c = inf.readInt(0, 1, "C");
        inf.readEoln();

        if (c == 1) {
            ++folderCount;
            ensuref(child != "main", "folder entry %d uses reserved root name main", i + 1);
            ensuref(folders.insert(child).second,
                    "duplicate folder name at entry %d: %s", i + 1, child.c_str());
            childFolders[parent][child] = 1;
        } else {
            ++fileCount;
            ensuref(childFiles[parent].insert(child).second,
                    "duplicate file name in folder %s at entry %d: %s",
                    parent.c_str(), i + 1, child.c_str());
        }
    }
    ensuref(folderCount == n, "expected %d folder entries, found %d", n, folderCount);
    ensuref(fileCount == m, "expected %d file entries, found %d", m, fileCount);

    for (const auto& [parent, _] : childFolders) {
        ensuref(folders.count(parent), "unknown parent folder: %s", parent.c_str());
    }
    for (const auto& [parent, _] : childFiles) {
        ensuref(folders.count(parent), "unknown parent folder: %s", parent.c_str());
    }

    set<string> reachable;
    vector<string> stack = {"main"};
    reachable.insert("main");
    while (!stack.empty()) {
        string parent = stack.back();
        stack.pop_back();
        for (const auto& [child, _] : childFolders[parent]) {
            ensuref(reachable.insert(child).second,
                    "folder is reachable through multiple paths or a cycle: %s", child.c_str());
            stack.push_back(child);
        }
    }
    ensuref(reachable.size() == folders.size(),
            "not all folders are reachable from main: reachable %d of %d",
            int(reachable.size()), int(folders.size()));

    int q = inf.readInt(1, 1000, "Q");
    inf.readEoln();
    for (int queryIndex = 0; queryIndex < q; ++queryIndex) {
        string path = inf.readToken(pathPattern, "query");
        inf.readEoln();

        vector<string> parts = splitPath(path);
        ensuref(!parts.empty() && parts[0] == "main",
                "query %d does not start from main: %s", queryIndex + 1, path.c_str());

        string current = "main";
        for (int i = 1; i < int(parts.size()); ++i) {
            const string& part = parts[i];
            ensuref(!part.empty(), "query %d contains an empty path component: %s",
                    queryIndex + 1, path.c_str());
            ensuref(part.size() <= 10, "query %d path component is too long: %s",
                    queryIndex + 1, part.c_str());
            ensuref(childFolders[current].count(part),
                    "query %d path does not resolve at component %s in %s",
                    queryIndex + 1, part.c_str(), current.c_str());
            current = part;
        }
    }

    inf.readEof();
}
