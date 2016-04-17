//#include "../../stdafx.h"
#include "j48_decision_tree.h"
#include "ImpurityMeasure\Entropy\Entropy.h"

using namespace std;

J48DecisionTree::J48DecisionTree(string _class_label)
{
	class_label = _class_label;
	impurity_measure = new Entropy();
	buildDecisionTree();
}

J48DecisionTree::J48DecisionTree(ImpurityMeasure* _impurity_measure, string _class_label)
{
	class_label = _class_label;
	impurity_measure = _impurity_measure; // TODO: check if class of ImpurityMeasure object is concrete
	impurity_measure->init(dataset_header, records, _class_label);
}


J48DecisionTree::~J48DecisionTree()
{
}

void J48DecisionTree::buildDecisionTree()
{
	class_label_impurity = impurity_measure->calculate_impurity(class_label);

}

void J48DecisionTree::predict(attribute class_attribute)
{
	return;
}
