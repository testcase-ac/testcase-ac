#include "testlib.h"
using namespace std;

int computeRemainder(const string &s) {
    int w[7] = {2, 7, 6, 5, 4, 3, 2};
    int sum = 0;
    for (int i = 0; i < 7; ++i)
        sum += (s[i] - '0') * w[i];
    return sum % 11;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int type = rnd.next(0, 6); // choose one of 7 patterns
    string s(7, '0');

    switch (type) {
        case 0: {
            // Fixed example from the statement
            s = "6830907";
            println(s);
            break;
        }
        case 1: {
            // All zeros
            s = "0000000";
            println(s);
            break;
        }
        case 2: {
            // All same digit
            int d = rnd.next(0, 9);
            s.assign(7, char('0' + d));
            println(s);
            break;
        }
        case 3: {
            // Palindromic number
            for (int i = 0; i < 4; ++i) {
                char c = char('0' + rnd.next(0, 9));
                s[i] = c;
                s[6 - i] = c;
            }
            println(s);
            break;
        }
        case 4: {
            // Leading zero, rest random
            s[0] = '0';
            for (int i = 1; i < 7; ++i)
                s[i] = char('0' + rnd.next(0, 9));
            println(s);
            break;
        }
        case 5: {
            // Fully random digits
            for (int i = 0; i < 7; ++i)
                s[i] = char('0' + rnd.next(0, 9));
            println(s);
            break;
        }
        case 6: {
            // Force a specific remainder (bias towards 0 and 10)
            int target;
            int coin = rnd.next(0, 9);
            if (coin < 4) target = 0;       // 40% chance
            else if (coin < 7) target = 10; // 30% chance
            else target = rnd.next(0, 10);  // 30% any

            bool found = false;
            for (int attempt = 0; attempt < 10000 && !found; ++attempt) {
                for (int i = 0; i < 7; ++i)
                    s[i] = char('0' + rnd.next(0, 9));
                if (computeRemainder(s) == target)
                    found = true;
            }
            if (!found) {
                // Fallback to random digits
                for (int i = 0; i < 7; ++i)
                    s[i] = char('0' + rnd.next(0, 9));
            }
            println(s);
            break;
        }
    }

    return 0;
}
