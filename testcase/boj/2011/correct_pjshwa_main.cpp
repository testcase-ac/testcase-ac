#include <cstdio>
#include <cstring>

int dp[5001];
int stringLength = 0;
char password[5001];
const int mod = 1e6;

int caseNumber(int index){
    if(dp[index] == -1) {
        if (index == stringLength - 1) {
            dp[index] = password[index] >= '1' && password[index] <= '9' ? 1 : 0;
        }
        else if (index == stringLength) dp[index] = 1;
        else {
            if (password[index + 1] == '0') {
                if (password[index] == '1' || password[index] == '2') {
                    dp[index] = caseNumber(index + 2);
                }
                else dp[index] = 0;
            }
            else {
                if (password[index] >= '1' && password[index] <= '9') {
                    dp[index] = caseNumber(index + 1);

                    if (password[index] == '1' || (password[index] == '2' && password[index + 1] <= '6')) {
                        dp[index] += caseNumber(index + 2);
                    }
                }
                else dp[index] = 0;
            }
        }
    }
    return dp[index] % mod;
}

int main(){
    scanf("%s", password);
    stringLength = strlen(password);
    for(int i = 0; i < stringLength + 1; i++){
        dp[i] = -1; // dp init
    }
    printf("%d", caseNumber(0));
}
