#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

struct User {
    string name;
    vector<string> explicitGroups;
    set<string> groups;
};

struct File {
    string name;
    string permission;
    string owner;
    string group;
};

string numberedName(char prefix, int index) {
    return string(1, prefix) + to_string(index);
}

int choosePermissionDigit() {
    static const vector<int> digits = {0, 1, 4, 5, 6, 7};
    return rnd.any(digits);
}

string choosePermission() {
    vector<string> permissions;
    for (int owner = 0; owner < 8; ++owner) {
        if (owner == 2 || owner == 3) {
            continue;
        }
        for (int group = 0; group < 8; ++group) {
            if (group == 2 || group == 3 || (owner | group) != owner) {
                continue;
            }
            for (int other = 0; other < 8; ++other) {
                if (other == 2 || other == 3 || (group | other) != group) {
                    continue;
                }
                permissions.push_back(to_string(owner) + to_string(group) + to_string(other));
            }
        }
    }
    return rnd.any(permissions);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int userCount = rnd.next(1, mode == 3 ? 10 : 6);
    int fileCount = rnd.next(1, mode == 3 ? 8 : 5);

    vector<User> users;
    for (int i = 0; i < userCount; ++i) {
        User user;
        user.name = numberedName('u', i);
        user.groups.insert(user.name);
        users.push_back(user);
    }

    int extraGroupCount = rnd.next(0, mode == 0 ? 2 : 8);
    vector<string> extraGroups;
    for (int i = 0; i < extraGroupCount; ++i) {
        extraGroups.push_back(numberedName('g', i));
    }

    for (User& user : users) {
        vector<string> candidates = extraGroups;
        if (mode == 2 && userCount > 1) {
            candidates.push_back(rnd.any(users).name);
        }
        shuffle(candidates.begin(), candidates.end());

        int groupCount = candidates.empty() ? 0 : rnd.next(0, min(10, (int)candidates.size()));
        set<string> seen;
        for (const string& group : candidates) {
            if ((int)user.explicitGroups.size() == groupCount) {
                break;
            }
            if (seen.insert(group).second) {
                user.explicitGroups.push_back(group);
                user.groups.insert(group);
            }
        }
    }

    set<string> knownGroupSet;
    for (const User& user : users) {
        knownGroupSet.insert(user.name);
        knownGroupSet.insert(user.explicitGroups.begin(), user.explicitGroups.end());
    }
    vector<string> groupPool(knownGroupSet.begin(), knownGroupSet.end());

    vector<File> files;
    for (int i = 0; i < fileCount; ++i) {
        File file;
        file.name = numberedName('f', i);
        file.permission = mode == 1 ? string(3, char('0' + choosePermissionDigit()))
                                    : choosePermission();
        file.owner = rnd.any(users).name;
        file.group = rnd.any(groupPool);
        files.push_back(file);
    }

    vector<string> operations = {"R", "W", "X"};
    vector<vector<string>> queries;
    for (const File& file : files) {
        queries.push_back({file.owner, file.name, rnd.any(operations)});

        vector<string> groupUsers;
        vector<string> otherUsers;
        for (const User& user : users) {
            if (user.name == file.owner) {
                continue;
            }
            if (user.groups.count(file.group)) {
                groupUsers.push_back(user.name);
            } else {
                otherUsers.push_back(user.name);
            }
        }
        if (!groupUsers.empty()) {
            queries.push_back({rnd.any(groupUsers), file.name, rnd.any(operations)});
        }
        if (!otherUsers.empty()) {
            queries.push_back({rnd.any(otherUsers), file.name, rnd.any(operations)});
        }
    }

    int randomQueryCount = rnd.next(1, mode == 3 ? 12 : 6);
    for (int i = 0; i < randomQueryCount; ++i) {
        queries.push_back({rnd.any(users).name, rnd.any(files).name, rnd.any(operations)});
    }
    shuffle(queries.begin(), queries.end());

    println(userCount, fileCount);
    for (const User& user : users) {
        if (user.explicitGroups.empty()) {
            println(user.name);
            continue;
        }
        printf("%s ", user.name.c_str());
        for (int i = 0; i < (int)user.explicitGroups.size(); ++i) {
            if (i > 0) {
                printf(",");
            }
            printf("%s", user.explicitGroups[i].c_str());
        }
        printf("\n");
    }

    for (const File& file : files) {
        println(file.name, file.permission, file.owner, file.group);
    }

    println((int)queries.size());
    for (const vector<string>& query : queries) {
        println(query);
    }

    return 0;
}
