//#include "../../stdafx.h"
#include "j48_decision_tree.h"
#include "ImpurityMeasure\Entropy\Entropy.h"

using namespace std;

J48DecisionTree::J48DecisionTree(/*string _class_label*/)
{
	//class_label = _class_label;
	impurity_measure = new Entropy();
	//impurity_measure->init(dataset_header, records/*, _class_label*/);
	//buildDecisionTree();
}

J48DecisionTree::J48DecisionTree(ImpurityMeasure* _impurity_measure/*, string _class_label*/)
{
	//class_label = _class_label;
	impurity_measure = _impurity_measure; // TODO: check if class of ImpurityMeasure object is concrete
	//impurity_measure->init(dataset_header, records/*, _class_label*/);
}


J48DecisionTree::~J48DecisionTree()
{
}

void J48DecisionTree::buildDecisionTree()
{
	if (impurity_measure != NULL)
		cout << "not null\n";
	else cout << "null\n";

	impurity_measure->init(dataset_header, records);

	class_label_impurity = impurity_measure->calculate_impurity(class_label_index);

	/* Find first attribute to split on */
	int i = 0;
	int minimum_impurity;
	for (attribute dataset_header_attribute : dataset_header) {

		if (i == class_label_index)
			continue;



		i++;
	}

}

void J48DecisionTree::predict(attribute class_attribute)
{
	return;
}

float J48DecisionTree::getClassLabelImpurity()
{
	return class_label_impurity;
}
