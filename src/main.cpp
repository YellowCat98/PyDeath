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

using PyScript = Task<uint64_t, int>;

PyScript runScript(std::string code) {
    return PyScript::run([code](auto progress, auto called) -> PyScript::Result {
        try {
            
                py::exec(code);
        } catch (const py::error_already_set& e) {
            log::info("Python Error:\n{}", e.what());
        }
        return 1;
    });
}

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
struct Fields {
    EventListener<PyScript> gameListener;
};
    void playerDestroyed(bool p0) {
        py::scoped_interpreter guard{}; // lets initialize the interpreter BEFORE running the task!!!
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
        m_fields->gameListener.bind([](PyScript::Event* event){});
        
        m_fields->gameListener.setFilter(runScript(code));
    }
};