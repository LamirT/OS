#include <fstream>
#include <stdlib.h>
#include <iostream>

int func(char);

int main() {

    const int p = 5;
    const int r = 3;
    
    char ch = 0;
    char input;
    
    int results;
    int alloc[5][3];
    int max[5][3];
    int avil[3];

    std::fstream in;
    in.open("banker.txt");

    if(in.fail()) {
        std::cerr << "Failed to open file" << std::endl;
    exit(1);
    }

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 3; j++){
            in.get(input);
            results = func(input);
            alloc[i][j] = results;
        }
        in.get(ch);
    }

    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 3; j++) {
            in.get(input);
            results = func(input);
            max[i][j] = results;
        }
        in.get(ch);
    }

    for(int i = 0; i < 3 ; i++) {
        in.get(input);
        results = func(input);
        avil[i] = results;
    }

    int f[p], ans[p], ind = 0;
    for(int k = 0; k < p; k++) {
        f[k] = 0;
    }

    int need[p][r];
    for(int i = 0; i < p; i++) {
        for(int j = 0; j < r; j++){
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
        int y = 0;
        for(int k = 0; k < 5; k++) {
            for(int i = 0; i < p; i++) {
                if(f[i] == 0) {
                    int flag = 0;
                    for (int j = 0; j < r; j++) {
                        if(need[i][j] > avil[j]) {
                            flag = 1;
                            break;
                        }
                    }
                    if(flag == 0) {
                        ans[ind++] = i;
                        for(y = 0; y < r; y++) {
                            avil[y] += alloc[i][y];
                        }
                        f[i] = 1;
                    }
                }
            }
        }

        int safe = 1;
        for(int i = 0; i < p; i++) {
            if(f[i] == 0) {
                safe = 0;
                std::cout << "The system is NOT in a safe state" << std::endl;
                break;
            }
        }

        if(safe == 1) {
            std::cout << "The system is in a safe state. Safe sequence: " << std::endl;
            for(int i = 0; i < p -1; i++) {
                std::cout << " P" << ans[i] << " -> ";
            }
                std::cout << " P" << ans[p - 1] << std::endl;
        }

        return 0;
}

int func(char ch) {
    return int(ch) - 48;
}