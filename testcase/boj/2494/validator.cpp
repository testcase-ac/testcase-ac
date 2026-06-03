#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 10000, "N");
    inf.readEoln();

    string current = inf.readToken("[0-9]{3,10000}", "current");
    inf.readEoln();
    string target = inf.readToken("[0-9]{3,10000}", "target");
    inf.readEoln();

    ensuref((int)current.size() == n,
            "current state length %d does not match N=%d",
            (int)current.size(), n);
    ensuref((int)target.size() == n,
            "target state length %d does not match N=%d",
            (int)target.size(), n);

    inf.readEof();
    return 0;
}
