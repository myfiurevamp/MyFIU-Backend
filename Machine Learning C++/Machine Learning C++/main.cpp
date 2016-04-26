#include "stdafx.h"


// Machine Learning C++.cpp : Defines the entry point for the console application.
//

//#include "DataFileParser\ARFFParser\arff_parser.h"

/* debug */
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

	string data_file_string = string("dat/student_transcript.arff");

	/* Open and parse file with parser object, and get relationObj */
	DataFileParser* parser_obj = new ArffParser();
	int open_file_error_num = parser_obj->openFile(data_file_string);
	cout << "Parsing Arff file...\n";
	int parse_file_error_num = parser_obj->parseFile();

	parser_obj->closeFile(); //redundant due to delete parse_obj call; delete SHOULD close file automatically if parser object is implemented correctly
	cout << "Done Parsing Arff file...\n";
	cout << "Extracting Relation Object...\n";
	relationObj relation_obj = parser_obj->getRelationObj();
	cout << "Deleting Parsing Object...\n";
	delete parser_obj;

	/* Create classifier object (classification algorithm), and build model based off of relation and class_label */
	string class_label = "grade_received";
	cout << "Initializing Decision Tree...\n";
	J48DecisionTree* classifier = new J48DecisionTree(relation_obj, class_label); 
	string def = classifier->relation_obj.getTable().getColumn(relation_obj.getIndexOfAttribute(class_label)).getMajorityValue();
	classifier->setDefaultClassLabel(def);
	vector<string> ignored_attributes = { "transcript_id", "course_name", /*"semester_taken",*/ /*"course_num"*/}; //error when only omitting course_num

	//cout << "Building Decision Tree...\n";
	//classifier->buildDecisionTree(); // predict should automatically call buildDecisionTree()
	//cout << "Done building Decision Tree...\n";

	/* Predict "grade_received" class label for record 
	(8, COP 5725, Fall 2016, ? , ? , Principles of Database Management Systems, Computer Programming)
	*/
	vector<string> record_values = 
		{"8", "COP 5727", "Fall 2016", "?", "?", "Principles of Database Management Systems", "Computer Programming"};

	tableRow record = tableRow(record_values.begin(), record_values.end());
	string predicted_class_label = classifier->predictIgnore(record, ignored_attributes.begin(), ignored_attributes.end());

	cout << "Full Decision Tree:\n" << *classifier;

	/* Print record */
	cout << "\nPredicted class label of record (";
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

