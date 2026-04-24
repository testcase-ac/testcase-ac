#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of lines
    int N = rnd.next(1, 10);

    // Hyper-parameters for diversity
    int maxWords    = rnd.next(1, 6);   // up to this many words per line
    int maxWordLen  = rnd.next(1, 10);  // up to this many characters per word

    // Alphabet for word characters
    string alphabet = "abcdefghijklmnopqrstuvwxyz"
                      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                      "0123456789";

    // Output the number of lines
    println(N);

    // Generate each line
    for (int i = 0; i < N; i++) {
        int words = rnd.next(1, maxWords);
        string line;
        for (int w = 0; w < words; w++) {
            if (w > 0) line.push_back(' ');
            int wlen = rnd.next(1, maxWordLen);
            for (int k = 0; k < wlen; k++) {
                line.push_back(rnd.any(alphabet));
            }
        }
        // Ensure we do not exceed 50 characters
        if ((int)line.size() > 50) {
            line.resize(50);
        }
        println(line);
    }

    return 0;
}
