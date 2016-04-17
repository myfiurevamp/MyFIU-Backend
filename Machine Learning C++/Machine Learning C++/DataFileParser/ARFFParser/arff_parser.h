#pragma once
#include "../data_file_parser.h"
#include <fstream>
#include <iterator>

	class ArffParser : public DataFileParser
	{

	public:
		ArffParser();
		~ArffParser();
		virtual int parseFile(); // override
		virtual std::string getRelationName();
		virtual std::vector<attribute> getDatasetHeader(); // override
		virtual std::vector<std::vector<std::string>> getRecords(); //override
		virtual int openFile(std::string _arff_file_directory); // override
		virtual int closeFile(); // override

		/* Private functions */
		std::vector<std::string> tokenizeAll(std::string::const_iterator& input_line_iterator, const std::string& input_line, const std::vector<std::string>& delimiters);
		std::string::const_iterator& tokenize(std::string::const_iterator& input_line_iterator, const std::string & input_line, std::string & string_token, const std::vector<std::string>& delimiters);

	private:
		std::ifstream arff_file_stream;






	};