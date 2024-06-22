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

using namespace geode::prelude;
namespace py = pybind11;

class $modify(MenuLayer) {
    void onMoreGames(CCObject*) {

        py::scoped_interpreter guard{};

        std::string code = R"(
import sys
print("Updated Python sys.path: ", sys.path)
)";
        try {
            py::exec(code);
        } catch (const py::error_already_set& e) {
            log::info("{}", e.what());
        }
        
    }
};