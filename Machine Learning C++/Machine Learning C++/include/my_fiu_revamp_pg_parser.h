/*

THINGS TO CHANGE:

-define macros to have the correct parameters to login to database
-course table name (i.e., taken_course -> courses)
-ignored column nums to have indexes of columns whose values are to be ignored (i.e. possibly NULL values such as grade) 

*/

#include <iostream>
#include <vector>
#include <pqxx/pqxx>
#include <algorithm>

#define DBNAME "myfiurevamp" //CHANGE THESE MACROS TO HAVE THE RIGHT LOGIN PARAMETERS
#define USER "postgres"
#define PASSWORD "JAA~cen4010"
#define HOSTADDR "162.243.21.173"
#define PORT "5432"

std::string courses_table_name = "taken_course"; // CHANGE FROM TAKEN_COURSE TO COURSES (without capitalization, of course)
int num_of_columns;
std::vector<std::string> column_names;
std::vector<std::vector<std::string> > all_records;
std::vector<int> ignored_column_nums = {5,6,7}; // CHANGE THIS TO ONLY 5 (DELETE 6 AND 7)

static void printVec(std::vector<std::string> string_vector)
{
  int i = 0;

  for (std::string str : string_vector)
      std::cout << "[" << str << "] ";
  
std::cout << std::endl;
  return;

}

static void trimRight(std::string& str){

 size_t endpos = str.find_last_not_of(" \t");
 
 if(std::string::npos != endpos )
    {
      str = str.substr( 0, endpos+1 );
    }

 return;

}

int main (int argc, char** argv)
{ 
  std::string conn_string = "";
  std::vector<std::pair <std::string, std::string> > conn_parameters;
   
  conn_parameters.push_back(std::pair<std::string, std::string>("dbname", DBNAME));
  conn_parameters.push_back(std::pair<std::string, std::string>("user", USER));
  conn_parameters.push_back(std::pair<std::string, std::string>("password", PASSWORD));
  conn_parameters.push_back(std::pair<std::string, std::string>("hostaddr", HOSTADDR));
  conn_parameters.push_back(std::pair<std::string, std::string>("port", PORT));

  for(std::pair<std::string, std::string> parameter_pair : conn_parameters)
     {
       std::string parameter_string = parameter_pair.first + "=" +parameter_pair.second + " ";
       conn_string += parameter_string;
     }

  conn_string.pop_back();

  std::cout <<  "Connection String: \"" << conn_string << "\"\n";
  pqxx::connection conn(conn_string);

  if(conn.is_open())
    {
      std::string sql_query;
      std::string buffer;

      std::cout << "Connected to " << DBNAME << "!\n";

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
	      else{
		value = "?";
	      }
      	      record.push_back(value);
      	    }
      	  all_records.push_back(record);
      	}
    
      /* Print all records */
      for(std::vector<std::string> record : all_records)
	  printVec(record);
      
      /* Disconnect from database */
      conn.disconnect();
      std::cout << "Disconnected from " << DBNAME << "!\n";
    }
  
  else
    {
      std::cout << "Error: Could not connect to " << DBNAME << "! Terminating...\n";
      exit(-1);
    }
  return 0;
}
