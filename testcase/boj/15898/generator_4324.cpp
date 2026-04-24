#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of materials
    int n = rnd.next(3, 10);
    println(n);

    // For each material, generate efficacy and color matrices
    for (int i = 0; i < n; i++) {
        // Hyper-parameter for efficacy bias: positive favors high, negative favors low
        int t_eff = rnd.next(-3, 3);
        // Efficacy: 4x4 integers in [-9,9]
        for (int r = 0; r < 4; r++) {
            vector<int> row(4);
            for (int c = 0; c < 4; c++) {
                // rnd.wnext(19, t_eff) gives [0..18] with bias, shift to [-9..9]
                row[c] = rnd.wnext(19, t_eff) - 9;
            }
            println(row);
        }

        // Hyper-parameter for color bias: 0 = many white, 1 = many colored, 2 = uniform
        int colorMode = rnd.next(0, 2);
        string col = "RBGY";
        string all = "RBGYW";
        // Colors: 4x4 chars
        for (int r = 0; r < 4; r++) {
            vector<char> crow(4);
            for (int c = 0; c < 4; c++) {
                double p = rnd.next();
                if (colorMode == 0) {
                    // many white
                    if (p < 0.7) crow[c] = 'W';
                    else           crow[c] = rnd.any(col);
                } else if (colorMode == 1) {
                    // many colored
                    if (p < 0.7) crow[c] = rnd.any(col);
                    else           crow[c] = 'W';
                } else {
                    // uniform among all 5
                    crow[c] = rnd.any(all);
                }
            }
            println(crow);
        }
    }

    return 0;
}
