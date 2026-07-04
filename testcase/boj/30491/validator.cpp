#include "testlib.h"

#include <string>
#include <unordered_set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    long long totalLength = 0;
    unordered_set<string> directoryPaths;
    unordered_set<string> filePaths;

    for (int i = 1; i <= n; ++i) {
        string s = inf.readLine("[^]{1,1000000}", "s");
        totalLength += static_cast<long long>(s.size());
        ensuref(totalLength <= 1000000, "total path length exceeds 1000000");

        ensuref(s.size() >= 2, "path %d is too short: %s", i, s.c_str());
        ensuref(s[0] == '/', "path %d does not start with '/': %s", i, s.c_str());
        ensuref(s.back() != '/', "path %d ends with '/': %s", i, s.c_str());

        for (int j = 1; j < static_cast<int>(s.size()); ++j) {
            char c = s[j];
            ensuref((c >= 'a' && c <= 'z') || c == '/',
                    "path %d contains invalid character at position %d", i, j + 1);
            ensuref(!(c == '/' && s[j - 1] == '/'),
                    "path %d contains consecutive slashes: %s", i, s.c_str());
        }

        string prefix;
        for (int j = 1; j < static_cast<int>(s.size()); ++j) {
            if (s[j] == '/') {
                prefix = s.substr(0, j);
                directoryPaths.insert(prefix);
                ensuref(filePaths.find(prefix) == filePaths.end(),
                        "path %s uses an existing file path as a directory", s.c_str());
            }
        }

        filePaths.insert(s);
        ensuref(directoryPaths.find(s) == directoryPaths.end(),
                "path %s is both a file and a directory", s.c_str());
    }

    inf.readEof();
}
