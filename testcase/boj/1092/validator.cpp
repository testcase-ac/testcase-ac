#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // 2. Read crane limits
    vector<int> cranes = inf.readInts(N, 1, 1000000, "crane_limit");
    inf.readEoln();

    // 3. Read M
    int M = inf.readInt(1, 10000, "M");
    inf.readEoln();

    // 4. Read box weights
    vector<int> boxes = inf.readInts(M, 1, 1000000, "box_weight");
    inf.readEoln();

    // 5. Global property: At least one crane can lift every box
    int max_crane = *max_element(cranes.begin(), cranes.end());
    int max_box = *max_element(boxes.begin(), boxes.end());
    ensuref(max_box <= max_crane, 
        "There exists a box too heavy for all cranes: max box weight = %d, max crane limit = %d", max_box, max_crane);

    inf.readEof();
}
