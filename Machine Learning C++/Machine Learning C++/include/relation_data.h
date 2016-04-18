#pragma once
#include <string>
#include <vector>

struct relation;

typedef struct relationData{

public:
	relationData();
	~relationData();
	relationData(std::vector<std::vector<std::string>>  _records);
	friend relation;
	/*int getSize();
	std::vector<std::vector<std::string>> getRecords();*/

private:
	int size;
	std::vector<std::vector<std::string>> records;

} relationData;