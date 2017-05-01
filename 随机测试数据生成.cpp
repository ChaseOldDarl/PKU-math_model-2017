#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;
double getNormalDis()
{
	double U1 = rand() / (RAND_MAX + 1.), U2 = rand() / (RAND_MAX + 1.);
	double R = sqrt(-2 * log(U2)), S = 2 * 3.14159 * U1;
	return R * sin(S);
}
const int item = 50, seller = 100, price_range = 10000;
const double divergence = 0.1;
int matrix[item][seller];
int main()
{
	srand(time(0));
	int total_money = price_range * item * 0.35;
	int max_seller = seller * 0.5;
	ofstream out_question("C:\\precious_data\\difficult_questions\\money_0.35.eug");
	for (int i = 0; i < 1000; i++)
	{
		for (int j = 0; j < item; j++)
		{
			int price = rand() % price_range;
			double rate = 0.3 + 0.1 * getNormalDis();
			while (rate <= 0 || rate >= 1)
				rate = 0.3 + 0.1 * getNormalDis();
			for (int k = 0; k < seller; k++)
			{
				double check = rand() / (RAND_MAX + 1.);
				if (check < rate)
				{
					double fluctuation = divergence * getNormalDis();
					while (fluctuation < -divergence * 3. || fluctuation > divergence * 3.)
						fluctuation = divergence * getNormalDis();
					matrix[j][k] = price * (1 + fluctuation);
				}
				else
					matrix[j][k] = item * price_range * 2;
			}
		}
		out_question << item << ' ' << seller << ' ' << total_money << ' ' << max_seller << ' ' << endl;
		for (int j = 0; j < item; j++)
		{
			for (int k = 0; k < seller; k++)
				out_question << setw(8) << setfill(' ') << matrix[j][k] << ' ';
			out_question << endl;
		}
	}
	return 0;
}
