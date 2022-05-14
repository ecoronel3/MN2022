#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include "mn/powerIteration.h"
#include "mn/PCA.h"
#include "mn/kNNClassifier.h"

namespace py = pybind11;

double powerIteration(Eigen::Ref<const Eigen::MatrixXd> B, Eigen::Ref<const Eigen::VectorXd> x0, const uint16_t niter, const double epsilon)
{   
    return mn::powerIteration(B, x0, niter, epsilon).first;
}

PYBIND11_MODULE(mnpy, m) 
{
    m.def("powerIteration", &powerIteration, "The Power Method");

    py::class_<mn::PCA>(m, "PCA")
        .def(py::init<std::uint16_t, std::uint16_t>())
        .def("fit", &mn::PCA::fit)
        .def("getEigenValues", &mn::PCA::getEigenValues)
        .def("getEigenVectors", &mn::PCA::getEigenVectors);

    py::class_<mn::kNNClassifier>(m, "kNNClassifier")
        .def(py::init<std::uint16_t>())
        .def("fit", &mn::kNNClassifier::fit)
        .def("predict", &mn::kNNClassifier::predict);
}
