#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read rates A, B, C with constraints 1 ≤ C ≤ B ≤ A ≤ 100
    int A = inf.readInt(1, 100, "A");
    inf.readSpace();
    int B = inf.readInt(1, 100, "B");
    inf.readSpace();
    int C = inf.readInt(1, 100, "C");
    inf.readEoln();
    ensuref(C <= B, "Rate constraint violated: C (%d) > B (%d)", C, B);
    ensuref(B <= A, "Rate constraint violated: B (%d) > A (%d)", B, A);

    // Read three trucks' arrival and departure times
    for (int i = 0; i < 3; i++) {
        int t_in  = inf.readInt(1, 100, "arrival_time");
        inf.readSpace();
        int t_out = inf.readInt(1, 100, "departure_time");
        inf.readEoln();
        ensuref(t_in < t_out,
                "Time constraint violated for truck %d: arrival %d >= departure %d",
                i+1, t_in, t_out);
    }

    inf.readEof();
    return 0;
}
