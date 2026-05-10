#include "testlib.h"
#include <vector>
#include <set>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // 2. Read N files
    vector<vector<int>> files;
    set<string> file_set; // to check for duplicate files

    for (int i = 0; i < N; ++i) {
        vector<int> file;
        bool found_minus1 = false;
        int cnt = 0;
        while (true) {
            int x = inf.readInt(-1, 2147483647, "file_element");
            ++cnt;
            if (x == -1) {
                found_minus1 = true;
                break;
            }
            ensuref(x >= 1, "File element must be a positive integer, got %d at file %d, position %d", x, i+1, cnt);
            file.push_back(x);
            // Next token: either space or EOLN
            char c = inf.curChar();
            if (c == ' ') {
                inf.readSpace();
            } else if (c == '\n' || c == '\r') {
                // Should not happen, -1 must be present in the line
                ensuref(false, "File %d: -1 terminator not found before end of line", i+1);
            }
        }
        // After -1, must be EOLN
        inf.readEoln();

        // Check file is not empty (length >= 1)
        ensuref(file.size() > 0, "File %d is empty (no elements before -1)", i+1);

        // Check for duplicate files (length and content)
        ostringstream oss;
        for (size_t j = 0; j < file.size(); ++j) {
            if (j) oss << ",";
            oss << file[j];
        }
        string sig = oss.str();
        ensuref(file_set.count(sig) == 0, "Duplicate file detected at index %d", i+1);
        file_set.insert(sig);

        files.push_back(file);
    }

    inf.readEof();
}
