#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(3, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        int m = rnd.next(1, 10);
        int n = rnd.next(1, 10);
        println(m, n);
        vector<int> row(n);
        if (tc == 0) {
            // All empty
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) row[j] = 0;
                println(row);
            }
        } else if (tc == 1) {
            // All boxes
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) row[j] = 1;
                println(row);
            }
        } else {
            // Random mix with varying density
            double density = rnd.next();
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++)
                    row[j] = (rnd.next() < density ? 1 : 0);
                println(row);
            }
        }
    }
    return 0;
}
