#include <cstdio>

int main(){
	int n;
	scanf("%d", &n);

	for(int i = 0; i < n; i++){
int j;
scanf("%d", &j);
int nu = 0;
for(int k = 2; k <=j; k++){
	int temp = j;
while(temp%k==0){
	temp/=k;
	nu++;

}

}
printf("%d\n", nu);
}
}