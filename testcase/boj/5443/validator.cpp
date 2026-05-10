#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        // Read day as a token to check leading zeros
        string d_s = inf.readToken("[0-9]+", "D");
        inf.readSpace();
        string m_s = inf.readToken("[0-9]+", "M");
        inf.readSpace();
        string y_s = inf.readToken("[0-9]+", "Y");
        inf.readEoln();

        // No leading zeros for D and M and Y
        ensuref(d_s.size() == 1 || d_s[0] != '0',
                "Leading zero in day on test case %d: \"%s\"", tc, d_s.c_str());
        ensuref(m_s.size() == 1 || m_s[0] != '0',
                "Leading zero in month on test case %d: \"%s\"", tc, m_s.c_str());
        // Year must not have leading zeros either
        ensuref(y_s.size() == 1 || y_s[0] != '0',
                "Leading zero in year on test case %d: \"%s\"", tc, y_s.c_str());

        // Parse to integers
        int D = stoi(d_s);
        int M = stoi(m_s);
        int Y = stoi(y_s);

        // Check ranges
        ensuref(1 <= D && D <= 31,
                "Day out of range on test case %d: %d", tc, D);
        ensuref(1 <= M && M <= 12,
                "Month out of range on test case %d: %d", tc, M);
        ensuref(1000 <= Y && Y <= 9999,
                "Year out of range on test case %d: %d", tc, Y);

        // Check that the date is a valid calendar date
        int maxDay;
        if (M == 2) {
            bool isLeap = (Y % 400 == 0) || (Y % 4 == 0 && Y % 100 != 0);
            maxDay = isLeap ? 29 : 28;
        } else if (M == 4 || M == 6 || M == 9 || M == 11) {
            maxDay = 30;
        } else {
            maxDay = 31;
        }
        ensuref(D <= maxDay,
                "Invalid date on test case %d: %d/%d/%d", tc, D, M, Y);
    }

    inf.readEof();
    return 0;
}
