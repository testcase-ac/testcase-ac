#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

string joinPath(const vector<string>& components) {
    string path;
    for (const string& component : components) path += "/" + component;
    return path;
}

string token(int value) {
    string s;
    do {
        s.push_back(static_cast<char>('a' + value % 26));
        value /= 26;
    } while (value > 0);
    reverse(s.begin(), s.end());
    return s;
}

void addPath(vector<string>& paths, set<string>& filePaths, const vector<string>& components) {
    string path = joinPath(components);
    if (filePaths.insert(path).second) paths.push_back(path);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(1, 18);
    vector<string> paths;
    set<string> filePaths;

    if (mode == 0) {
        vector<string> base = {"a", "b", "c"};
        addPath(paths, filePaths, base);
        int repeats = rnd.next(1, n);
        for (int i = 0; i < repeats; ++i) paths.push_back(joinPath(base));
        for (int i = repeats; i < n; ++i) {
            vector<string> components = {"a", "b", token(i + 3)};
            addPath(paths, filePaths, components);
        }
    } else if (mode == 1) {
        vector<string> prefix = {"home", "jury"};
        int branches = rnd.next(2, 5);
        for (int i = 0; i < n; ++i) {
            vector<string> components = prefix;
            components.push_back(token(rnd.next(0, branches - 1)));
            components.push_back(token(30 + i));
            addPath(paths, filePaths, components);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int depth = rnd.next(1, 5);
            vector<string> components;
            for (int j = 0; j < depth; ++j) {
                components.push_back(token(i * 7 + j + rnd.next(0, 3)));
            }
            addPath(paths, filePaths, components);
        }
    } else {
        int groups = rnd.next(2, 4);
        for (int i = 0; i < n; ++i) {
            int group = rnd.next(0, groups - 1);
            vector<string> components = {token(group), token(20 + group)};
            if (rnd.next(0, 1) == 1) components.push_back(token(40 + rnd.next(0, 5)));
            components.push_back(token(80 + i));
            addPath(paths, filePaths, components);
        }
    }

    while (paths.empty()) addPath(paths, filePaths, {token(rnd.next(0, 25))});
    shuffle(paths.begin(), paths.end());

    println(static_cast<int>(paths.size()));
    for (const string& path : paths) println(path);

    return 0;
}
