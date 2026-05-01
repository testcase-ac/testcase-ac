#include <iostream>
#include <algorithm>
using namespace std;
int T, N;
string answer, S[151], buffer[151];

string reverseString(string str)
{
    reverse(str.begin(), str.end());
    return str;
}

bool dfs(int index)
{
    if (answer.size() == N)
    {
        return true;
    }

    const string &curS = S[answer.size()];

    if (answer.empty() || buffer[index - 1] <= curS)
    {
        buffer[index] = curS;
        answer.push_back('0');
        if (dfs(index + 1))
        {
            return true;
        }
        answer.pop_back();
    }

    string reverseS = reverseString(curS);
    if (answer.empty() || buffer[index - 1] <= reverseS)
    {
        buffer[index] = reverseS;
        answer.push_back('1');
        if (dfs(index + 1))
        {
            return true;
        }
        answer.pop_back();
    }

    return false;
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> T;
    while (T--)
    {
        answer.clear();

        cin >> N;
        for (int i = 0; i < N; ++i)
        {
            cin >> S[i];
        }

        dfs(0);
        cout << answer << "\n";
    }
    return 0;
}
