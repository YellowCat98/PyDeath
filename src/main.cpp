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
#include <Geode/loader/Event.hpp>

using namespace geode::prelude;
namespace py = pybind11;

using PyScript = Task<int, int>;

std::string getPyScript() {
    auto path = Mod::get()->getSettingValue<std::filesystem::path>("select-pyfile");
    std::ifstream pyscript(path);

    if (!pyscript) {
std::string theCode = R"(
import random
list = ["You are dead!", "You have DIED...", "the PlayerObject::playerDestroyed function has been called"]

value = random.choice(list)
print(value)
)";
        return theCode;
    }
    std::stringstream buffer;
    buffer << pyscript.rdbuf();
    return buffer.str();
}

PyScript runScript() {
    return PyScript::run([](auto progress, auto called) -> PyScript::Result {
        std::string code;
        code = getPyScript();
        try {
            py::scoped_interpreter guard{};
            py::exec(code);
        } catch (const py::error_already_set& e) {
            PyErr_Print();
            PyErr_Clear();
        }
        return 1;
    });
}

class $modify(PlayerObject) {
struct Fields {
    EventListener<PyScript> gameListener;
};
    void playerDestroyed(bool p0) {
        m_fields->gameListener.bind([](PyScript::Event* event){});
        
        m_fields->gameListener.setFilter(runScript());
    }
};