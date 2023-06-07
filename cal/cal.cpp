#include <vector>
#include <stdexcept>

using namespace std;

class Cal
{
public:
	int getSum(int a, int b)
	{
		return a + b;
	}

	vector<int> change(vector<int>& arr)
	{
		vector<int> result = arr;
		for(int &num : result)
		{
			if(num >= 10 || num == 4)
			{
				throw std::invalid_argument("잘못된 값");
			}
			num = (num + 1) % 10;
			if (num == 4)
				num = 5;
		}
		return result;
	}

	int getValue()
	{
		return x;
	}

private:
	int x = 100;
};

class TradingAPI
{
public:
	virtual string buy() = 0;
};

class KiwoomAPI : public TradingAPI
{
public:
	string buy() override
	{
		return name;
	}

private:
	string name = "MySon_DB";
};

class TradingSystem
{
public:
	TradingSystem(TradingAPI* ti) : TI(ti) {}

	string getLogMessage(string content)
	{
		string msg = "";
		msg += string("[") + TI->buy() + string("]");
		msg += content + string("\n");
		return msg;
	}

private:
	TradingAPI* TI;
};
