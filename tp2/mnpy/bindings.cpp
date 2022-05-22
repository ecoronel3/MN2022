#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>

#include "mn/powerIteration.h"
#include "mn/PCA.h"
#include "mn/kNNClassifier.h"
#include "mn/DistanceMetric.h"
#include "mn/Weights.h"

namespace py = pybind11;

PYBIND11_MODULE(mnpy, m) 
{
    m.def("powerIteration", &mn::powerIteration, "The Power Method");

    py::class_<mn::PCA>(m, "PCA", py::dynamic_attr())
        .def(py::init())
        .def(py::init<std::uint16_t, std::uint16_t>())
        .def("fit", py::overload_cast<const Eigen::MatrixXd&>(&mn::PCA::fit))
        .def("fit", py::overload_cast<const Eigen::MatrixXd&, const Eigen::VectorXi&>(&mn::PCA::fit))
        .def("transform", &mn::PCA::transform)
        .def("getEigenValues", &mn::PCA::getEigenValues)
        .def("getComponents", &mn::PCA::getComponents)
        .def_readwrite("n_components", &mn::PCA::nComponents)
        .def_readwrite("iterated_power", &mn::PCA::iteratedPower)
        .def_readwrite("tolerance_error", &mn::PCA::toleranceError)
        .def("__copy__",  [](const mn::PCA& self) {
            return mn::PCA(self);
        })
        .def("__deepcopy__", [](const mn::PCA& self, py::dict) {
            return mn::PCA(self);
        })
        .def("set_params", [](mn::PCA& self, const py::kwargs& kwargs) {

            if (kwargs.contains("n_components"))
            {
                self.nComponents = kwargs["n_components"].cast<std::uint16_t>();
            }

            if (kwargs.contains("iterated_power"))
            {
                self.iteratedPower = kwargs["iterated_power"].cast<std::uint16_t>();
            }

            if (kwargs.contains("tolerance_error"))
            {
                self.toleranceError = kwargs["tolerance_error"].cast<double>();
            }
            return self;
        })
        .def(py::pickle(
            [](const mn::PCA& self) { // __getstate__
                /* Return a tuple that fully encodes the state of the object */
                return py::make_tuple(self.nComponents, self.iteratedPower, self.toleranceError);
            },
            [](py::tuple t) { // __setstate__
                if (t.size() != 3)
                    throw std::runtime_error("Invalid state for PCA!");

                /* Create a new C++ instance */
                mn::PCA pca;
                pca.nComponents = (t[0].cast<std::uint16_t>());
                pca.iteratedPower = (t[1].cast<std::uint16_t>());
                pca.toleranceError = (t[2].cast<double>());

                return pca;
            }
        ));

    py::class_<mn::kNNClassifier> knn(m, "kNNClassifier", py::dynamic_attr());
    knn.def(py::init())
        .def(py::init<std::uint16_t, mn::DistanceMetric, mn::Weights>())
        .def("fit", &mn::kNNClassifier::fit)
        .def("predict", &mn::kNNClassifier::predict)
        .def("score", &mn::kNNClassifier::score)
        .def_readwrite("k_neighbors", &mn::kNNClassifier::kNeighbors)
        .def_readwrite("distance_metric", &mn::kNNClassifier::distanceMetric)
        .def_readwrite("weights", &mn::kNNClassifier::weights)
        .def("__copy__",  [](const mn::kNNClassifier& self) {
            return mn::kNNClassifier(self);
        })
        .def("__deepcopy__", [](const mn::kNNClassifier& self, py::dict) {
            return mn::kNNClassifier(self);
        })
        .def("set_params", [](mn::kNNClassifier& self, const py::kwargs& kwargs) {

            if (kwargs.contains("k_neighbors"))
            {
                self.kNeighbors = kwargs["k_neighbors"].cast<std::uint16_t>();
            }

            if (kwargs.contains("distance_metric"))
            {
                self.distanceMetric = kwargs["distance_metric"].cast<mn::DistanceMetric>();
            }

            if (kwargs.contains("weights"))
            {
                self.weights = kwargs["weights"].cast<mn::Weights>();
            }

            return self;
        })
        .def(py::pickle(
            [](const mn::kNNClassifier& self) { // __getstate__
                /* Return a tuple that fully encodes the state of the object */
                return py::make_tuple(self.kNeighbors, self.distanceMetric, self.weights);
            },
            [](py::tuple t) { // __setstate__
                if (t.size() != 3)
                    throw std::runtime_error("Invalid state for kNNClassifier!");

                /* Create a new C++ instance */
                mn::kNNClassifier knn;
                knn.kNeighbors = (t[0].cast<std::uint16_t>());
                knn.distanceMetric = (t[1].cast<mn::DistanceMetric>());
                knn.weights = (t[2].cast<mn::Weights>());
                return knn;
            }
        ));

    py::enum_<mn::DistanceMetric>(m, "DistanceMetric")
        .value("Euclidean", mn::DistanceMetric::Euclidean)
        .value("Manhattan", mn::DistanceMetric::Manhattan)
        .value("Chebyshev", mn::DistanceMetric::Chebyshev)
        .export_values();

    py::enum_<mn::Weights>(m, "Weights")
        .value("Uniform", mn::Weights::Uniform)
        .value("Distance", mn::Weights::Distance)
        .export_values();
}
