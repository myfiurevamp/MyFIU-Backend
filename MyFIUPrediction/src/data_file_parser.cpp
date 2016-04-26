//#include "../stdafx.h"
#include "../include/data_file_parser.h"

	using namespace std;


	DataFileParser::DataFileParser()
	{
	}


	DataFileParser::~DataFileParser()
	{
	}

	int DataFileParser::parseFile()
	{
		string relation_name;
		vector<attribute> attr_list;
		vector<vector<string>> records;


		relation_name = parseName();

		attr_list = parseAttributeList();
		records = parseRecords();

		relationHeader header = relationHeader(attributeList(attr_list.begin(), attr_list.end()));
		relationTable table = relationTable(records.begin(), records.end());

		relation_obj = relationObj(relation_name, header, table);

		return 0;
	}

	string::const_iterator DataFileParser::tokenize(string::const_iterator input_line_iterator, const string& input_line, string& string_token, const vector<string>& delimiters)
	{
		string_token = "";
		string character;

		const vector<string> spaces = { " ", "\t", "\n" };

		bool is_first_character_read = false;

		/* Get first character of string */
		while (is_first_character_read == false)
		{
			if (input_line_iterator == input_line.end()) // premature end of input_line
				return input_line_iterator;

			character = *input_line_iterator;

			if (find(spaces.begin(), spaces.end(), character) == spaces.end()) // if character is not a space, first character is read
				is_first_character_read = true;

			input_line_iterator++;

		} /* End get first character of string */

		string_token += character; // add first character to result token

								   /* Get token i.e., get all characters until a delimiter is met */
		while (input_line_iterator != input_line.end())
		{
			if (input_line_iterator == input_line.end())
				return input_line_iterator;

			character = *input_line_iterator;

			if (find(delimiters.begin(), delimiters.end(), character) != delimiters.end()) // if character is a delimiter...
				return ++input_line_iterator; // increment iterator first to return iterator to character after delimiter

			string_token += character;
			input_line_iterator++;
		} /* End get token */

		return input_line_iterator; // return iterator to character after retrieved token
	}

	bool DataFileParser::contains(string s, char c)
	{
		if (find(s.begin(), s.end(), c) != s.end())
			return true;
		else return false;
	}
	
	vector<string> DataFileParser::tokenizeAll(string::const_iterator input_line_iterator, const string& input_line, const vector<string>& delimiters)
	{

		vector<string> all_string_tokens;
		string string_token;

		while (input_line_iterator != input_line.end())
		{
			input_line_iterator = tokenize(input_line_iterator, input_line, string_token, delimiters);
			all_string_tokens.push_back(string_token);
		}

		return all_string_tokens;

	}

