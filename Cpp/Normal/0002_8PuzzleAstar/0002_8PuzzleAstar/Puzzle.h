#pragma once
/*
@brief : Puzzle A* 알고리즘 풀이
@author: eslee
@date: 2024.02.08
@comment: 추상적으로 알고있는 A* 알고리즘에 대한 코드 정립 및 최적화에 대한 생각들을 구체화하고 정리하기 위해 생각나는대로 멋대로 구현해봄
*/
#include<iostream>
#include<vector>
#include<conio.h>
#include<queue>
#include<random>
#include<ctime>
#include<functional>
using namespace std;

class Puzzle {
public:
	enum EMove{
		eLEFT = 0,
		eRIGHT,
		eUP,
		eDOWN,
		eMax
	};
private:
	struct Position_t
	{
		int iRow;
		int iCol;
	};
	class ANode {
	public:
		vector<int> moveList;// 0 left, 1 right, 2 up, 3 down
		vector<vector<int>> puzzle;
		Position_t pos;
		int f;	// 총 비용
		int g;	// 지금까지 이동 비용
		int h;	// 목적지까지의 예상 비용
	};
	struct ANodeComp {
		//우선순위 큐 정렬 기준
		bool operator() (ANode& src1, ANode& src2)
		{
			if (src1.f == src2.f) {
				if (src1.g == src2.g) 
				{
					return src1.h > src2.h;
				}
				return src1.g > src2.g;
			}
			return src1.f > src2.f;
		}
	};

private:
	vector<vector<int>> m_puzzle;
	vector<int> m_hintList;
	int m_rowCnt;
	int m_colCnt;
public:
	void Run(int rowCnt, int colCnt);
	int GetRowCnt() { return m_rowCnt; }
	int GetColCnt() { return m_colCnt; }
private:
	//A* 관련 함수 

	//A* 알고리즘
	void AStar();	
	
	//puzzle의 원본에 대한 평가함수
	int Evaluate(vector<vector<int>>& puzzle);

	//동일한 puzzle이 존재하는지 확인
	bool IsExistSamePuzzle(const vector<ANode>& nodeList, const vector<vector<int>>& puzzleB, int h);
	bool IsExistSamePuzzle(const vector<ANode>& nodeList, const vector<vector<int>>& puzzleB);

	//이동
	bool Move(vector<vector<int>>& puzzle, const int moveIdx);

private:
	void Solve();

	void GetZeroPos(int& retRow, int& retCol, const vector<vector<int>>& puzzle);

	void GetZeroPos(Position_t& retPos, const vector<vector<int>>& puzzle);

	bool CheckState();

	//Puzzle 초기화 3x3 4x3 등등
	void InitPuzzle(int rowCnt, int colCnt);
	
	//출력 
	void View();

	void View(const vector<vector<int>>& puzzle);

private: //셔플 관련
	
	//퍼즐 섞기
	void Shuffle();
	int GetRandomMoveNumber();

private:
	static void SwapInt(int& src1, int& src2) {
		int tmp = src1;
		src1 = src2;
		src2 = tmp;
	}
};
