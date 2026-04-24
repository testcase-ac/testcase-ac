#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 200, "n");
    inf.readEoln();

    // For each student i = 1..n
    for (int i = 1; i <= n; i++) {
        // Read last year's teacher: 0,1,2
        int t = inf.readInt(0, 2, "teacher_of_" + to_string(i));
        // Prepare seen array for favorites
        vector<bool> seen(n+1, false);
        // We expect exactly n-1 favorites
        for (int j = 1; j <= n-1; j++) {
            inf.readSpace();
            int fav = inf.readInt(1, n, "fav_" + to_string(i) + "_" + to_string(j));
            // A student cannot list themselves
            ensuref(fav != i,
                "Student %d lists themselves at position %d", i, j);
            // No duplicates
            ensuref(!seen[fav],
                "Duplicate favorite %d by student %d at position %d", fav, i, j);
            seen[fav] = true;
        }
        // End of this line
        inf.readEoln();

        // Ensure it's a full permutation of {1..n} \ {i}
        for (int x = 1; x <= n; x++) {
            if (x == i) continue;
            ensuref(seen[x],
                "Student %d missing favorite %d", i, x);
        }
    }

    // No extra data
    inf.readEof();
    return 0;
}
