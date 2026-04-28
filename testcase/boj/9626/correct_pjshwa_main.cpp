#include <cstdio>

int main(){
	int m, n, u, l, r, d;
	scanf("%d%d%d%d%d%d", &m, &n, &u, &l, &r, &d);
	char puzzle[m][n+1];

	for(int i = 0; i < m; i++){
		scanf("%s", puzzle[i]);
	}

	for(int i = 0; i < u + d + m; i++){
		if(i < u || i >= u + m){
			for(int j = 0; j < n + l + r; j++){
				if((i+j)%2) printf(".");
				else printf("#");
			}
			printf("\n");
		}
		else {
			for(int j = 0; j < l; j++){
				if((i+j)%2) printf(".");
				else printf("#");
			}
			printf("%s", puzzle[i-u]);
			for(int j = n + l; j < n + l + r; j++){
				if((i+j)%2) printf(".");
				else printf("#");
			}
			printf("\n");
		}	
	}
}