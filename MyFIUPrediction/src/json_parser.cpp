////#include "stdafx.h"
//#include "../include/json_parser.h"
//
//using namespace std;
//
//JSONParser::JSONParser()
//{
//	json_string = "";
//
//}
//
//
//JSONParser::~JSONParser()
//{
//}
//
//int JSONParser::openFile(std::string _json_string)
//{
//	json_string = _json_string;
//	json_string_stream = std::istringstream(json_string);
//	return 0;
//}
//
//string JSONParser::parseName()
//{
//	return "";
//}
//
//vector<attribute> JSONParser::parseAttributeList()
//{
//	//parse float, if not, parse string
//	string input_line;
//	string string_token;
//	vector<string> delimiters = { "," };
//
//	char left_bracket = '[';
//	char left_curly_brace = '{';
//	char right_bracket = ']';
//	char right_curly_brace = '}';
//
//	bool done_parsing = false;
//
//	bool left_bracket_read = false;
//	bool left_curly_brace_read = false;
//	bool right_bracket_read = false;
//	bool right_curly_brace_read = false;
//	
//	bool in_array_element_mode = false;
//	bool in_key_read_mode = false;
//	bool in_value_read_mode = false;
//	
//	bool in_value_parse_mode = false;
//
//	string key_name;
//	string value_name;
//	vector<pair<string, string>> key_value_pairs;
//
//	vector<attribute> _attr_list;
//	int attribute_count = 0;
//
//	/* For every line... */
//	while (getline(json_string_stream, input_line))
//	{
//		/* For every character in every line... */
//		for (char c : input_line)
//		{
//			/* Get left bracket */
//			if (left_bracket_read == false)
//			{
//				if (c == left_bracket)
//				{
//					left_bracket_read = true;
//					continue;
//				}
//				else if (c == ' ' || c == '\t' || c == '\n')
//					continue;
//				else throw exception("Expected left bracket");
//			}
//
//			/* Get left paren */
//			else if(left_curly_brace_read == false)
//			{
//				if (c == left_curly_brace)
//				{
//					left_curly_brace_read = true;
//					in_array_element_mode = true;
//					in_key_read_mode = true;
//					continue;
//				}
//				else if (c == ' ' || c == '\t' || c == '\n')
//					continue;
//				else throw exception("Expected left paren");
//			}
//
//			/* Get rest of info */
//			else if (true)
//			{
//				if (in_key_read_mode == true)
//				{
//					if (c == ' ' || c == '\t' || c == '\n')
//						throw exception("Space encountered. Expected a colon.");
//					else if ( c == ',' || c == left_bracket || c == right_bracket || c == left_curly_brace || c == right_curly_brace)
//						throw exception("Expected key value");
//					else if (c == ':')
//					{
//						in_value_read_mode = true;
//						in_key_read_mode = false;
//					}
//					else
//					{
//						key_name.push_back(c);
//						continue;
//					}
//				}
//				else if (in_value_read_mode == true)
//				{
//					if (c == ' ' || c == '\t' || c == '\n')
//						continue;
//					else if (c == '\"')
//						if (in_value_parse_mode == false)
//						{
//							in_value_parse_mode = true;
//							continue;
//						}
//						else
//						{
//							key_value_pairs.push_back(pair<string, string>(key_name, value_name));
//							key_name.clear();
//							value_name.clear();
//							in_value_read_mode == false;
//						}
//						//else throw exception("Expected first character of value name");
//					else if (c == ',' || c == left_bracket || c == right_bracket || c == left_curly_brace || c == right_curly_brace)
//						throw exception("Expected first character of value name");
//					else
//					{
//						value_name.push_back(c);
//						continue;
//					}
//
//				}
//				else if(right_curly_brace_read == false)
//				{
//					if (c == ' ' || c == '\t' || c == '\n')
//						continue;
//					else if (c == ',')
//					{
//						in_key_read_mode = true;
//						continue;
//					}
//					else if(c == right_curly_brace)
//					{ 
//						right_curly_brace_read = true;
//						break;
//					}
//					else throw exception("Expected a comma or right curly brace");
//						
//				}
//				else
//				{
//					if (c == ' ' || c == '\t' || c == '\n')
//						continue;
//					else if (c == ',')
//					{
//						in_array_element_mode = false;
//						continue;
//					}
//					else if (c == right_bracket)
//					{
//						done_parsing = true;
//						// do something, then break
//					}
//				}
//
//			}
//
//
//		}
//
//	}
//	return;
//}
//
//std::vector<std::vector<std::string>> JSONParser::parseRecords()
//{
//	return std::vector<std::vector<std::string>>();
//}
//
//vector<vector<string>> parseRecords()
//{
//	return;
//}
