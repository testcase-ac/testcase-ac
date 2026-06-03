#include "testlib.h"

#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for K; use the local default cap.
    int k = inf.readInt(1, 100000, "K");
    inf.readEoln();

    for (int tc = 1; tc <= k; ++tc) {
        setTestCase(tc);

        int m = inf.readInt(1, 20, "M");
        inf.readSpace();
        int n = inf.readInt(1, 20, "N");
        inf.readEoln();

        vector<bool> covered(m + 1, false);
        for (int problem = 1; problem <= n; ++problem) {
            string line = inf.readLine();
            ensuref(!line.empty(), "category line in dataset %d problem %c is empty",
                    tc, char('A' + problem - 1));
            for (char ch : line) {
                ensuref(('0' <= ch && ch <= '9') || ch == ' ',
                        "category line in dataset %d problem %c has invalid character",
                        tc, char('A' + problem - 1));
            }
            ensuref(line.front() != ' ' && line.back() != ' ',
                    "category line in dataset %d problem %c has outer space",
                    tc, char('A' + problem - 1));
            ensuref(line.find("  ") == string::npos,
                    "category line in dataset %d problem %c has repeated spaces",
                    tc, char('A' + problem - 1));
            stringstream ss(line);
            string token;
            set<int> seen;

            while (ss >> token) {
                ensuref(token == "0" || token[0] != '0',
                        "category has leading zero in dataset %d problem %c: %s",
                        tc, char('A' + problem - 1), token.c_str());

                int category = stoi(token);
                ensuref(1 <= category && category <= m,
                        "category out of range in dataset %d problem %c: %d",
                        tc, char('A' + problem - 1), category);

                // CHECK: Categories covered by one problem are a set; duplicates would
                // not describe additional coverage.
                ensuref(seen.insert(category).second,
                        "duplicate category in dataset %d problem %c: %d",
                        tc, char('A' + problem - 1), category);
                covered[category] = true;
            }

            ensuref(!seen.empty(), "problem %c in dataset %d covers no categories",
                    char('A' + problem - 1), tc);
        }

        for (int category = 1; category <= m; ++category) {
            ensuref(covered[category],
                    "dataset %d has no solution because category %d is uncovered",
                    tc, category);
        }
    }

    inf.readEof();
}
