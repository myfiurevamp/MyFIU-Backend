#include "../include/relation_table.h"

using namespace std;

struct relationTable;

relationTable::relationTable()
{
}

relationTable::~relationTable()
{
}

//template <class InputIterator>
//relationTable::relationTable(InputIterator first, InputIterator last) // use template
//{
//	setAllRows(first, last);
//}

tableRow relationTable::getRow(int index)
{
	return all_rows[index];
}

tableColumn relationTable::getColumn(int index)
{
	tableColumn column;

	for (tableRow row : all_rows)
		column.push_back(row[index]);

	return column;
}

void relationTable::push_back(tableRow row)
{
	all_rows.push_back(row);
}

relationTable relationTable::selectAll(int attribute_index, std::string attribute_value_name)
{
	relationTable result;
	for (tableRow record : all_rows)
		if (record[attribute_index] == attribute_value_name)
			result.push_back(record);

	return result;
}

int relationTable::getNumOfRows()
{
	return all_rows.size();
}

//template <class InputIterator>
//void relationTable::setAllRows(InputIterator first, InputIterator last)
//{
//
//	for (InputIterator table_iterator = first; table_iterator != last; table_iterator++)
//	{
//		tableRow new_row;
//		decltype(*table_iterator) record = *table_iterator;
//
//		for (string value : record) 
//			new_row.push_back(value);
//
//		all_rows.push_back(new_row);
//
//	}
//
//	return;
//}


//int relationData::getSize()
//{
//	return size;
//}
//
//vector<vector<string>> relationData::getRecords()
//{
//	return records;
//}
