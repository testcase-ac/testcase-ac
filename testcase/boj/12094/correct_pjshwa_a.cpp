#include<iostream>
#include<queue>
using namespace std;
 
int N;
int ans;
bool flag;
int board[21][21];
int threshold_value[11];
 
// 최소값을 구하는 함수
int findmaxvalue()
{
    int val = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] > val) val = board[i][j];
        }
    }
    return val;
}
 
// 배열의 값을 복사하는 함수
void copy_arr(int(*temp)[21], int(*board)[21])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            *(temp[i] + j) = *(board[i] + j);
        }
    }
    return;
}
 
// 4방향을 탐색하는 함수
void direct(int dir)
{
    queue<int> q; // board의 값을 넣을 queue
 
    if (dir == 0) // UP
    {
        for (int j = 0; j < N; j++)
        {
            for (int i = 0; i < N; i++)
            {
                if (board[i][j]) {
                    // 0 이 아니면 값을 queue에 넣고 board의 값을 0 으로 채운다.
                    q.push(board[i][j]);
                    board[i][j] = 0;
                }
            }
            int idx = 0;
            // 모든 값을 빼내면서
            while (!q.empty())
            {
                int val = q.front();
                q.pop();
 
                // board의 값이 0 이면 그 자리에 queue에 넣었던 값을 넣는다.
                if (!board[idx][j]) board[idx][j] = val;
                // board의 값이 queue의 값과 같다면 두 값을 합쳐 넣고 위치를 한 칸 이동시킨다.
                else if (board[idx][j] == val) board[idx++][j] += val;
                // board의 값이 queue의 값과 다르다면 다음 위치로 한 칸 이동시켜 값을 넣는다.
                else if (board[idx][j]) board[++idx][j] = val;
            }
        }
    }
    else if (dir == 1) // DOWN
    {
        for (int j = 0; j < N; j++)
        {
            for (int i = N - 1; i >= 0; i--)
            {
                if (board[i][j]) {
                    q.push(board[i][j]);
                    board[i][j] = 0;
                }
            }
            int idx = N - 1;
            while (!q.empty())
            {
                int val = q.front();
                q.pop();
 
                if (!board[idx][j]) board[idx][j] = val;
                else if (board[idx][j] == val) board[idx--][j] += val;
                else if (board[idx][j]) board[--idx][j] = val;
            }
        }
    }
    else if (dir == 2) // LEFT
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (board[i][j]) {
                    q.push(board[i][j]);
                    board[i][j] = 0;
                }
            }
            int idx = 0;
            while (!q.empty())
            {
                int val = q.front();
                q.pop();
 
                if (!board[i][idx]) board[i][idx] = val;
                else if (board[i][idx] == val) board[i][idx++] += val;
                else if (board[i][idx]) board[i][++idx] = val;
            }
        }
    }
    else if (dir == 3) // RIGHT
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = N - 1; j >= 0; j--)
            {
                if (board[i][j]) {
                    q.push(board[i][j]);
                    board[i][j] = 0;
                }
            }
            int idx = N - 1;
            while (!q.empty())
            {
                int val = q.front();
                q.pop();
 
                if (!board[i][idx]) board[i][idx] = val;
                else if (board[i][idx] == val) board[i][idx--] += val;
                else if (board[i][idx]) board[i][--idx] = val;
            }
        }
    }
}
bool compare_arr(int (*temp)[21], int (*board)[21])
{
    for (int j = 0; j < N; j++)
    {
        for (int k = 0; k < N; k++)
        {
            if (temp[j][k] != board[j][k]) return true;
        }
    }
    return false;
}
void dfs(int _cnt)
{
    int val = findmaxvalue();
 
    if (val <= threshold_value[_cnt]) return; // 현재 count에서 최대값 만드는게 불가능
 
    // count 10번째까지 오면
    // count마다 가져야할 최소값을 갱신한다.
    if (_cnt == 10) {
        ans = max(ans, val);
        int v = ans;
        while (_cnt > 0) {
            threshold_value[_cnt--] = v;
            v /= 2;
        }
        return;
    }
 
    int temp[21][21] = { 0 };
    copy_arr(temp, board);
 
    for (int i = 0; i < 4; i++)
    {
        direct(i);
 
        flag = compare_arr(temp, board);
 
        if (flag) {
            dfs(_cnt + 1);
            copy_arr(board, temp);
        }
    }
    return;
}
 
int main()
{
    int cnt = 0;
 
    cin >> N;
 
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> board[i][j];
        }
    }
 
    ans = findmaxvalue();
 
    dfs(cnt);
 
    cout << ans;
 
    return 0;
}

