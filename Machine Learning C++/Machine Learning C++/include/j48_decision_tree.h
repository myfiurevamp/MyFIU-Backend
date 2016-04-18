#pragma once
#include "classification_algorithm.h"
#include "impurity_measure.h"
#include "j48_node.h"

	class J48DecisionTree : public ClassificationAlgorithm
	{
	public:
		J48DecisionTree();
		J48DecisionTree(std::string _class_label);
		J48DecisionTree(ImpurityMeasure* _impurity_measure, std::string _class_label);
		J48DecisionTree(relation _relation_obj, std::string _class_label);
		J48DecisionTree(relation _relation_obj, ImpurityMeasure * _impurity_measure, std::string _class_label);

		~J48DecisionTree();

		void setImpurityMeasure(ImpurityMeasure* _impurity_measure);
		void J48DecisionTree::buildDecisionTree();
		virtual void predict(attribute class_attribute);
		float getClassLabelImpurity();

		float class_label_impurity;

	protected:
		j48_node* root;
		int fanout;
		ImpurityMeasure* impurity_measure;

		std::string class_label;

	};