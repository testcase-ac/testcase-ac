#include "testlib.h"
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of files
    int N = inf.readInt(1, 50000, "N");
    inf.readEoln();

    for (int i = 0; i < N; i++) {
        // Read the file name line: only lowercase letters and dots, length [3,100]
        string fname = inf.readLine("[a-z.]{3,100}", "filename");
        // Validate exactly one dot
        int cnt = count(fname.begin(), fname.end(), '.');
        ensuref(cnt == 1,
                "filename \"%s\" must contain exactly one dot, found %d",
                fname.c_str(), cnt);
        // Dot must not be first character
        ensuref(fname.front() != '.',
                "filename \"%s\" must not start with a dot", fname.c_str());
        // Dot must not be last character
        ensuref(fname.back() != '.',
                "filename \"%s\" must not end with a dot", fname.c_str());
    }

    // No extra content
    inf.readEof();
    return 0;
}
