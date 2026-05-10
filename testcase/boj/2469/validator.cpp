#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read k
    int k = inf.readInt(3, 26, "k");
    inf.readEoln();

    // 2. Read n
    int n = inf.readInt(3, 1000, "n");
    inf.readEoln();

    // 3. Read final order
    string final_order = inf.readToken("[A-Z]{1,26}", "final_order");
    ensuref((int)final_order.size() == k, "final_order length must be k=%d, but got %d", k, (int)final_order.size());
    // All letters must be unique and must be first k uppercase letters
    set<char> allowed;
    for (int i = 0; i < k; ++i) allowed.insert('A' + i);
    set<char> seen;
    for (int i = 0; i < k; ++i) {
        char c = final_order[i];
        ensuref(allowed.count(c), "final_order contains invalid character '%c' at position %d", c, i);
        ensuref(!seen.count(c), "final_order contains duplicate character '%c'", c);
        seen.insert(c);
    }
    inf.readEoln();

    // 4. Read n ladder rows
    int hidden_row = -1;
    vector<string> ladder;
    for (int i = 0; i < n; ++i) {
        string row = inf.readToken("[*\\-\\?]{1,25}", "ladder_row");
        ensuref((int)row.size() == k-1, "ladder row %d length must be k-1=%d, but got %d", i+1, k-1, (int)row.size());
        // Check for hidden row
        if (row.find('?') != string::npos) {
            ensuref(row == string(k-1, '?'), "ladder row %d: if '?' present, all characters must be '?'", i+1);
            ensuref(hidden_row == -1, "Multiple hidden rows detected: previous at %d, now at %d", hidden_row+1, i+1);
            hidden_row = i;
        } else {
            // Only '*' or '-' allowed
            for (int j = 0; j < k-1; ++j) {
                ensuref(row[j] == '*' || row[j] == '-', "ladder row %d: invalid character '%c' at position %d", i+1, row[j], j+1);
            }
            // No adjacent '-'
            for (int j = 0; j < k-2; ++j) {
                ensuref(!(row[j] == '-' && row[j+1] == '-'), "ladder row %d: adjacent '-' at positions %d and %d", i+1, j+1, j+2);
            }
        }
        ladder.push_back(row);
        inf.readEoln();
    }
    ensuref(hidden_row != -1, "No hidden row ('?' row) found in ladder");

    inf.readEof();
}
