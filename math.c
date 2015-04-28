#define ZERO_THRESHOLD 0.000000001

double atan2(double x, double y)
{
	if(x < ZERO_THRESHOLD && x > -ZERO_THRESHOLD) // check for x = 0, (but really if its really small)
	{
		if(y < ZERO_THRESHOLD && y > -ZERO_THRESHOLD)
		{
			return 0; // undefined, just use 0 to make things happy
		}
		if(y > ZERO_THRESHOLD)
		{
			return 90;     
		}
		if(y < -ZERO_THRESHOLD)
		{
			return -90;
		}
	}
	if(y > ZERO_THRESHOLD || y < -ZERO_THRESHOLD)
	{
		double tan = atan(x/y);
	}
	else
	{
		double tan = 90;
	}
	if(x > ZERO_THRESHOLD)
	{
		return tan;
	}
	if(y >= ZERO_THRESHOLD)
	{
		return tan + 90;
	}
	if(y < -ZERO_THRESHOLD)
	{
		return tan - 90;
	}

	return 0; // return 0 if we managed to avoid all of the other ifs
}

/* calculates the value of atan(x)
 * using the formula 90*(.6x+x^2)/(1+1.2x+x^2)
 */
double atan(double x)
{
	unsigned char negative = 0;
	if(x < 0) // doesn't need to use zero-threshold because we strictly need to check sign
	{
		x = 0-x;
		negative = 1; 
	}
	// trying to optimize the calculation using a trick I learned in my numerical analysis class
	double n0 = .6;
	double n1 = n0 + x;
	double n2 = n1 * x;
	double n3 = n2 * 90.0;
	double d0 = 1.2;
	double d1 = d0 + x;
	double d2 = d1 * x;
	double d3 = d2 + 1.0;

	double atan_n = n3 / d3;

	if(negative)
	{
		return 0-atan_n;
	}

	return atan_n;

}