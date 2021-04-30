#include <cstdio>

int calcPower(char color);
void calcPowerRecursive(char color, int i, int j);
void init();

char soldiers[101][101];
bool check[101][101];
int power, width, height;

int main(){
  scanf("%d%d", &width, &height);

  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      scanf("%1s", &soldiers[i][j] );
    }
  }
  init();
  /*
     printf("----------\n");
     for(int i=0; i<height; i++){
     for(int j=0; j<width; j++){
     printf("%c", soldiers[i][j]);
     }
     printf("\n");
     }
     */
  printf("%d %d", calcPower('W'), calcPower('B'));
}

void init(){
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      check[i][j] = false;
    }
  }
  power = 0;
}

int calcPower(char color){
  init();
  for(int i=0; i<height; i++){
    for(int j=0; j<width; j++){
      calcPowerRecursive(color, i, j);
    }
  }
  return power*power;
}

void calcPowerRecursive(char color, int i, int j){
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
}
