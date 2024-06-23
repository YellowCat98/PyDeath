#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <filesystem>
#include <vector>
#include <string>
#include <Geode/utils/Web.hpp>
#include <chrono>
#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;
namespace py = pybind11;

class $modify(PlayerObject) {
    void playerDestroyed(bool p0) {

        py::scoped_interpreter guard{};

        std::string code = R"(
import random

value = random.randint(1, 1000000)
print(value)
)";
        try {
            py::exec(code);
        } catch (const py::error_already_set& e) {
            log::info("{}", e.what());
        }
        
    }
};