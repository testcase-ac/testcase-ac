#include "testlib.h"
#include <set>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

// Helper: check if a string is in "a is b" format, with a != b, both lowercase
// Accepts both "a is b" and "a is b\n" (but readLine() strips \n)
void parse_is_line(const string& line, char& a, char& b, int line_no, const char* type) {
    // Must be exactly 5 characters: "a is b"
    // 0: a, 1: ' ', 2: 'i', 3: 's', 4: ' ', 5: b
    // But in the sample, "a is b" is 6 characters: a, ' ', 'i', 's', ' ', b
    // So, must be 6 characters
    ensuref(line.size() == 6, "Line %d (%s): Must be exactly 6 characters, got \"%s\" (len=%zu)", line_no, type, line.c_str(), line.size());
    a = line[0];
    ensuref(a >= 'a' && a <= 'z', "Line %d (%s): First character must be a lowercase letter, got '%c'", line_no, type, a);
    ensuref(line[1] == ' ', "Line %d (%s): 2nd char must be space, got '%c'", line_no, type, line[1]);
    ensuref(line[2] == 'i', "Line %d (%s): 3rd char must be 'i', got '%c'", line_no, type, line[2]);
    ensuref(line[3] == 's', "Line %d (%s): 4th char must be 's', got '%c'", line_no, type, line[3]);
    ensuref(line[4] == ' ', "Line %d (%s): 5th char must be space, got '%c'", line_no, type, line[4]);
    b = line[5];
    ensuref(b >= 'a' && b <= 'z', "Line %d (%s): Last character must be a lowercase letter, got '%c'", line_no, type, b);
    ensuref(a != b, "Line %d (%s): a and b must be different, got '%c' and '%c'", line_no, type, a, b);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read n
    int n = inf.readInt(2, 26, "n");
    inf.readEoln();

    // 2. Read n premises
    vector<int> premise_target(26, -1);
    for (int i = 0; i < n; ++i) {
        string line = inf.readLine("[^]+", "premise"); // Read whole line, check format manually
        char a, b;
        parse_is_line(line, a, b, i+2, "premise");
        int lhs = a - 'a';
        int rhs = b - 'a';
        ensuref(premise_target[lhs] == -1 || premise_target[lhs] == rhs, "Premise at line %d gives '%c' more than one target", i+2, a);
        premise_target[lhs] = rhs;
    }

    // 3. Read m
    int m = inf.readInt(1, 10, "m");
    inf.readEoln();

    // 4. Read m conclusions
    for (int i = 0; i < m; ++i) {
        string line = inf.readLine("[^]+", "conclusion");
        char a, b;
        parse_is_line(line, a, b, n+3+i, "conclusion");
        // Duplicates in conclusions are allowed (not specified), so no check here
    }

    // 5. File must end with EOF
    inf.readEof();
}
