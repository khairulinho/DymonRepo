//created by Hu Kun on 30 Nov 2012
//class for standard IRS with fix to floating legs in one currency.
//rates for fixed and floating in private data members are all in terms of annual rates

#ifndef SWAP_H
#define SWAP_H
#include "currency.h"
#include "date.h"
#include "AbstractInstrument.h"
#include <vector>
#include "zero.h"
#include <tuple>
#include <iterator>
#include "cashflow.h"
#include "cashflowLeg.h"
#include "BuilderCashFlowLeg.h"
#include "RecordHelper.h"

using namespace utilities;
using namespace std;
using namespace enums;

namespace instruments {
	class swap: public AbstractInstrument {
	public:
		//tuple<double rate,date historicalDates,double tenors> floatLegBenchMark
		//contains the Libors obervations historicals across tenors
		swap(date tradeDate, date maturityDate, double notional, double couponRate, vector<double> FLiborRate, currency fixLegCurr, currency floatingLegCurr, int paymentFreqFixLeg, int paymentFreqFloatingLeg, bool rollAccuralDates, RecordHelper::HolidayMap holidayMap);

		~swap();

		cashflowLeg getCashflowLegFix();
		cashflowLeg getCashflowLegFloat();

		/*double getParRate();
		vector<date> getFloatingFixingDate();
		vector<date> getFixLegPaymentDate();
		vector<date> getFloatLegPaymentDate();
		vector<date> getFloatLegAccuralBeginDate();
		double getSwapValue();
		*/



	protected:


	private:

		cashflowLeg _fixCashflowLeg;
		cashflowLeg _floatingCashflowLeg;
		//double _fixLegRate;
		//double _floatLegSpread;
		//tuple<double,date,double> _floatLegBenchMark; //example: Libor floating rate
		//double _notional;
		//date _issueDate;
		//date _maturityDate;
		////swapCurr inclusive of dayCount, dayRoll, payment freq and compound freq
		////annually=1, semi-annual=2, quarterly=4; monthly=12;
		//currency _fixLegCurr;
		//currency _floatLegCurr;

		//double _swapValue;

		////fixing dates should follow float leg payment frequencies.
		//vector<date> _floatingFixingDate;
		//vector<date> _accuralBeginDate;
		//vector<date> _fixLegPaymentDate;
		//vector<date> _floatLegPaymentDate;

		//double _parRate;
		//vector<zero> _zeroStrips;
	};

}
#endif