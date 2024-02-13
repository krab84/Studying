#pragma once
/*
@brief : Puzzle A* �˰��� Ǯ��
@author: eslee
@date: 2024.02.08
@comment: �߻������� �˰��ִ� A* �˰��� ���� �ڵ� ���� �� ����ȭ�� ���� �������� ��üȭ�ϰ� �����ϱ� ���� �������´�� �ڴ�� �����غ�
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
		int f;	// �� ���
		int g;	// ���ݱ��� �̵� ���
		int h;	// ������������ ���� ���
	};
	struct ANodeComp {
		//�켱���� ť ���� ����
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
	//A* ���� �Լ� 

	//A* �˰���
	void AStar();	
	
	//puzzle�� ������ ���� ���Լ�
	int Evaluate(vector<vector<int>>& puzzle);

	//������ puzzle�� �����ϴ��� Ȯ��
	bool IsExistSamePuzzle(const vector<ANode>& nodeList, const vector<vector<int>>& puzzleB, int h);
	bool IsExistSamePuzzle(const vector<ANode>& nodeList, const vector<vector<int>>& puzzleB);

	//�̵�
	bool Move(vector<vector<int>>& puzzle, const int moveIdx);

private:
	void Solve();

	void GetZeroPos(int& retRow, int& retCol, const vector<vector<int>>& puzzle);

	void GetZeroPos(Position_t& retPos, const vector<vector<int>>& puzzle);

	bool CheckState();

	//Puzzle �ʱ�ȭ 3x3 4x3 ���
	void InitPuzzle(int rowCnt, int colCnt);
	
	//��� 
	void View();

	void View(const vector<vector<int>>& puzzle);

private: //���� ����
	
	//���� ����
	void Shuffle();
	int GetRandomMoveNumber();

private:
	static void SwapInt(int& src1, int& src2) {
		int tmp = src1;
		src1 = src2;
		src2 = tmp;
	}
};
