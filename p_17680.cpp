#include <algorithm> // find, min_element
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int solution(int cacheSize, vector<string> cities);
int main(){
    vector<string> cities;
    cities.push_back("Jeju"); 
    cities.push_back("Pangyo");
    cities.push_back("Seoul" );
    cities.push_back("NewYork");
    cities.push_back("LA");
    cities.push_back("Jeju");
    cities.push_back("Pangyo");
    cities.push_back("Seoul" );
    cities.push_back("NewYork" );
    cities.push_back("LA");
    cout << solution(3, cities);
}
int solution(int cacheSize, vector<string> cities) {
    vector<string> cache;
    int duration = 0;
    vector<int> used(cacheSize);
    int cachePosition;

    for (int i = 0; i < cities.size(); i++) {
        
        
        // for(int j =0;j<cache.size();j++){
        //     cout << cache[i] << " ";
        // }
        // cout << "\n";


        if (cache.empty()) {
            cache.push_back(cities[i]);
            used[cacheSize-1] = i;
            duration += 5;
        } else {
            cachePosition = find(cache.begin(), cache.end(), cities[i]) - cache.begin();

            if (cachePosition != cache.size()) { // hit
                // used[cachePosition] = i;
                used.at(cachePosition) = i;
                duration += 1;
            } else if (cache.size() == cache.size()) { // miss, full
                cachePosition =
                    min_element(used.begin(), used.end()) - used.begin();
                // cache[cachePosition] = cities[i];
                // used[cachePosition] = i;
                cache.at(cachePosition) = cities.at(i);
                used.at(cachePosition) = i;
                duration += 5;

            } else {
                cache.push_back(cities[i]);
                duration += 5;
                // used[cacheSize-1] = i;
                used.at(cacheSize - 1) = i;
            }
        }
    }
    return duration;
}