#include "testlib.h"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int N = rnd.next(1, 5); // Generates N between 1 and 3
    vector<string> grades = {
        "A+", "A0", "A-", "B+", "B0", "B-",
        "C+", "C0", "C-", "D+", "D0", "D-", "F"
    };
    
    println(N);
    for (int i = 0; i < N; ++i) {
        string subject = "course" + to_string(i + 1);
        int credit = rnd.next(1, 3);
        string grade = grades[rnd.next(0, 12)];
        println(subject, credit, grade);
    }
    
    return 0;
}
