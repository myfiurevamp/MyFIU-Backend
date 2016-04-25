//#include "../../stdafx.h"
#include "../include/arff_parser.h"
#include <algorithm> 

	using namespace std;

	ArffParser::ArffParser()
	{
	}


	ArffParser::~ArffParser()
	{
		closeFile();
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

	std::string ArffParser::parseName()
	{
		using namespace std;

		string input_line;
		string string_token;
		vector<string> delimiters;

		const string arff_relation_tag = "@RELATION";
		const string arff_attribute_tag = "@ATTRIBUTE";
		const string arff_data_tag = "@DATA";
		const string arff_comment_tag = "%";

		string _relation_name;

		/* Get relation name */
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
				_relation_name = *vec_relation_name.begin();
				return _relation_name;
			}
			else
				return ""; // error, throw exception

		}
	}

	std::vector<attribute> ArffParser::parseAttributeList()
	{
		using namespace std;

		string input_line;
		string string_token;
		vector<string> delimiters;

		const string arff_relation_tag = "@RELATION";
		const string arff_attribute_tag = "@ATTRIBUTE";
		const string arff_data_tag = "@DATA";
		const string arff_comment_tag = "%";

		vector<attribute> _attr_list;
		int attribute_count = 0;

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
					throw exception("No Attributes");
			}
			else if (string_token == arff_attribute_tag)
			{
				vector<string> vec_attribute = tokenizeAll(input_line_iterator, input_line, delimiters);
				//printVec(vec_attribute);

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
							throw exception("No close parens");

						attribute_type.pop_back(); // remove close paren

						new_attribute.type = attribute_type::NOMINAL;
						delimiters = { "," };
						vector<string> all_tokens = tokenizeAll(attribute_type.begin(), attribute_type, delimiters);
						new_attribute.setAllValues(all_tokens.begin(), all_tokens.end());
					}
					else
						throw exception("Attribute Error");
				}

				_attr_list.push_back(new_attribute);
				attribute_count++;

				continue;
			}
			else
				throw exception("No relation name");
		} /* End get relation header */

		return _attr_list;
	}

	std::vector<std::vector<std::string>> ArffParser::parseRecords()
	{
		using namespace std;

		string input_line;
		string string_token;
		vector<string> delimiters;

		const string arff_relation_tag = "@RELATION";
		const string arff_attribute_tag = "@ATTRIBUTE";
		const string arff_data_tag = "@DATA";
		const string arff_comment_tag = "%";

		int record_count = 0;

		/* Get records */
		vector<string> record;
		vector<vector<string>> _records;

		delimiters = { "," };

		while (getline(arff_file_stream, input_line))
		{
			//cout << "test\n";
			record = tokenizeAll(input_line.begin(), input_line, delimiters);
			_records.push_back(record);

		} /* End get records */

		return _records;

	}


	//int ArffParser::parseFile()
	//{
	//	string input_line;
	//	string string_token;
	//	vector<string> delimiters;

	//	const string arff_relation_tag = "@RELATION";
	//	const string arff_attribute_tag = "@ATTRIBUTE";
	//	const string arff_data_tag = "@DATA";
	//	const string arff_comment_tag = "%";

	//	int attribute_count = 0;
	//	int record_count = 0;
	//	//cout << "hi\n";

	//	  /* Get relation header */
	//	while (getline(arff_file_stream, input_line))
	//	{
	//		//cout << "line: " << input_line << endl;
	//		//cout << attribute_count << endl;
	//		delimiters = { " ", "\t", "\n" };
	//		auto input_line_iterator = tokenize(input_line.begin(), input_line, string_token, delimiters);
	//		//cout << "string_token [" << string_token <<"]" << endl;
	//		//cout << "comment tag [" << arff_data_tag << "]" << endl;
	//		if (string_token == "") {
	//			//cout << "ppppp\n";
	//			continue;
	//		}
	//		else if (string_token == arff_comment_tag)
	//			continue;
	//		else if (string_token == arff_data_tag)
	//		{ //cout << "data tag\n";
	//			if (attribute_count > 0)
	//				break;
	//			else
	//				return ERROR_NUMBER = NO_ATTRIBUTES_ERROR;
	//		}
	//		else if (string_token == arff_attribute_tag)
	//		{
	//			vector<string> vec_attribute = tokenizeAll(input_line_iterator, input_line, delimiters);
	//			//printVec(vec_attribute);

	//			attribute new_attribute;
	//			auto it = vec_attribute.begin();
	//			new_attribute.name = *it;
	//			//cout << "attribute name " << new_attribute.name << endl;
	//			string attribute_type = *(++it);
	//			//cout << "attribute type: [" << attribute_type << "]"<< endl;
	//			if (attribute_type == "NUMERIC") 
	//			{
	//				//cout << "k\n";
	//				new_attribute.type = attribute_type::NUMERIC;
	//			}
	//			else if (attribute_type == "STRING")
	//				new_attribute.type = attribute_type::STRING;
	//			else if (attribute_type == "DATE")
	//				new_attribute.type = attribute_type::DATE;
	//			else
	//			{
	//				//cout << "yoooo\n";
	//				//cout << "[[[" << attribute_type[0] << endl;
	//				char first_character = *attribute_type.begin();

	//				if (first_character == '{') 
	//				{
	//					attribute_type.erase(attribute_type.begin());

	//					char last_character = attribute_type.back();
	//					if (last_character != '}')
	//						return ATTRIBUTE_NO_CLOSE_PAREN_ERROR;

	//					attribute_type.pop_back(); // remove close paren

	//					new_attribute.type = attribute_type::NOMINAL;
	//					delimiters = { "," };
	//					vector<string> all_tokens = tokenizeAll(attribute_type.begin(), attribute_type, delimiters);
	//					new_attribute.setAllValues(all_tokens.begin(), all_tokens.end());
	//				}
	//				else
	//					return ERROR_NUMBER = ATTRIBUTE_TYPE_ERROR;
	//			}

	//			relation_header.push_back(new_attribute);
	//			attribute_count++;

	//			continue;
	//		}
	//		else
	//			return ERROR_NUMBER = NO_RELATION_NAME_ERROR;
	//	} /* End get relation header */
	//	//cout << attribute_count << "gufu" << endl;

	//	  /* Get records */
	//	vector<string> record;
	//	delimiters = { "," };

	//	while (getline(arff_file_stream, input_line))
	//	{
	//		//cout << "test\n";
	//		record = tokenizeAll(input_line.begin(), input_line, delimiters);
	//		records.push_back(record);

	//	} /* End get records */

	//	return ERROR_NUMBER = NO_ERROR;

	//}





