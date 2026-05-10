#include "testlib.h"
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MAX = 15;
    const int SUM_MAX = 30;
    const int CASES_MAX = 100000;

    int case_count = 0;
    while (true) {
        // Read the whole line (since n=0 can be on a line by itself)
        string line = inf.readLine("[^]+", "input line");
        stringstream ss(line);

        // Read n
        int n;
        ss >> n;
        ensuref(!ss.fail(), "Failed to read n on line %d", case_count + 1);

        if (n == 0) {
            // No trailing spaces allowed after 0
            string rest;
            ss >> rest;
            ensuref(ss.eof(), "Trailing data after n=0 on line %d", case_count + 1);
            break;
        }

        ensuref(1 <= n && n <= N_MAX, "n=%d is out of bounds [1, %d] on line %d", n, N_MAX, case_count + 1);

        vector<int> ratings;
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            int x;
            ss >> x;
            ensuref(!ss.fail(), "Failed to read rating %d on line %d", i + 1, case_count + 1);
            ensuref(x >= 0, "Rating %d is negative (%d) on line %d", i + 1, x, case_count + 1);
            ratings.push_back(x);
            sum += x;
        }
        ensuref(sum <= SUM_MAX, "Sum of ratings (%d) exceeds %d on line %d", sum, SUM_MAX, case_count + 1);

        // No trailing data
        string rest;
        ss >> rest;
        ensuref(ss.eof(), "Trailing data after ratings on line %d", case_count + 1);

        ++case_count;
        ensuref(case_count <= CASES_MAX, "Too many test cases: %d (max %d)", case_count, CASES_MAX);
    }

    inf.readEof();
}
