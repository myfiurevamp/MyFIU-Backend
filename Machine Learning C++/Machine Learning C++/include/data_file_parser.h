#pragma once
#include "attribute.h"

	//look at perror
#define NO_ERROR 0
#define DEFAULT_ERROR -1
#define OPEN_FILE_ERROR -2
#define PARSE_ATTR_HEADER_ERROR -3
#define PARSE_RECORD_ERROR -4
#define PARSE_RECORDS_ERROR -5
#define NO_RELATION_NAME_ERROR -6
#define NO_ATTRIBUTES_ERROR -7
#define ATTRIBUTE_TYPE_ERROR -8
#define ATTRIBUTE_NO_CLOSE_PAREN_ERROR -9

	class DataFileParser
	{
	public:
		DataFileParser();
		virtual ~DataFileParser() = 0;

		virtual int openFile(std::string _data_file_directory) = 0;
		virtual int closeFile() = 0;
		virtual int parseFile() = 0;
		virtual std::string getRelationName() = 0;
		virtual std::vector<attribute> getRelationHeader() = 0;
		virtual std::vector<std::vector<std::string>> getRecords() = 0;
		//virtual string getErrorMessage(int error_number); // call for object -- may be overriden.
		//static string getErrorMessage(int error_number); // use for abstract class's interpretation of error number.

	protected:
		std::string data_file_directory;
		std::string relation_name;
		std::vector<attribute> relation_header;
		std::vector<std::vector<std::string>> records;
		int ERROR_NUMBER = 0; // initialize to 0

	};

