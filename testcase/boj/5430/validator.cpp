#include "testlib.h"
#include <string>
#include <vector>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    // Keep track of global sums
    long long total_p_len = 0;
    long long total_n_sum = 0;

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read the function string p
        string p = inf.readToken("[RD]+", "p");
        inf.readEoln();
        int m = (int)p.size();
        ensuref(m >= 1 && m <= 100000,
                "Length of p must be in [1,100000], but got %d in test case %d", m, tc);
        total_p_len += m;

        // Read n
        int n = inf.readInt(0, 100000, "n");
        inf.readEoln();
        total_n_sum += n;

        // Read the array line as a single token
        string s = inf.readToken("[^]+", "array");
        inf.readEoln();

        // Check brackets
        ensuref(s.size() >= 2 && s.front() == '[' && s.back() == ']',
                "Array must start with '[' and end with ']' in test case %d; got: %s", tc, s.c_str());
        string content = s.substr(1, s.size() - 2);

        // If n == 0, content must be empty
        if (n == 0) {
            ensuref(content.empty(),
                    "Expected empty array content for n=0 in test case %d; got: %s", tc, content.c_str());
        } else {
            // n > 0: content must be non-empty
            ensuref(!content.empty(),
                    "Expected non-empty array content for n=%d in test case %d", n, tc);
        }

        // Split by commas
        vector<string> elems;
        if (!content.empty()) {
            size_t start = 0;
            while (start < content.size()) {
                size_t pos = content.find(',', start);
                if (pos == string::npos) pos = content.size();
                string tok = content.substr(start, pos - start);
                elems.push_back(tok);
                start = pos + 1;
            }
        }

        // Check count matches n
        ensuref((int)elems.size() == n,
                "Number of elements %d does not match n=%d in test case %d", (int)elems.size(), n, tc);

        // Validate each element
        for (int i = 0; i < (int)elems.size(); i++) {
            const string &tok = elems[i];
            ensuref(!tok.empty(),
                    "Empty element at index %d in test case %d", i, tc);
            // All digits
            for (char c : tok) {
                ensuref(isdigit(c),
                        "Non-digit character '%c' in element %d in test case %d", c, i, tc);
            }
            // Parse integer value
            int val = 0;
            for (char c : tok) {
                val = val * 10 + (c - '0');
                // early bound check to avoid overflow
                ensuref(val <= 1000,
                        "Value overflow (>%d) when parsing element %d in test case %d", 1000, i, tc);
            }
            ensuref(val >= 1 && val <= 100,
                    "Element value out of bounds [1,100]: got %d at index %d in test case %d",
                    val, i, tc);
        }
    }

    // Check global sum constraints
    ensuref(total_p_len <= 700000,
            "Sum of lengths of all p over all test cases must be <=700000; got %lld",
            total_p_len);
    ensuref(total_n_sum <= 700000,
            "Sum of all n over all test cases must be <=700000; got %lld",
            total_n_sum);

    inf.readEof();
    return 0;
}
