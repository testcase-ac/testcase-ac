#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read p and w
    int p = inf.readInt(1, 1000, "p");
    inf.readSpace();
    int w = inf.readInt(1, 1000, "w");
    inf.readEoln();

    // Read the message line as a whole (may contain spaces)
    string s = inf.readLine("[A-Z\\ ]*", "message");

    // Length constraint: "length is less than 1000"
    ensuref((int)s.size() < 1000, "message length must be less than 1000, got %d", (int)s.size());

    // No leading or trailing spaces
    if (!s.empty()) {
        ensuref(s.front() != ' ', "message must not start with a space");
        ensuref(s.back()  != ' ', "message must not end with a space");
    }

    // Characters are restricted by regex to 'A'-'Z' and space; no further per-char check needed

    // Now verify all global constraints implied by the statement:
    //
    // We will simulate typing and check:
    // - The keypad mapping is applied correctly.
    // - The total time fits into 32-bit signed int (problem expects normal int output).
    //   In worst case: length < 1000, each character up to 4 presses, plus waits.
    //   Maximum theoretical: (999 * 4 presses * 1000 p) + (998 * 1000 w) ~ 8e9, may exceed 32-bit.
    //   We'll use 64-bit during computation, but there is no explicit bound in statement on result,
    //   so no extra ensure is needed, just avoid overflow in validator.

    auto getKeyAndPresses = [](char c) -> pair<int,int> {
        if (c == ' ') return make_pair(1, 1);
        // Map letters to (key, presses)
        // 2: ABC, 3: DEF, 4: GHI, 5: JKL, 6: MNO, 7: PQRS, 8: TUV, 9: WXYZ
        if (c >= 'A' && c <= 'C') return make_pair(2, c - 'A' + 1);
        if (c >= 'D' && c <= 'F') return make_pair(3, c - 'D' + 1);
        if (c >= 'G' && c <= 'I') return make_pair(4, c - 'G' + 1);
        if (c >= 'J' && c <= 'L') return make_pair(5, c - 'J' + 1);
        if (c >= 'M' && c <= 'O') return make_pair(6, c - 'M' + 1);
        if (c >= 'P' && c <= 'S') return make_pair(7, c - 'P' + 1);
        if (c >= 'T' && c <= 'V') return make_pair(8, c - 'T' + 1);
        if (c >= 'W' && c <= 'Z') return make_pair(9, c - 'W' + 1);
        // Should not reach here because of regex
        return make_pair(-1, 0);
    };

    long long totalTime = 0;
    int prevKey = -1;
    bool first = true;

    for (int i = 0; i < (int)s.size(); ++i) {
        char c = s[i];
        auto kp = getKeyAndPresses(c);
        int key = kp.first;
        int presses = kp.second;

        // Sanity check: mapping should be valid
        ensuref(key != -1 && presses > 0, "invalid character mapping at position %d ('%c')", i, c);

        if (!first) {
            // If same key and not both spaces, we must wait w before next character
            // But the statement explicitly says: "공백을 연속으로 누를 때는 기다릴 필요가 없다."
            // which means no wait between consecutive spaces (both ' ' -> key 1).
            if (key == prevKey && !(c == ' ' && s[i-1] == ' ')) {
                totalTime += w;
            }
        }
        first = false;

        // Time for presses of this character
        totalTime += 1LL * presses * p;
    }

    // No extra constraints on totalTime in statement; just ensure no overflow occurred logically.
    // Using long long is sufficient for given bounds.

    inf.readEof();
}
