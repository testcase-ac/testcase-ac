#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int length = rnd.next(1, 6);
    string s;

    // Generate first digit with higher probability for 6 and 9
    string first_digits = "12345667899"; // 11 characters (6 and 9 appear twice)
    shuffle(first_digits.begin(), first_digits.end());
    first_digits = first_digits.substr(0, length);
    s += first_digits[rnd.next(0, (int)first_digits.size()-1)];
    
    // Generate remaining digits with higher probability for 6 and 9
    string other_digits = "0" + first_digits;
    for (int i = 1; i < length; ++i) {
        s += other_digits[rnd.next(0, (int)other_digits.size()-1)];
    }
    
    cout << s << endl;
    return 0;
}
