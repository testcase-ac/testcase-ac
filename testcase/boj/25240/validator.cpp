#include "testlib.h"

#include <set>
#include <string>

using namespace std;

namespace {

constexpr int kMaxUsers = 500000;
constexpr int kMaxFiles = 500000;
constexpr int kMaxQueries = 500000;
constexpr int kMaxExplicitGroups = 100000;

string readName(const char* fieldName) {
    return inf.readToken("[A-Za-z0-9]{1,10}", fieldName);
}

bool hasWriteWithoutRead(int permission) {
    return (permission & 2) && !(permission & 4);
}

int readPermission() {
    string token = inf.readToken("[0-7]{3}", "file_permission");
    int owner = token[0] - '0';
    int group = token[1] - '0';
    int other = token[2] - '0';

    ensuref((owner | group) == owner,
            "owner permission must include group permission: %s",
            token.c_str());
    ensuref((group | other) == group,
            "group permission must include other permission: %s",
            token.c_str());
    ensuref(!hasWriteWithoutRead(owner),
            "owner write permission must include read permission: %s",
            token.c_str());
    ensuref(!hasWriteWithoutRead(group),
            "group write permission must include read permission: %s",
            token.c_str());
    ensuref(!hasWriteWithoutRead(other),
            "other write permission must include read permission: %s",
            token.c_str());

    return owner * 100 + group * 10 + other;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int userCount = inf.readInt(1, kMaxUsers, "U");
    inf.readSpace();
    int fileCount = inf.readInt(1, kMaxFiles, "F");
    inf.readEoln();

    set<string> users;
    set<string> groups;
    int explicitGroupCount = 0;

    for (int i = 0; i < userCount; ++i) {
        string userName = readName("user_name");
        ensuref(users.insert(userName).second, "duplicate user name: %s", userName.c_str());
        groups.insert(userName);

        if (inf.eoln()) {
            continue;
        }

        inf.readSpace();
        string groupToken = inf.readToken("[A-Za-z0-9,]{1,109}", "user_groups");
        inf.readEoln();

        set<string> userGroups;
        int groupCountForUser = 0;
        size_t start = 0;
        while (true) {
            size_t comma = groupToken.find(',', start);
            string groupName = groupToken.substr(start, comma == string::npos ? string::npos
                                                                              : comma - start);
            ensuref(!groupName.empty(), "empty group name in user %s", userName.c_str());
            ensuref(groupName.size() <= 10,
                    "group name too long in user %s: %s",
                    userName.c_str(),
                    groupName.c_str());
            ensuref(userGroups.insert(groupName).second,
                    "duplicate group in user %s: %s",
                    userName.c_str(),
                    groupName.c_str());
            groups.insert(groupName);
            ++explicitGroupCount;
            ++groupCountForUser;
            ensuref(groupCountForUser <= 10,
                    "too many groups for user %s: %d",
                    userName.c_str(),
                    groupCountForUser);

            if (comma == string::npos) {
                break;
            }
            start = comma + 1;
        }
    }

    ensuref(explicitGroupCount <= kMaxExplicitGroups,
            "total explicit group memberships exceeds %d: %d",
            kMaxExplicitGroups,
            explicitGroupCount);

    set<string> files;
    for (int i = 0; i < fileCount; ++i) {
        string fileName = readName("file_name");
        ensuref(files.insert(fileName).second, "duplicate file name: %s", fileName.c_str());
        ensuref(!users.count(fileName), "file name duplicates user name: %s", fileName.c_str());

        inf.readSpace();
        readPermission();
        inf.readSpace();
        string owner = readName("owner");
        ensuref(users.count(owner), "unknown owner: %s", owner.c_str());
        inf.readSpace();
        string ownedGroup = readName("owned_group");
        ensuref(groups.count(ownedGroup), "unknown owned group: %s", ownedGroup.c_str());
        inf.readEoln();
    }

    int queryCount = inf.readInt(1, kMaxQueries, "Q");
    inf.readEoln();

    for (int i = 0; i < queryCount; ++i) {
        string userName = readName("query_user_name");
        ensuref(users.count(userName), "unknown query user: %s", userName.c_str());
        inf.readSpace();
        string fileName = readName("query_file_name");
        ensuref(files.count(fileName), "unknown query file: %s", fileName.c_str());
        inf.readSpace();
        inf.readToken("R|W|X", "operation");
        inf.readEoln();
    }

    inf.readEof();
}
