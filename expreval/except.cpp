// File:    except.cpp
// Author:  Brian Vanderburg II
// Purpose: ExprEval exceptions
//------------------------------------------------------------------------------


// Includes
#include "except.h"
#include <cerrno>
#include <cstring>

using namespace ExprEval;


// Default/unknown ExprEval exception
//------------------------------------------------------------------------------
Exception::Exception()
{
    m_type = Type_Exception;

    if (errno) m_error = strerror(errno);

    m_start = m_end = (std::string::size_type)-1;
}

Exception::~Exception() throw()
{
}

// Not found exception
//------------------------------------------------------------------------------
NotFoundException::NotFoundException(const std::string& name)
{
    m_type = Type_NotFoundException;
    m_value = name;
}

// Already exists exception
//------------------------------------------------------------------------------
AlreadyExistsException::AlreadyExistsException(const std::string& name)
{
    m_type = Type_AlreadyExistsException;
    m_value = name;
}

// Null pointer exception
//------------------------------------------------------------------------------
NullPointerException::NullPointerException(const std::string& method)
{
    m_type = Type_NullPointerException;
    m_value = method;
}

// Math error exception
//------------------------------------------------------------------------------
MathException::MathException(const std::string& function)
{
    m_type = Type_MathException;
    m_value = function;
}

// Divide by zero
//------------------------------------------------------------------------------
DivideByZeroException::DivideByZeroException()
{
    m_type = Type_DivideByZeroException;
}

// No value list found during parsing
//------------------------------------------------------------------------------
NoValueListException::NoValueListException()
{
    m_type = Type_NoValueListException;
}

// No function list found during parsing
//------------------------------------------------------------------------------
NoFunctionListException::NoFunctionListException()
{
    m_type = Type_NoFunctionListException;
}

// Expression abort
//------------------------------------------------------------------------------
AbortException::AbortException()
{
    m_type = Type_AbortException;
}

// Empty expression
//------------------------------------------------------------------------------
EmptyExpressionException::EmptyExpressionException()
{
    m_type = Type_EmptyExpressionException;
}

// Unknown token found during parsing
//------------------------------------------------------------------------------
UnknownTokenException::UnknownTokenException()
{
    m_type = Type_UnknownTokenException;
}

// Invalid argument count
//------------------------------------------------------------------------------
InvalidArgumentCountException::InvalidArgumentCountException(const std::string& function)
{
    m_type = Type_InvalidArgumentCountException;
    m_value = function;
}

// Assign to constant
//------------------------------------------------------------------------------
ConstantAssignException::ConstantAssignException(const std::string& value)
{
    m_type = Type_ConstantAssignException;
    m_value = value;
}

// Pass constant by reference
//------------------------------------------------------------------------------
ConstantReferenceException::ConstantReferenceException(const std::string& value)
{
    m_type = Type_ConstantReferenceException;
    m_value = value;
}

// Syntax error exception
//------------------------------------------------------------------------------
SyntaxException::SyntaxException()
{
    m_type = Type_SyntaxException;
}

// Unmatched parenthesis
//------------------------------------------------------------------------------
UnmatchedParenthesisException::UnmatchedParenthesisException()
{
    m_type = Type_UnmatchedParenthesisException;
}
