#pragma once

/*
 * Copyright (c) 2018, Yung-Yu Chen <yyc@solvcon.net>
 * BSD 3-Clause License, see COPYING
 */

#include "spacetime/python/common.hpp"

namespace spacetime
{

namespace python
{

class
SPACETIME_PYTHON_WRAPPER_VISIBILITY
WrapInviscidBurgersSolver
  : public WrapSolverBase< WrapInviscidBurgersSolver, InviscidBurgersSolver >
{

    using base_type = WrapSolverBase< WrapInviscidBurgersSolver, InviscidBurgersSolver >;
    using wrapper_type = typename base_type::wrapper_type;
    using wrapped_type = typename base_type::wrapped_type;

    friend base_type;
    friend base_type::base_type;

    WrapInviscidBurgersSolver(pybind11::module & mod, const char * pyname, const char * clsdoc)
      : base_type(mod, pyname, clsdoc)
    {
        namespace py = pybind11;
        (*this)
            .def(
                py::init([](std::shared_ptr<Grid> const & grid, typename wrapped_type::value_type time_increment) {
                    return wrapped_type::construct(grid, time_increment);
                })
              , py::arg("grid"), py::arg("time_increment")
            )
        ;
    }

}; /* end class WrapInviscidBurgersSolver */

class
SPACETIME_PYTHON_WRAPPER_VISIBILITY
WrapInviscidBurgersSelm
  : public WrapElementBase< WrapInviscidBurgersSelm, InviscidBurgersSelm >
{

    using base_type = WrapElementBase< WrapInviscidBurgersSelm, InviscidBurgersSelm >;
    using wrapper_type = typename base_type::wrapper_type;
    using wrapped_type = typename base_type::wrapped_type;

    friend base_type;
    friend base_type::base_type;

    WrapInviscidBurgersSelm(pybind11::module & mod, const char * pyname, const char * clsdoc)
      : base_type(mod, pyname, clsdoc)
    {
        (*this)
            .def(
                "so0",
                static_cast<wrapped_type::value_type const & (wrapped_type::*)(size_t) const>(&wrapped_type::so0)
            )
            .def(
                "set_so0",
                [](wrapped_type & self, size_t it, wrapped_type::value_type val) {
                    self.so0(it) = val;
                }
            )
            .def(
                "so1",
                static_cast<wrapped_type::value_type const & (wrapped_type::*)(size_t) const>(&wrapped_type::so1)
            )
            .def(
                "set_so1",
                [](wrapped_type & self, size_t it, wrapped_type::value_type val) {
                    self.so1(it) = val;
                }
            )
            .def("xn", &wrapped_type::xn)
            .def("xp", &wrapped_type::xp)
            .def("tn", &wrapped_type::tn)
            .def("tp", &wrapped_type::tp)
        ;
    }

}; /* end class WrapInviscidBurgersSelm */

class
SPACETIME_PYTHON_WRAPPER_VISIBILITY
WrapInviscidBurgersCelm
  : public WrapElementBase< WrapInviscidBurgersCelm, InviscidBurgersCelm >
{

    using base_type = WrapElementBase< WrapInviscidBurgersCelm, InviscidBurgersCelm >;
    using wrapper_type = typename base_type::wrapper_type;
    using wrapped_type = typename base_type::wrapped_type;

    friend base_type;
    friend base_type::base_type;

    WrapInviscidBurgersCelm(pybind11::module & mod, const char * pyname, const char * clsdoc)
      : base_type(mod, pyname, clsdoc)
    {
        (*this)
            .def_property_readonly("selm_xn", &wrapped_type::selm_xn)
            .def_property_readonly("selm_xp", &wrapped_type::selm_xp)
            .def_property_readonly("selm_tn", &wrapped_type::selm_tp)
            .def_property_readonly("selm_tp", &wrapped_type::selm_tp)
        ;
    }

}; /* end class WrapInviscidBurgersCelm */

} /* end namespace python */

} /* end namespace spacetime */

// vim: set et sw=4 ts=4:
