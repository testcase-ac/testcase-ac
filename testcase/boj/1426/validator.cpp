#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // 2. Read N cards: each line is "<int> <char>"
    vector<int> card_num(N);
    vector<char> card_char(N);
    for (int i = 0; i < N; ++i) {
        card_num[i] = inf.readInt(1, 1000, "card_num");
        inf.readSpace();
        string s = inf.readToken("[A-Z]", "card_char");
        ensuref(s.size() == 1, "Card character must be a single uppercase letter, got '%s' at line %d", s.c_str(), i+2);
        card_char[i] = s[0];
        inf.readEoln();
    }

    // 3. Read N bin numbers
    vector<int> bin_num = inf.readInts(N, 1, 1000, "bin_num");
    inf.readEoln();

    // 4. No further input
    inf.readEof();

    // 5. Validate: Each card is (int, char), all in bounds (already checked above)
    // 6. Validate: Each bin number is in [1,1000] (already checked above)

    // 7. Validate: It is possible that the answer is -1 (i.e., not always possible to assign)
    // But the problem does NOT guarantee that the answer always exists, so we do NOT need to check that every input is solvable.

    // 8. Validate: No further global constraints are implied by the statement.

    // 9. Check for duplicate cards? The statement does not forbid duplicate cards.

    // 10. Check for duplicate bin numbers? The statement does not forbid duplicate bin numbers.

    // 11. Check for unnecessary leading zeros in numbers? The statement says "자연수" (natural number), but does not mention leading zeros.
    // However, testlib's readInt will reject leading zeros except for 0 itself, so no further check is needed.

    // All constraints are checked.

    return 0;
}
