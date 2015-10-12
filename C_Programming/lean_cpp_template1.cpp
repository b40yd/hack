//#include <stdio.h>
#include <iostream>
using namespace std;

template <class T> T mins(T x,T y)
{
	return (x < y) ? x : y;
};

int main()
{
	int n1, n2;
	n1 = 1;
	n2 = 2;
	int res;
	res = mins<int>(n1,n2);
	//printf("%d\n",res);	
	cout << "Min: \t" << res << endl;
	return 0;
}
