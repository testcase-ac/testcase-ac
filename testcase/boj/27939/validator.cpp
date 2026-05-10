#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(2, 1000, "n");
    inf.readEoln();

    // Read n colors (P or W)
    vector<char> color(n);
    for (int i = 0; i < n; i++) {
        string c = inf.readToken("[PW]", "color");
        color[i] = c[0];
        if (i + 1 < n) {
            inf.readSpace();
        }
    }
    inf.readEoln();

    // Read m and k
    int m = inf.readInt(2, 1000, "m");
    inf.readSpace();
    int k = inf.readInt(2, n, "k");
    inf.readEoln();

    // Read each assistant's list of k distinct varieties
    for (int i = 0; i < m; i++) {
        vector<bool> seen(n+1, false);
        for (int j = 0; j < k; j++) {
            int a = inf.readInt(1, n, "a");
            ensuref(!seen[a],
                    "Duplicate variety %d in assistant %d", a, i+1);
            seen[a] = true;
            if (j + 1 < k) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
