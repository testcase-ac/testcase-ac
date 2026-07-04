#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

bool isGraphical(vector<int> degrees) {
    while (true) {
        sort(degrees.begin(), degrees.end(), greater<int>());
        if (degrees.empty() || degrees[0] == 0) {
            return true;
        }

        int d = degrees[0];
        degrees.erase(degrees.begin());
        if (d > static_cast<int>(degrees.size())) {
            return false;
        }

        for (int i = 0; i < d; ++i) {
            --degrees[i];
            if (degrees[i] < 0) {
                return false;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 500, "n");
    inf.readEoln();

    vector<int> degrees(n);
    int degreeSum = 0;
    for (int i = 0; i < n; ++i) {
        degrees[i] = inf.readInt(1, n - 1, format("d[%d]", i + 1).c_str());
        inf.readEoln();
        degreeSum += degrees[i];
    }

    ensuref(degreeSum % 2 == 0, "degree sum must be even, got %d", degreeSum);
    ensuref(isGraphical(degrees), "degree sequence must admit a simple graph");

    inf.readEof();
}
