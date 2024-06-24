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
#include <sstream>
#include <fstream>

using namespace geode::prelude;
namespace py = pybind11;

std::string getPyScript() {
    auto path = Mod::get()->getSettingValue<std::filesystem::path>("select-pyfile");
    std::ifstream pyscript(path);
    if (!pyscript) {
        return "";
    }
    std::stringstream buffer;
    buffer << pyscript.rdbuf();
    return buffer.str();
}

class $modify(PlayerObject) {
    void playerDestroyed(bool p0) {

        py::scoped_interpreter guard{};

        std::string code;
        if (getPyScript().empty()) {
            code = R"(
import random
list = ["You are dead!", "You have DIED...", "the PlayerObject::playerDestroyed function has been called"]

value = random.choice(list)
print(value)
            )";
        } else {
            code = getPyScript();
        }
        try {
            py::exec(code);
        } catch (const py::error_already_set& e) {
            log::info("{}", e.what());
        }
        PlayerObject::playerDestroyed(p0);
        
    }
};