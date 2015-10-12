#include <iostream>

using namespace std;

template <class T> class A
{
public:
	T min(T x,T y);
};

template <class T> T A<T>::min(T x, T y)
{
	return (x<y)?x:y;
}

int main()
{
	int n1 = 1, n2 = 10;
	double v1 = 2.2, v2 = 3.3;
	A<int> a;
	A<double> b;	
	cout << "Min:" << a.min(n1,n2) << endl;
	cout << "Min:" << b.min(v1,v2) <<endl;
	return 0;
}
