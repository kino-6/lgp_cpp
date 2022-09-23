#include "AggregateInfo.h"

AggregateInfo::AggregateInfo(vector<double> lst) {
	this->max_value = 0;
	this->min_value = UINT_MAX;
	this->sum = 0;
	this->sq_sum = 0;
	this->variance = 0;
	this->stddev = 0;

	for (size_t i = 0; i < lst.size(); i++) {
		this->max_value = std::max(this->max_value, lst[i]);
		this->min_value = std::min(this->min_value, lst[i]);
		this->sum += lst[i];
	}

	this->avg = sum / lst.size();

	for (size_t i = 0; i < lst.size(); i++) {
		sq_sum += pow((lst[i] - this->avg), 2);
	}

	this->variance = sq_sum / lst.size();
	this->stddev = sqrt(this->variance);
}

AggregateInfo::~AggregateInfo() {
}

void AggregateInfo::ShowAggregate() {
	cout << 
		"min: " << this->min_value << ", " <<
		"max: " << this->max_value << ", " <<
		"avg: " << this->avg << ", " <<
		//"variance: " << this->variance << ", " <<
		"stddev: " << this->stddev << ", " << endl;
}
