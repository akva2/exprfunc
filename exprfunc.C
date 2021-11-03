//==============================================================================
//!
//! \file exprfunc.C
//!
//! \date Nov 3 2021
//!
//! \author Arne Morten Kvarving / SINTEF
//!
//! \brief Exports the exprfunc python module.
//!
//==============================================================================

#include <pybind11/stl.h>

#include "expreval/expreval.h"

#include <memory>
#include <iostream>

class ExprFunc {
public:
  ExprFunc(const std::string& definition)
  {
    expr = std::make_unique<ExprEval::Expression>();
    f = std::make_unique<ExprEval::FunctionList>();
    v = std::make_unique<ExprEval::ValueList>();
    f->AddDefaultFunctions();
    v->AddDefaultValues();
    v->Add("x",0.0,false);
    v->Add("y",0.0,false);
    v->Add("z",0.0,false);
    v->Add("t",0.0,false);
    expr->SetFunctionList(f.get());
    expr->SetValueList(v.get());
    expr->Parse(definition.c_str());
    arg.x = v->GetAddress("x");
    arg.y = v->GetAddress("y");
    arg.z = v->GetAddress("z");
    arg.t = v->GetAddress("t");
  }

  double operator()(const std::vector<double>& x)
  {
    *arg.x = *arg.y = *arg.z = *arg.t = 0.0;
    if (x.size() >= 1)
      *arg.x = x[0];
    if (x.size() >= 2)
      *arg.y = x[1];
    if (x.size() >= 3)
      *arg.z = x[2];
    if (x.size() >= 4)
      *arg.t = x[3];

    return expr->Evaluate();
  }

protected:
  std::unique_ptr<ExprEval::Expression> expr; //!< Roots of the expression tree
  std::unique_ptr<ExprEval::FunctionList>  f; //!< Lists of functions
  std::unique_ptr<ExprEval::ValueList>     v; //!< Lists of variables and constants

  //! \brief A struct representing a spatial function argument.
  struct Arg
  {
    double* x; //!< X-coordinate
    double* y; //!< Y-coordinate
    double* z; //!< Z-coordinate
    double* t; //!< Time
  };

  Arg arg; //!< Function argument values
};


PYBIND11_MODULE(exprfunc, m)
{
  pybind11::class_<ExprFunc>(m, "ExprFunc")
      .def(pybind11::init<const std::string&>(),
           pybind11::arg("definition"))
      .def("__call__", [](ExprFunc& self, const std::vector<double>& x)
            {
              return self(x);
            }
          );
}
