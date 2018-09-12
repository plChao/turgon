#pragma once

/*
 * Copyright (c) 2018, Yung-Yu Chen <yyc@solvcon.net>
 * BSD 3-Clause License, see COPYING
 */

#include "pybind11/pybind11.h"
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#define FORCE_IMPORT_ARRAY
#include "xtensor-python/pyarray.hpp"

#include "spacetime/python/WrapBase.hpp"
#include "spacetime/python/wrapper_spacetime.hpp"

/* vim: set et ts=4 sw=4: */
