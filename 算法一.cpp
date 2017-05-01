#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <windows.h>
using namespace std;
template<class T>
struct matrix
{
	const int m, n;
	T *ip;
	matrix(int mm, int nn): m(mm), n(nn)
	{
		ip = new T[m * n];
	}
	T *operator[](int row)
	{
		return ip + row * n;
	}
	~matrix()
	{
		delete []ip;
	}
};
struct paircoor
{
	int row;
	int column;
};
struct tmpstr
{
	int no;
	int p;
	bool operator<(const tmpstr &t) const
	{
		if (p < t.p)
			return true;
		return false;
	}
};
int findrow(const vector<paircoor> &m, int i)
{
	for (int k = 0; k < m.size(); k++)
		if (m[k].row == i)
			return k;
	return -1;
}
bool findcolumn(const vector<paircoor> &m, int j)
{
	for (int k = 0; k < m.size(); k++)
		if (m[k].column == j)
			return true;
	return false;
}
int main()
{
	LARGE_INTEGER time_begin, time_end, time_freq;
	QueryPerformanceFrequency(&time_freq);
	QueryPerformanceCounter(&time_begin);
	ifstream in("C:\\precious_data\\questions\\size_25_25.eug");
	ofstream out("C:\\precious_data\\answer1\\size_25_25.msk");
	int m, n, total_money, max_seller;
	int process_count = 0;
	while (in >> m >> n >> total_money >> max_seller)
	{
		matrix<tmpstr> mat(n, m);
		matrix<int> initialmat(n, m);
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
			{
				in >> mat[j][i].p;
				initialmat[j][i] = mat[j][i].p;
				mat[j][i].no = i;
			}
		for (int j = 0; j < n; j++)
			sort(mat[j], mat[j] + m);
		vector<paircoor> max_record;
		int max_item = 0, total_cost = 0, amount_seller = 0;
		while (amount_seller < max_seller)
		{
			vector<int> max_row;
			int max_column, add_item = 0, add_cost = 0;
			for (int j = 0; j < n; j++)
				if (!findcolumn(max_record, j))
				{
					vector<int> row;
					int item = 0, cost = 0;
					int k;
					for (int i = 0; i < m; i++)
						if ((k = findrow(max_record, mat[j][i].no)) != -1 && mat[j][i].p < initialmat[max_record[k].column][max_record[k].row])
							cost += mat[j][i].p - initialmat[max_record[k].column][max_record[k].row];
					for (int i = 0; i < m; i++)
						if (findrow(max_record, mat[j][i].no) == -1)
						{
							if (cost + mat[j][i].p <= total_money - total_cost)
							{
								cost += mat[j][i].p;
								item++;
								row.push_back(mat[j][i].no);
							}
							else
								break;
						}
					if (item > add_item)
					{
						max_row = row;
						max_column = j;
						add_item = item;
						add_cost = cost;
					}
					else if (item == add_item && cost < add_cost)
					{
						max_row = row;
						max_column = j;
						add_cost = cost;
					}
				}
			if (add_item != 0 || add_cost != 0)
			{
				amount_seller++;
				total_cost += add_cost;
				max_item += add_item;
				int k;
				vector<int> no_record;
				for (int i = 0; i < m; i++)
					if ((k = findrow(max_record, mat[max_column][i].no)) != -1 && mat[max_column][i].p < initialmat[max_record[k].column][max_record[k].row])
					{
						no_record.push_back(mat[max_column][i].no);
						int no_column = max_record[k].column;
						max_record.erase(max_record.begin() + k);
						if (!findcolumn(max_record, no_column))
							amount_seller--;
					}
				for (int ii = 0; ii < no_record.size(); ii++)
				{
					paircoor tmp;
					tmp.row = no_record[ii];
					tmp.column = max_column;
					max_record.push_back(tmp);
				}
				for (int ii = 0; ii < max_row.size(); ii++)
				{
					paircoor tmp;
					tmp.row = max_row[ii];
					tmp.column = max_column;
					max_record.push_back(tmp);
				}
			}
			else
				break;
		}
		process_count++;
		cout << process_count << endl;
		out << max_item << ' ' << total_cost << ' ' << endl;
		for (int w = 0; w < max_record.size(); w++)
			out << '(' << max_record[w].row << ',' << max_record[w].column << ')' << ' ';
		out << endl;
	}
	QueryPerformanceCounter(&time_end);
	double time = (double)(time_end.QuadPart - time_begin.QuadPart) / (double)time_freq.QuadPart;
	cout << time << endl;
	return 0;
}
