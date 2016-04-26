#include "../include/table_slice.h"
#include <stdexcept>

using namespace std;

tableSlice::tableSlice()
{
}

//template <class InputIterator>
//tableSlice::tableSlice(InputIterator first, InputIterator last) // use template
//{
//	setAllValues(first, last);
//}


tableSlice::~tableSlice()
{
}

int tableSlice::size()
{
	return all_values.size();
}

//template <class InputIterator>
//void tableSlice::setAllValues(InputIterator first, InputIterator last) // use template
//{
//	for (InputIterator all_values_iterator = first; all_values_iterator != last; all_values_iterator++)
//	{
//		try 
//		{
//			string value = *all_values_iterator;
//		}
//		catch
//		{
//			throw invalid_argument("Iterator does not point to string!");
//		}
//		all_values.push_back();
//	}
//
//}

//void tableSlice::setAllValues(vector<string> _all_values) // use template
//
//{
//	for (auto value_iterator = _all_values.begin(); value_iterator != _all_values.end(); value_iterator++)
//	{
//		all_values.push_back(*value_iterator);
//	}
//
//}

string tableSlice::getMajorityValue()
{
	vector<pair<string, int>> v;
	bool does_value_exist;

	for (string value : all_values)
	{
		does_value_exist = false;

		for (pair<string, int>& p : v)
		{
			/* If p is contained in v */
			if (p.first == value)
			{
				p.second++;
				does_value_exist = true;
			}
		}

		if (does_value_exist == false)
			v.push_back(pair<string, int>(value, 0));
	}

	pair<string, int> most_frequent_value;

	most_frequent_value = *v.begin();

	for (pair<string, int> p2 : v)
	{
		if (p2.second > most_frequent_value.second)
			most_frequent_value = p2;
	}

	return most_frequent_value.first;
}

void tableSlice::push_back(string value)
{
	all_values.push_back(value);

	return;
}

bool tableSlice::hasDistinctValues()
{
	vector<string> v;
	bool has_distinct_values;

	for (string value : all_values)
	{
		/* If value exists in v, then this tableSlice does NOT have distinct values */
		if (find(v.begin(), v.end(), value) != v.end())
			return has_distinct_values = false;

		v.push_back(value);
	}

	return has_distinct_values = true;
}

