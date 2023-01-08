#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")

/*
Title:TSP problem
Written By 練鈞揚
This is a code for TSP
dfs + greedy + 2-opt
using -std=c++11 version
Date: 31/12/2022
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <numeric>
#include <sstream>
#include <algorithm>
using namespace std;

class Solution {
public:
	static constexpr auto INIT_NUMBER = std::numeric_limits<std::int32_t>::max();

private:
	// show the graph can not run
	inline static void __can_not_run(const std::string& fileNameOut) {
		std::ofstream outFile(fileNameOut);
		outFile << "No";
		outFile.close();
	}

	inline static void __can_run(const std::string& fileNameOut, const std::vector<std::int32_t>& path, const std::int32_t& cost) {
		std::ofstream outFile(fileNameOut);
		outFile << "Yes\n";
		outFile << "Path: ";

		for (auto itr = path.cbegin(); itr != path.cend(); itr++) {
			outFile << *itr << (std::next(itr) != path.cend() ? ' ' : '\n');
		}

		outFile << "Cost: " << cost;

		outFile.close();
	}

	// this is a function to sum up the cost 
	inline std::int32_t __sum_path_cost(const std::vector<std::int32_t>& pathVec) const {
		std::int32_t totalLength = {};

		for (auto itr = pathVec.cbegin(); itr != pathVec.cend(); itr++) {
			if (std::next(itr) == pathVec.end()) {
				break;
			}

			auto tmpLen = this->_adjMatrixGraph[*itr][*std::next(itr)];
			if (tmpLen == Solution::INIT_NUMBER) {
				throw std::invalid_argument("is not connect graph");
			}
			totalLength += tmpLen;
		}

		return totalLength;
	}

	// using dfs - greedy algorithm 
	// end the dfs when the last node have connect to the start node // edge is n 
	inline std::vector <std::int32_t> __dfs_find_path_greedy(const std::int32_t& startPoint, int32_t& backCntLim, int32_t& backCnt) const {
		// add the visit boolean // size is the node number // init false 
		std::deque<bool> visit(this->_nodeNumber, false);
		// this is a array to save 
		std::vector<std::int32_t> adjListCnt(this->_nodeNumber, 0);

		bool isFinish = false;

		// come from node
		std::int32_t fatherNode = -1;

		// this is a stack for save the // start in 0 // can startPoint
		std::vector<std::int32_t> _stk(1, startPoint);

		while (isFinish == false) {
			auto topNode = _stk.back();
			visit[topNode] = true;

			// 
			try {
				auto nextPoint = this->_adjListGraph[topNode].at(adjListCnt[topNode]++);

				// find it // check is is visit all 
				if (nextPoint == fatherNode || (visit[nextPoint] && nextPoint != startPoint)) {
					continue;
				}

				// check the node number // because all point in the stack 
				if (_stk.size() == this->_nodeNumber) {

					isFinish = (nextPoint == startPoint);

					if (isFinish) {
						_stk.push_back(nextPoint);
						continue;
					}

					// if the next point is not start point 
					// and find the adj list have the start point 
					if (this->_adjMatrixGraph[topNode][startPoint] == Solution::INIT_NUMBER) {
						// not find 
						return {};
					}

					_stk.push_back(startPoint);
				}

				// not visit 
				else if (visit[nextPoint] == false) {
					fatherNode = topNode;
					_stk.push_back(nextPoint);
				}
			}
			catch (const std::exception& e) {
				// over the topNode 
				adjListCnt[topNode] = 0;
				visit[topNode] = false;
				// can not find it 
				if (topNode == startPoint) {
					return {};
				}
				_stk.pop_back();

				backCnt++;

				if (backCnt > backCntLim) {
					return { Solution::INIT_NUMBER };
				}

				fatherNode = (_stk.size() >= 2 ? *std::next(_stk.rbegin()) : -1);
			}
		}
		if (backCntLim == Solution::INIT_NUMBER) {
			backCntLim = backCnt;
		}
		return _stk;
	}


	// using the 2-opt to close the answer 
	// https://www.youtube.com/watch?v=UAEjUk0Zf90
	inline std::vector<std::int32_t> __two_opt() const {
		std::vector<std::int32_t> tour = this->_path;
		tour.pop_back();
		auto _sz = tour.size();

		bool improve = true;
		while (improve) {
			improve = false;
			for (int32_t i = 0; i < tour.size(); i++) {
				for (int32_t j = i + 1; j < tour.size(); j++) {
					// old edge 
					//tour[i], tour[i + 1]; 
					//tour[j], tour[j + 1];

					auto oldCur1 = this->_adjMatrixGraph[tour[i]][tour[i + 1]];
					auto oldCur2 = this->_adjMatrixGraph[tour[j]][tour[(j + 1) % _sz]];
					auto oldLen = oldCur1 + oldCur2;

					//tour[i] , tour[j]
					// dis {tour[i+1] , tour[j +1] }
					auto newCur1 = this->_adjMatrixGraph[tour[i]][tour[j]];
					auto newCur2 = this->_adjMatrixGraph[tour[i + 1]][tour[(j + 1) % _sz]];
					// if dis == INIT_NUMBER // can not
					if (newCur1 == Solution::INIT_NUMBER || newCur2 == Solution::INIT_NUMBER) {
						continue;
					}
					auto newLen = newCur1 + newCur2;

					// compare this two edge weight 
					if (newLen < oldLen) {
						//swap it  
						auto headBegin = tour.begin();

						std::reverse(std::next(headBegin, i + 1), std::next(headBegin, j + 1));
						improve = true;
					}
				}
			}
		}

		auto frontElm = tour.front();
		tour.push_back(frontElm);
		return tour;
	}
public:
	Solution() = default;
	~Solution() = default;

	inline void read_file(const std::string& fileNameIn) {
		ifstream inFile;
		inFile.exceptions(std::ios::badbit | std::ios::eofbit | std::ios::failbit);
		std::stringstream ssIn;

		try {
			inFile.open(fileNameIn); ssIn << inFile.rdbuf(); inFile.close();
		}
		catch (const std::exception& e) {
			inFile.close();
			throw e;
		}

		ssIn >> this->_nodeNumber >> this->_edgeNumber;

		// init the array 
		this->_adjMatrixGraph.assign(this->_nodeNumber, std::vector<std::int32_t>(this->_nodeNumber, INIT_NUMBER));
		this->_nodeDegree.assign(this->_nodeNumber, 0);

		this->_adjListGraph.assign(this->_nodeNumber, {});
		this->_pathCost = Solution::INIT_NUMBER;

		std::int32_t a, b, length;
		while (ssIn >> a >> b >> length) {
			// Matrix 
			this->_adjMatrixGraph[a][b] = length;
			this->_adjMatrixGraph[b][a] = length;

			// List 
			this->_adjListGraph[a].push_back(b);
			this->_adjListGraph[b].push_back(a);

			// cnt the node degree
			this->_nodeDegree[a]++;
			this->_nodeDegree[b]++;
		}

		// copy the matrix graph for the sorting 
		auto&& tmp = this->_adjMatrixGraph;

		// sorting the list and easily to find the answer 
		for (size_t i = 0; i < this->_adjListGraph.size(); i++) {
			std::sort(this->_adjListGraph[i].begin(), this->_adjListGraph[i].end(),
				[&tmp, &i](const std::int32_t& a, const std::int32_t& b) {
					return tmp[i][a] < tmp[i][b];
				}
			);
		}
	}

	void run_solution(const std::string& fileNameOut) {
		// edge number less than node number 
		if (this->_edgeNumber < this->_nodeNumber) {
			Solution::__can_not_run(fileNameOut);
			return;
		}

		// check is it connect if all degree >= 2 
		bool isItConnect = std::all_of(this->_nodeDegree.begin(), this->_nodeDegree.end(),
			[](const std::int32_t& a) {
				return a >= 2;
			}
		);

		if (isItConnect == false) {
			Solution::__can_not_run(fileNameOut);
			return;
		}

		std::int32_t baseCnt = Solution::INIT_NUMBER, backCnt = 0;
		for (std::int32_t i = this->_adjListGraph.size() - 1; i >= 0; i--) {
			auto res = this->__dfs_find_path_greedy(i, baseCnt, backCnt);
			// not find the path
			if (res.empty()) {
				Solution::__can_not_run(fileNameOut);
				return;
			}
			// need skip
			if (res.front() == Solution::INIT_NUMBER) {
				continue;
			}
			// find the path cost
			auto cost = this->__sum_path_cost(res);
			if (cost < this->_pathCost) {
				this->_pathCost = cost;
				this->_path = res;
			}

		}

		auto newRes = this->__two_opt();
		auto cost = this->__sum_path_cost(newRes);

		if (cost < this->_pathCost) {
			this->_pathCost = cost;
			this->_path = newRes;
		}

		// testing find the path //! Need add  if can not find handle 
		Solution::__can_run(fileNameOut, this->_path, this->_pathCost);
	}

private:

	std::int32_t _nodeNumber, _edgeNumber;
	std::vector<std::vector<std::int32_t>> _adjMatrixGraph;
	std::vector<std::vector<std::int32_t>> _adjListGraph;

	std::vector<std::int32_t> _path, _nodeDegree;
	std::int32_t _pathCost;

} solutionTools;


int main(int argc, char* argv[]) {

	try {
		solutionTools.read_file(argv[1]);
		solutionTools.run_solution(argv[2]);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		exit(-1);
	}

	return 0;
}
