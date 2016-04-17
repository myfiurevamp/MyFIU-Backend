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

	ClassificationAlgorithm* algo = new J48DecisionTree();
	error = algo->initDataset(dataset_header, records);
	cout << "initDataset result: " << error << endl;
	//cout << "[" << *it << "]" << endl;


	//printVec(v);

	//vector<attribute> dataset_header;
	//vector<vector<string>> records;

	//DataFileParser* arff_parser = new ArffParser();
	//arff_parser->openFile("TestData/playing_tennis.arff"); // put directory of file in XML file
	//arff_parser->parseFile();
	//dataset_header = arff_parser->getDatasetHeader();
	//records = arff_parser->getRecords();

	//ClassificationAlgorithm* decision_tree = new J48DecisionTree();
	//decision_tree->initDataset(dataset_header, records);

	//attribute class_label;
	//class_label.name = "PlayTennis";
	//class_label.type = attribute_type::NOMINAL;
	//class_label.values = vector<string>{ "yes", "no" };

	//decision_tree->predict(class_label); // get from XML file?

    return 0;
}

