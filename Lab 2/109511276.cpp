#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")

/*
Title:Algorithm Lab 2 Graph MST
Written By 練鈞揚
This is a code for the Algorithm Lab 2 MST
using -std=c++11
Date: 5/12/2022
*/

#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;
namespace tools {

    int rootNumber = 0,
        res = 0; // mini cost 

    vector<int> ds; // disjoin point 

    vector<array<int, 3>> arr; // using for the distance 
    vector<pair<int, int>> points, addEdgesRes;

    // https://yuihuang.com/union-find-algorithm/
    inline int find(int i) {
        return (ds[i] < 0 ? i : ds[i] = find(ds[i]));
    }

}

int main(int argc, char* argv[]) {
    ifstream inFile(argv[1]);
    if (!inFile.is_open()) {
        return -1;
    }
    int a, b;
    inFile >> tools::rootNumber;

    tools::ds.assign(tools::rootNumber, -1);
    tools::points.assign(tools::rootNumber, { 0,0 });

    for (auto& pointElm : tools::points) {
        inFile >> a >> b;
        pointElm = { a, b };
    }

    // init edges 
    while (inFile >> a >> b) {
        int i = tools::find(a), j = tools::find(b);

        tools::ds[i] += tools::ds[j];
        tools::ds[j] = i;
        if (tools::ds[i] == -tools::rootNumber) {
            ofstream outFile(argv[2]);

            outFile << tools::res << '\n';
            for (const auto& elm : tools::addEdgesRes) {
                outFile << elm.first << ' ' << elm.second << '\n';
            }

            outFile.close();
            return 0;
        }
    }
    inFile.close();

    for (int x = 0; x < tools::rootNumber; x++) {
        for (int y = x + 1; y < tools::rootNumber; y++) {
            // find the point is in 
            tools::arr.push_back(
                { abs(tools::points[x].first - tools::points[y].first)
                + abs(tools::points[x].second - tools::points[y].second),
                x ,
                y }
            );
        }
    }

    // make heap;
    make_heap(tools::arr.begin(), tools::arr.end(), greater<array<int, 3>>());

    while (!tools::arr.empty()) {
        pop_heap(tools::arr.begin(), tools::arr.end(), greater<array<int, 3>>());
        array<int, 3> tmp = tools::arr.back();
        tools::arr.pop_back();

        int dist = tmp[0], i = tools::find(tmp[1]), j = tools::find(tmp[2]);

        if (i != j) { // add 
            tools::res += dist;
            tools::ds[i] += tools::ds[j];
            tools::ds[j] = i;
            tools::addEdgesRes.emplace_back(tmp[1], tmp[2]);
            if (tools::ds[i] == -tools::rootNumber) {
                break;
            }
        }
    }
    // output 
    ofstream outFile(argv[2]);

    outFile << tools::res << '\n';
    for (const auto& elm : tools::addEdgesRes) {
        outFile << elm.first << ' ' << elm.second << '\n';
    }

    outFile.close();

    return 0;

}