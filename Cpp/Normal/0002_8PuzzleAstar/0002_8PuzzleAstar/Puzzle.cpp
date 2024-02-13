#include "Puzzle.h"
#if 0
#define IS_PRINT_LOG_PUZZLE true
#else
#define IS_PRINT_LOG_PUZZLE false
#endif

#define LOG(codes) if(IS_PRINT_LOG_PUZZLE){codes; }


void Puzzle::Run(int rowCnt, int colCnt)
{
	InitPuzzle(rowCnt, colCnt);
	View();
	Shuffle();
	View();
	AStar();
	Solve();
}

void Puzzle::AStar() {
	priority_queue<ANode, vector<ANode>, ANodeComp> openHeap;

	vector<ANode> closedNodeList;

	if (openHeap.empty())
	{
		//초기 상태 입력
		ANode sNode;
		sNode.puzzle = m_puzzle;
		sNode.f = 0;
		sNode.g = 0;
		sNode.h = Evaluate(sNode.puzzle);
		openHeap.push(sNode);
		sNode.pos;
	}

	//A* Search
	bool isFind = true;
	while (true)
	{
		if (openHeap.empty())
		{
			isFind = false;
			LOG(std::cout << "\nHeap empty!!!!!!!\n";)
				break;
		}
		else if (openHeap.top().h == 0)
		{
			//OpenHeap의 Top이 h=0일 경우 종료.
			break;
		}

		auto topNode = openHeap.top();
		closedNodeList.push_back(topNode);
		openHeap.pop();
		for (int moveIdx = 0; moveIdx < eMax; ++moveIdx) {
#if 0
			if (0 != topNode.moveList.size())
			{
				//직전 노드로 이동하지 않음
				//직전이 left이고 현재 right 이동?
				if ((eLEFT == topNode.moveList.back() && eRIGHT == moveIdx)
					|| (eRIGHT == topNode.moveList.back() && eLEFT == moveIdx)
					|| (eUP == topNode.moveList.back() && eDOWN == moveIdx)
					|| (eDOWN == topNode.moveList.back() && eUP == moveIdx)
					)
				{
					//continue;
				}
			}
#endif
			ANode tmpNode = topNode;
			if (Move(tmpNode.puzzle, moveIdx))
			{
				//s

				tmpNode.moveList.push_back(moveIdx);
				tmpNode.g++;
				tmpNode.h = Evaluate(tmpNode.puzzle);
				tmpNode.f = tmpNode.g + tmpNode.h;
				if (IsExistSamePuzzle(closedNodeList, tmpNode.puzzle, tmpNode.h))
				{
					continue;
				}
				openHeap.push(tmpNode);
				LOG(
					std::cout << "f,g,h:" << tmpNode.f << " " << tmpNode.g << " " << tmpNode.h << "\n";
					View(tmpNode.puzzle);
					)
			}
		}
	}

	if (isFind)
	{
		LOG(
			const auto topNode = openHeap.top();
		std::cout << "search success\n";
		std::cout << "f,g,h:" << topNode.f << " " << topNode.g << " " << topNode.h << "\n";
		View(topNode.puzzle);
		)
		m_hintList = openHeap.top().moveList;
	}
	else
	{
		LOG(std::cout << "search fail\n";)
	}
}


//현재 puzzle 상태에 대한 Heuristic Value 가져옴

bool Puzzle::Move(vector<vector<int>>& puzzle, const int moveIdx)
{
	bool isSuccess = false;
	int row_0 = -1;
	int col_0 = -1;
	GetZeroPos(row_0, col_0, puzzle);
	LOG(std::cout << "\n(" << row_0 << "," << col_0 << ")";)
#if 0
		switch (moveIdx)
		{
		case eLEFT:
		{
			if (col_0 - 1 > -1)
			{
				swap(puzzle[row_0][col_0 - 1], puzzle[row_0][col_0]);
				//col_0--;
				isSuccess = true;
			}
		}
		break;
		case eRIGHT:
			if (col_0 + 1 < GetColCnt())
			{
				swap(puzzle[row_0][col_0 + 1], puzzle[row_0][col_0]);
				//col_0++;
				isSuccess = true;
			}
			break;
		case eUP:
			if (row_0 - 1 > -1)
			{
				swap(puzzle[row_0 - 1][col_0], puzzle[row_0][col_0]);
				//row_0--;
				isSuccess = true;
			}
			break;
		case eDOWN:
			if (row_0 + 1 < GetRowCnt())
			{
				swap(puzzle[row_0 + 1][col_0], puzzle[row_0][col_0]);
				//row_0++;
				isSuccess = true;
			}
			break;
		default:
			break;
		}
#else
		int row_next = 0;
	int col_next = 0;
	switch (moveIdx)
	{
	case eLEFT:
		row_next = row_0;
		col_next = col_0 - 1;
		break;
	case eRIGHT:
		row_next = row_0;
		col_next = col_0 + 1;
		break;
	case eUP:
		row_next = row_0 - 1;
		col_next = col_0;
		break;
	case eDOWN:
		row_next = row_0 + 1;
		col_next = col_0;
		break;
	default:
		break;
	}
	if ((row_next < GetRowCnt() && row_next >= 0)
		&& (col_next < GetColCnt() && col_next >= 0))
	{
		swap(puzzle[row_next][col_next], puzzle[row_0][col_0]);
		isSuccess = true;
	}
#endif
	return isSuccess;
}

