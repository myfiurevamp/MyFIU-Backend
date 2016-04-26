#include "../include/my_fiu_revamp_pg_parser.h"

using namespace std;

MyFIUPgParser::MyFIUPgParser()
{

}

MyFIUPgParser::~MyFIUPgParser()
{
  closeFile();
}

void MyFIUPgParser::setCourseTableName(string _course_table_name)
{
  course_table_name = _course_table_name;
  return;
}

void MyFIUPgParser::setTypes(vector<string> _type_list)
{
  type_list = _type_list;
  return;
}

void MyFIUPgParser::setIgnoredColumnNums(vector<int> _ignored_column_nums)
{
  ignored_column_nums = _ignored_column_nums; // CHANGE THIS TO ONLY 5 (DELETE 6 AND 7)
  return;
}

int MyFIUPgParser::openFile(std::string conn_string)
{ 
  std::cout <<  "Connection String: \"" << conn_string << "\"\n";
  pqxx::connection conn(conn_string);
  
  if(conn.is_open())
    {
      std::string sql_query;
      std::string buffer;
      
      std::cout << "Connected!\n";
      return 0;
    }
  else
    {
      std::cout << "Error: Could not connect! Terminating...\n";
      return -1;
    }
}

int MyFIUPgParser::closeFile()
{
  /* Disconnect from database */
  conn.disconnect();
  std::cout << "Disconnected!\n";
      
}

string MyFIUPgParser::parseName()
{
  return course_table_name;
}

vector<attribute> MyFIUPgParser::parseAttributeList()
{

  vector<string> column_names;

  pqxx::nontransaction query_obj(conn);
  
  /* Get number of columns for taken_course table */
  sql_query = "SELECT COUNT(*) FROM INFORMATION_SCHEMA.COLUMNS WHERE table_name = '" + courses_table_name + "';"; 
  pqxx::result num_of_col_query_result (query_obj.exec(sql_query));
  buffer = num_of_col_query_result.begin()[0].as<std::string>();
  
  num_of_columns = std::stoi(buffer);
  
  /* Get all column names */
  sql_query = "SELECT column_name FROM INFORMATION_SCHEMA.COLUMNS WHERE table_name = '" + courses_table_name + "';"; 
  pqxx::result col_names_query_result (query_obj.exec(sql_query));
  
  for(pqxx::result::const_iterator result_it = col_names_query_result. begin(); result_it != col_names_query_result.end(); ++result_it)
    {
      std::string col_name = result_it[0].as<std::string>();
      column_names.push_back(col_name);
    }
  
  printVec(column_names);

  /* Convert columns to attributes */
  vector<attribute> attr_list;
  
  int i = 0;
  for(string column_name : column_names)
    {
      attribute attr;
      attr.name = column_name;
      
      string attr_type = type_list[i];

      if(attr_type == "numeric")
	attr.type = attribute_type::NUMERIC;
      else if(attr_type == "string")
	attr.type = attribute_type::STRING;
      else if(attr_type == "nominal")
	{
	  attr.type == attribute_type::NOMINAL;
	  vector<string> values = {"t", "f"}; // HARD CODE
	  attr.setAllValues(values.begin(), values.end());
	}
      else if(attr_type == "date")
	attr.type == attribute_type::DATE;
      else{
	cout << "Type does not exist\n";
	exit(-1);
      }

      attr_list.push_back(attr);
      i++;
    }
  
  return attr_list;

}

vector<vector<string>> MyFIUPgParser::parseRecords()
{
  vector<vector<string>> all_records;

  /* Get all taken courses */
  sql_query = "SELECT * FROM " + courses_table_name + ";"; 
  pqxx::result all_taken_courses_query_result (query_obj.exec(sql_query));
  
  for(pqxx::result::const_iterator result_it = all_taken_courses_query_result. begin(); result_it != all_taken_courses_query_result.end(); ++result_it)
    {
      std::vector<std::string> record;
      for(int i = 0; i < num_of_columns; i++)
	{
	  std::string value;
	  if(std::find(ignored_column_nums.begin(), ignored_column_nums.end(), i) == ignored_column_nums.end())
	    {
	      value = result_it[i].as<std::string>();
	      trimRight(value);
	    }
	  else
	    {
	      value = "?";
	    }
	  record.push_back(value);
	}
      all_records.push_back(record);
    }
  
  /* Print all records */
  for(std::vector<std::string> record : all_records)
    printVec(record);

  return all_records;
  
}
