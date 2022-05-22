#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>

#include "mn/powerIteration.h"
#include "mn/PCA.h"
#include "mn/kNNClassifier.h"

namespace py = pybind11;

PYBIND11_MODULE(mnpy, m) 
{
    m.def("powerIteration", &mn::powerIteration, "The Power Method");

    py::class_<mn::PCA>(m, "PCA", py::dynamic_attr())
        .def(py::init())
        .def(py::init<std::uint16_t, std::uint16_t>())
        .def(py::init<mn::PCA const &>())
        .def("fit", py::overload_cast<const Eigen::MatrixXd&>(&mn::PCA::fit))
        .def("fit", py::overload_cast<const Eigen::MatrixXd&, const Eigen::VectorXi&>(&mn::PCA::fit))
        .def("transform", &mn::PCA::transform)
        .def("getEigenValues", &mn::PCA::getEigenValues)
        .def("getComponents", &mn::PCA::getComponents)
        .def_readwrite("n_components", &mn::PCA::nComponents)
        .def_readwrite("iterated_power", &mn::PCA::iteratedPower)
        .def_readwrite("tolerance_error", &mn::PCA::toleranceError);

    py::class_<mn::kNNClassifier> knn(m, "kNNClassifier", py::dynamic_attr());
    knn.def(py::init())
        .def(py::init<std::uint16_t, mn::KNNWeights>())
        .def("fit", &mn::kNNClassifier::fit)
        .def("predict", &mn::kNNClassifier::predict)
        .def("score", &mn::kNNClassifier::score)
        .def_readwrite("k_neighbors", &mn::kNNClassifier::kNeighbors);

    py::enum_<mn::KNNWeights>(m, "KNNWeights")
        .value("Uniform", mn::KNNWeights::Uniform)
        .value("Distance", mn::KNNWeights::Distance)
        .value("Manhattan", mn::KNNWeights::Manhattan)
        .export_values();
}
