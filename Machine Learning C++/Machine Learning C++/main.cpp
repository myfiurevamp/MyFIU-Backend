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



int main()
{

	using namespace std;

	/* Open and parse file with parser object */
	DataFileParser* p = new ArffParser();
	int res = p->openFile("TestData\\playing_tennis.arff");
	int error = p->parseFile();
	p->closeFile();

	/* Get relation name, attributes, and records from parse object */
	string relation_name = p->getRelationName();
	vector<attribute> all_attributes = p->getRelationHeader();
	vector<vector<string>> records = p->getRecords();

	/* Create relation object */
	relationHeader header = relationHeader(all_attributes);
	relationData data = relationData(records);
	relation relation_obj = relation(relation_name, all_attributes, records);

	/* Create classifier object (classification algorithm), and build model based off of relation and class_label */
	string class_label = "PlayTennis";
	J48DecisionTree* classifier = new J48DecisionTree(relation_obj, class_label); 
	classifier->buildDecisionTree();
	cout << "Class Label Impurity (" << class_label << "): " << classifier->getClassLabelImpurity() << endl;

	//classifier->initClassLabel(class_label);


    return 0;
}

