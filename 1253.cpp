#include <iostream>
#include <map>

using namespace std;

int res;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int N;
    cin >> N;

    map<int, int> num_map;

    for(int i = 0; i < N; i++) {
        int input;
        cin >> input;
        //cout << input;
        auto it = num_map.find(input);

        if (it != num_map.end()) {
            // cout << "key:" << it->first << "value:" << it->second << "\n";
            num_map[it->first] += 1;
        } else {
            num_map[input] = 1;
            // cout << num_map[input] << "\n";
        }
    }

    auto it = num_map.begin();

    for(auto it = num_map.begin(); it != num_map.end(); it++) {
        // cout << "iterate " << it->first << "\n";

        for (auto target_it = num_map.begin(); target_it != num_map.end(); target_it++) {
            int target_value = it->first - target_it->first;

            if(it == target_it) {
                if(target_it->second < 2) {
                    continue;
                }
            }

            // cout << "target_value " << target_value << "\n";

            auto find_it = num_map.find(target_value);

            if(target_it == find_it) {
                if(find_it->second < 2) {
                    continue;
                } else if(find_it == it) {
                    if(find_it->second < 3) {
                        continue;
                    }
                }
            }

            if(find_it != num_map.end()) {
                // cout << "find it " << find_it->first << "\n";
                if(find_it == target_it) {
                    // cout << "find it equal target it\n";
                    if(target_it == it) {
                        //cout << "target it == it\n";
                        if(find_it->second > 2) {
                            res += it->second;
                            break;
                        }
                    } else if(find_it->second > 1) {
                        res += it->second;
                        //cout << "and sumation res" << res << "\n";
                        break;
                    }
                } else {
                    if(it == find_it) {
                        if(find_it->second > 1) {
                            res += it->second;
                            //cout << "sumation res " << res << "\n";
                            break;
                        }
                    } else {
                        res += it->second;
                        //cout << "sumation res " << res << "\n";
                        break;
                    }
                }
            }
        }
    }

    cout << res;
}