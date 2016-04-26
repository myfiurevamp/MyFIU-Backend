
#if (_MSC_VER)
    #include <memory>
#else
    #if __cplusplus<201103L
        #include <tr1/memory>
// import smart pointers utils into std
namespace std {
  using std::tr1::shared_ptr;
  using std::tr1::weak_ptr;
  using std::tr1::enable_shared_from_this;
  using std::tr1::static_pointer_cast;
  using std::tr1::dynamic_pointer_cast;
  using std::tr1::const_pointer_cast;
  using std::tr1::__dynamic_cast_tag;
}
    #else
        #include <memory>
//still have to deal with __dynamic_cast_tag here!
    #endif
#endif

#include <iostream>
#include <pqxx/pqxx>
#include "data_file_parser.h"

/* Debug function */
static void printVec(std::vector<std::string> string_vector)
{
  int i = 0;
  
  for (std::string str : string_vector)
    std::cout << "[" << str << "] ";
  
  std::cout << std::endl;
  return;
  
}

/* Trim whitespace at end of string */
static void trimRight(std::string& str){

  size_t endpos = str.find_last_not_of(" \t");
  
  if(std::string::npos != endpos )
    str = str.substr( 0, endpos+1 );
  
  return;
  
}

class MyFIUPgParser : public DataFileParser
{
  
 public:
  MyFIUPgParser();
  ~MyFIUPgParser();
  
  int openFile(std::string _conn_string);
  int closeFile();
  std::string parseName();
  std::vector<attribute> parseAttributeList();
  std::vector<std::vector<std::string>> parseRecords();
  
  void setCourseTableName(std::string _course_table_name);
  void setTypes(std::vector<std::string> _type_list);
  void setIgnoredColumnNums(std::vector<int> _ignored_column_nums);
  
 private:
  std::string course_table_name;
  int num_of_columns;
  std::string type_list;
  std::vector<int> ignored_column_nums;
  
  
};
