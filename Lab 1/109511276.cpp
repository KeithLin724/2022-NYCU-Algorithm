/*
Title:Algorithm DP Lab 1
Written By 練鈞揚
This is a code for the algorithm Lab 1
using -std=c++11 version
Date: 5/11/2022
*/

#pragma GCC optimize(3,"Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include <deque>
#include <fstream>
using namespace std;

#define ll long long 

long N, A, B, X = 0;
ll total = 0, fTotal = 0, R = 0;
size_t dayIndex = 0, fIndex = 0, i = 1, j;

int main(int argc, char* argv[]) {
    ifstream inFile(argv[1]);
    ofstream outFile(argv[2]);
    if (!inFile.is_open()) { // cant open file 
        exit(-1);
    }
    if (!outFile.is_open()) {
        exit(-2);
    }

    inFile >> N >> A >> B;

    ll* dp = (ll*)calloc(static_cast<size_t>(N) + 1, sizeof(ll)), * index = (ll*)calloc(static_cast<size_t>(N) + 1, sizeof(ll));

    deque<ll> save;

    for (; i <= static_cast<size_t>(N); i++) {
        inFile >> R;

        total = dp[0] - R;
        fIndex = 0;
        fTotal = (-9223372036854775807 - 1);

        for (j = i; j > 0; j--) {
            total = max(total, dp[j - 1] - R);

            dp[j] = dp[j - 1] + A - j * j * B;
            if (dp[j] > fTotal) {
                fTotal = dp[j];
                fIndex = j;
            }

        }

        dp[0] = total;
        if (dp[0] > fTotal) {
            fTotal = dp[0];
            fIndex = 0;
        }
        index[i] = fIndex;
    }
    inFile.close();
    outFile << dp[fIndex] << '\n';

    dayIndex = N;
    while (dayIndex > 1) {
        if (index[dayIndex] == 0) {
            save.emplace_front(0);
            dayIndex--;
            continue;
        }
        save.insert(save.begin(), index[dayIndex], 1);
        if (save.size() == N) {
            break;
        }
        save.emplace_front(0);
        dayIndex -= (index[dayIndex] + 1);
    }

    if (save.size() < N) {
        save.emplace_front(index[1]);
    }

    // add const 
    for (const auto& elm : save) {
        outFile << elm << ' ';
    }

    outFile.close();

    free(dp);
    free(index);

    return 0;
}


