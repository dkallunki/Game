// Dana Kallunki
// April 9, 2015
// CS 333 Spring 2015
// calc.h 
// dots and boxes assiognment

#ifndef CALC_H
#define CALC_H

#if 0
class calc {  // THIS CLASS ONLY HANDLES "int"
public:
	// multiply method int = x * y
	int multiply(int x, int y);
	// add method int = x + y
	int add(int x, int y);
	// sub method int = x - y
	int sub(int x, int y);
private:
};

// multiply method int = x * y
int calc::multiply(int x, int y)
{
	return(x * y);
}
// add method int = x + y
int Calc::add(int x, int y);
{
	return(x + y);
}
// sub method int = x + y
int Calc::sub(int x, int y);
{
	return(x - y);
}
#endif


template <class A_Type> class calc { // THIS CLASS HANDLES "int, double, unsigned, float, etc"
public:
	// multiply method int = x * y
	A_Type multiply(A_Type x, A_Type y);
	// add method int = x + y
	A_Type add(A_Type x, A_Type y);
	// sub method int = x - y
	A_Type sub(A_Type x, A_Type y);
private:
};


// sub_function type = x - y
template <class type> type sub_function(type x, type y)
{
	return(x - y);
}

// multiply method A_Type = x * y
template <class A_Type> A_Type calc <A_Type>::multiply(A_Type x, A_Type y)
{
	return(x * y);
}
// add method A_Type = x + y
template <class A_Type> A_Type calc <A_Type>::add(A_Type x, A_Type y)
{
	return(x + y);
}

// sub method A_Type = x - y
template <class A_Type> A_Type calc <A_Type>::sub(A_Type x, A_Type y)
{
	A_Type result = sub_function(x, y);
	return(result);
}


#endif
