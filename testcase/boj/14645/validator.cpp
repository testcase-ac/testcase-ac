#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    long long passengers = inf.readInt(1, 10000, "K");
    inf.readEoln();

    for (int i = 1; i <= n; i++) {
        int A = inf.readInt(0, 10000, "A");
        inf.readSpace();
        int B = inf.readInt(0, 10000, "B");
        inf.readEoln();
        passengers += A;
        ensuref(passengers >= B, "station %d has %d alighting passengers but only %lld on the bus", i, B, passengers);
        passengers -= B;
    }

    inf.readEof();
}
