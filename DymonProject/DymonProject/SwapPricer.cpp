//created by Hu Kun on 16 Dec 2012
#include "SwapPricer.h"
#include "AbstractPricer.h"
#include "cashflowLeg.h"

using namespace std;
using namespace instruments;

double SwapPricer::getMPVFixLeg(cashflowLeg* fixCashflowLeg,DiscountCurve* discountCurve) {
	_fixCashflowLeg=fixCashflowLeg;
	_discountCurve=discountCurve;
	vector<cashflow> cfVector=fixCashflowLeg->getCashFlowVector();
	vector<cashflow>::iterator it=cfVector.begin();
	double sum=0.0;
	int count=0;
	for (;it!=cfVector.end();it++) {
		cashflow aCF=*it;
		date paymentDate=aCF.getPaymentDate();
		sum+=aCF.getNotional()*aCF.getAccuralFactor()*aCF.getCouponRate()*_discountCurve->getDiscountFactor(paymentDate);
	}

	return sum;
}

double SwapPricer::getMPVFloatLeg(cashflowLeg* floatCashflowLeg,DiscountCurve* discountCurve) {
	_floatCashflowLeg=floatCashflowLeg;
	_discountCurve=discountCurve;
	vector<cashflow> cfVector=floatCashflowLeg->getCashFlowVector();
	vector<cashflow>::iterator it=cfVector.begin();
	double sum=0.0;
	int count=0;
	for (;it!=cfVector.end();it++) {
		cashflow aCF=*it;
		date accrualEndDate=aCF.getAccuralEndDate();
		date accrualStartDate=aCF.getAccuralStartDate();

		//Market cashflowCurr=aCF.getCashFlowCurr();
		//double FLiborRate=aDiscountCurve->getFLiborRate(accrualStartDate,accrualEndDate,cashflowCurr.getDayCountSwapConvention());
		//sum+=aCF.getNotional()*aCF.getAccuralFactor()*(FLiborRate)*(_pricingDiscountCurve->getDiscountFactor(aCF.getPaymentDate()));
	}

	return sum;
}


double SwapPricer::calFLiborRate(date forwardStartDate, date forwardEndDate, double accuralFactor) {
   return (_discountCurve->getDiscountFactor(forwardStartDate)/ _discountCurve->getDiscountFactor(forwardEndDate)-1)/accuralFactor;
}

double SwapPricer::getMPV(){
   return 0;
}

double SwapPricer::getMPV(cashflowLeg* fixCashflowLeg,cashflowLeg* floatCashflowLeg,DiscountCurve* aDiscountCurve) {
   _MPV=getMPVFixLeg(fixCashflowLeg,aDiscountCurve)-getMPVFloatLeg(floatCashflowLeg,aDiscountCurve);
   return _MPV;
}

double SwapPricer::getParRate(cashflowLeg* floatCashflowLeg,cashflowLeg* fixCashflowLeg,DiscountCurve* discountCurve) {

	_floatCashflowLeg=floatCashflowLeg;
	_fixCashflowLeg=fixCashflowLeg;
	_discountCurve=discountCurve;
	vector<cashflow> cfVector=fixCashflowLeg->getCashFlowVector();
	vector<cashflow>::iterator it=cfVector.begin();
	double denom=0.0;

	for (;it!=cfVector.end();it++) {
		cashflow aCF=*it;
		date paymentDate=aCF.getPaymentDate();
		denom+=aCF.getNotional()*aCF.getAccuralFactor()*(_discountCurve->getDiscountFactor(paymentDate));
	}

	_parRate=getMPVFloatLeg(floatCashflowLeg,_discountCurve)/denom;
	return _parRate;
}

