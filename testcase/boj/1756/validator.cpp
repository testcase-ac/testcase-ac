#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_COUNT = 300000;
    const int MAX_DIAMETER = 1000000000;

    int d = inf.readInt(1, MAX_COUNT, "D");
    inf.readSpace();
    int n = inf.readInt(1, MAX_COUNT, "N");
    inf.readEoln();

    vector<int> oven = inf.readInts(d, 1, MAX_DIAMETER, "oven_diameter");
    inf.readEoln();

    vector<int> pizzas = inf.readInts(n, 1, MAX_DIAMETER, "pizza_diameter");
    inf.readEoln();

    inf.readEof();
}
