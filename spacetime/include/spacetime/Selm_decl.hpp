#pragma once

/*
 * Copyright (c) 2018, Yung-Yu Chen <yyc@solvcon.net>
 * BSD 3-Clause License, see COPYING
 */

#include "spacetime/system.hpp"
#include "spacetime/type.hpp"
#include "spacetime/ElementBase_decl.hpp"
#include "spacetime/Grid_decl.hpp"
#include "spacetime/Solution_decl.hpp"

namespace spacetime
{

/**
 * A solution element.
 */
class Selm
  : public ElementBase<Selm>
{

public:

    Selm(Solution & sol, size_t index)
      : base_type(sol.grid().xptr_selm(index, Grid::SelmPK()))
      , m_sol(&sol)
    {}

    Selm(Solution & sol, size_t index, bool odd_plane)
      : base_type(sol.grid().xptr_selm(index, odd_plane, Grid::SelmPK()))
      , m_sol(&sol)
    {}

    /**
     * Selm index.
     */
    index_type index() const { return (xindex() - 1) >> 1; }

    /**
     * Return true for even plane, false for odd plane (temporal).
     */
    bool on_even_plane() const { return !on_odd_plane(); }
    bool on_odd_plane() const { return bool((xindex() - 1) & 1); }

    Grid const & grid() const { return sol().grid(); }
    Solution const & sol() const { return *m_sol; }
    Solution       & sol()       { return *m_sol; }

    real_type xctr() const { return (xneg()+xpos())/2; }

    Selm & move_at(ssize_t offset);

    value_type const & so0(size_t it) const { return sol().so0()[it]; }
    value_type       & so0(size_t it)       { return sol().so0()[it]; }

    value_type const & so1(size_t it) const { return sol().so1()[it]; }
    value_type       & so1(size_t it)       { return sol().so1()[it]; }

private:

    Solution * m_sol;

}; /* end class Selm */

} /* end namespace spacetime */

/* vim: set et ts=4 sw=4: */
