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

	ArffParser* p = new ArffParser();
	int res = p->openFile("TestData\\playing_tennis.arff");
	int error = p->parseFile();
	p->closeFile();

	string relation_name = p->getRelationName();
	vector<attribute> dataset_header = p->getDatasetHeader();
	vector<vector<string>> records = p->getRecords();

	J48DecisionTree* classifier = new J48DecisionTree(); 
	error = classifier->initDataset(dataset_header, records);

	string class_label = "PlayTennis";
	classifier->initClassLabel(class_label);
	classifier->buildDecisionTree();
	cout << "Class Label Impurity (" << class_label << "): " << classifier->getClassLabelImpurity() << endl;
	





    return 0;
}

