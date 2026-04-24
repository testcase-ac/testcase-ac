#include "testlib.h"
#include <string>
#include <vector>
#include <cctype>
using namespace std;

static long long parseIntPart(const string &s, long long lo, long long hi,
                              const string &name, int idx, int line_no) {
    // s must be non-empty, all digits
    ensuref(!s.empty(), "Empty %s at part %d on line %d", name.c_str(), idx, line_no);
    for (int i = 0; i < (int)s.size(); i++) {
        ensuref(isdigit(s[i]), "Non-digit character '%c' in %s at part %d on line %d",
                s[i], name.c_str(), idx, line_no);
    }
    // parse with __int128
    __int128_t val = 0;
    for (char ch : s) {
        val = val * 10 + (ch - '0');
        ensuref(val <= (__int128_t)hi,
                "%s at part %d on line %d is too large: %s > %lld",
                name.c_str(), idx, line_no, s.c_str(), hi);
    }
    ensuref(val >= lo,
            "%s at part %d on line %d is too small: %s < %lld",
            name.c_str(), idx, line_no, s.c_str(), lo);
    return (long long)val;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: ℓ and m
    long long L = inf.readLong(1LL, 1000000LL, "l");
    inf.readSpace();
    int m = inf.readInt(1, 100, "m");
    inf.readEoln();

    // Process m mower descriptions
    for (int i = 0; i < m; i++) {
        string line = inf.readLine("[^]+", "mower_line");
        int line_no = i + 2; // line number in file (1-based)

        // Find commas
        vector<int> commaPos;
        for (int j = 0; j < (int)line.size(); j++) {
            if (line[j] == ',') commaPos.push_back(j);
        }
        ensuref((int)commaPos.size() == 4,
                "Expected 4 commas on mower line %d, found %d", line_no, (int)commaPos.size());

        // Extract parts
        string part_name = line.substr(0, commaPos[0]);
        string part_p    = line.substr(commaPos[0]+1, commaPos[1] - (commaPos[0]+1));
        string part_c    = line.substr(commaPos[1]+1, commaPos[2] - (commaPos[1]+1));
        string part_t    = line.substr(commaPos[2]+1, commaPos[3] - (commaPos[2]+1));
        string part_r    = line.substr(commaPos[3]+1);

        // Validate name
        ensuref(!part_name.empty(), "Empty mower name on line %d", line_no);
        ensuref((int)part_name.size() <= 60,
                "Mower name too long (%d chars) on line %d", (int)part_name.size(), line_no);
        ensuref(part_name.front() != ' ' && part_name.back() != ' ',
                "Mower name on line %d starts or ends with space", line_no);
        for (int j = 0; j < (int)part_name.size(); j++) {
            unsigned char ch = part_name[j];
            ensuref(ch >= 32 && ch <= 126,
                    "Invalid character (ASCII %d) in mower name on line %d", ch, line_no);
            ensuref(ch != ',',
                    "Comma not allowed in mower name on line %d", line_no);
        }

        // Validate numeric parts
        long long p = parseIntPart(part_p, 1LL, 100000LL, "price",    1, line_no);
        long long c = parseIntPart(part_c, 1LL, 100LL,    "cut rate", 2, line_no);
        long long t = parseIntPart(part_t, 1LL, 10080LL,  "cut time", 3, line_no);
        long long r = parseIntPart(part_r, 1LL, 10080LL,  "recharge", 4, line_no);
        // no further checks implied
    }

    inf.readEof();
    return 0;
}
