#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseCount = rnd.next(3, 8);
    for (int tc = 0; tc < caseCount; ++tc) {
        int n = rnd.next(1, 25);
        vector<int> results(n);

        int mode = rnd.next(0, 5);
        if (mode == 0) {
            fill(results.begin(), results.end(), 0);
        } else if (mode == 1) {
            fill(results.begin(), results.end(), 1);
        } else if (mode == 2) {
            int first = rnd.next(0, 1);
            for (int i = 0; i < n; ++i) {
                results[i] = (first + i) % 2;
            }
        } else {
            int johnWeight = rnd.next(1, 9);
            for (int i = 0; i < n; ++i) {
                results[i] = rnd.next(1, 10) <= johnWeight ? 1 : 0;
            }
        }

        println(n);
        println(results);
    }
    println(0);

    return 0;
}
