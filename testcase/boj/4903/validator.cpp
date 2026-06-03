#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCases = 0;
    while (true) {
        string line = inf.readLine("[^]+", "case_line");
        size_t split = line.find(' ');
        ensuref(split != string::npos, "line must contain two numbers");
        ensuref(line.front() != ' ' && line.back() != ' ',
                "line must not have leading or trailing spaces");

        string first = line.substr(0, split);
        size_t secondStart = line.find_first_not_of(' ', split);
        ensuref(secondStart != string::npos, "line must contain a second number");
        string second = line.substr(secondStart);
        ensuref(second.find(' ') == string::npos, "line must contain exactly two numbers");

        long long a = stringToLongLong(inf, first);
        long long b = stringToLongLong(inf, second);

        if (a == -1 && b == -1) {
            break;
        }

        ++testCases;
        setTestCase(testCases);
        ensuref(testCases <= 100000,
                "too many test cases: %d",
                testCases); // CHECK: statement gives no case-count limit.
        ensuref(0 <= a && a <= 10, "A must be between 0 and 10, got %lld", a);
        ensuref(0 <= b && b <= 10, "B must be between 0 and 10, got %lld", b);
    }

    inf.readEof();
}
