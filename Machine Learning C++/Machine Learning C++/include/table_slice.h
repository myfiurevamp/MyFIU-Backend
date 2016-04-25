#pragma once
#include <vector>
#include <string>

struct relationTable;

typedef struct tableSlice
{

public:

	tableSlice();
	template <class InputIterator>
	tableSlice(InputIterator first, InputIterator last)
	{
		setAllValues(first, last);
	} // use template

	~tableSlice();
	int size();
	std::string operator[](int index) { return all_values[index]; }
	friend relationTable;

	std::string getMajorityValue();
	std::vector<std::string> all_values;
	void push_back(std::string value);
	bool hasDistinctValues();

	auto begin() -> decltype(all_values.begin()) { return all_values.begin(); }
	auto end() -> decltype(all_values.end()) { return all_values.end(); }

protected:
	template <class InputIterator>
	void setAllValues(InputIterator first, InputIterator last)
	{
		for (InputIterator all_values_iterator = first; all_values_iterator != last; all_values_iterator++)
		{
			/*try
			{*/
				std::string value = *all_values_iterator;
		/*	}*/
		/*	catch
			{
				throw invalid_argument("Iterator does not point to string!");
			}*/
			all_values.push_back(value);
		}
	
	} // use template

private:

} tableSlice;

