/*
 
 THINGS TO CHANGE:
 
 -define macros to have the correct parameters to login to database
 -course table name (i.e., taken_course -> courses)
 -ignored column nums to have indexes of columns whose values are to be ignored (i.e. possibly NULL values such as grade)
 -ignore attributes to match Alastair's schema
 
 */

#include "stdafx.h"
#include "include/json.h"
#include "include/json-forwards.h"
//#include "json/writer.h"

#include <iostream>
//#include "include/my_fiu_revamp_pg_parser.h"

// #define DBNAME "myfiurevamp" //CHANGE THESE MACROS TO HAVE THE RIGHT LOGIN PARAMETERS
// #define USER "postgres"
// #define PASSWORD "JAA~cen4010"
// #define HOSTADDR "162.243.21.173"
// #define PORT "5432"

// std::string conn_string;

static void printVec(std::vector<std::string> string_vector)
{
  int i = 0;

  for (std::string str : string_vector)
    std::cout << "[" << str << "] ";
  std::cout << std::endl;
  return;

}

int main(int argc, char* argv[])
{
	using namespace std;

	vector<vector<string>> records; 
	int num_of_columns = 7;
	records.reserve(num_of_columns);

	string taken_courses_json_string = argv[1];

	// string taken_courses_json_string = "[{\"pantherId\" : \"4070455\", \"id\" : \"CNT 4713\", \"name\" : \"Net-centric Computing\", \"semesterMonth\" : \"Fall\", \"semesterYear\" : \"2015\", \"grade\" : \"A-\", \"units\" : \"3\"}, {\"pantherId\" : \"4070466\", \"id\" : \"CIS 4911\", \"name\" : \"Senior Design\", \"semesterMonth\" : \"Spring\", \"semesterYear\" : \"2016\", \"grade\" : \"B+\", \"units\" : \"3\"}]"; 


	string predicted_courses_json_string = argv[2];

	// string predicted_courses_json_string =  "[{\"pantherId\" : \"4070455\", \"id\" : \"CNT 4713\", \"name\" : \"Net-centric Computing\", \"semesterMonth\" : \"Fall\", \"semesterYear\" : \"2015\", \"grade\" : \"A-\", \"units\" : \"3\"}, {\"pantherId\" : \"4070466\", \"id\" : \"CIS 4911\", \"name\" : \"Senior Design\", \"semesterMonth\" : \"Spring\", \"semesterYear\" : \"2016\", \"grade\" : \"B+\", \"units\" : \"3\"}]"; 

	istringstream json_string_stream = istringstream(taken_courses_json_string);

	Json::Value json_values;
	json_string_stream >> json_values;

	int row_num = 0;

	for(auto course : json_values)
	  {

	    vector<string> record;
	    string pantherId = course["pantherId"].asString();
	    string courseId = course["id"].asString();
	    string name = course["name"].asString();
	    string semesterMonth = course["semesterMonth"].asString();
	    string semesterYear = course["semesterYear"].asString();
	    string grade = course["grade"].asString();
	    string units = course["units"].asString();
	    
	    record.push_back(pantherId);
	    record.push_back(courseId);
	    record.push_back(name);
	    record.push_back(semesterMonth);
	    record.push_back(semesterYear);
	    record.push_back(grade);
	    record.push_back(units);
	    
	    records.push_back(record);

	    // printVec(record);

	  }

	attribute attr0;
	attr0.name = "pantherId";
	attr0.type = attribute_type::STRING;
	
	attribute attr1;
	attr1.name = "courseId";
	attr1.type = attribute_type::STRING;

	attribute attr2;
	attr2.name = "name";
	attr2.type = attribute_type::STRING;

	attribute attr3;
	attr3.name = "semesterMonth";
	attr3.type = attribute_type::STRING;

	attribute attr4;
	attr4.name = "semesterYear";
	attr4.type = attribute_type::STRING;

	attribute attr5;
	attr5.name = "grade";
	attr5.type = attribute_type::STRING;

	attribute attr6;
	attr6.name = "units";
	attr6.type = attribute_type::NUMERIC;

	vector<attribute> list;

	list.push_back(attr0);
	list.push_back(attr1);
	list.push_back(attr2);
	list.push_back(attr3);
	list.push_back(attr4);
	list.push_back(attr5);
	list.push_back(attr6);

	attributeList attr_list = attributeList(list.begin(), list.end());
	relationHeader header = relationHeader(attr_list);

	relationTable table = relationTable(records.begin(), records.end());
	
	relationObj relation_obj = relationObj("taken_course", header, table);
       
	string class_label = "grade";
	//cout << "Initializing Decision Tree...\n";
	J48DecisionTree* classifier = new J48DecisionTree(relation_obj, class_label); 
	string def = classifier->relation_obj.getTable().getColumn(relation_obj.getIndexOfAttribute(class_label)).getMajorityValue();
	classifier->setDefaultClassLabel(def);

	vector<string> ignored_attributes = { "pantherId"/*, "course_name", "tc_credits" /*"semester_taken",*/ /*"course_num"*/};

	classifier->buildDecisionTree();

	/* Classify new records */
	Json::Value predicted_records;

	istringstream new_json_string_stream = istringstream(predicted_courses_json_string);
	new_json_string_stream >> predicted_records;

	for(auto course : predicted_records)
	  {
	    //cout << "hi" << endl;
	    vector<string> record;
	    string pantherId = course["pantherId"].asString();
	    string courseId = course["id"].asString();
	    string name = course["name"].asString();
	    string semesterMonth = course["semesterMonth"].asString();
	    string semesterYear = course["semesterYear"].asString();
	    string grade = course["grade"].asString();
	    string units = course["units"].asString();
	    
	    record.push_back(pantherId);
	    record.push_back(courseId);
	    record.push_back(name);
	    record.push_back(semesterMonth);
	    record.push_back(semesterYear);
	    record.push_back(grade);
	    record.push_back(units);

	    //printVec(record);

	    Json::Value event;
	    tableRow row = tableRow(record.begin(), record.end());
	    string predicted_grade = classifier->predict(row);
	    event["pantherId"] = pantherId;
	    event["courseId"] = courseId;
	    event["name"] = name;
	    event["semesterMonth"] = semesterMonth;
	    event["semesterYear"] = semesterYear;
	    event["grade"] = predicted_grade;
	    event["units"] = units;

	    cout << event  << endl;

	  }   
	delete classifier;

	// vector<pair <string, string> > conn_parameters;
	
	// conn_parameters.push_back(pair<string, string>("dbname", DBNAME));
	// conn_parameters.push_back(pair<string, string>("user", USER));
	// conn_parameters.push_back(pair<string, string>("password", PASSWORD));
	// conn_parameters.push_back(pair<string, string>("hostaddr", HOSTADDR));
	// conn_parameters.push_back(pair<string, string>("port", PORT));
	
	// for(pair<string, string> parameter_pair : conn_parameters)
	//   {
	//     string parameter_string = parameter_pair.first + "=" +parameter_pair.second + " ";
	//     conn_string += parameter_string;
        //   }
	
	// conn_string.pop_back();



	
	/* Open and parse file with parser object, and get relationObj */
	// MyFIUPgParser* parser_obj = new MyFIUPgParser();
	// parser_obj->setCourseTableName("taken_course"); // CHANGE "taken_course" TO "course"
	// int open_file_error_num = parser_obj->openFile(conn_string);
	// parser_obj->closeFile();
	// parser_obj->setTypes(vector<string>({"numeric", "string", "string", "string", "nominal", "string", "numeric", "string"})); //CHANGE TO "numeric", "string", "string", "string", "string", "string", "numeric"
	// parser_obj->setIgnoredColumnNums({5,6,7}); // CHANGE "5,6,7" TO ONLY "5"

	// cout << "Parsing Student Data...\n";
	// int parse_file_error_num = parser_obj->parseFile();

	// parser_obj->closeFile(); //redundant due to delete parse_obj call; delete SHOULD close file automatically if parser object is implemented correctly
	// cout << "Done Parsing Student Data...\n";
	// cout << "Extracting Relation Object...\n";
	// relationObj relation_obj = parser_obj->getRelationObj();
	// cout << "Deleting Parsing Object...\n";
	// delete parser_obj;

	/* Create classifier object (classification algorithm), and build model based off of relation and class_label */


 // CHANGE TO MATCH ALASTAIR'S SCHEMA

	//cout << "Building Decision Tree...\n";
	//classifier->buildDecisionTree(); // predict should automatically call buildDecisionTree()
	//cout << "Done building Decision Tree...\n";

	// /* Predict "grade_received" class label for record 
	// (8, COP 5725, Fall 2016, ? , ? , Principles of Database Management Systems, Computer Programming)
	// */
	

	//vector<string> record_values = 
	// {"3575889", "COP 5727", "Principles of Database Management Systems", "Fall", "2017", "?", "3"};


		
	/* Predict "PlayTennis" class label for record (14,Rain,Mild,High,Strong,No) */
	//vector<string> record_values = {"15", "Rain", "Hot", "High", "Weak", "No"};
	//tableRow record = tableRow(record_values.begin(), record_values.end());
	//string predicted_class_label = classifier->predict(record);

	/* Print record */
	/*cout << "\nPredicted class label of record (";
	int i = 0;
	for (string value : record_values)
	{
		if (i == 0)
			cout << value;
		else
			cout << "," << value;

		i++;
	}
	cout <<  "): " << predicted_class_label << endl;
*/
	//delete classifier;


	return 0;
}

