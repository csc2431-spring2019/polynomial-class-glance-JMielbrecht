#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <string>
using std::istream;
using std::ostream;
using std::string;

class Polynomial{
	size_t _degree;
	float* _coefficients;
public:
	//Constructor that initializes poly object with _degree param
	Polynomial(size_t);
	//Constructor that takes _degree and pointer to _coefficients as a param
	Polynomial(size_t, const float*);
	//Copy constructor
	Polynomial(const Polynomial&);
	//Destructor
	~Polynomial();

	// Sums two polynomials
	//Params: polynomial to be summed with [this]
	//Returns: Polynomial as sum
	//Error handling: None
	const Polynomial Sum(const Polynomial&)const;
	// Subtracts poly param from [this] poly
	//Params: polynomial object
	//Returns: Polynomial as difference
	//Error handling: None
	const Polynomial Subtract(const Polynomial&)const;
	// Converts each coefficient of poly to opposite sign
	//Params: none
	//Returns: "Opposite-signed" Polynomial object
	//Error handling: None
	const Polynomial Minus()const;
	// Multiplies two Polynomial objects
	//Params: Polynomial object to multiply [this] by
	//Returns: Product as a Polynomial object
	//Error handling: None
	const Polynomial Multiply(const Polynomial&)const;
	const Polynomial Divide(const Polynomial&)const;
	// Finds derivative of [this] Polynomial object
	//Params: none
	//Returns: Derivative os a Polynomial object
	//Error handling: None
	const Polynomial Derive()const;
	// Evaluates [this] for passed value of X
	//Params: Value for X to be evaluated
	//Returns: Evaluation as float
	//Error handling: None
	float Evaluate(float)const;
	float Integrate(float, float)const;
	const Polynomial& operator=(const Polynomial&);
	// Converts polynomial to a string
	//Params: none
	//Returns: Polynomial as a string
	//Error handling: None
	string ToString()const;
	// Compares two polynomials
	//Params: Polynomial object to compare with [this]
	//Returns: true/false (whether or not they are equivalent)
	//Error handling: None
	bool Equals(const Polynomial&)const;
	// Outputs "unformatted" polynomial to the specified output stream
	//Params: output stream
	//Returns: output stream (used in cascading ops)
	//Error handling: None
	ostream& Write(ostream&)const;
	// Reads polynomial from input stream
	//Params: Input stream
	//Returns: input stream (used in cascading ops)
	//Error handling: None
	istream& Read(istream&);

};



#endif
