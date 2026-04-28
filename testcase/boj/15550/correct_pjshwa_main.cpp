#include <iostream>

using namespace std;
int main() {
    long long a = 9007199254740992;
    double b = 9007199254740992.0;
    long long c = 9007199254740993;
    if (a == b && b == c && c != a) {
        cout << "true" << '\n';
    } else {
        cout << "false" << '\n';
    }
    return 0;
}

// Answer:
// long long 9007199254740992
// double 9007199254740992.0
// long long 9007199254740993

// #include <iostream>
 
// using namespace std;
 
// int main()
// {
//     cout << "char \t\t: " << sizeof(char) << " bytes\n";
//     cout << "unsigned char \t: " << sizeof(unsigned char) << " bytes\n";
//     cout << "wchar_t \t: " << sizeof(wchar_t) << " bytes\n";
//     cout << "bool \t\t: " << sizeof(bool) << " bytes\n";
//     cout << "short \t\t: " << sizeof(short) << " bytes\n";
//     cout << "unsigned short \t: " << sizeof(unsigned short) << " bytes\n";
//     cout << "int \t\t: " << sizeof(int) << " bytes\n";
//     cout << "unsigned int \t: " << sizeof(unsigned int) << " bytes\n";
//     cout << "long  \t\t: " << sizeof(long) << " bytes\n";
//     cout << "unsigned long \t: " << sizeof(unsigned long) << " bytes\n";
//     cout << "float \t\t: " << sizeof(float) << " bytes\n";
//     cout << "double \t\t: " << sizeof(double) << " bytes\n";
//     return 0;
// }
