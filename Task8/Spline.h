#pragma once
#include <vector>
#include <algorithm>

using namespace std;


namespace interpol
{

	struct point
	{
		double x, y;
	};

	bool operator < (const point &A, const point &B);

	class CubicSpline
	{
	private:
			vector<double> b, c, d, A, B, C, q1, q2, h, F;
			vector<point> p;
	public:

			CubicSpline(vector<point> _points);

			double operator()(double x0);
	};
};
