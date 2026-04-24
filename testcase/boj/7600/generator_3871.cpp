#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of lines before the terminating '#'
    int L = rnd.next(1, 8);

    // Pool of special characters (excluding '#' to avoid accidental termination)
    string specials = "!@$%&*()_+-=[]{};:,.<>?/";

    for (int i = 0; i < L; i++) {
        // Line length between 1 and 40
        int N = rnd.next(1, 40);

        // Hyper-parameters as integer percents
        int P_letter = rnd.next(30, 70);               // [30%,70%]
        int maxSP = min(30, 100 - P_letter);
        int P_space  = rnd.next(0, maxSP);             // up to 30%
        int maxD = min(30, 100 - P_letter - P_space);
        int P_digit  = rnd.next(0, maxD);              // up to 30%
        double p_letter = P_letter / 100.0;
        double p_space  = P_space  / 100.0;
        double p_digit  = P_digit  / 100.0;

        string line;
        line.reserve(N);
        bool hasNonSpace = false;

        for (int j = 0; j < N; j++) {
            double r = rnd.next();
            char c;
            if (r < p_letter) {
                // Letter
                bool upper = rnd.next(0, 1);
                char base = upper ? 'A' : 'a';
                c = char(base + rnd.next(0, 25));
                hasNonSpace = true;
            } else if (r < p_letter + p_space) {
                // Space
                c = ' ';
            } else if (r < p_letter + p_space + p_digit) {
                // Digit
                c = char('0' + rnd.next(0, 9));
                hasNonSpace = true;
            } else {
                // Special
                c = specials[rnd.next(0, int(specials.size()) - 1)];
                hasNonSpace = true;
            }
            line.push_back(c);
        }

        // Ensure at least one non-space character
        if (!hasNonSpace) {
            int pos = rnd.next(0, N - 1);
            bool upper = rnd.next(0, 1);
            char base = upper ? 'A' : 'a';
            line[pos] = char(base + rnd.next(0, 25));
        }

        // Output the line
        printf("%s\n", line.c_str());
    }

    // Terminating line
    printf("#\n");
    return 0;
}
