#include <cstdio>

int main(){
	int n;
	scanf("%d", &n);
	char mirror_image[n][101];
	for(int i = 0; i < n; i++){
		scanf("%s", mirror_image[i]);
	}
	int k;
	scanf("%d", &k);
	switch(k){
		case 1:
			for(int i = 0; i < n; i++){
				printf("%s\n", mirror_image[i]);
			}
			break;
		case 2:
			for(int i = 0; i < n; i++){
				for(int j = n-1; j >= 0; j--){
					printf("%c", mirror_image[i][j]);
				}
				printf("\n");
			}
			break;
		default:
			for(int i = n-1; i >= 0; i--){
				printf("%s\n", mirror_image[i]);
			}
	}
}