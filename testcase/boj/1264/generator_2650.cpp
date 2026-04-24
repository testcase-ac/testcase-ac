#include "testlib.h"
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test lines
    int L = rnd.next(1, 10);
    const string glue = " ,.!?";

    for (int i = 0; i < L; ++i) {
        // Number of words in this line
        int T = rnd.next(1, 10);
        string line;
        for (int t = 0; t < T; ++t) {
            // Word length
            int W = rnd.next(1, 10);
            for (int j = 0; j < W; ++j) {
                char c = char('a' + rnd.next(0, 25));
                if (rnd.next(2) == 1) c = char(toupper(c));
                line.push_back(c);
            }
            if (t + 1 < T) {
                // Random separator: space or punctuation
                line.push_back(rnd.any(glue));
            }
        }
        println(line);
    }

    // End marker
    println("#");
    return 0;
}
