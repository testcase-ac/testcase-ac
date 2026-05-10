#include "testlib.h"
#include <vector>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

// Helper: check if a string consists only of digits 1-8, no leading zeros, non-empty, length <= 10000
void validate_piece_string(const string& s, int line_no) {
    ensuref(!s.empty(), "Line %d: Empty input line", line_no);
    ensuref(s.size() <= 10000, "Line %d: Too many pieces (%zu > 10000)", line_no, s.size());
    for (size_t i = 0; i < s.size(); ++i) {
        ensuref('1' <= s[i] && s[i] <= '8', "Line %d: Invalid piece '%c' at position %zu (must be 1-8)", line_no, s[i], i+1);
    }
}

// Simulate the rules to check if a given arrangement is "VALID"
bool is_valid(const string& s) {
    int n = s.size();
    if (n == 0) return false;
    // 1. 가장 왼쪽 조각은 1번, 가장 오른쪽 조각은 2번이어야 한다.
    if (s[0] != '1' || s[n-1] != '2') return false;

    // 2. 인접한 조각은 서로 맞물려야 한다.
    //    예: 4번,5번은 항상 1번 오른쪽에 있어야 한다. 4번은 1번/3번 오른쪽에만 올 수 있다.
    //    1번 왼쪽, 2번 오른쪽에 맞물리는 조각은 없다.
    //    각각의 1번에 대해 대응하는 2번, 5번에 대해 6번 대응

    // We'll use a stack to simulate the block structure.
    // 1/5: openers, 2/6: closers, 3/4/7/8: mid pieces
    // Rules:
    // - 1 must be closed by 2
    // - 5 must be closed by 6
    // - 4 can only follow 1 or 3
    // - 5/6 must be inside a 1...2 block
    // - 7/8 can be anywhere inside a 1...2 block

    struct Frame {
        char type; // '1' or '5'
        int pos;   // position in string (for error reporting)
    };
    stack<Frame> stk;

    // To ensure 5/6 are inside a 1...2 block, track if we are inside a 1...2
    int open1 = 0;

    for (int i = 0; i < n; ++i) {
        char c = s[i];
        if (c == '1') {
            // 1번 조각의 왼쪽에 맞물리는 조각은 없다.
            if (i != 0) return false;
            stk.push({'1', i});
            open1++;
        }
        else if (c == '2') {
            // 2번 조각의 오른쪽에 맞물리는 조각은 없다.
            if (i != n-1) return false;
            if (stk.empty() || stk.top().type != '1') return false;
            stk.pop();
            open1--;
        }
        else if (c == '5') {
            // 5 must be inside a 1...2 block
            if (open1 == 0) return false;
            stk.push({'5', i});
        }
        else if (c == '6') {
            // 6 must close a 5
            if (stk.empty() || stk.top().type != '5') return false;
            stk.pop();
        }
        else if (c == '4') {
            // 4번 조각은 1번이나 3번 오른쪽에만 올 수 있다.
            if (i == 0) return false;
            if (s[i-1] != '1' && s[i-1] != '3') return false;
            // 4 must be inside a 1...2 block
            if (open1 == 0) return false;
        }
        else if (c == '3') {
            // 3 can be anywhere inside a 1...2 block (except first)
            if (i == 0) return false;
            if (open1 == 0) return false;
        }
        else if (c == '7' || c == '8') {
            // 7/8 can be anywhere inside a 1...2 block (except first)
            if (i == 0) return false;
            if (open1 == 0) return false;
        }
        else {
            // Should not happen due to earlier validation
            return false;
        }
    }
    // After processing, stack must be empty
    if (!stk.empty()) return false;
    if (open1 != 0) return false;
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int line_no = 0;
    while (true) {
        string s = inf.readLine("[^]+", "block_string");
        ++line_no;
        // Last line: single '0'
        if (s == "0") break;

        // Validate string: only digits 1-8, length 1..10000
        validate_piece_string(s, line_no);

        // No further checks here: the problem is to check validity in the solution, not in the validator
        // (But we must check that the input is syntactically valid and within constraints)
    }
    inf.readEof();
}
