#pragma once
#include "../classification_algorithm.h"
#include "ImpurityMeasure\impurity_measure.h"
#include "j48_node.h"

	class J48DecisionTree : public ClassificationAlgorithm
	{
	public:
		J48DecisionTree(std::string _class_label);
		J48DecisionTree(ImpurityMeasure* _impurity_measure, std::string _class_label);
		~J48DecisionTree();

		void J48DecisionTree::buildDecisionTree() {};

		virtual void predict(attribute class_attribute);

	protected:
		j48_node* root;
		int fanout;
		ImpurityMeasure* impurity_measure;

		std::string class_label;
		float class_label_impurity;

	};