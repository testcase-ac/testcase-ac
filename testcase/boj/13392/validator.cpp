#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(3, 10000, "N");
    inf.readEoln();

    // Read current state: exactly N digits
    string cur = inf.readLine("[0-9]{1,10000}", "current");
    ensuref((int)cur.size() == N,
            "Length of current state is %d but expected %d", (int)cur.size(), N);

    // Read desired state: exactly N digits
    string des = inf.readLine("[0-9]{1,10000}", "desired");
    ensuref((int)des.size() == N,
            "Length of desired state is %d but expected %d", (int)des.size(), N);

    // No extra input
    inf.readEof();
    return 0;
}
