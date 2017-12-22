//Implementation of cubic spline interpolation

#include "Spline.h"

using namespace interpol;
using namespace std;

interpol::CubicSpline::CubicSpline(vector<point> _points) : p(_points)
{
	int n = p.size() - 1;

	sort(p.begin(), p.end());

	h.resize(n + 1);
	q1.resize(n + 1);
	q2.resize(n + 1);
	b.resize(n + 1);
	c.resize(n + 1);
	d.resize(n + 1);
	A.resize(n);
	B.resize(n + 1);
	C.resize(n + 1);
	F.resize(n + 1);
	for (int i = 1; i <= n; ++i)
		h[i] = p[i].x - p[i - 1].x;

	C[0] = 2 * h[1];
	for (int i = 1; i<n; ++i) {
		A[i - 1] = h[i];
		C[i] = 2 * (h[i + 1] + h[i]);
		B[i] = h[i];
		F[i] = 3 * ((p[i + 1].y - p[i].y) / h[i + 1] - (p[i].y - p[i - 1].y) / h[i]);
	}
	B[n] = h[n];
	A[n - 1] = h[n];
	C[n] = 2 * h[n];

	q1[0] = -A[0] / C[0];
	q2[0] = F[0] / C[0];

	for (int i = 1; i < n; ++i)
	{
		q1[i] = -A[i] / (B[i] * q1[i - 1] + C[i]);
		q2[i] = (F[i] - A[i] * q2[i - 1]) / (A[i] * q1[i - 1] + C[i]);
	}

	for (int i = n - 1; i >= 1; --i)
		c[i] = q1[i] * c[i + 1] + q2[i];

	for (int i = 0; i < n; ++i)
	{
		d[i] = (c[i + 1] - c[i]) / (3 * h[i + 1]);
		b[i] = (p[i + 1].y - p[i].y) / h[i + 1] - 1 / 3 * h[i + 1] * (c[i + 1] + 2 * c[i]);
	}
}

double interpol::CubicSpline::operator()(double x0)
{
	if (x0 < p[0].x || x0 > p[p.size()-1].x)
		throw(exception("argument is out of range : operator()"));
	int i = 0;
	while (x0 >= p[i+1].x)
		++i;
	double x = x0 - p[i].x;
	return p[i].y + b[i] * x + c[i]/2 * pow(x, 2) + d[i]/6 * pow(x, 3);
}

bool interpol::operator<(const point & A, const point & B)
{
	return A.x < B.x ? 1 : 0;
}
