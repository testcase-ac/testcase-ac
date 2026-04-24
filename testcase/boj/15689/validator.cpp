#include "testlib.h"
#include <string>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read m and n
    int m = inf.readInt(1, 1000000, "m");
    inf.readSpace();
    int n = inf.readInt(2, 1000000, "n");
    inf.readEoln();

    // Read k
    long long k = inf.readLong(1LL, 1000000000000000000LL, "k");
    inf.readEoln();

    // Read each bus description
    for (int i = 0; i < m; i++) {
        // stations
        int a = inf.readInt(0, n-1, "a_i");
        inf.readSpace();
        int b = inf.readInt(0, n-1, "b_i");
        ensuref(a != b,
                "Bus %d: start and destination must differ, got a=%d, b=%d",
                i, a, b);
        inf.readSpace();
        // times
        long long s = inf.readLong(0LL, k, "s_i");
        inf.readSpace();
        long long t = inf.readLong(0LL, k, "t_i");
        ensuref(s < t,
                "Bus %d: departure time must be less than arrival time, got s=%lld, t=%lld",
                i, s, t);
        inf.readSpace();
        // probability as token
        string p = inf.readToken("[^]+", "p_i");
        // manual check of format and bounds
        int dot_count = 0;
        for (char c : p) {
            if (c == '.') {
                dot_count++;
            } else if (!isdigit(c)) {
                ensuref(false,
                        "Bus %d: probability contains invalid character '%c' in \"%s\"",
                        i, c, p.c_str());
            }
        }
        ensuref(dot_count <= 1,
                "Bus %d: probability has more than one decimal point: \"%s\"",
                i, p.c_str());
        // split integer and fractional parts
        string int_part, frac_part;
        size_t pos = p.find('.');
        if (pos == string::npos) {
            int_part = p;
            frac_part = "";
        } else {
            int_part = p.substr(0, pos);
            frac_part = p.substr(pos + 1);
        }
        // integer part must be "0" or "1"
        ensuref(int_part == "0" || int_part == "1",
                "Bus %d: probability integer part must be 0 or 1, got \"%s\" in \"%s\"",
                i, int_part.c_str(), p.c_str());
        if (frac_part.empty()) {
            // no decimal: must be exactly "0" or "1"
            ensuref(p == "0" || p == "1",
                    "Bus %d: probability without decimal must be exactly 0 or 1, got \"%s\"",
                    i, p.c_str());
        } else {
            // decimal part length 1..10
            ensuref((int)frac_part.size() >= 1 && (int)frac_part.size() <= 10,
                    "Bus %d: probability fractional part must have 1 to 10 digits, got \"%s\"",
                    i, p.c_str());
            if (int_part == "1") {
                // must be all zeros
                for (char c : frac_part) {
                    ensuref(c == '0',
                            "Bus %d: probability \"%s\" > 1 not allowed",
                            i, p.c_str());
                }
            }
            // if int_part == "0", any fractional digits OK
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
