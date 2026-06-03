#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> widths = {136, 142, 148, 154};

    int mode = rnd.next(6);
    int n;
    vector<int> bills;

    if (mode == 0) {
        n = 1;
        bills.push_back(rnd.any(widths));
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        int width = rnd.any(widths);
        bills.assign(n, width);
    } else if (mode == 2) {
        n = rnd.next(4, 12);
        for (int i = 0; i < n; ++i) {
            bills.push_back(widths[i % (int)widths.size()]);
        }
    } else if (mode == 3) {
        n = rnd.next(5, 20);
        vector<int> small = {136, 142};
        for (int i = 0; i < n; ++i) {
            bills.push_back(rnd.any(small));
        }
    } else if (mode == 4) {
        n = rnd.next(5, 20);
        vector<int> large = {148, 154};
        for (int i = 0; i < n; ++i) {
            bills.push_back(rnd.any(large));
        }
    } else {
        n = rnd.next(21, 100);
        for (int i = 0; i < n; ++i) {
            bills.push_back(rnd.any(widths));
        }
    }

    shuffle(bills.begin(), bills.end());

    println(n);
    for (int width : bills) {
        println(width, 68);
    }

    return 0;
}
