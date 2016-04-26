#pragma once
#include "table_slice.h"


struct relationTable;

typedef struct tableColumn : public tableSlice
{

public:
	tableColumn();
	template <class InputIterator>
	tableColumn(InputIterator first, InputIterator last) : tableSlice(first, last) {}; // use template
	~tableColumn();
	friend relationTable;
} tableColumn;

