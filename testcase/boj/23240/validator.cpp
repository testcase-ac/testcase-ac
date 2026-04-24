#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read m: number of distinct disk sizes (largest diameter)
    int m = inf.readInt(1, 25, "m");
    inf.readEoln();

    // For each size i = 1..m, read color and count k_i
    long long total_disks = 0;
    for (int i = 1; i <= m; i++) {
        // Color must be one of 'R', 'G', 'B'
        // Use a simple regex matching exactly one of these letters
        string color_name = string("color_") + to_string(i);
        inf.readToken("[RGB]", color_name.c_str());
        inf.readSpace();

        // k_i >= 1, and since total disks <= 50, each k_i <= 50
        string count_name = string("k_") + to_string(i);
        int k = inf.readInt(1, 50, count_name.c_str());
        inf.readEoln();

        total_disks += k;
    }

    // Sum of all disks must not exceed 50
    ensuref(total_disks <= 50,
            "Total number of disks is %lld, but must be at most 50", total_disks);

    inf.readEof();
    return 0;
}
