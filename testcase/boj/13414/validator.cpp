#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read K and L
    int K = inf.readInt(1, 100000, "K");
    inf.readSpace();
    int L = inf.readInt(1, 500000, "L");
    inf.readEoln();

    // Each of the next L lines is an 8-digit student ID
    for (int i = 0; i < L; i++) {
        inf.readToken("[0-9]{8}", "student_id");
        inf.readEoln();
    }

    // No extra content
    inf.readEof();
    return 0;
}
