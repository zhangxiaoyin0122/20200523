#include <iostream>
using namespace std;
class Date
{
public:
	Date(int year = 1, int month = 1, int day = 1)
	{
		//�ж������Ƿ�Ϸ�
		if (year > 0 && month > 0 && month < 13
			&& day > 0 && day <= getMonthDay(year, month))
		{
			_year = year;
			_month = month;
			_day = day;
		}
		else
		{
			cout << "���ڲ��Ϸ��� " << year << "-" << month << "-" << day << endl;
			cout << "����ΪĬ��ֵ�� 2000-1-1" << endl;
			_year = 2000;
			_month = 1;
			_day = 1;
		}

	}

	int getMonthDay(int year, int month)
	{
		static int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day = days[month];
		//�����2����Ϊ���꣬+1
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
			//2020.5.21 + 20 --> 2020.5.41 --> ��λ --> -31 -->�·ݽ�λ --> 2020.6.10
			//2020.12.6 + 90 --> 2020.12.96 --> ��λ --> -31 -->�·ݽ�λ --> 2020.13.65 -->���λ
			// --> 2021.1.65--> --> ��λ --> -31 -->�·ݽ�λ --> 2021.2.34 --> --> ��λ --> -28 -->�·ݽ�λ --> 2021.3.6
		_day += day;
		//�ж������Ƿ����,�����Ҫ��λ
		while (_day > getMonthDay(_year, _month))
		{
			//��ȥ���µ��������·ݽ�λ
			_day -= getMonthDay(_year, _month);
			++_month;
			//�ж��·��Ƿ����
			if (_month == 13)
			{
				//��λ����һ���1��
				_month = 1;
				_year++;
			}
		}
		return *this;
	}

	//ǰ��++: ++d: ����++������++֮���ֵ
	Date& operator++()
	{
		return *this += 1;
		//return (*this).operator+=(1);
		//return *this;
	}

	//����++: d++: ����++�� ����++֮ǰ��ֵ
	//ǰ��++�� ����++��Ϊ��Ŀ�����
	//���Ϊ��Ա�����������ϲ���Ҫ��ʽ���Σ����������Զ�����thisָ��
	//int�� �ββ���һ�������Ĳ�����ֻ��һ����ǲ��������������������Ķ��壬ͨ���﷨�����������Խ���Ϊ����++
	Date operator++(int)
	{
		//����++֮ǰ��ֵ
		Date ret(*this);
		//++
		*this += 1;
		//����++֮ǰ��ֵ
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
	//ǰ��++
	d2.operator++();
	d2.printD();
	//����++
	d2.operator++(0);
	d2.printD();
	d2++;
	d2.printD(); //�ȼ�d2.operator++(0);
}

void test2()
{
	Date d(2020, 5, 23);
	d.printD();
	cout << "ǰ��++" << endl;
	cout << (++d) << endl;
	d.printD();
	cout << "����++" << endl;
	cout << (d++) << endl;
	d.printD();
}

int main()
{
	//test();
	test2();
	return 0;
}