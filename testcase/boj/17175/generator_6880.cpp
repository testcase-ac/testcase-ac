#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Define diverse ranges to cover edge, small, medium, and large n
    vector<pair<int,int>> ranges = {
        {0, 0},    // n = 0 edge case
        {1, 1},    // n = 1 edge case
        {2, 5},    // small n
        {6, 30},   // medium n
        {31, 50}   // large n
    };
    // Pick a random range and then a value within it
    auto range = rnd.any(ranges);
    int n = rnd.next(range.first, range.second);

    println(n);
    return 0;
}
