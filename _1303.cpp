#include <cstdio>
#include <math.h>

int calcPower(char color);
int calcPowerRecursive(char color, int i, int j);
void init();

char soldiers[101][101];
bool check[101][101];
int power, width, height;

int main(){
	scanf("%d%d", &width, &height); //가로 세로

	for(int i=0; i<height; i++){
		for(int j=0; j<width; j++){
			scanf("%1s", &soldiers[i][j] );
		}
	}

	printf("%d %d", calcPower('W'),calcPower('B'));

}

int calcPower(char color){
	init();
	int res = 0;

	if(height == width && height == 1){
		if(color == soldiers[0][0]){
			return 1;
		}
		else{
			return 0;
		}
	}

	for(int i=0; i<height; i++){
		for(int j=0; j<width; j++){
			res += pow(calcPowerRecursive(color, i, j), 2.0);
			power = 0;
		}
	}

	return res;
}

int calcPowerRecursive(char color, int i, int j){
	if(i+1 < height && soldiers[i+1][j] == color && !check[i+1][j]){
		power++;
		check[i+1][j] = true;
		calcPowerRecursive(color, i+1, j);
	}
	if(i-1 >=0 && soldiers[i-1][j] == color && !check[i-1][j]){
		power++;
		check[i-1][j] = true;
		calcPowerRecursive(color, i-1, j);
	}
	if(j+1 < width && soldiers[i][j+1] == color && !check[i][j+1]){
		power++;
		check[i][j+1] = true;
		calcPowerRecursive(color, i, j+1);
	}

	if(j-1 >=0 && soldiers[i][j-1] == color && !check[i][j-1]){
		power++;
		check[i][j-1] = true;
		calcPowerRecursive(color, i, j-1);
	}

	return power;
}

void init(){
	for(int i=0; i<height; i++){
		for(int j=0; j<width; j++){
			check[i][j] = false;
		}
	}
	power = 0;
}

