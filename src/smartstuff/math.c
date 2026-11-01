#include "math.h"
#include <stdio.h>

int factorial(int base);
double power(double base, int power);
double remainder(double divident, double divider);

double
sinus(double rad)
{
	if (remainder(rad+PI/2, 2*PI)-PI > 0) rad = -rad;
	rad = (remainder(rad+PI/2, PI)-PI/2);
	
	double result = 0.0;
	for (int i = 1; i < 4; ++i)
	{
		result += (power(rad, (i<<1)-1) / factorial((i<<1)-1))*(-1+((i%2)<<1));
	}
	printf("%f\n", result);
	return result;
}

double
cosinus(double rad)
{
	int invert = 1;
	if (remainder(rad+PI/2, 2*PI)-PI > 0) invert= -1;
	rad = (remainder(rad+PI/2, PI)-PI/2);
	
	double result = 1.0;
	for (int i = 1; i < 4; ++i)
	{
		result += (power(rad, (i<<1)) / factorial((i<<1)))*(1-((i%2)<<1));
	}
	printf("%f\n", result);
	return result*invert;
}

double
squareroot(double x)
{
	double eps = 1e-6;
	double y1, y2;
	y1 = x;
	y2 = y1 / 2;
	while (y1 - y2 > eps || y2 - y1 > eps) {
		y1 = y2;
		y2 = (y1 + x / y1) / 2;
	}
	return y2;
}


double
remainder(double divident, double divider)
{
	while(divident >= divider)divident -= divider;
	while(divident < 0)divident += divider;
	return divident;
}

double
power(double base, int power)
{
	double result = 1;
	if(power >=0)
		while(power != 0)
		{
			--power;
			result *= base;
		}
	else
		while(power != 0)
		{
			++power;
			result /= base;
		}


	return result;
}

int 
factorial(int base)
{
	int result = base;
	while(base != 1) result*=(--base);
	return result;
}