int Puzzle::Evaluate(vector<vector<int>>& puzzle)
{
	//각 위치별 맞게 돌아가기 위한 이동횟수로 평가함
	int ret = 0;
	for (int iRowIdx = 0; iRowIdx < GetRowCnt(); ++iRowIdx) {
		for (int iColIdx = 0; iColIdx < GetColCnt(); ++iColIdx) {
			int currNum = puzzle[iRowIdx][iColIdx];
			if (0 == currNum)
				currNum = GetRowCnt() * GetColCnt();
			currNum--;
			int iRowIdx_tmp = currNum / GetColCnt();
			int iColIdx_tmp = (currNum % GetColCnt());
			ret += abs(iRowIdx - iRowIdx_tmp) + abs(iColIdx - iColIdx_tmp);
		}
	}
	return ret;
}

bool Puzzle::IsExistSamePuzzle(const vector<ANode>& nodeList, const vector<vector<int>>& puzzleB, int h)
{
	bool isExist = false;
	for (auto curNode : nodeList)
	{
		if (curNode.h != h)
			continue;
		const auto& puzzleA = curNode.puzzle;
		bool isSame = true;
		for (int iRowIdx = 0; iRowIdx < m_rowCnt; ++iRowIdx) {
			for (int iColIdx = 0; iColIdx < m_colCnt; ++iColIdx)
			{
				if (puzzleA[iRowIdx][iColIdx] != puzzleB[iRowIdx][iColIdx])
				{
					isSame = false;
					break;
				}
			}
			if (false == isSame)
				break;
		}
		if (isSame)
		{
			isExist = true;
			break;
		}
	}
	return isExist;
}

bool Puzzle::IsExistSamePuzzle(const vector<ANode>& nodeList, const vector<vector<int>>& puzzleB)
{
	bool isExist = false;
	for (auto curNode : nodeList)
	{

		const auto& puzzleA = curNode.puzzle;
		bool isSame = true;
#if 0
		for (int iRowIdx = 0; iRowIdx < puzzleA.size() && isSame; ++iRowIdx) {
			for (int iColIdx = 0; iColIdx < puzzleA[rowIdx].size() && isSame; ++iColIdx)
			{
				isSame = isSame && (puzzleA[iRowIdx][iColIdx] == puzzleB[iRowIdx][iColIdx]);
			}
		}
#else
		for (int iRowIdx = 0; iRowIdx < GetRowCnt(); ++iRowIdx) {
			for (int iColIdx = 0; iColIdx < GetColCnt(); ++iColIdx)
			{
				if (puzzleA[iRowIdx][iColIdx] != puzzleB[iRowIdx][iColIdx])
				{
					isSame = false;
					break;
				}
			}
			if (false == isSame)
				break;
		}
#endif
		if (isSame)
		{
			isExist = true;
			break;
		}
	}
	return isExist;
}

void Puzzle::Solve() {
	int row_0;
	int col_0;
	GetZeroPos(row_0, col_0, m_puzzle);
	const int maxDepth = m_hintList.size();
	for (int i = 0; i < m_hintList.size(); ++i) {
		int row_next = row_0;
		int col_next = col_0;
		switch (m_hintList[i]) {
		case eLEFT:
			col_next--;
		break;
		case eRIGHT:
			col_next++;
			break;
		case eUP:
			row_next--;
			break;
		case eDOWN:
		default:
			row_next++;
			break;
		}
		swap(m_puzzle[row_next][col_next], m_puzzle[row_0][col_0]);
		row_0 = row_next;
		col_0 = col_next;
		std::cout << "status:" << i << "/" << maxDepth << "\n";
		View();
	}
}

void Puzzle::GetZeroPos(int & retRow, int & retCol, const vector<vector<int>>& puzzle) {
	retRow = retCol = 0;
	for (int iRowIdx = 0; iRowIdx < GetRowCnt(); ++iRowIdx)
	{
		for (int iColIdx = 0; iColIdx < GetColCnt(); ++iColIdx) {
			if (puzzle[iRowIdx][iColIdx] == 0)
			{
				retRow = iRowIdx;
				retCol = iColIdx;
				return;
			}
		}
	}
}

void Puzzle::GetZeroPos(Position_t & retPos, const vector<vector<int>>& puzzle)
{
	retPos.iRow = retPos.iCol = -1;
	for (int iRowIdx = 0; iRowIdx < GetRowCnt(); ++iRowIdx)
	{
		for (int iColIdx = 0; iColIdx < GetColCnt(); ++iColIdx) {
			if (puzzle[iRowIdx][iColIdx] == 0)
			{
				retPos.iRow = iRowIdx;
				retPos.iCol = iColIdx;
				return;
			}
		}
	}
}

