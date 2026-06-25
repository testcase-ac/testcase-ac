#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "n");
    inf.readEoln();

    vector<int> initialTravelTimes = inf.readInts(n - 1, 1, 1000000, "t_i");
    inf.readEoln();

    int k = inf.readInt(0, 200000, "k");
    inf.readEoln();

    for (int i = 0; i < k; ++i) {
        int j = inf.readInt(1, n - 1, "j");
        inf.readSpace();
        int updatedTravelTime = inf.readInt(1, 1000000, "updated_t");
        inf.readEoln();
    }

    inf.readEof();
}
