/*
 * Copyright (c) 2018, Yung-Yu Chen <yyc@solvcon.net>
 * BSD 3-Clause License, see COPYING
 */

#include "spacetime/python.hpp"

#include <utility>
#include <memory>
#include <vector>
#include <algorithm>
#include <cstring>

#include "spacetime.hpp"

namespace spacetime
{

namespace python
{

PyObject * ModuleInitializer::initialize_spacetime(pybind11::module & mod)
{
    xt::import_numpy(); // or numpy c api segfault.

    mod.doc() = "_libst: One-dimensional space-time CESE method code";

    WrapGrid::commit(mod, "Grid", "Spatial grid");
    WrapCelm::commit(mod, "Celm", "Conservation element");
    WrapSelm::commit(mod, "Selm", "Solution element");
    WrapSolution::commit(mod, "Solution", "Solution field");

    return mod.ptr();
}

} /* end namespace python */

} /* end namespace march */

PYBIND11_MODULE(_libst, mod) {
    ::spacetime::python::ModuleInitializer::get_instance().initialize(mod);
}

// vim: set et sw=4 ts=4: