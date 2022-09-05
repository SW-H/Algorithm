#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
  int count;
  vector<int> arr;
  cin >> count;
  int tmp;
  for(int i=0;i<count;i++){
    cin >> tmp;
    arr.push_back(tmp);
  }
  cout << ((*min_element(arr.begin(), arr.end())) * (*max_element(arr.begin(), arr.end())));
}
