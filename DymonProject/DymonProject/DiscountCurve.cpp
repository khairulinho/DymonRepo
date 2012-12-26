//created by Wang Jianwei on 1 Dec 2012

#include "DiscountCurve.h"
#include <cmath>
#include "dateUtil.h"
#include "Enums.h"

using namespace utilities;
using namespace std;

typedef tuple<date, double> point;
typedef AbstractCurve super;

void DiscountCurve::insertLineSection(AbstractInterpolator* lineSection){
	super::insertLineSection(lineSection);
}

double DiscountCurve::getValue(date date0){
	return super::getValue(date0);
}

double DiscountCurve::getDiscountFactor(date date0){
	return getValue(date0);
}

double DiscountCurve::getFLiborRate(date forwardStartDate,date forwardEndDate,enums::DayCountEnum dayCount) {
	double cal=getDiscountFactor(forwardStartDate)/getDiscountFactor(forwardEndDate);

	return (cal-1)/dateUtil::getAccrualFactor(forwardStartDate,forwardEndDate,dayCount);
}

std::string DiscountCurve::toString(){
	return "\nYield "+AbstractCurve::toString();
}