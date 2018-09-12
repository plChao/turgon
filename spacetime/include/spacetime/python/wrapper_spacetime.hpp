#pragma once

/*
 * Copyright (c) 2018, Yung-Yu Chen <yyc@solvcon.net>
 * BSD 3-Clause License, see COPYING
 */

#include <sstream>

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "xtensor-python/pyarray.hpp"

#include "spacetime.hpp"
#include "spacetime/python/WrapBase.hpp"

namespace spacetime
{

namespace python
{

namespace detail {

template<class T> std::string to_str(T const & self) { return Formatter() << self >> Formatter::to_str; }

} /* end namespace detail */

class
SPACETIME_PYTHON_WRAPPER_VISIBILITY
WrapGrid
  : public WrapBase< WrapGrid, Grid, std::shared_ptr<Grid> >
{

    friend base_type;

    WrapGrid(pybind11::module & mod, const char * pyname, const char * clsdoc)
      : base_type(mod, pyname, clsdoc)
    {
        namespace py = pybind11;
        (*this)
            .def(
                py::init([](real_type xmin, real_type xmax, size_t nelm) {
                    return Grid::construct(xmin, xmax, nelm);
                }),
                py::arg("xmin"), py::arg("xmax"), py::arg("nelm")
            )
            .def(
                py::init([](xt::pyarray<wrapped_type::value_type> & xloc) {
                    return Grid::construct(xloc);
                }),
                py::arg("xloc")
            )
            .def("__str__", &detail::to_str<wrapped_type>)
            .def_property_readonly("xmin", &wrapped_type::xmin)
            .def_property_readonly("xmax", &wrapped_type::xmax)
            .def_property_readonly("ncelm", &wrapped_type::ncelm)
            .def_property_readonly("nselm", &wrapped_type::nselm)
            .def(
                "celm",
                static_cast<Celm (wrapped_type::*)(size_t, bool)>(&wrapped_type::celm_at),
                py::arg("ielm"), py::arg("odd_plane")=false
            )
        ;
    }

}; /* end class WrapGrid */

template<class WT, class ET>
class
SPACETIME_PYTHON_WRAPPER_VISIBILITY
WrapElementBase
  : public WrapBase< WT, ET >
{

public:

    using base_type = WrapBase< WT, ET >;
    using wrapper_type = typename base_type::wrapper_type;
    using wrapped_type = typename base_type::wrapped_type;

    friend base_type;

protected:

    using base_type::base_type;

    WrapElementBase(pybind11::module & mod, const char * pyname, const char * clsdoc)
      : base_type(mod, pyname, clsdoc)
    {
        (*this)
            .def("__str__", &detail::to_str<wrapped_type>)
            .def("duplicate", &wrapped_type::duplicate)
            .def_property_readonly("dup", &wrapped_type::duplicate)
            .def_property_readonly("x", &wrapped_type::x)
            .def_property_readonly("xneg", &wrapped_type::xneg)
            .def_property_readonly("xpos", &wrapped_type::xpos)
            .def_property_readonly("xctr", &wrapped_type::xctr)
            .def_property_readonly("index", &wrapped_type::index)
            .def_property_readonly("on_even_plane", &wrapped_type::on_even_plane)
            .def_property_readonly("on_odd_plane", &wrapped_type::on_odd_plane)
            .def_property_readonly("grid", &wrapped_type::grid)
            .def("move", &wrapped_type::move_at)
            .def("move_left", &wrapped_type::move_left_at)
            .def("move_right", &wrapped_type::move_right_at)
            .def("move_neg", &wrapped_type::move_neg_at)
            .def("move_pos", &wrapped_type::move_pos_at)
        ;
    }

}; /* end class WrapElementBase */

class
SPACETIME_PYTHON_WRAPPER_VISIBILITY
WrapCelm
  : public WrapElementBase< WrapCelm, Celm >
{

    using base_type = WrapElementBase< WrapCelm, Celm >;
    using wrapper_type = typename base_type::wrapper_type;
    using wrapped_type = typename base_type::wrapped_type;

    friend base_type;
    friend base_type::base_type;

    WrapCelm(pybind11::module & mod, const char * pyname, const char * clsdoc)
      : base_type(mod, pyname, clsdoc)
    {}

}; /* end class WrapCelm */

class
SPACETIME_PYTHON_WRAPPER_VISIBILITY
WrapSelm
  : public WrapElementBase< WrapSelm, Selm >
{

    using base_type = WrapElementBase< WrapSelm, Selm >;
    using wrapper_type = typename base_type::wrapper_type;
    using wrapped_type = typename base_type::wrapped_type;

    friend base_type;
    friend base_type::base_type;

    WrapSelm(pybind11::module & mod, const char * pyname, const char * clsdoc)
      : base_type(mod, pyname, clsdoc)
    {
        (*this)
            .def_property_readonly("sol", &wrapped_type::sol)
        ;
    }

}; /* end class WrapSelm */

class
SPACETIME_PYTHON_WRAPPER_VISIBILITY
WrapSolution
  : public WrapBase< WrapSolution, Solution, std::shared_ptr<Solution> >
{

    friend base_type;

    WrapSolution(pybind11::module & mod, const char * pyname, const char * clsdoc)
      : base_type(mod, pyname, clsdoc)
    {
        namespace py = pybind11;
        (*this)
            .def(
                py::init([](std::shared_ptr<Grid> const & grid, size_t nvar, wrapped_type::value_type time_increment) {
                    return Solution::construct(grid, nvar, time_increment);
                }),
                py::arg("grid"), py::arg("nvar"), py::arg("time_increment")
            )
            .def("__str__", &detail::to_str<wrapped_type>)
            .def_property_readonly("grid", [](wrapped_type & self){ return self.grid().shared_from_this(); })
            .def_property_readonly("nvar", &wrapped_type::nvar)
            .def_property(
                "time_increment",
                [](wrapped_type & self) { return self.time_increment(); },
                [](wrapped_type & self, wrapped_type::value_type val) { return self.time_increment() = val; }
            )
            .def(
                "selm",
                static_cast<Selm (wrapped_type::*)(size_t, bool)>(&wrapped_type::selm_at),
                py::arg("ielm"), py::arg("odd_plane")=false
            )
        ;
    }

}; /* end class WrapSolution */

} /* end namespace python */

} /* end namespace spacetime */

// vim: set et sw=4 ts=4: