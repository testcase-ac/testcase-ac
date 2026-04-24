#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of semesters T
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Prepare allowed grade values multiplied by 10
    // Allowed original grades: 0, 0.7, 1, 1.3, 1.7, 2, 2.3, 2.7, 3, 3.3, 3.7, 4, 4.3
    // After scaling by 10:  0,  7, 10, 13, 17, 20, 23, 27, 30, 33, 37, 40, 43
    static bool allowed[100] = { false };
    int allowed_vals[] = {0, 7, 10, 13, 17, 20, 23, 27, 30, 33, 37, 40, 43};
    for (int v : allowed_vals) {
        allowed[v] = true;
    }

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Number of courses in this semester
        int N = inf.readInt(1, 10, "N");
        inf.readEoln();

        for (int i = 1; i <= N; i++) {
            // Read credit C
            int C = inf.readInt(1, 6, "C");
            inf.readSpace();

            // Read grade G as a token (any non-whitespace), we'll validate format manually
            string G = inf.readToken("[^]+", "G");
            inf.readEoln();

            // Validate format: only digits and at most one dot
            int dot_count = 0;
            for (char ch : G) {
                if (ch == '.') {
                    dot_count++;
                } else if (ch < '0' || ch > '9') {
                    ensuref(false,
                            "Invalid character '%c' in grade '%s' at test %d course %d",
                            ch, G.c_str(), tc, i);
                }
            }
            ensuref(dot_count <= 1,
                    "More than one decimal point in grade '%s' at test %d course %d",
                    G.c_str(), tc, i);

            // Split integer and decimal parts
            int int_part = 0;
            int dec_part = 0;
            if (dot_count == 0) {
                // Entire string is integer part
                // Must be non-empty
                ensuref(!G.empty(),
                        "Empty grade token at test %d course %d", tc, i);
                // Parse integer digits
                for (char ch : G) {
                    int_part = int_part * 10 + (ch - '0');
                }
                dec_part = 0;
            } else {
                // Has exactly one dot
                size_t p = G.find('.');
                // Dot cannot be first or last
                ensuref(p > 0 && p + 1 < G.size(),
                        "Misplaced decimal point in grade '%s' at test %d course %d",
                        G.c_str(), tc, i);
                // Integer part: G[0..p-1]
                for (size_t j = 0; j < p; j++) {
                    char ch = G[j];
                    // Already ensured digits or dot
                    int_part = int_part * 10 + (ch - '0');
                }
                // Decimal part: exactly one digit
                ensuref(p + 2 == G.size(),
                        "Decimal part length != 1 in grade '%s' at test %d course %d",
                        G.c_str(), tc, i);
                char dch = G[p+1];
                // Must be digit
                ensuref(dch >= '0' && dch <= '9',
                        "Non-digit in decimal part of grade '%s' at test %d course %d",
                        G.c_str(), tc, i);
                dec_part = dch - '0';
            }

            // Compute scaled value and check allowed
            long long v = (long long)int_part * 10 + dec_part;
            ensuref(v >= 0 && v < 100,
                    "Scaled grade %lld out of bounds from '%s' at test %d course %d",
                    v, G.c_str(), tc, i);
            ensuref(allowed[v],
                    "Grade '%s' (scaled %lld) is not an allowed value at test %d course %d",
                    G.c_str(), v, tc, i);
        }
    }

    inf.readEof();
    return 0;
}
