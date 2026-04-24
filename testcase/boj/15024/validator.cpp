#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of files
    int n = inf.readInt(1, 500, "n");
    inf.readEoln();

    // Read the list of file names
    vector<string> names(n);
    set<string> nameSet;
    for (int i = 0; i < n; i++) {
        if (i > 0) inf.readSpace();
        string s = inf.readToken("[a-z]{1,8}", "file_name");
        ensuref(!nameSet.count(s),
                "Duplicate file name on second line: '%s'", s.c_str());
        names[i] = s;
        nameSet.insert(s);
    }
    inf.readEoln();

    // Build a lookup map from name to index
    unordered_map<string,int> nameToIdx;
    nameToIdx.reserve(n);
    for (int i = 0; i < n; i++) {
        nameToIdx[names[i]] = i;
    }

    // For each file section
    for (int i = 0; i < n; i++) {
        // Section header: <filename> <k>
        string secName = inf.readToken("[a-z]{1,8}", "section_name");
        ensuref(secName == names[i],
                "Section %d: expected file name '%s' but found '%s'",
                i+1, names[i].c_str(), secName.c_str());
        inf.readSpace();
        int k = inf.readInt(0, n, "k");
        inf.readEoln();

        // Track all imported files in this section to forbid duplicates
        set<string> imported;

        // Read k import lines
        for (int j = 0; j < k; j++) {
            string line = inf.readLine("[^]+", "import_line");
            // Must start with "import "
            ensuref(line.size() >= 8 && line.substr(0, 7) == "import ",
                    "Import line %d in section %d does not start with 'import '",
                    j+1, i+1);
            // No trailing spaces: last char must be a lowercase letter
            char lc = line.back();
            ensuref(lc >= 'a' && lc <= 'z',
                    "Import line %d in section %d has invalid trailing character '%c'",
                    j+1, i+1, lc);

            // Extract the comma-space separated list
            string rest = line.substr(7);
            ensuref(!rest.empty(),
                    "Import line %d in section %d has no dependencies listed",
                    j+1, i+1);

            size_t pos = 0;
            while (pos < rest.size()) {
                size_t nxt = rest.find(", ", pos);
                string token;
                if (nxt == string::npos) {
                    token = rest.substr(pos);
                    pos = rest.size();
                } else {
                    token = rest.substr(pos, nxt - pos);
                    pos = nxt + 2;
                }
                // Validate that token is a known file
                auto it = nameToIdx.find(token);
                ensuref(it != nameToIdx.end(),
                        "Import line %d in section %d names unknown file '%s'",
                        j+1, i+1, token.c_str());
                // No duplicate imports within this file
                ensuref(!imported.count(token),
                        "File '%s' imports '%s' more than once (in section %d)",
                        names[i].c_str(), token.c_str(), i+1);
                imported.insert(token);
            }
        }
    }

    inf.readEof();
    return 0;
}
