#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 4;
    const int N_MAX = 100;
    const int A_MIN = -1000000;
    const int A_MAX = 1000000;
    const int MAX_CASES = 100000;

    int case_cnt = 0;
    while (true) {
        // Read first token of the line (either N or 0)
        // Allow leading/trailing spaces on the line, so use readLine and parse
        string line = inf.readLine("[^]+", "N line");
        // Remove leading/trailing spaces
        size_t start = line.find_first_not_of(' ');
        size_t end = line.find_last_not_of(' ');
        ensuref(start != string::npos, "Empty line where N or 0 expected");
        string trimmed = line.substr(start, end - start + 1);

        // Parse N
        ensuref(trimmed.size() > 0, "No N found in line");
        // Only allow a single integer in the line
        size_t pos = 0;
        while (pos < trimmed.size() && (trimmed[pos] == '-' || isdigit(trimmed[pos]))) ++pos;
        ensuref(pos == trimmed.size(), "Extra characters after N in line: '%s'", trimmed.c_str());
        int N = atoi(trimmed.c_str());
        ensuref(N >= 0 && N <= N_MAX, "N out of range: %d", N);

        if (N == 0) {
            break;
        }
        ++case_cnt;
        ensuref(case_cnt <= MAX_CASES, "Too many test cases: %d (max %d)", case_cnt, MAX_CASES);
        ensuref(N >= N_MIN, "N too small: %d (min %d)", N, N_MIN);

        // Read N lines of N integers, allow arbitrary spaces between numbers
        for (int i = 0; i < N; ++i) {
            string row = inf.readLine("[^]+", "row");
            // Remove leading/trailing spaces
            size_t s = row.find_first_not_of(' ');
            size_t e = row.find_last_not_of(' ');
            ensuref(s != string::npos, "Empty row at line %d", i+1);
            string trimmed_row = row.substr(s, e - s + 1);

            // Now parse the row into N integers, allowing multiple spaces
            vector<int> vals;
            size_t idx = 0;
            while (idx < trimmed_row.size()) {
                // Skip spaces
                while (idx < trimmed_row.size() && trimmed_row[idx] == ' ') ++idx;
                if (idx == trimmed_row.size()) break;
                // Parse integer
                int sign = 1;
                if (trimmed_row[idx] == '-') {
                    sign = -1;
                    ++idx;
                }
                ensuref(idx < trimmed_row.size() && isdigit(trimmed_row[idx]), "Invalid integer in row %d", i+1);
                int val = 0;
                while (idx < trimmed_row.size() && isdigit(trimmed_row[idx])) {
                    int digit = trimmed_row[idx] - '0';
                    // Check for overflow
                    ensuref(val <= (A_MAX + (sign == -1)), "Integer overflow in row %d", i+1);
                    val = val * 10 + digit;
                    ++idx;
                }
                val *= sign;
                ensuref(val >= A_MIN && val <= A_MAX, "Value out of range at row %d: %d", i+1, val);
                vals.push_back(val);
            }
            ensuref((int)vals.size() == N, "Row %d does not have exactly N=%d values (got %d)", i+1, N, (int)vals.size());
        }
    }

    inf.readEof();
}
