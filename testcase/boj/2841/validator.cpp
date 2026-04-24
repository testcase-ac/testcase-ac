#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N (number of notes) and P (number of frets per string)
    int N = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int P = inf.readInt(2, 300000, "P");
    inf.readEoln();

    // For each note, read the string index and the fret number
    for (int i = 0; i < N; i++) {
        int s = inf.readInt(1, N, "string_i"); // as per statement: string number ∈ [1, N]
        inf.readSpace();
        int f = inf.readInt(1, P, "fret_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
