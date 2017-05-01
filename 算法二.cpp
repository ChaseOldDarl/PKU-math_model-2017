#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
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
struct seller_pack
{
	vector<int> row;
	int column;
	int item;
	int cost;
	seller_pack(int col): column(col), item(0), cost(0)
	{
	}
	bool operator<(const seller_pack &p) const
	{
		if (item > p.item)
			return true;
		if (item == p.item && cost < p.cost)
			return true;
		return false;
	}
};
void recursion(vector<paircoor> &max_record, int &max_item, int &total_cost, vector<paircoor> record, int item, int cost, int m, int n, int total_money, int max_seller, matrix<tmpstr> &mat, matrix<int> &initialmat)
{
	int amount_seller = 0;
	for (int j = 0; j < n; j++)
		if (findcolumn(record, j))
			amount_seller++;
	if (amount_seller == max_seller)
	{
		if (item > max_item || (item == max_item && cost < total_cost))
		{
			max_record = record;
			max_item = item;
			total_cost = cost;
		}
		return;
	}
	else
	{
		vector<seller_pack> every_seller;
		for (int j = 0; j < n; j++)
			if (!findcolumn(record, j))
			{
				seller_pack pack(j);
				int k;
				for (int i = 0; i < m; i++)
					if ((k = findrow(record, mat[j][i].no)) != -1 && mat[j][i].p < initialmat[record[k].column][record[k].row])
						pack.cost += mat[j][i].p - initialmat[record[k].column][record[k].row];
				for (int i = 0; i < m; i++)
					if (findrow(record, mat[j][i].no) == -1)
					{
						if (pack.cost + mat[j][i].p <= total_money - cost)
						{
							pack.cost += mat[j][i].p;
							pack.item++;
							pack.row.push_back(mat[j][i].no);
						}
						else
							break;
					}
				if (pack.item != 0 || pack.cost != 0)
					every_seller.push_back(pack);
			}
		if (every_seller.size() == 0)
		{
			if (item > max_item || (item == max_item && cost < total_cost))
			{
				max_record = record;
				max_item = item;
				total_cost = cost;
			}
			return;
		}
		seller_pack min_pack = every_seller[0];
		int min_index = 0;
		for (int i = 1; i < every_seller.size(); i++)
			if (every_seller[i] < min_pack)
			{
				min_pack = every_seller[i];
				min_index = i;
			}
		every_seller.erase(every_seller.begin() + min_index);
		double variable = pow((double)n, 0.5) * pow((double)amount_seller, 3.) / (pow((double)max_seller, 1. / 3.) * (exp((double)amount_seller + 1.) - 1.));
		int factor = variable;
		int *random;
		if (every_seller.size() <= factor)
		{
			factor = every_seller.size();
			random = new int[factor + 1];
			for (int i = 0; i < factor; i++)
				random[i] = i;
		}
		else
		{
			random = new int[factor + 1];
			int *hashtable = new int[every_seller.size()];
			for (int i = 0; i < every_seller.size(); i++)
				hashtable[i] = i;
			srand(time(0));
			for (int i = 0; i < factor; i++)
			{
				int index = rand() % (every_seller.size() - i);
				random[i] = hashtable[index];
				hashtable[index] = hashtable[every_seller.size() - i - 1];
			}
			delete []hashtable;
		}
		every_seller.push_back(min_pack);
		random[factor] = every_seller.size() - 1;
		for (int i = 0; i <= factor; i++)
		{
			vector<paircoor> newrecord = record;
			int newitem = item + every_seller[random[i]].item;
			int newcost = cost + every_seller[random[i]].cost;
			int k;
			for (int ii = 0; ii < m; ii++)
				if ((k = findrow(newrecord, mat[every_seller[random[i]].column][ii].no)) != -1 && mat[every_seller[random[i]].column][ii].p < initialmat[newrecord[k].column][newrecord[k].row])
					{
						newrecord.erase(newrecord.begin() + k);
						paircoor tmp;
						tmp.row = mat[every_seller[random[i]].column][ii].no;
						tmp.column = every_seller[random[i]].column;
						newrecord.push_back(tmp);
					}
			for (int ii = 0; ii < every_seller[random[i]].row.size(); ii++)
			{
				paircoor tmp;
				tmp.row = every_seller[random[i]].row[ii];
				tmp.column = every_seller[random[i]].column;
				newrecord.push_back(tmp);
			}
			recursion(max_record, max_item, total_cost, newrecord, newitem, newcost, m, n, total_money, max_seller, mat, initialmat);
		}
		delete []random;
	}
}
int main()
{
	LARGE_INTEGER time_begin, time_end, time_freq;
	QueryPerformanceFrequency(&time_freq);
	QueryPerformanceCounter(&time_begin);
	ifstream in("C:\\precious_data\\questions\\size_25_25.eug");
	ofstream out("C:\\precious_data\\answer3\\size_25_25.msk");
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
		int max_item = 0, total_cost = 0;
		recursion(max_record, max_item, total_cost, vector<paircoor>(), 0, 0, m, n, total_money, max_seller, mat, initialmat);
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
