#include "polynomial.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cfloat>
#include <cmath> //For pow method

using std::istream;
using std::ostream;
using std::string;
using std::stringstream;
using std::fixed;
using std::setprecision;
using std::showpos;

Polynomial::Polynomial(size_t degree) : _degree(degree){
	_coefficients = new float[_degree + 1];
	for (size_t i = 0; i < _degree + 1; i++) {
		_coefficients[i] = 0.0;
	}
}
Polynomial::Polynomial(size_t degree, const float* coefficients): _degree(degree){
	_coefficients = new float[_degree + 1];
	for (size_t i = 0; i < _degree + 1; i++) {
		_coefficients[i] = coefficients[i];
	}
}
Polynomial::Polynomial(const Polynomial& polynomial): _degree(polynomial._degree){
	_coefficients = new float[_degree + 1];
	for (size_t i = 0; i < _degree + 1; i++) {
		_coefficients[i] = polynomial._coefficients[i];
	}
}
Polynomial::~Polynomial(){
	// DO THIS FIRST TO PREVENT MEMORY LEAKS!
	delete[] _coefficients;
}
const Polynomial Polynomial::Sum(const Polynomial& rhs)const{
	//Value to store highest degree of two summed poly's
	size_t highDeg = 0;
	//Variable to determine for loop max
	size_t max = 0;

	if (rhs._degree > _degree)
	{
		highDeg = rhs._degree;
		max = _degree; //To prevent out-of-bounds array access later
	}
	else
	{
		highDeg = _degree;
		max = rhs._degree; // "   "       "   "   "    "       "    "
	}

	//Polynomial object (*eventually returned) to sum
	Polynomial sumPoly(highDeg);

	//Summing elements of this and rhs to be stored in sumPoly polynomial
	size_t i = 0;
	while (i < max+1)
	{
		sumPoly._coefficients[i] = rhs._coefficients[i] + _coefficients[i];
		i++;
	}
	//Adding rest of longest polynomial to sumPoly
	if (rhs._degree > _degree)
	{
		for (size_t j = i; j < rhs._degree+1; j++)
		{
			sumPoly._coefficients[i] = rhs._coefficients[i];
		}
	}
	else if (rhs._degree < _degree)
	{
		for (size_t j = i; j < _degree+1; j++)
		{
			sumPoly._coefficients[i] = _coefficients[i];
		}
	}
	return sumPoly;
}
const Polynomial Polynomial::Subtract(const Polynomial& rhs)const{
	//Value to store highest degree of substracted poly's
	size_t highDeg = 0;
	//Variable to determine while loop max
	size_t max = 0;

	if (rhs._degree > _degree)
	{
		highDeg = rhs._degree;
		max = _degree; //To prevent out-of-bounds array access later

		//Polynomial object (*eventually returned) to sum
		Polynomial subPoly(highDeg);

		//While loop for subtraction
		size_t i = 0;
		while(i < max+1)
		{
			subPoly._coefficients[i] = _coefficients[i] - rhs._coefficients[i];
			i++;
		}
		//In order to complete subtraction, rhs' coefficients must be run through and "added" (negatively) to subPoly
		for (size_t j = i; j < highDeg+1; j++)
		{
			subPoly._coefficients[j] = 0 - rhs._coefficients[i];
		}
		return subPoly;
	}
	else
	{
		highDeg = _degree;
		max = rhs._degree; // "   "       "   "   "    "       "    "

		//Polynomial object (*eventually returned) to sum
		Polynomial subPoly(highDeg);

		//While loop for subtraction
		size_t i = 0;
		while (i < max+1)
		{
			subPoly._coefficients[i] = _coefficients[i] - rhs._coefficients[i];
			i++;
		}

		//NOTE: Because [this] is greater in degree than rhs, we don't have to worry about "completing" subtraction in another loop
		//		Instead, we simply load the rest of _coefficients into subPoly._coefficients.
		for (size_t j = i; j < highDeg+1; j++)
		{
			subPoly._coefficients[j] = _coefficients[j];
		}
		return subPoly;
	}
}
const Polynomial Polynomial::Minus()const{
	Polynomial retVal(*this);
	for (size_t i = 0; i < _degree + 1; i++) {
		retVal._coefficients[i] *= -1;
	}
	return retVal;
}
const Polynomial Polynomial::Multiply(const Polynomial& rhs)const{

	//Returned poly with degree that is rhs._degree * _degree + 1
	Polynomial multPoly(_degree+rhs._degree);

	if (_degree < rhs._degree)
	{
		//Nested for loop "distributes" _coefficients[i] to each member of rhs._coefficients
		for (size_t i = 0; i < _degree+1; i++)
		{
			for (size_t j = 0; j < rhs._degree+1; j++)
			{
				multPoly._coefficients[i+j] += _coefficients[i] * rhs._coefficients[j];
			}
		}
		return multPoly;
	}
	else
	{
		//Nested for loop "distributes" rhs._coefficients[i] to each member of _coefficients
		for (size_t i = 0; i < rhs._degree+1; i++)
		{
			for (size_t j = 0; j < _degree+1; j++)
			{
				multPoly._coefficients[i+j] += rhs._coefficients[i] * _coefficients[j];
			}
		}
		return multPoly;
	}
}
const Polynomial Polynomial::Divide(const Polynomial& rhs)const{
	return Polynomial(0);
}
const Polynomial Polynomial::Derive()const{
	//Iterating through each coefficient and multiplying it by i (a la the Power Rule of calculus)
	for (size_t i = 0; i < _degree+1; i++)
	{
		_coefficients[i] *= i; //Multiplied by the degree
	}

	//Creating temporary float to store coefficients
	float temp;
	//Downshifting all _coefficients elements a degree
	for (size_t i = 0; i < _degree; i++)
	{
		temp = _coefficients[i];
		_coefficients[i] = _coefficients[i+1];
		_coefficients[i+1] = temp;
	}

	//Creating new polynomial with _degree one less than [this]
	Polynomial derivedPoly(_degree-1);
	//Creating shallow copy of [this]._coefficients that will be returned
	for (size_t i = 0; i < derivedPoly._degree+1; i++)
	{
		derivedPoly._coefficients[i] = _coefficients[i];
	}

	return derivedPoly;
}
float Polynomial::Evaluate(float x)const{
	//Returned evaluation
	float answer = 0;
	for (size_t i = 0; i < _degree+1; i++)
	{
		answer += _coefficients[i]*pow(x, i); //Adding product of coefficient * x^i
	}

	return answer;
}
float Polynomial::Integrate(float start, float end)const{
	return FLT_MAX;
}
const Polynomial& Polynomial::operator=(const Polynomial& rhs){
	if (&rhs == this){
		return *this;
	}
	if (_degree != rhs._degree){
		if (_coefficients){
			delete[] _coefficients;
		}
		_degree = rhs._degree;
		_coefficients = new float[_degree + 1];
	}
	for (size_t i = 0; i < _degree + 1; i++) {
		_coefficients[i] = rhs._coefficients[i];
	}
	return *this;
}
bool Polynomial::Equals(const Polynomial& rhs)const{
	if (_degree != rhs._degree){
		return false;
	}
	for (size_t i=0; i < _degree; i++){
		if (abs(_coefficients[i] - rhs._coefficients[i]) > 0.0001){
			return false;
		}
	}
	return true;
}
string Polynomial::ToString()const{
	stringstream ss;
	for (size_t i = _degree; i > 0; i--) {
		ss << showpos << fixed << setprecision(2) << _coefficients[i] << "x^" << i << " ";
	}
	ss << showpos << fixed << setprecision(2) << _coefficients[0];
	return ss.str();
}
ostream& Polynomial::Write(ostream& output)const{
	output << _degree << " ";
	for (size_t i = 0; i < _degree + 1; i++) {
		output << _coefficients[i] << " ";
	}
	return output;
}
istream& Polynomial::Read(istream& input){
	size_t degree;
	input >> degree;
	if (input.fail()){
		return input;
	}
	float* coefficients = new float[degree + 1];
	for (size_t i = 0; i < degree + 1; i++) {
		input >> coefficients[i];
		if (input.fail()){
			delete[] coefficients;
			return input;
		}
	}

	if (degree != _degree){
		if (_coefficients){
			delete[] _coefficients;
		}
		_degree = degree;
		_coefficients = coefficients;
	}else{
		for (size_t i = 0; i < _degree + 1; i++) {
			_coefficients[i] = coefficients[i];
		}
		delete[] coefficients;
	}
	return input;
}
