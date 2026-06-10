#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "n");
    inf.readEoln();

    vector<int> a = inf.readInts(n, -100, 100, "a_i");
    inf.readEoln();

    int sum = 0;
    for (int x : a) {
        sum += x;
    }

    bool hasAnswer = false;
    for (int x : a) {
        if (2 * x == sum) {
            hasAnswer = true;
        }
    }
    ensuref(hasAnswer, "no card equals the sum of all other cards");

    inf.readEof();
}
