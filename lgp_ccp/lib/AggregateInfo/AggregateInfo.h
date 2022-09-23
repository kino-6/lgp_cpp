#include "std_lib.h"
#include "SLGP_Common.h"

class AggregateInfo
{
	public:
		double avg;
		double max_value;
		double min_value;
		double sum;
		double sq_sum;
		double variance;
		double stddev;

		AggregateInfo(vector<double> lst);
		~AggregateInfo();
		void ShowAggregate();
};