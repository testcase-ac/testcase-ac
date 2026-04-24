#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of members N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // For each member, read age and name
    for (int i = 0; i < N; i++) {
        int age = inf.readInt(1, 200, "age");
        inf.readSpace();
        // Name: only alphabet letters, length 1 to 100
        inf.readToken("[A-Za-z]{1,100}", "name");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
