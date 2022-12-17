// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <exception>
#include <string>

//MT: CUSTOM EXCEPTION CLASS
struct MTCustomException : public std::exception {
    const char * what() const throw() {
        return "MT Custom Exception";
    }
};

bool do_even_more_custom_application_logic()
{
    // TODO: Throw any standard exception
    std::cout << "Running Even More Custom Application Logic." << std::endl;

    //MT: CREATE OVERFLOW SITUATION BY ADDING num1 + num2
    int num1 = 2147483644;
    int num2 = 20;                  //MT: CREATES AN OVERFLOW RESULT
    //int num2 = 2;                 //MT: TEST WITHOUT OVERFLOW TO MAKE SURE EXCEPTION IS BYPASSED.

    if (num1 < INT_MAX - num2) {    //MT: INT_MAX = +2147483647
        int result = num1 + num2;
        std::cout << result << std::endl;
    }
    else {                          //MT: standard exception = std::overflow_error
        throw std::overflow_error("Overflow Error\n");
    }
    return true;
}
void do_custom_application_logic()
{
    // TODO: Wrap the call to do_even_more_custom_application_logic()
    //  with an exception handler that catches std::exception, displays
    //  a message and the exception.what(), then continues processing
    std::cout << "Running Custom Application Logic." << std::endl;

    try {
        if (do_even_more_custom_application_logic())
            {
                std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
            }
    } 
    
    //MT: TEST IF OVERFLOW ERROR THROWN IN do_even_more_custom_application_logic() 
    //    METHOD AND PRINT EXCEPTION IF CAUGHT
    catch (std::overflow_error& e) {
        std::cout << "CustomAppLogic catch: " << e.what() << std::endl;
    }
    

    // TODO: Throw a custom exception derived from std::exception
    //  and catch it explictly in main

    //MT:  THROW CUSTOM EXCEPTION
    throw MTCustomException(); 
         
    std::cout << "Leaving Custom Application Logic." << std::endl;
    
}

float divide(float num, float den)
{
    // TODO: Throw an exception to deal with divide by zero errors using
    //  a standard C++ defined exception
    if (den == 0) {
        throw std::runtime_error("Divide by zero runtime error\n");
    }
    return (num / den);
}

void do_division() noexcept
{
    //  TODO: create an exception handler to capture ONLY the exception thrown
    //  by divide.

    float numerator = 10.0f;
    float denominator = 0;

    try {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (std::runtime_error& e) {
        std::cout << "DoDivision catch: " << e.what() << std::endl;
    }    
}

int main()
{
    // TODO: Create exception handlers that catch (in this order):
    //  your custom exception
    //  std::exception
    //  uncaught exception 
    //  that wraps the whole main function, and displays a message to the console.
    try {
        std::cout << "Exceptions Tests!" << std::endl;
        do_division();
    }
    catch (std::runtime_error& e) {
        std::cout << "Main catch: " << e.what() << std::endl;
    }
    try {
        do_custom_application_logic();
    }
    //MT: ALL EXCEPTIONS (INCLUDING CUSTOM) ARE DERIVED FROM THE STD::EXCEPTION CLASS.
    //    THEREFORE ONLY ONE CATCH IS NEEDED FOR ALL EXCEPTIONS.
    catch (std::overflow_error& e) {
        std::cout << "Main catch: " << e.what() << std::endl;
    }
    catch (std::exception& e) {
        std::cout << "Main catch: " << e.what() << std::endl;
    }
}