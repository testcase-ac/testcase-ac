#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read s
    int s = inf.readInt(1, 3000, "s");
    inf.readEoln();

    // Read problem name
    string name = inf.readToken("[a-z]{1,3000}", "problem_name");
    inf.readEoln();

    int n = int(name.size());

    // Global constraint: "불가능한 입력(s < k, 25*길이 < s)은 없다."
    // So, s >= 1, s <= 25*n always holds.
    // But let's check that s <= 25*n
    ensuref(s <= 25 * n, "s (%d) must be <= 25 * length of name (%d)", s, n);

    // No further global constraints to check.

    inf.readEof();
}
