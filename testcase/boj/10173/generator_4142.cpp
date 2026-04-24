#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of lines (at least 2 to ensure both Found and Missing)
    int L = rnd.next(2, 10);
    int F = rnd.next(1, min(L-1, 3)); // number of lines containing "nemo"
    int M = L - F;                     // number of lines without "nemo"

    vector<string> lines;

    // Helper to generate random printable ASCII string of given length
    auto gen_rand = [&](int len) {
        string s;
        s.reserve(len);
        for (int i = 0; i < len; i++) {
            char c = char(rnd.next(32, 126));
            s.push_back(c);
        }
        return s;
    };

    // Generate F lines that contain "nemo" in random casing and position
    for (int i = 0; i < F; i++) {
        // choose prefix and suffix lengths so total <= 80
        int pre = rnd.next(0, 80 - 4);
        int suf = rnd.next(0, 80 - 4 - pre);
        string s = gen_rand(pre);
        // insert "nemo" with random casing
        string token = "nemo";
        for (char &c : token) {
            if (rnd.next(0, 1)) c = char(toupper(c));
        }
        s += token;
        s += gen_rand(suf);
        lines.push_back(s);
    }

    // Generate M lines that do NOT contain "nemo" (case-insensitive)
    for (int i = 0; i < M; i++) {
        string s;
        do {
            int len = rnd.next(1, 80);
            s = gen_rand(len);
            string low = s;
            for (char &c : low) c = char(tolower(c));
            if (low.find("nemo") == string::npos) break;
        } while (true);
        lines.push_back(s);
    }

    // Shuffle lines for diversity
    shuffle(lines.begin(), lines.end());

    // Output the generated test case
    for (auto &ln : lines) {
        println(ln);
    }
    println("EOI");

    return 0;
}
