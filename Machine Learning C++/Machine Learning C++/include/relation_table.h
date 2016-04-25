#pragma once
#include <vector> // necessary?
#include "table_column.h"
#include "table_row.h"
#include "table_slice.h" // necessary?

struct relationObj;

//for example... vector<vector<string>>

//template <typename container< typename container <std::string>>>;

typedef struct relationTable{

public:
	relationTable();
	~relationTable();
	template <class InputIterator>
	relationTable(InputIterator first, InputIterator last) { setAllRows(first, last); } // use template
	tableRow getRow(int index);
	tableColumn getColumn(int index);
	void push_back(tableRow row);
	relationTable selectAll(int attribute_index, std::string attribute_value_name);
	friend relationObj;
	/*int getSize();
	std::vector<std::vector<std::string>> getRecords();*/

	std::vector<tableRow> all_rows;
	int getNumOfRows();

	auto begin() -> decltype(all_rows.begin()) { return all_rows.begin(); }
	auto end() -> decltype(all_rows.end()) { return all_rows.end(); }

	template <class InputIterator>
	void setAllRows(InputIterator first, InputIterator last) 
	{
		for (InputIterator table_iterator = first; table_iterator != last; table_iterator++)
		{
			tableRow new_row;
			decltype(*table_iterator) record = *table_iterator;

			for (std::string value : record)
				new_row.push_back(value);

			all_rows.push_back(new_row);

		}

		return;
	} // use template


} relationTable;