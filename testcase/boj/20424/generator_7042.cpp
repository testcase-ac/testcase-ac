#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Define characters that have valid mirror mappings
    string valid = "AEHIMOSTUVWXYZ";        // uppercase
    valid += "bdilmnopqruvwx";              // lowercase
    valid += "0123578";                     // digits

    // Define characters that do NOT have mirror mappings
    string invalid = "BCDFGJKLNPR";         // uppercase invalid
    invalid += "acefghjkstyz";              // lowercase invalid
    invalid += "469";                       // digit invalid

    // Choose length from 1 to 20, biased towards smaller lengths
    int n = rnd.wnext(19, -2) + 1;

    bool makeInvalid = rnd.next(0, 99) < 30;  // 30% chance to include an impossible char
    string s;
    s.resize(n);
    if (makeInvalid) {
        // Pick one position to be invalid
        int pos = rnd.next(0, n - 1);
        for (int i = 0; i < n; i++) {
            if (i == pos) {
                s[i] = rnd.any(invalid);
            } else {
                s[i] = rnd.any(valid);
            }
        }
    } else {
        // All characters valid
        for (int i = 0; i < n; i++) {
            s[i] = rnd.any(valid);
        }
    }
    println(s);
    return 0;
}
