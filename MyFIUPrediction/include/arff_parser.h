#pragma once
#include <fstream>
#include <iterator>
#include "relation_header.h"
#include "data_file_parser.h"

	class ArffParser : public DataFileParser
	{

	public:
		ArffParser();
		~ArffParser();
		virtual int openFile(std::string _arff_file_directory); // override
		virtual int closeFile(); // override

		std::string parseName();
		std::vector<attribute> parseAttributeList();
		std::vector<std::vector<std::string>> parseRecords();
		
	private:
	
		std::ifstream arff_file_stream;


	};