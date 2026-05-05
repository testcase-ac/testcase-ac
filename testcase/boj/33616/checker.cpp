#include <cmath>
#include <string>
#include "testlib.h"

int main(int argc, char* argv[])
{
    registerTestlibCmd(argc, argv);

    int T = inf.readInt();
    
    for (int i = 0; i < T; i++)
    {
        int a = inf.readInt();
        int b = inf.readInt();

        int k = ouf.readInt();
        int diff = std::abs(a - b) / 2;

        if ((a ^ b) & 1)
        {
            if (k != -1)
            {
                quitf(_wa, "Not adjacent number of commands (AC: -1, WA: %d)", k);
            }
        }
        else if ((a > b) ? (a ^ diff) == b + diff : a + diff == (b ^ diff))
        {
            if (k != 1)
            {
                quitf(_wa, "Not adjacent number of commands (AC: 1, WA: %d)", k);
            }

            std::string s = ouf.readToken("[AB]");
            if (s.length() != 1) quitf(_wa, "Expected single character command ('A' or 'B'), but found \"%s\"", s.c_str());
            char c = s[0];
            int x = ouf.readInt(1, (1 << 30) - 1);
            if (c != 'A' && c != 'B')
            {
                quitf(_wa, "Expected A or B, got %c", c);
            }

            if (c == 'A')
            {
                a ^= x, b += x;
            }
            else
            {
                a += x, b ^= x;
            }

            if (a != b)
            {
                quitf(_wa, "It can't be same number");
            }
        }
        else
        {
            if (k != 2)
            {
                quitf(_wa, "Not adjacent number of commands (AC: 2, WA: %d)", k);
            }

            std::string s = ouf.readToken("[AB]");
            if (s.length() != 1) quitf(_wa, "Expected single character command ('A' or 'B'), but found \"%s\"", s.c_str());
            char c = s[0];
            int x = ouf.readInt(1, (1 << 30) - 1);
            if (c != 'A' && c != 'B')
            {
                quitf(_wa, "Expected A or B, got %c", c);
            }

            if (c == 'A')
            {
                a ^= x, b += x;
            }
            else
            {
                a += x, b ^= x;
            }

            s = ouf.readToken("[AB]");
            if (s.length() != 1) quitf(_wa, "Expected single character command ('A' or 'B'), but found \"%s\"", s.c_str());
            c = s[0];
            x = ouf.readInt(1, (1 << 30) - 1);
            if (c != 'A' && c != 'B')
            {
                quitf(_wa, "Expected A or B, got %c", c);
            }

            if (c == 'A')
            {
                a ^= x, b += x;
            }
            else
            {
                a += x, b ^= x;
            }

            if (a != b)
            {
                quitf(_wa, "It can't be same number");
            }
        }
    }
    
        quitf(_ok, "all pass");
}
