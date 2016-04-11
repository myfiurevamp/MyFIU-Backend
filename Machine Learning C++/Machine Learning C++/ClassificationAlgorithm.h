#pragma once
class ClassificationAlgorithm
{
public:
	ClassificationAlgorithm();
	~ClassificationAlgorithm();
	virtual void predict() =  0;
};

