#pragma once
#include "classification_algorithm.h"
#include "impurity_measure.h"
#include "j48_node.h"
#include <iostream>

/*
TODO: deal with decision trees that don't cover all rules
*/

	class J48DecisionTree : public ClassificationAlgorithm
	{
	public:
		J48DecisionTree();
		/*J48DecisionTree(std::string _class_label);
		J48DecisionTree(ImpurityMeasure* _impurity_measure, std::string _class_label);*/
		J48DecisionTree(relationObj _relation_obj, std::string _class_label);
		J48DecisionTree(relationObj _relation_obj, ImpurityMeasure * _impurity_measure, std::string _class_label);

		~J48DecisionTree();

		void setImpurityMeasure(ImpurityMeasure* _impurity_measure);
		void buildDecisionTree();
		virtual std::string predict(tableRow record);

		template <class InputIterator>
		std::string predictIgnore(tableRow record, InputIterator first, InputIterator last)
		{
			std::vector<int> ignored_attribute_indexes;

			for (InputIterator it = first; it != last; it++)
			{
				std::string ignored_attribute_name = *it;
				int ignored_attribute_index = relation_obj.getIndexOfAttribute(ignored_attribute_name);
				ignored_attribute_indexes.push_back(ignored_attribute_index);
			}

			impurity_measure->setIgnoredAttributes(ignored_attribute_indexes.begin(), ignored_attribute_indexes.end());

			buildDecisionTree();

			std::string predicted_class_label = recPredict(record, root);

			return predicted_class_label;
		}

		void setDefaultClassLabel(std::string _default_class_label_value) { default_class_label_value = _default_class_label_value; }
		//float getClassLabelImpurity();
		void operator<<(int i) { return; }
		friend std::ostream& operator<<(std::ostream& os, const J48DecisionTree& jdt);

	protected:
		j48_node* root;
		//int fanout;
		ImpurityMeasure* impurity_measure;
		void recBuildSubtrees(j48_node* node, relationTable table);
		/* virtual? */ std::string recPredict(tableRow record, j48_node* curr_node);
		std::string default_class_label_value;
		//static void operatorHelper(relationObj& _rel_obj, j48_node* node, int num_of_spaces);

		std::string class_label;

	};
