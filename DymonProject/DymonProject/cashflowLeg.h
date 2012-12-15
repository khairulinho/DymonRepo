#ifndef CASHFLOWLEG_H
#define CASHFLOWLEG_H

#include "cashflow.h"
#include "currency.h"
#include "Enums.h"
#include "date.h"
#include "dateUtil.h"
#include <vector>
#include <iterator>

using namespace utilities;
using namespace std;
using namespace enums;

namespace instruments {
	class cashflowLeg {

	public:
		cashflowLeg();
		cashflowLeg(vector<cashflow> cashflowLeg);
		~cashflowLeg();
		
		vector<cashflow> getCashFlowVector();
		cashflowLeg getCashFlowLeg();

		void setCashFlowLeg(vector<cashflow> cashflowLeg);
		
		
	private:
		vector<cashflow> _cashflowLeg;

	};

}



#endif