#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of files N
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // All filenames must have the same length
    int expected_len = -1;
    for (int i = 0; i < N; i++) {
        // Filenames consist of lowercase letters and '.' only, length 1 to 50
        string fname = inf.readToken("[a-z.]{1,50}", "filename");
        if (i == 0) {
            expected_len = (int)fname.size();
            ensuref(expected_len >= 1 && expected_len <= 50,
                    "Filename length %d is out of bounds [1,50]", expected_len);
        } else {
            ensuref((int)fname.size() == expected_len,
                    "Filename #%d has length %d but expected %d",
                    i+1, (int)fname.size(), expected_len);
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
