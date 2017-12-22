//Interpolation. The function f(x) is given by a table of its values.
//Construct a cubic spline and evaluate the value of the function at the specified point x0. 
//(x : -0.5 1.5 2.0 3.5 6.0 9.0, f(x) : 2.5 6 - 3.5 - 7 - 10 2) x0 = 2.5


#include <iostream>
#include <vector>
#include "Spline.h"
using namespace std;


using namespace interpol;



int main()
{
	vector<point> _points1 = { {-0.5, 2.5}, {1.5, 6}, { 2.0, -3.5}, {3.5, -7}, {6.0, -10}, {9.0, 2} };
	vector<point> _points = { {1, 1.0002}, {2, 1.0341}, {3, 0.6}, {4, 0.40105}, {5, 0.1}, {6, 0.23975} };
	double x0 = 2.5;

	cout << endl;
	CubicSpline sp(_points);

	for (double i = 1.1; i <= 5.9; i += 0.1)
	{
		cout << "x = " << i << " y = " << sp(i) << endl;
	}

	system("pause");
	return 0;
}