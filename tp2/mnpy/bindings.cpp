#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include "mn/powerIteration.h"

int add(int i, int j) {
    return i + j;
}

double powerIteration(Eigen::Ref<const Eigen::MatrixXd> B, Eigen::Ref<const Eigen::VectorXd> x0, const uint16_t niter, const double epsilon)
{   
    return mn::powerIteration(B, x0, niter, epsilon).first;
}

PYBIND11_MODULE(mnpy, m) 
{
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("add", &add, "A function that adds two numbers");

    m.def("powerIteration", &powerIteration, "The Power Method");
}
