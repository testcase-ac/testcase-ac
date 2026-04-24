#include "testlib.h"
#include <string>
#include <cassert>
using namespace std;

static int parse_cents(const string &s) {
    // s is in form D...D.DD
    int dot = -1;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '.') {
            dot = i;
            break;
        }
    }
    // we assume format is validated by regex before
    assert(dot > 0 && dot + 2 < (int)s.size());
    int ip = 0;
    for (int i = 0; i < dot; i++) {
        ip = ip * 10 + (s[i] - '0');
    }
    int fp = (s[dot+1] - '0') * 10 + (s[dot+2] - '0');
    return ip * 100 + fp;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const string money_re = "(0\\.[0-9]{2}|[1-9][0-9]?\\.[0-9]{2}|100\\.00)";
    int tc = 0;
    bool terminated = false;
    while (true) {
        // read n and m
        int n = inf.readInt(0, 5000, "n");
        inf.readSpace();
        string m_str = inf.readToken(money_re.c_str(), "m");
        inf.readEoln();

        int m_cents = parse_cents(m_str);

        if (n == 0) {
            // termination line
            ensuref(m_cents == 0,
                    "Termination line must be '0 0.00', found m = %s", m_str.c_str());
            terminated = true;
            break;
        }

        tc++;
        ensuref(tc <= 100000, "Number of test cases exceeds 100000: %d", tc);
        // for real cases, m >= 0.01
        ensuref(m_cents >= 1 && m_cents <= 100*100,
                "Test case %d: m must be between 0.01 and 100.00, found %s", tc, m_str.c_str());

        // read n candy lines
        for (int i = 0; i < n; i++) {
            int c = inf.readInt(1, 5000, "c_i");
            inf.readSpace();
            string p_str = inf.readToken(money_re.c_str(), "p_i");
            inf.readEoln();
            int p_cents = parse_cents(p_str);
            ensuref(p_cents >= 1 && p_cents <= 100*100,
                    "Test case %d, candy %d: price must be between 0.01 and 100.00, found %s",
                    tc, i+1, p_str.c_str());
        }
    }

    ensuref(terminated, "Input must end with termination line '0 0.00'");
    inf.readEof();
    return 0;
}
