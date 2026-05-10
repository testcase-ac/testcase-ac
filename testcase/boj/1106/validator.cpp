#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the required total customers C and number of cities N
    int C = inf.readInt(1, 1000, "C");
    inf.readSpace();
    int N = inf.readInt(1, 20, "N");
    inf.readEoln();

    // For each city, read cost and customer gain
    for (int i = 0; i < N; i++) {
        // cost_i: cost to advertise in city i
        inf.readInt(1, 100, "cost_i");
        inf.readSpace();
        // customer_i: number of customers gained at that cost
        inf.readInt(1, 100, "customer_i");
        inf.readEoln();
    }

    // No extra data allowed
    inf.readEof();
    return 0;
}
