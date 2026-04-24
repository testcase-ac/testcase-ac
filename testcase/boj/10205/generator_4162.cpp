#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of data sets
    int K = rnd.next(1, 5);
    println(K);

    for (int tc = 0; tc < K; tc++) {
        // Initial head count 1..50
        int h0 = rnd.next(1, 50);
        int heads = h0;
        string s;

        // Decide whether this case will kill the hydra or leave it alive
        bool kill = rnd.next(0, 1) == 1;

        if (kill) {
            // Generate some random actions, then finish off with burns
            double pb = rnd.next(0.3, 1.0);       // bias towards burning
            int cap = rnd.next(1, 10);            // initial random actions
            for (int i = 0; i < cap && heads > 0; i++) {
                char act = (rnd.next() < pb ? 'b' : 'c');
                s += act;
                if (act == 'b') heads--;
                else heads = heads - 1 + 2;
            }
            // If still alive, burn remaining heads
            if (heads > 0) {
                s += string(heads, 'b');
                heads = 0;
            }
        } else {
            // Generate a fixed-length sequence that never kills the hydra
            double pb = rnd.next(0.0, 0.7);       // bias towards cutting
            int len = rnd.next(1, 100);          // total actions
            for (int i = 0; i < len; i++) {
                char act;
                if (heads == 1) {
                    // avoid the kill
                    act = 'c';
                } else {
                    act = (rnd.next() < pb ? 'b' : 'c');
                }
                s += act;
                if (act == 'b') heads--;
                else heads = heads - 1 + 2;
            }
            // heads > 0 guaranteed
        }

        // Output this data set: initial heads, then action string
        println(h0);
        println(s);
    }

    return 0;
}
