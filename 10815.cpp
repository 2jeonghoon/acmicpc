#include <iostream>
#include <map>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    
    int N, M;

    std::cin >> N;

    std::map<int, int> num_card;

    for(int i = 0; i < N; i++) {
        int _n;
        std::cin >> _n;
        num_card.insert({_n, _n});
    }

    std::cin >> M;

    for(int i = 0; i < M; i++) {
        int _m;
        std::cin >> _m;
        
        if(num_card.find(_m) != num_card.end()) {
            std::cout << "1 ";
        } else {
            std::cout << "0 ";
        }
    }
}