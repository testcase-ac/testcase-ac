#include "testlib.h"

#include <string>

using namespace std;

namespace {

bool isName(const string& value) {
    if (value.empty() || value.size() > 20) {
        return false;
    }
    for (char ch : value) {
        if (ch < 'a' || ch > 'z') {
            return false;
        }
    }
    return true;
}

bool isRemoveAlbumArg(const string& value) {
    return value == "-1" || value == "0" || value == "1" || isName(value);
}

bool isDeletePhotoArg(const string& value) {
    return value == "-1" || value == "0" || value == "1" || isName(value);
}

bool isChangeAlbumArg(const string& value) {
    return value == ".." || value == "/" || isName(value);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        string command = inf.readToken("[a-z]{2,6}", "command");
        inf.readSpace();
        string argument = inf.readToken("[^\\ ]{1,20}", "argument");
        inf.readEoln();

        if (command == "mkalb" || command == "insert") {
            ensuref(isName(argument), "%s argument must be a lowercase name at command %d",
                    command.c_str(), i);
        } else if (command == "rmalb") {
            ensuref(isRemoveAlbumArg(argument), "invalid rmalb argument at command %d: %s", i,
                    argument.c_str());
        } else if (command == "delete") {
            ensuref(isDeletePhotoArg(argument), "invalid delete argument at command %d: %s", i,
                    argument.c_str());
        } else if (command == "ca") {
            ensuref(isChangeAlbumArg(argument), "invalid ca argument at command %d: %s", i,
                    argument.c_str());
        } else {
            ensuref(false, "unknown command at command %d: %s", i, command.c_str());
        }
    }

    inf.readEof();
}
