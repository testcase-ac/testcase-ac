#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single line of commands: only '(', ')', '-' allowed, length 1..200000
    string s = inf.readLine("[()\\-]{1,200000}", "commands");
    // After readLine, EOLN is consumed. We expect EOF next.
    
    // Simulate the editor text size to ensure no '-' when text is empty.
    // '(' and ')' both append one character, '-' removes one.
    int text_size = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        char c = s[i];
        if (c == '(' || c == ')') {
            text_size++;
        } else {
            // c == '-'
            ensuref(text_size > 0,
                    "Invalid command '-' at position %d: text is already empty", 
                    i + 1);
            text_size--;
        }
    }

    inf.readEof();
    return 0;
}
