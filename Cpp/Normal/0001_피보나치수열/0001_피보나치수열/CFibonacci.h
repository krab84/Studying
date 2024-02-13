#pragma once

#include<vector>
class CFibonacci
{
public:
	using INT64 = long long;

public:
	CFibonacci() {

	}

	//�ݺ���
	INT64 GetResult1(int n)
	{
		if (n == 0)
			return 0;
		else if (n == 1 || n == 2)
			return 1;
		INT64 f1, f2, f3;
		f1 = 1;
		f2 = 1;
		for (int i = 3; i <= n; ++i)
		{
			f3 = f1 + f2;
			f1 = f2;
			f2 = f3;
		}
		return f3;
	}
	//�ݺ��� + ����
	INT64 GetResult2(int n)
	{
		// static std::vector<INT64> list = { 0,1,1 };
		if (list.size() <= n)
		{
			//current size ���� ����ä���
			int stIdx = list.size();
			for (int idx = stIdx; idx <= n; ++idx)
			{
				list.push_back(list[idx - 1] + list[idx - 2]);
			}
		}
		return list[n];
	}

	//���
	INT64 GetResult3(int n)
	{
		if (n == 0)
			return 0;
		else if (n == 1)
			return 1;
		return GetResult3(n - 1) + GetResult3(n - 2);
	}
	//��� + ����
	INT64 GetResult4(int n)
	{
		// static std::vector<INT64> list = { 0,1,1 };
		if (list.size() > n)
			return list[n];
		auto res = GetResult4(n - 1) + GetResult4(n - 2);
		list.push_back(res);
		return res;
	}
private:
	std::vector<INT64> list = { 0,1,1 };

};