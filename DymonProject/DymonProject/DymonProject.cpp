// DymonProject.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "date.h"
#include "dateUtil.h"
#include "zero.h"
#include "cashflow.h"
#include "DymonRecordHelper.h"

using namespace utilities;
using namespace std;
using namespace instruments;
using namespace Session;

void RecordTest();
void DateUtilTest();
void CashFlowTest();

int _tmain(int argc, _TCHAR* argv[])
{
	//DateUtilTest();
	//RecordTest();
	CashFlowTest();
}

void ZeroTest(){
	date date0(2012,12,1);
	//cout<<date0.getJudianDayNumber()<<" "<<date0.isBusinessDay()<<endl;
	date date1(2012,12,8);
	date date2(2013,12,1);
	date date3(2012,1,1);

	zero zero1(0.001,1,date2,date0);

	//cout<<date1.getJudianDayNumber()<<" "<<date1.isBusinessDay()<<endl;
	//cout<<"Days inbetween: "<<dateUtil::getDaysBetween(date0, date1)<<endl;
	//cout<<"Business days inbetween: "<<dateUtil::getBizDaysBetween(date1, date2)<<endl;
	//cout<<"Today is "<<dateUtil::getTodayYear()<<" "<<dateUtil::getTodayMonth()<<" "<<dateUtil::getTodayDay()<<endl;
	cout<<"zero1 price is "<<zero1.getPrice()<<endl;
	cout<<"zero2 implied spot rate is "<<zero1.getImpliedSpotRate()<<endl;
}

void DateUtilTest(){
	{
		date date0(2456270);
		date date1(2012,12,8);
		cout<<date0.isEqual(date1)<<endl;} 
	{
		date date0(2011,9,18);
		date date1 = dateUtil::dayRollAdjust(date0, DayRollEnum::Following, "");
		date date2(2011,9,19);
		cout<<date1.isEqual(date2)<<endl;}
	{
		date date0(2011,9,18);
		date date1 = dateUtil::dayRollAdjust(date0, DayRollEnum::Preceding, "");
		date date2(2011,9,16);
		cout<<date1.isEqual(date2)<<endl;}
	{
		date date0(2011,7,30);
		date date1 = dateUtil::dayRollAdjust(date0, DayRollEnum::Mfollowing, "");
		date date2(2011,7,29);
		cout<<date1.isEqual(date2)<<endl;}
	{
		date date0(2011,7,30);
		date date1 = dateUtil::dayRollAdjust(date0, DayRollEnum::Mfollowingbi, "");
		date date2(2011,7,29);
		cout<<date1.isEqual(date2)<<endl;}
	{
		date date0(2011,10,15);
		date date1 = dateUtil::dayRollAdjust(date0, DayRollEnum::Mfollowingbi, "");
		date date2(2011,10,14);
		cout<<date1.isEqual(date2)<<endl;}
	{
		date date0(2012,1,31);
		date date1 = dateUtil::getEndDate(date0, 1, true);
		date date2(2012,2,29);
		cout<<date1.isEqual(date2)<<endl;}
	{
		date date0(2012,10,31);
		date date1 = dateUtil::getEndDate(date0, 4, true);
		date date2(2013,2,28);
		cout<<date1.isEqual(date2)<<endl;}
}

void RecordTest(){
	cout << "******** RecordHelper Test ********" << endl;
	Configuration cfg;
	DymonRecordHelper* recordHelper = new DymonRecordHelper();
	recordHelper->init(cfg);
	for(map<string, set<long>>::iterator outer_iter=DymonRecordHelper::holidayMap.begin(); outer_iter!=DymonRecordHelper::holidayMap.end(); ++outer_iter) {
		for(set<long>::iterator inner_iter=outer_iter->second.begin(); inner_iter!=outer_iter->second.end(); ++inner_iter) {
			cout << outer_iter->first<< " -> " << *inner_iter << endl;
		}
	}
}

void CashFlowTest() {

	date tradeDate(2012,11,2);
	date startDate(2012,10,2);
	date maturityDate(2014,8,13);
	double notional=1000000.0;
	double couponRate=0.04;
	double margin=0.05;
	int paymentFreq=3;

	currency cashFlowCurr=currency(USD,ACT_360, ACT_365, Mfollowing, paymentFreq,1);
	cashflow testCashFlow=cashflow(startDate,tradeDate,couponRate,notional, margin, paymentFreq, maturityDate, cashFlowCurr);

	testCashFlow.printPVs();
}