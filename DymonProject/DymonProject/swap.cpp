//created by Hu Kun 04 Dec 2012
//rewrote again with cashflow constructs by Kun 16 Dec 2012
#include "Swap.h"
#include <iterator>
#include "date.h"
#include "dateUtil.h"
#include "cashflow.h"
#include "cashflowLeg.h"
#include "CashFlowLegBuilder.h"
#include "AbstractPricer.h"

using namespace instruments;
using namespace utilities;
using namespace std;
using namespace enums;

void Swap::deriveDates(){
	_expiryDate = date(_spotDate.getJudianDayNumber()+_daysToMty);
	_deliveryDate = dateUtil::dayRollAdjust(_expiryDate, _market.getDayRollSwapConvention(), _market.getCurrencyEnum());
}

void Swap::buildFixedLeg(){
	CashFlowLegBuilder builder = CashFlowLegBuilder(this);
	builder.setPaymentFreq(getPayFreqFixed());
	builder.setDayCountEnum(getDayCountFixed());
	builder.setPaymentNumber(getCouponNumberFixed());
	_fixedCashflowLeg.setCashFlowVector(*builder.build());
}

void Swap::buildFloatLeg(){
	CashFlowLegBuilder builder = CashFlowLegBuilder(this);
	builder.setPaymentFreq(getPayFreqFloat());
	builder.setDayCountEnum(getDayCountFloat());
	builder.setPaymentNumber(getCouponNumberFloat());
	_floatCashflowLeg.setCashFlowVector(*builder.build());
}

void Swap::printCashflowLegFix() {
	_fixedCashflowLeg.printCashFlowLeg();
}

void Swap::printCashflowLegFloat() {
	_floatCashflowLeg.printCashFlowLeg();
}