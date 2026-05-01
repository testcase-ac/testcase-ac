#include "testlib.h"
using namespace std;

char randomLetter() {
    return char('A' + rnd.next(0, 25));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Generate p and w with diverse patterns
    int modePW = rnd.next(0, 3);
    int p, w;
    switch (modePW) {
        case 0:
            p = 1;
            w = 1;
            break;
        case 1:
            p = 1;
            w = 1000;
            break;
        case 2:
            p = 1000;
            w = 1;
            break;
        default:
            p = rnd.next(1, 1000);
            w = rnd.next(1, 1000);
            break;
    }

    string message;
    int mode = rnd.next(0, 3);

    if (mode == 0) {
        // Canned small and tricky cases
        vector<string> canned = {
            "A",
            "Z",
            "AZ",
            "AAA",
            "ABC",
            "ABA",
            "A A",
            "AB BA",
            "ABC DEF",
            "HELLO WORLD",
            "ABBAS SALAM",
            "SMS",
            "TEXT MESSAGE",
            "MULTI TAP",
            "QQQ WWW",
            "A B C",
            "WXYZ WXYZ",
            "AA BB CC",
            "S O S"
        };
        message = rnd.any(canned);
    } else if (mode == 1) {
        // Same-key-heavy patterns with possible multiple spaces
        vector<string> keyGroups = {
            "ABC",   // 2
            "DEF",   // 3
            "GHI",   // 4
            "JKL",   // 5
            "MNO",   // 6
            "PQRS",  // 7
            "TUV",   // 8
            "WXYZ"   // 9
        };

        int groups = rnd.next(1, 5);
        message.clear();
        for (int g = 0; g < groups; ++g) {
            int idx = rnd.next(0, (int)keyGroups.size() - 1);
            string letters = keyGroups[idx];
            int len = rnd.next(1, 5);
            for (int i = 0; i < len; ++i) {
                char c = letters[rnd.next(0, (int)letters.size() - 1)];
                message.push_back(c);
            }
            if (g + 1 < groups) {
                int spaces = rnd.next(1, 3); // create single or multiple spaces
                for (int s = 0; s < spaces; ++s)
                    message.push_back(' ');
            }
        }
    } else {
        // Random message, with short or medium length
        bool medium = rnd.next(0, 1); // 0: short, 1: medium
        int n;
        if (!medium) n = rnd.next(1, 30);
        else n = rnd.next(31, 200);

        message.assign(n, 'A');
        for (int i = 0; i < n; ++i) {
            // 20% chance of space inside
            if (rnd.next(0, 4) == 0)
                message[i] = ' ';
            else
                message[i] = randomLetter();
        }
        // Fix first and last to not be spaces
        if (message[0] == ' ')
            message[0] = randomLetter();
        if (message[n - 1] == ' ')
            message[n - 1] = randomLetter();
    }

    // Output
    println(p, w);
    println(message);

    return 0;
}
