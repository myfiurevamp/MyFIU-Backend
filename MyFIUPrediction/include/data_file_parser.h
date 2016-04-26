#pragma once
#include "attribute.h"
#include "relation_obj.h"

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

	int parseFile();

	virtual std::string parseName() = 0;
	virtual std::vector<attribute> parseAttributeList() = 0;
	virtual std::vector<std::vector<std::string>> parseRecords() = 0;

	std::vector<std::string> tokenizeAll(std::string::const_iterator input_line_iterator, const std::string& input_line, const std::vector<std::string>& delimiters);
	std::string::const_iterator tokenize(std::string::const_iterator input_line_iterator, const std::string & input_line, std::string & string_token, const std::vector<std::string>& delimiters);

	static bool contains(std::string s, char c);
	relationObj getRelationObj() { return relation_obj; }

	//std::string getRelationName() { return relation_name; }

	//template <class InputIterator>
	//std::pair<InputIterator, InputIterator> getAttrList()
	//{
	//	std::pair<InputIterator, InputIterator> attr_list_iterators = std::pair<InputIterator, InputIterator>(attr_list.begin(), attr_list.end());
	//	return attr_list_iterators;
	//}

	//template <class InputIterator>
	//std::pair<InputIterator, InputIterator> getRecords()
	//{
	//	std::pair<InputIterator, InputIterator> records_iterators = std::pair<InputIterator, InputIterator>(records.begin(), records.end());
	//	return records_iterators;
	//}
		//virtual string getErrorMessage(int error_number); // call for object -- may be overriden.
		//static string getErrorMessage(int error_number); // use for abstract class's interpretation of error number.

	protected:
		std::string data_file_directory;

		relationObj relation_obj;
		int ERROR_NUMBER = 0; // initialize to 0

	};