bool Puzzle::CheckState()
{
	bool isInvalid = false;
	int stdIdx = 1;
	for (int iRowIdx = 0; iRowIdx < GetRowCnt() && isInvalid == false; ++iRowIdx)
	{
		for (int iColIdx = 0; iColIdx < GetColCnt(); ++iColIdx)
		{
			if (m_puzzle[iRowIdx][iColIdx] != stdIdx)
			{
				if (iRowIdx == GetRowCnt()- 1 && iColIdx == GetColCnt() - 1 && m_puzzle[iRowIdx][iColIdx] == 0)
				{
					continue;
				}
				else
				{
					isInvalid = true;
					break;
				}
			}
		}
	}
	return isInvalid;
}

int Puzzle::GetRandomMoveNumber()
{
	static mt19937 engine((unsigned int)time(NULL));                    // MT19937 난수 엔진
	static uniform_int_distribution<int> distribution(0, 1000);          // 생성 범위
	static auto generator = bind(distribution, engine);
	return generator() % eMax;
}

void Puzzle::Shuffle()
{
	LOG(std::cout << "shuffle\n"; )
	int row_0 = GetRowCnt() - 1;
	int col_0 = GetColCnt() - 1;

	const int shuffleCnt = 10 * GetRowCnt();
	LOG(std::cout << "\n";)
	for (int shuffleIdx = 0; shuffleIdx < shuffleCnt; ++shuffleIdx)
	{
		int getNum = GetRandomMoveNumber();
		LOG(std::cout << getNum << " ";)

#if 0
		switch (getNum)
		{
		case eLEFT:
		{
			if (col_0 - 1 > -1)
			{
				swap(m_puzzle[row_0][col_0 - 1], m_puzzle[row_0][col_0]);
				col_0--;
			}
		}
		break;
		case eRIGHT:
			if (col_0 + 1 < GetColCnt())
			{
				swap(m_puzzle[row_0][col_0 + 1], m_puzzle[row_0][col_0]);
				col_0++;
			}
			break;
		case eUP:
			if (row_0 - 1 > -1)
			{
				swap(m_puzzle[row_0 - 1][col_0], m_puzzle[row_0][col_0]);
				row_0--;
			}
			break;
		case eDOWN:
			if (row_0 + 1 < GetRowCnt())
			{
				swap(m_puzzle[row_0 + 1][col_0], m_puzzle[row_0][col_0]);
				row_0++;
			}
			break;
		}
#else
		int row_next = row_0;
		int col_next = col_0;
		switch (getNum)
		{
		case eLEFT:
			col_next--;
			if (!(col_next >= 0 && col_next < GetColCnt()))
				continue;
			break;
		case eRIGHT:
			col_next++;
			if (!(col_next >= 0 && col_next < GetColCnt()))
				continue;
			break;
		case eUP:
			row_next--;
			if (!(row_next >= 0 && row_next < GetRowCnt()))
				continue;
			break;
		case eDOWN:
			row_next++;
			if (!(row_next >= 0 && row_next < GetRowCnt()))
				continue;
			break;
		}
		swap(m_puzzle[row_next][col_next], m_puzzle[row_0][col_0]);
		row_0 = row_next;
		col_0 = col_next;
#endif
	}
	LOG(std::cout << "\n";)
}

void Puzzle::InitPuzzle(int rowCnt, int colCnt)
{
	m_rowCnt = rowCnt;
	m_colCnt = colCnt;
	m_puzzle.resize(m_rowCnt);
	int stdIdx = 1;
	for (int iRowIdx = 0; iRowIdx < m_rowCnt; ++iRowIdx)
	{
		m_puzzle[iRowIdx].resize(m_colCnt);
		for (int iColIdx = 0; iColIdx < m_colCnt; ++iColIdx) {
			if (iRowIdx + 1 == m_puzzle.size() && iColIdx + 1 == m_puzzle[iRowIdx].size())
			{
				m_puzzle[iRowIdx][iColIdx] = 0;
			}
			else
			{
				m_puzzle[iRowIdx][iColIdx] = stdIdx;
			}
			stdIdx++;
		}
	}
}

//출력 

void Puzzle::View()
{
	for (int iRowIdx = 0; iRowIdx < GetRowCnt(); ++iRowIdx) {
		for (int iColIdx = 0; iColIdx < GetColCnt(); ++iColIdx) {
			if (0 != m_puzzle[iRowIdx][iColIdx])
				std::cout << m_puzzle[iRowIdx][iColIdx] << " ";
			else
				std::cout << "  ";
		}
		std::cout << "\n";
	}
}

void Puzzle::View(const vector<vector<int>>& puzzle)
{
	for (int iRowIdx = 0; iRowIdx < GetRowCnt(); ++iRowIdx) {
		for (int iColIdx = 0; iColIdx < GetColCnt(); ++iColIdx) {
			if (0 != puzzle[iRowIdx][iColIdx])
				std::cout << puzzle[iRowIdx][iColIdx] << " ";
			else
				std::cout << "  ";
		}
		std::cout << "\n";
	}
}
