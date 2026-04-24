#include "testlib.h"
#include <string>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of courses: unspecified upper bound => assume up to 100,000
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Regex for subject name: letters (upper/lower), digits, underscore
    const string subj_regex = "[A-Za-z0-9_]+";
    // Regex for grade tokens
    const string grade_regex = "A\\+|A0|A\\-|B\\+|B0|B\\-|C\\+|C0|C\\-|D\\+|D0|D\\-|F";

    for (int i = 0; i < N; i++) {
        // Read subject name
        string subj = inf.readToken(subj_regex, "subject_name");
        // Check length ≤ 100
        ensuref((int)subj.size() <= 100,
                "Length of subject_name at line %d is %d, but must be at most 100",
                i + 2, (int)subj.size());
        inf.readSpace();

        // Read credit: 1 to 3
        int credit = inf.readInt(1, 3, "credit");
        (void)credit;
        inf.readSpace();

        // Read grade
        string grade = inf.readToken(grade_regex, "grade");
        (void)grade;

        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
