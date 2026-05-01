#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: probability to reuse an existing color
    double dupProb = rnd.next(0.0, 1.0);
    // Hyper-parameter: skew for length generation (-2..2)
    int tLen = rnd.next(-2, 2);

    vector<string> cols;
    for (int i = 0; i < 4; i++) {
        // Maybe duplicate one of the previous colors
        if (i > 0 && rnd.next() < dupProb) {
            cols.push_back(rnd.any(cols));
        } else {
            // Generate a new random color name of length 1..20
            int len = rnd.wnext(20, tLen) + 1;
            string s;
            for (int j = 0; j < len; j++)
                s.push_back(char('a' + rnd.next(0, 25)));
            cols.push_back(s);
        }
    }

    // Output: father body & tail, then mother body & tail
    println(cols[0], cols[1]);
    println(cols[2], cols[3]);
    return 0;
}
