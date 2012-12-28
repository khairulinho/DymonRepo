//created by Wang Jianwei on 01 Dec 2012
#ifndef LOGLINEARINTERPOLATOR_H
#define LOGLINEARINTERPOLATOR_H
#include "AbstractInterpolator.h"
#define NaN -999999

namespace utilities{
	template<typename T> class LogLinearInterpolator: public AbstractInterpolator<T>{

	public:

		typedef tuple<T, double> point;

		LogLinearInterpolator(point startPoint, point endPoint):
		AbstractInterpolator(startPoint, endPoint){
			_slope = NaN;
			_algo = enums::LOGLINEAR;
		}

		virtual point interpolate(T xVal);

	private:

		double _slope;
	};

	template <class T> 
	point LinearInterpolator<T>::interpolate(T xVal){
		dateInRangeCheck(xVal);
		if (_slope == NaN){
			double startVal = std::get<1>(_startPoint);
			double endVal = std::get<1>(_endPoint);
			double yDiff = log(endVal) - log(startVal);
			double xDiff = std::get<0>(_endPoint) - std::get<0>(_startPoint);
			_slope = yDiff / xDiff;
		}
		double  yVal = _slope*(xVal - std::get<0>(_startPoint))+ log(std::get<1>(_startPoint));
		return point(xVal, yVal);
	}
}
#endif