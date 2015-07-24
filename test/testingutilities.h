/*
 * This file is part of the SPLINTER library.
 * Copyright (C) 2012 Bjarne Grimstad (bjarne.grimstad@gmail.com).
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifndef SPLINTER_TESTINGUTILITIES_H
#define SPLINTER_TESTINGUTILITIES_H

#include <datatable.h>
#include <function.h>
#include <generaldefinitions.h>
#include <bspline.h>
#include "termfunction.h"
#include <operator_overloads.h>


namespace SPLINTER
{

/*
 * TODO:
 * Rename this?
 */
enum class TestType {
    All,
    FunctionValue,
    Jacobian,
    Hessian
};

bool equalsWithinRange(double a, double b, double margin = 0.0);

bool compareFunctions(const Function &exact, const Function &approx, const std::vector<std::vector<double>> &points);

bool compareFunctions(const Function &exact, const Function &approx, const std::vector<std::vector<double>> &points, double one_norm_epsilon, double two_norm_epsilon, double inf_norm_epsilon);

bool compareFunctions(const Function &exact, const Function &approx);

bool compareBSplines(const BSpline &left, const BSpline &right);

DataTable sample(const Function &func, std::vector<std::vector<double>> &points);
DataTable sample(const Function *func, std::vector<std::vector<double>> &points);

std::vector<double> linspace(double start, double stop, unsigned int points);

// points is a vector where each element is the number of points for that dim
std::vector<std::vector<double>> linspace(std::vector<double> start, std::vector<double> end, std::vector<unsigned int> points);

// points is the total number of points, not per dim
std::vector<std::vector<double>> linspace(int dim, double start, double end, unsigned int points);

// Returns a default linspace of dim dim
std::vector<std::vector<double>> linspace(int dim);

std::vector<std::vector<double>> linspace(int dim, unsigned int pointsPerDim);

double sixHumpCamelBack(DenseVector x);

double getOneNorm(const DenseMatrix &m);

double getTwoNorm(const DenseMatrix &m);

double getInfNorm(const DenseMatrix &m);

// returns log(x) in base base
double log(double base, double x);

std::vector<double> denseToVec(const DenseVector &dense);

DenseVector vecToDense(const std::vector<double> &vec);

std::string pretty_print(const DenseVector &denseVec);

TermFunction *getTestFunction(int numVariables, int degree);
std::vector<TermFunction *> getTestFunctionsOfDegree(int degree);
std::vector<TermFunction *> getTestFunctionWithNumVariables(int numVariables);
std::vector<TermFunction *> getPolynomialFunctions();
std::vector<TermFunction *> getNastyTestFunctions();


/*
 * Returns 3x3 matrix,
 * first row: function value error norms
 * second row: jacobian value error norms
 * third row: hessian value error norms
 * first col: 1-norms
 * second col: 2-norms
 * third col: inf-norms
 */
DenseMatrix getErrorNorms(const Function *exact, const Function *approx, const std::vector<std::vector<double>> &points);

void checkNorms(DenseMatrix normValues, size_t numPoints, double one_eps, double two_eps, double inf_eps);
void checkNorm(DenseMatrix normValues, TestType type, size_t numPoints, double one_eps, double two_eps, double inf_eps);
void _checkNorm(DenseMatrix normValues, int row, size_t numPoints, double one_eps, double two_eps, double inf_eps);

void testApproximation(std::vector<TermFunction *> funcs,
                       std::function<Approximant *(const DataTable &table)> approx_gen_func,
                       TestType type, size_t numSamplePoints, size_t numEvalPoints,
                       double one_eps, double two_eps, double inf_eps);

} // namespace SPLINTER

#endif // SPLINTER_TESTINGUTILITIES_H
