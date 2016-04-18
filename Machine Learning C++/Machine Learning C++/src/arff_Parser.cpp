//#include "../../stdafx.h"
#include "../include/arff_parser.h"
#include <algorithm> 

	using namespace std;

	ArffParser::ArffParser()
	{
	}


	ArffParser::~ArffParser()
	{
		arff_file_stream.close();
	}


	static void printVec(std::vector<std::string> string_vector)
	{
		int i = 0;

		for (std::string str : string_vector)
			std::cout << "[" << str << "] ";
		std::cout << std::endl;
		return;

	}

	int ArffParser::openFile(string _arff_file_directory)
	{
		data_file_directory = _arff_file_directory;
		arff_file_stream = ifstream(_arff_file_directory);

		if (arff_file_stream.fail())
			return ERROR_NUMBER = OPEN_FILE_ERROR;
		else
			return ERROR_NUMBER = NO_ERROR;
	}

	int ArffParser::closeFile() {

		arff_file_stream.close();

		return 0;

	}

	string::const_iterator& ArffParser::tokenize(string::const_iterator& input_line_iterator, const string& input_line, string& string_token, const vector<string>& delimiters)
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

	vector<string> ArffParser::tokenizeAll(string::const_iterator& input_line_iterator, const string& input_line, const vector<string>& delimiters)
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

	int ArffParser::parseFile()
	{
		string input_line;
		string string_token;
		vector<string> delimiters;

		const string arff_relation_tag = "@RELATION";
		const string arff_attribute_tag = "@ATTRIBUTE";
		const string arff_data_tag = "@DATA";
		const string arff_comment_tag = "%";

		int attribute_count = 0;
		int record_count = 0;
		//cout << "hi\n";
		/* Get relation name */

		cout << "Relation Header:\n";
		while (getline(arff_file_stream, input_line))
		{
			delimiters = { " ", "\t", "\n" };
			auto input_line_iterator = tokenize(input_line.begin(), input_line, string_token, delimiters);

			if (input_line_iterator == input_line.end())
				continue;
			else if (string_token == arff_comment_tag)
				continue;
			else if (string_token == arff_relation_tag)
			{
				delimiters = { "\n" };
				vector<string> vec_relation_name = tokenizeAll(input_line_iterator, input_line, delimiters);
				relation_name = *vec_relation_name.begin();
				break;
			}
			else
				return ERROR_NUMBER = NO_RELATION_NAME_ERROR;
		} /* End get relation name */

		  /* Get relation header */
		while (getline(arff_file_stream, input_line))
		{
			//cout << "line: " << input_line << endl;
			//cout << attribute_count << endl;
			delimiters = { " ", "\t", "\n" };
			auto input_line_iterator = tokenize(input_line.begin(), input_line, string_token, delimiters);
			//cout << "string_token [" << string_token <<"]" << endl;
			//cout << "comment tag [" << arff_data_tag << "]" << endl;
			if (string_token == "") {
				//cout << "ppppp\n";
				continue;
			}
			else if (string_token == arff_comment_tag)
				continue;
			else if (string_token == arff_data_tag)
			{ //cout << "data tag\n";
				if (attribute_count > 0)
					break;
				else
					return ERROR_NUMBER = NO_ATTRIBUTES_ERROR;
			}
			else if (string_token == arff_attribute_tag)
			{
				vector<string> vec_attribute = tokenizeAll(input_line_iterator, input_line, delimiters);
				printVec(vec_attribute);

				attribute new_attribute;
				auto it = vec_attribute.begin();
				new_attribute.name = *it;
				//cout << "attribute name " << new_attribute.name << endl;
				string attribute_type = *(++it);
				//cout << "attribute type: [" << attribute_type << "]"<< endl;
				if (attribute_type == "NUMERIC") 
				{
					//cout << "k\n";
					new_attribute.type = attribute_type::NUMERIC;
				}
				else if (attribute_type == "STRING")
					new_attribute.type = attribute_type::STRING;
				else if (attribute_type == "DATE")
					new_attribute.type = attribute_type::DATE;
				else
				{
					//cout << "yoooo\n";
					//cout << "[[[" << attribute_type[0] << endl;
					char first_character = *attribute_type.begin();

					if (first_character == '{') 
					{
						attribute_type.erase(attribute_type.begin());

						char last_character = attribute_type.back();
						if (last_character != '}')
							return ATTRIBUTE_NO_CLOSE_PAREN_ERROR;

						attribute_type.pop_back(); // remove close paren

						new_attribute.type = attribute_type::NOMINAL;
						delimiters = { "," };
						new_attribute.values = tokenizeAll(attribute_type.begin(), attribute_type, delimiters);
					}
					else
						return ERROR_NUMBER = ATTRIBUTE_TYPE_ERROR;
				}

				relation_header.push_back(new_attribute);
				attribute_count++;

				continue;
			}
			else
				return ERROR_NUMBER = NO_RELATION_NAME_ERROR;
		} /* End get relation header */
		//cout << attribute_count << "gufu" << endl;

		  /* Get records */
		vector<string> record;
		delimiters = { "," };

		while (getline(arff_file_stream, input_line))
		{
			//cout << "test\n";
			record = tokenizeAll(input_line.begin(), input_line, delimiters);
			records.push_back(record);

		} /* End get records */

		return ERROR_NUMBER = NO_ERROR;

	}

	string ArffParser::getRelationName()
	{
		return relation_name;

	}

	vector<attribute> ArffParser::getRelationHeader()
	{
		return relation_header;
	}

	vector<vector<string>> ArffParser::getRecords()
	{
		return records;
	}




