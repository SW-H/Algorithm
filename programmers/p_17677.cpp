#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <cctype> //isdigit
using namespace std;
int solution(string str1, string str2);
int main(){
    solution("FRANCE", "French");
}
int solution(string str1, string str2) {
    vector<string> strUnion;
    set<string> intersection;
    set<string>::iterator it = intersection.begin();
    int i,j=1,k,l=1;
    string target1, target2;
    
    for(i = 0; i<str1.length() && j < str1.length() ;i++){
        j = i+1;
        for(k = 0; k<str2.length() && l < str2.length(); k++){
            l = k+1;
            while(!isalpha(str1[i])) i++;
            while(!isalpha(str1[j])) j++;
            while(!isalpha(str2[k])) k++;
            while(!isalpha(str2[l])) l++;
            str1[i] = tolower(str1[i]);
            str1[j] = tolower(str1[j]);
            str2[k] = tolower(str2[k]);
            str2[l] = tolower(str2[l]);
            
            target1 = str1[i]+str1[j];
            target2 = str2[k]+str2[l];
            cout << target1 << " " << target2 << "\n";
            if(target1.compare(target2) == 0){
                strUnion.push_back(target1);
                intersection.insert(it, target1);
            }
            l++;
        }
        j++;
    }
    for(int i=0;i<strUnion.size();i++){
        cout << strUnion[i] << " ";
    }
   return 0;
}

//교집합크기/합집합크기
// 모두 공집합 =>1