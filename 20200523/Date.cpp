#include <iostream>
using namespace std;
class Date
{
public:
	Date(int year = 1, int month = 1, int day = 1)
	{
		//判断日期是否合法
		if (year > 0 && month > 0 && month < 13
			&& day > 0 && day <= getMonthDay(year, month))
		{
			_year = year;
			_month = month;
			_day = day;
		}
		else
		{
			cout << "日期不合法： " << year << "-" << month << "-" << day << endl;
			cout << "重置为默认值： 2000-1-1" << endl;
			_year = 2000;
			_month = 1;
			_day = 1;
		}

	}

	int getMonthDay(int year, int month)
	{
		static int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day = days[month];
		//如果是2月且为闰年，+1
		if (month == 2
			&& (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)))
			++day;
		return day;
	}
	// a += b
	Date& operator+=(int day)
	{
		// a += -b  --> a -= b
		/*if (day < 0)
			return *this -= -day;*/

			//2020.5.1  + 20  --> 2020.5.21
			//2020.5.21 + 20 --> 2020.5.41 --> 进位 --> -31 -->月份进位 --> 2020.6.10
			//2020.12.6 + 90 --> 2020.12.96 --> 进位 --> -31 -->月份进位 --> 2020.13.65 -->年进位
			// --> 2021.1.65--> --> 进位 --> -31 -->月份进位 --> 2021.2.34 --> --> 进位 --> -28 -->月份进位 --> 2021.3.6
		_day += day;
		//判断日期是否溢出,溢出需要进位
		while (_day > getMonthDay(_year, _month))
		{
			//减去当月的天数，月份进位
			_day -= getMonthDay(_year, _month);
			++_month;
			//判断月份是否溢出
			if (_month == 13)
			{
				//进位到下一年的1月
				_month = 1;
				_year++;
			}
		}
		return *this;
	}

	//前置++: ++d: 首先++，返回++之后的值
	Date& operator++()
	{
		return *this += 1;
		//return (*this).operator+=(1);
		//return *this;
	}

	//后置++: d++: 本身++， 返回++之前的值
	//前置++， 后置++都为单目运算符
	//如果为成员函数，则本质上不需要显式传参，编译器会自动传入this指针
	//int： 形参不是一个真正的参数，只是一个标记参数，编译器看到这样的定义，通过语法树搜索，可以解释为后置++
	Date operator++(int)
	{
		//保存++之前的值
		Date ret(*this);
		//++
		*this += 1;
		//返回++之前的值
		return ret;
	}

	void printD()
	{
		cout << _year << " " << _month << " " << _day << endl;
	}

	Date& operator-=(int day);

	//private:
	int _year;
	int _month;
	int _day;
};
ostream& operator<<(ostream& _cout, const Date& date)
{
	_cout << date._year << " " << date._month << " " << date._day << endl;
	return _cout;
}


void test()
{
	Date d(2020, 5, 1);
	d.printD();
	d += 20;
	d.printD();
	d += 20;
	Date d2(2020, 12, 6);
	d2.printD();
	d2 += 90;
	d2.printD();
	d2 += 3650;
	d2.printD();
	++d2;
	//前置++
	d2.operator++();
	d2.printD();
	//后置++
	d2.operator++(0);
	d2.printD();
	d2++;
	d2.printD(); //等价d2.operator++(0);
}

void test2()
{
	Date d(2020, 5, 23);
	d.printD();
	cout << "前置++" << endl;
	cout << (++d) << endl;
	d.printD();
	cout << "后置++" << endl;
	cout << (d++) << endl;
	d.printD();
}

int main()
{
	//test();
	test2();
	return 0;
}