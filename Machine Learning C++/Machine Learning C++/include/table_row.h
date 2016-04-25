#pragma once
#include "table_slice.h"

struct relationTable;

typedef struct tableRow : public tableSlice
{
public:
	tableRow();
	template <class InputIterator>
	tableRow(InputIterator first, InputIterator last) : tableSlice(first, last) {}; // use template
	~tableRow();
	friend relationTable;
} tableRow;

