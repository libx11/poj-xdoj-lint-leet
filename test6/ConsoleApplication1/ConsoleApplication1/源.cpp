#include <iostream>
using namespace std;

class a
{
protected:
	int b;
public:
	a(int i)
	{
		b = i+50;
		show();

	}
	a() {}
	virtual void show()
	{
		cout << "b.show.b=" << b << endl;

	}

};

class c :public a
{
protected:
	int d;
public:
	c(int i) :a(i) {
		d = i + 100;
		show();

	}
	c() {};
	void show()
	{
		cout << "d.show.d=" << d << endl;
	}
};

int main()
{
	int a;
	c c1(100);
	cin >> a;
	return 0;
}

