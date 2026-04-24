#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseNo = 0;
    while (true) {
        // New test case (or terminator)
        caseNo++;
        setTestCase(caseNo);

        // Read first integer on the line: can be -1 (terminator) or a data element [1,99].
        int x = inf.readInt(-1, 99, "value");
        if (x == -1) {
            // terminator line, must be alone on the line
            inf.readEoln();
            break;
        }
        // Cannot be zero or negative besides -1
        ensuref(x > 0, "Test case %d: first element is %d, but must be in [1,99]", caseNo, x);

        // Read the rest of the list until sentinel 0
        vector<int> a;
        a.push_back(x);
        while (true) {
            inf.readSpace();
            int y = inf.readInt(0, 99, "value");
            if (y == 0) {
                // end of this test case
                break;
            }
            a.push_back(y);
        }
        inf.readEoln();

        // Check size constraint: 2 ≤ n ≤ 15
        int n = (int)a.size();
        ensuref(2 <= n && n <= 15,
                "Test case %d: number of elements is %d, but must be in [2,15]", 
                caseNo, n);

        // Check all elements are distinct and within [1,99]
        sort(a.begin(), a.end());
        for (int i = 0; i < n; i++) {
            ensuref(1 <= a[i] && a[i] <= 99,
                    "Test case %d: element %d is %d, but must be in [1,99]",
                    caseNo, i+1, a[i]);
            if (i > 0) {
                ensuref(a[i] != a[i-1],
                        "Test case %d: duplicate element %d found", 
                        caseNo, a[i]);
            }
        }
    }

    // Total test cases (excluding terminator) must be <= 100000
    int totalCases = caseNo - 1;
    ensuref(totalCases <= 100000,
            "Number of test cases is %d, but must be at most 100000",
            totalCases);

    inf.readEof();
    return 0;
}
