#include <Geode/Geode.hpp>
#include <pybind11/pybind11.h>
#include <Geode/binding/FLAlertLayer.hpp>

using namespace geode::prelude;
namespace py = pybind11;

PYBIND11_MODULE(binding_module, m) {
    py::class_<FLAlertLayer>(m, "FLAlertLayer")
    .def(py::init<>())
    .def_static("create", [](const FLAlertLayer &FLAlertLayer, FLAlertLayerProtocol* delegate, char const* title, gd::string desc, char const* btn1, char const* btn2, float width, bool scroll, float height, float textScale) {
        FLAlertLayer.create(delegate, title, desc, btn1, btn2, width, scroll, height, textScale);
    })
    .def("show", &FLAlertLayer::show);
}