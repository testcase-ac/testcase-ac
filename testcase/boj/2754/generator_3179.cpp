#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Possible letter grades
    vector<string> letters = {"A", "B", "C", "D", "F"};
    // Hyper-parameter for biasing letter selection
    int t1 = rnd.next(-2, 2);
    int li = rnd.wnext((int)letters.size(), t1);
    string grade = letters[li];

    // If not 'F', add a sign part
    if (grade != "F") {
        vector<string> signs = {"+", "0", "-"};
        // Hyper-parameter for biasing sign selection
        int t2 = rnd.next(-1, 1);
        int si = rnd.wnext((int)signs.size(), t2);
        grade += signs[si];
    }

    // Output the single grade input
    println(grade);

    return 0;
}
