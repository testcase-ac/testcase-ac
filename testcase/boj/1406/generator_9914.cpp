#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // With small probability, output one of the samples from the statement
    if (rnd.next(0, 9) == 0) {
        int sampleId = rnd.next(1, 3);
        if (sampleId == 1) {
            string s = "abcd";
            int M = 3;
            println(s);
            println(M);
            println("P", 'x');
            println(string("L"));
            println("P", 'y');
        } else if (sampleId == 2) {
            string s = "abc";
            int M = 9;
            println(s);
            println(M);
            println(string("L"));
            println(string("L"));
            println(string("L"));
            println(string("L"));
            println(string("L"));
            println("P", 'x');
            println(string("L"));
            println(string("B"));
            println("P", 'y');
        } else {
            string s = "dmih";
            int M = 11;
            println(s);
            println(M);
            println(string("B"));
            println(string("B"));
            println("P", 'x');
            println(string("L"));
            println(string("B"));
            println(string("B"));
            println(string("B"));
            println("P", 'y');
            println(string("D"));
            println(string("D"));
            println("P", 'z');
        }
        return 0;
    }

    struct Scenario {
        int minLen, maxLen;
        int minM, maxM;
        double pL, pD, pB, pP;
    };

    vector<Scenario> scenarios = {
        // 0: Tiny, fully random
        {0, 5, 1, 5,   0.25, 0.25, 0.25, 0.25},
        // 1: Medium, insert-heavy
        {1, 15, 10, 40, 0.2, 0.2, 0.1, 0.5},
        // 2: Delete & boundary heavy
        {0, 10, 20, 60, 0.3, 0.1, 0.5, 0.1},
        // 3: Move-only (string should stay same)
        {1, 20, 20, 60, 0.5, 0.5, 0.0, 0.0},
        // 4: Insert-heavy, some useless deletes
        {0, 10, 20, 60, 0.1, 0.0, 0.1, 0.8},
        // 5: Balanced, slightly larger
        {3, 25, 30, 80, 0.25, 0.25, 0.25, 0.25}
    };

    int scenarioId = rnd.next(0, (int)scenarios.size() - 1);
    Scenario sc = scenarios[scenarioId];

    int len0 = rnd.next(sc.minLen, sc.maxLen);
    int M = rnd.next(sc.minM, sc.maxM);

    // Generate initial string
    string s;
    if (len0 > 0) {
        int style = rnd.next(0, 2); // 0,1,2
        if (style == 0) {
            // Single repeated character
            char c = char('a' + rnd.next(0, 2)); // 'a'..'c'
            s.assign(len0, c);
        } else if (style == 1) {
            // Repeating pattern "abc..."
            for (int i = 0; i < len0; ++i)
                s.push_back(char('a' + (i % 3)));
        } else {
            // Random from small alphabet
            for (int i = 0; i < len0; ++i)
                s.push_back(char('a' + rnd.next(0, 5))); // 'a'..'f'
        }
    }

    vector<pair<char, char>> cmds;
    cmds.reserve(M);

    double pL = sc.pL, pD = sc.pD, pB = sc.pB, pP = sc.pP;
    double sumP = pL + pD + pB + pP;
    // Normalize just in case
    if (sumP == 0.0) {
        // Fallback: all moves to the right
        pL = 0.0; pD = 1.0; pB = 0.0; pP = 0.0;
        sumP = 1.0;
    }
    pL /= sumP; pD /= sumP; pB /= sumP; pP /= sumP;

    for (int i = 0; i < M; ++i) {
        double r = rnd.next(); // [0,1)
        char cmd;
        char extra = 0;

        if (r < pL) {
            cmd = 'L';
        } else if (r < pL + pD) {
            cmd = 'D';
        } else if (r < pL + pD + pB) {
            cmd = 'B';
        } else {
            cmd = 'P';
            // Choose inserted character with some structure
            int choose = rnd.next(0, 9);
            if (choose < 3) {
                extra = char('a' + rnd.next(0, 2)); // 'a'..'c'
            } else if (choose < 6) {
                extra = char('x' + rnd.next(0, 2)); // 'x'..'z'
            } else {
                extra = char('a' + rnd.next(0, 25)); // any lowercase
            }
        }

        cmds.push_back(make_pair(cmd, extra));
    }

    // Output
    println(s);
    println(M);
    for (auto &cmd : cmds) {
        if (cmd.first == 'P') {
            println("P", cmd.second);
        } else {
            string line(1, cmd.first);
            println(line);
        }
    }

    return 0;
}
