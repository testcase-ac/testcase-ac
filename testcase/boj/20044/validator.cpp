#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of teams n (so number of students is 2*n)
    int n = inf.readInt(1, 5000, "n");
    inf.readEoln();

    // Read 2n distinct positive integers w(s_i) in [1,100000]
    int total_students = 2 * n;
    vector<int> w = inf.readInts(total_students, 1, 100000, "w");
    inf.readEoln();

    // Check all coding abilities are distinct
    set<int> seen(w.begin(), w.end());
    ensuref((int)seen.size() == total_students,
            "Duplicate coding ability detected: expected %d distinct values, got %d",
            total_students, (int)seen.size());

    inf.readEof();
    return 0;
}
