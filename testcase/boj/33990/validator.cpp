#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of students
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Each student's 1RM for bench press, squat, deadlift
    for (int i = 0; i < N; i++) {
        int A = inf.readInt(0, 200, "A_i");
        inf.readSpace();
        int B = inf.readInt(0, 200, "B_i");
        inf.readSpace();
        int C = inf.readInt(0, 200, "C_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
