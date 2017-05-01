#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
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
struct status_pack
{
	vector<paircoor> record;
	int item;
	int cost;
	int amount_seller;
	int post_time;
	double d_cost;
	double d_amount_seller;
	double d_post_time;
	double final_result;
	status_pack(vector<paircoor> r, int i, int c): record(r), item(i), cost(c)
	{
	}
};
vector<status_pack> finalpack;
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
		finalpack.push_back(status_pack(record, item, cost));
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
			finalpack.push_back(status_pack(record, item, cost));
			return;
		}
		double variable = pow((double)n, 0.5) * exp(-(double)amount_seller / 3.) / pow((double)max_seller, 0.33);
		int factor = variable + 1;
		if (every_seller.size() <= factor)
			factor = every_seller.size();
		else
			sort(every_seller.begin(), every_seller.end());
		for (int i = 0; i < factor; i++)
		{
			vector<paircoor> newrecord = record;
			int newitem = item + every_seller[i].item;
			int newcost = cost + every_seller[i].cost;
			int k;
			for (int ii = 0; ii < m; ii++)
				if ((k = findrow(newrecord, mat[every_seller[i].column][ii].no)) != -1 && mat[every_seller[i].column][ii].p < initialmat[newrecord[k].column][newrecord[k].row])
					{
						newrecord.erase(newrecord.begin() + k);
						paircoor tmp;
						tmp.row = mat[every_seller[i].column][ii].no;
						tmp.column = every_seller[i].column;
						newrecord.push_back(tmp);
					}
			for (int ii = 0; ii < every_seller[i].row.size(); ii++)
			{
				paircoor tmp;
				tmp.row = every_seller[i].row[ii];
				tmp.column = every_seller[i].column;
				newrecord.push_back(tmp);
			}
			recursion(max_record, max_item, total_cost, newrecord, newitem, newcost, m, n, total_money, max_seller, mat, initialmat);
		}
	}
}
int main()
{
	//ostream &out = cout;
	ofstream out("C:\\finalresults\\result.txt");
	const int m = 6, n = 19;
	int total_money, max_seller;
	matrix<tmpstr> mat(n, m);
	matrix<int> initialmat(n, m);
	matrix<int> post_time(n, m);
	int data1[114] = {150, 142, 116, 116, 158, 180, 1000, 148, 158, 148, 239, 128, 160, 1000, 1000, 1000, 1000, 1000, 1000,
	                  85, 99, 1000, 1000, 88, 1000, 94, 79, 112, 98, 1000, 1000, 1000, 62, 98, 1000, 1000, 1000, 1000,
					  140, 140, 101, 138, 158, 180, 150, 118, 1000, 145, 148, 128, 165, 1000, 163, 147, 1000, 1000, 1000,
					  72, 1000, 73, 1000, 81, 1000, 1000, 72, 1000, 1000, 55, 92, 1000, 1000, 47, 78, 1000, 1000, 1000,
					  256, 200, 1000, 1000, 1000, 1000, 230, 200, 375, 174, 190, 1000, 1000, 1000, 50, 1000, 370, 250, 248,
					  150, 146, 1000, 1000, 1000, 1000, 120, 160, 180, 150, 1000, 1000, 1000, 1000, 160, 128, 120, 1000, 160};
	int data2[114] = {48, 48, 72, 72, 72, 48, 0, 48, 48, 48, 48, 72, 72, 0, 0, 0, 0, 0, 0,
	                  48, 48, 0, 0, 48, 0, 72, 48, 24, 48, 0, 0, 0, 72, 48, 0, 0, 0, 0,
					  48, 48, 72, 72, 48, 48, 72, 48, 0, 72, 48, 72, 48, 0, 48, 72, 0, 0, 0,
					  48, 0, 72, 0, 48, 0, 0, 48, 0, 0, 48, 72, 0, 0, 48, 72, 0, 0, 0,
					  48, 48, 0, 0, 0, 0, 72, 48, 24, 72, 48, 0, 0, 0, 48, 0, 48, 48, 48,
					  48, 48, 0, 0, 0, 0, 72, 48, 24, 72, 0, 0, 0, 0, 48, 72, 48, 0, 48};
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			mat[j][i].p = data1[i * n + j];
			initialmat[j][i] = mat[j][i].p;
			mat[j][i].no = i;
		}
	for (int j = 0; j < n; j++)
		sort(mat[j], mat[j] + m);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			post_time[j][i] = data2[i * m + j];
	while (cin >> total_money >> max_seller)
	{
		vector<paircoor> max_record;
		int max_item = 0, total_cost = 0;
		finalpack.clear();
		recursion(max_record, max_item, total_cost, vector<paircoor>(), 0, 0, m, n, total_money, max_seller, mat, initialmat);
		for (vector<status_pack>::iterator it = finalpack.begin(); it != finalpack.end(); it++)
			if (it->item < max_item)
			{
				--it;
				vector<status_pack>::iterator tmpit = it;
				++it;
				finalpack.erase(it);
				it = tmpit;
			}
		for (int k = 0; k < finalpack.size(); k++)
		{
			finalpack[k].amount_seller = 0;
			for (int j = 0; j < n; j++)
				if (findcolumn(finalpack[k].record, j))
					finalpack[k].amount_seller++;
			finalpack[k].post_time = 0;
			for (int w = 0; w < finalpack[k].record.size(); w++)
				finalpack[k].post_time += post_time[finalpack[k].record[w].column][finalpack[k].record[w].row];
		}
		int min_cost = finalpack[0].cost, max_cost = finalpack[0].cost;
		int min_amount_seller = finalpack[0].amount_seller, max_amount_seller = finalpack[0].amount_seller;
		int min_post_time = finalpack[0].post_time, max_post_time = finalpack[0].post_time;
		for (int k = 1; k < finalpack.size(); k++)
		{
			if (finalpack[k].cost < min_cost)
				min_cost = finalpack[k].cost;
			if (finalpack[k].cost > max_cost)
				max_cost = finalpack[k].cost;
			if (finalpack[k].amount_seller < min_amount_seller)
				min_amount_seller = finalpack[k].amount_seller;
			if (finalpack[k].amount_seller > max_amount_seller)
				max_amount_seller = finalpack[k].amount_seller;
			if (finalpack[k].post_time < min_post_time)
				min_post_time = finalpack[k].post_time;
			if (finalpack[k].post_time > max_post_time)
				max_post_time = finalpack[k].post_time;
		}
		double E1 = 0, E2 = 0, E3 = 0;
		if (max_cost == min_cost)
		{
			for (int k = 0; k < finalpack.size(); k++)
				finalpack[k].d_cost = 0;
		}
		else
		{
			int delta_cost = max_cost - min_cost;
			double d_total_cost = 0;
			for (int k = 0; k < finalpack.size(); k++)
			{
				finalpack[k].d_cost = (double)(finalpack[k].cost - min_cost) / (double)delta_cost;
				d_total_cost += finalpack[k].d_cost;
			}
			for (int k = 0; k < finalpack.size(); k++)
				if (finalpack[k].d_cost != 0)
				{
					double tmpf = finalpack[k].d_cost / d_total_cost;
					E1 -= tmpf * log(tmpf) / log((double)finalpack.size());
				}
		}
		if (max_amount_seller == min_amount_seller)
		{
			for (int k = 0; k < finalpack.size(); k++)
				finalpack[k].d_amount_seller = 0;
		}
		else
		{
			int delta_amount_seller = max_amount_seller - min_amount_seller;
			double d_total_amount_seller = 0;
			for (int k = 0; k < finalpack.size(); k++)
			{
				finalpack[k].d_amount_seller = (double)(finalpack[k].amount_seller - min_amount_seller) / (double)delta_amount_seller;
				d_total_amount_seller += finalpack[k].d_amount_seller;
			}
			for (int k = 0; k < finalpack.size(); k++)
				if (finalpack[k].d_amount_seller != 0)
				{
					double tmpf = finalpack[k].d_amount_seller / d_total_amount_seller;
					E2 -= tmpf * log(tmpf) / log((double)finalpack.size());
				}
		}
		if (max_post_time == min_post_time)
		{
			for (int k = 0; k < finalpack.size(); k++)
				finalpack[k].d_post_time = 0;
		}
		else
		{
			int delta_post_time = max_post_time - min_post_time;
			double d_total_post_time = 0;
			for (int k = 0; k < finalpack.size(); k++)
			{
				finalpack[k].d_post_time = (double)(finalpack[k].post_time - min_post_time) / (double)delta_post_time;
				d_total_post_time += finalpack[k].d_post_time;
			}
			for (int k = 0; k < finalpack.size(); k++)
				if (finalpack[k].d_post_time != 0)
				{
					double tmpf = finalpack[k].d_post_time / d_total_post_time;
					E3 -= tmpf * log(tmpf) / log((double)finalpack.size());
				}
		}
		double W1 = (1 - E1) / (3 - E1 - E2 - E3);
		double W2 = (1 - E2) / (3 - E1 - E2 - E3);
		double W3 = (1 - E3) / (3 - E1 - E2 - E3);
		double best_final_result = 2;
		int best_final_index = -1;
		for (int k = 0; k < finalpack.size(); k++)
		{
			finalpack[k].final_result = W1 * finalpack[k].d_cost + W2 * finalpack[k].d_amount_seller + W3 * finalpack[k].d_post_time;
			if (finalpack[k].final_result < best_final_result)
			{
				best_final_result = finalpack[k].final_result;
				best_final_index = k;
			}
		}
		out << W1 << ' ' << W2 << ' ' << W3 << ' ' << finalpack.size() << endl;
		out << "********************" << endl;
		for (int k = 0; k < finalpack.size(); k++)
		{
			out << finalpack[k].item << endl;
			out << finalpack[k].cost << ' ' << finalpack[k].amount_seller << ' ' << finalpack[k].post_time << ' ';
			out << finalpack[k].d_cost << ' ' << finalpack[k].d_amount_seller << ' ' << finalpack[k].d_post_time << endl;
			out << finalpack[k].final_result << ' ';
			if (best_final_index == k)
				out << "%%%%%%%%%%";
			out << endl;
			for (int w = 0; w < finalpack[k].record.size(); w++)
				out << '(' << finalpack[k].record[w].row << ',' << finalpack[k].record[w].column << ')' << ' ';
			out << endl;
		}
		out << "********************" << endl;
	}
	return 0;
}
