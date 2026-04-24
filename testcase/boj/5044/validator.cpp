#include "testlib.h"
#include <string>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of known open-source repositories
    int N = inf.readInt(0, 100, "N");
    inf.readEoln();

    // Track filenames to ensure uniqueness
    set<string> filenames;

    // Read each open-source entry
    for (int i = 0; i < N; i++) {
        // File name: no spaces, ASCII 33('!') to 126('~'), length 1..254
        string fname = inf.readToken("[!-~]{1,254}", "file_name");
        inf.readEoln();
        ensuref(!filenames.count(fname),
                "Duplicate file name: %s", fname.c_str());
        filenames.insert(fname);

        // Read source lines until "***END***"
        int line_cnt = 0;
        while (true) {
            // Read entire line (up to newline), any characters
            string s = inf.readLine("[^]*", "source_line");
            // Check sentinel
            if (s == "***END***") {
                break;
            }
            // Count and bounds checks
            line_cnt++;
            ensuref(line_cnt <= 10000,
                    "Too many lines in source %s: got %d, max is 10000",
                    fname.c_str(), line_cnt);
            // Each line length ≤ 254
            ensuref((int)s.size() <= 254,
                    "Line too long in source %s: length %d, max is 254",
                    fname.c_str(), (int)s.size());
            // Each character must be ASCII 32..126
            for (int j = 0; j < (int)s.size(); j++) {
                unsigned char c = s[j];
                ensuref(c >= 32 && c <= 126,
                        "Invalid character (code %d) in source %s at line %d, pos %d",
                        c, fname.c_str(), line_cnt, j+1);
            }
        }
    }

    // Read the submitted source to compare (no filename header)
    int cmp_lines = 0;
    while (true) {
        string s = inf.readLine("[^]*", "compare_source_line");
        if (s == "***END***") {
            break;
        }
        cmp_lines++;
        ensuref(cmp_lines <= 10000,
                "Too many lines in comparison source: got %d, max is 10000",
                cmp_lines);
        ensuref((int)s.size() <= 254,
                "Line too long in comparison source: length %d, max is 254",
                (int)s.size());
        for (int j = 0; j < (int)s.size(); j++) {
            unsigned char c = s[j];
            ensuref(c >= 32 && c <= 126,
                    "Invalid character (code %d) in comparison source at line %d, pos %d",
                    c, cmp_lines, j+1);
        }
    }

    // No extra data after final END
    inf.readEof();
    return 0;
}
