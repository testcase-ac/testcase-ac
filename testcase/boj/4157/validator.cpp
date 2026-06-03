#include "testlib.h"

#include <unordered_set>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    unordered_set<int> seen;
    seen.reserve(static_cast<size_t>(n) * 2);

    for (int i = 0; i < n; ++i) {
        // CHECK: The statement gives no numeric bound for student numbers; keep a broad practical int range.
        int student = inf.readInt(-1000000000, 1000000000, "student_number");
        inf.readEoln();

        ensuref(seen.insert(student).second,
                "duplicate student number at line %d: %d", i + 2, student);
    }

    inf.readEof();
}
