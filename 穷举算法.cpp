#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
double getNormalDis()
{
	double U1 = rand() / (RAND_MAX + 1.), U2 = rand() / (RAND_MAX + 1.);
	double R = sqrt(-2 * log(U2)), S = 2 * 3.14159 * U1;
	return R * sin(S);
}
const int item = 25, seller = 25, price_range = 10000;
const double divergence = 0.1;
int matrix[item][seller];
int rank[item][seller];
struct paircoor
{
	int row;
	int column;
	bool operator<(const paircoor &p) const
	{
		if (matrix[row][column] < matrix[p.row][p.column])
			return true;
		return false;
	}
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
int main()
{
	srand(time(0));
	int total_money = price_range * item * 0.35;
	int max_seller = seller * 0.5;
	ofstream out_question("C:\\tmp25\\size_25_25.eug");
	ofstream out_answer("C:\\tmp25\\size_25_25.msk");
	for (int i = 0; i < 251; i++)
	{
		for (int j = 0; j < item; j++)
		{
			int price = rand() % price_range;
			double rate = rand() / (RAND_MAX + 1.);
			for (int k = 0; k < seller; k++)
			{
				double check = rand() / (RAND_MAX + 1.);
				if (check < rate)
					matrix[j][k] = price * (1 + divergence * getNormalDis());
				else
					matrix[j][k] = item * price_range * 2;
			}
		}
		for (int j = 0; j < item; j++)
		{
			tmpstr tmp[seller];
			for (int k = 0; k < seller; k++)
			{
				tmp[k].p = matrix[j][k];
				tmp[k].no = k;
			}
			sort(tmp, tmp + seller);
			for (int k = 0; k < seller; k++)
				rank[j][k] = tmp[k].no;
		}
		vector<int> no;
		no.push_back(0);
		int max_item = 0, min_cost = 0;
		vector<paircoor> max_record;
		while (true)
		{
			while (no.size() < max_seller)
				no.push_back(no.back() + 1);
			vector<paircoor> record;
			for (int jj = 0; jj < item; jj++)
				for (int kk = 0; kk < seller; kk++)
					if (find(no.begin(), no.end(), rank[jj][kk]) != no.end())
					{
						paircoor tmp;
						tmp.row = jj;
						tmp.column = rank[jj][kk];
						record.push_back(tmp);
						break;
					}
			sort(record.begin(), record.end());
			int anitem = 0, cost = 0, ii = 0;
			while (ii < item && cost + matrix[record[ii].row][record[ii].column] <= total_money)
			{
				anitem++;
				cost += matrix[record[ii].row][record[ii].column];
				ii++;
			}
			if (anitem > max_item)
			{
				max_item = anitem;
				min_cost = cost;
				max_record = record;
			}
			else if (anitem == max_item && cost < min_cost)
			{
				min_cost = cost;
				max_record = record;
			}
			while (no.back() == no.size() - max_seller + seller - 1)
				no.pop_back();
			if (no.size() == 0)
				break;
			no.back() += 1;
		}
		cout << i << endl;
		out_question << item << ' ' << seller << ' ' << total_money << ' ' << max_seller << ' ' << endl;
		for (int j = 0; j < item; j++)
		{
			for (int k = 0; k < seller; k++)
				out_question << setw(8) << setfill(' ') << matrix[j][k] << ' ';
			out_question << endl;
		}
		out_answer << max_item << ' ' << min_cost << ' ' << endl;
		for (int w = 0; w < max_item; w++)
			out_answer << '(' << max_record[w].row << ',' << max_record[w].column << ')' << ' ';
		out_answer << endl;
	}
	return 0;
}
