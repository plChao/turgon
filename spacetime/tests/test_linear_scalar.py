# Copyright (c) 2018, Yung-Yu Chen <yyc@solvcon.net>
# BSD 3-Clause License, see COPYING

import unittest

import numpy as np

import libst


class LinearScalarSolverTC(unittest.TestCase):

    @staticmethod
    def _build_solver(resolution):

        # Build grid.
        xcrd = np.arange(resolution+1) / resolution
        xcrd *= 2 * np.pi
        grid = libst.Grid(xcrd)
        dx = (grid.xmax - grid.xmin) / grid.ncelm

        # Build solver.
        time_stop = 2*np.pi
        cfl_max = 1.0
        dt_max = dx * cfl_max
        nstep = int(np.ceil(time_stop / dt_max))
        dt = time_stop / nstep
        cfl = dt / dx
        svr = libst.LinearScalarSolver(
            grid=grid,
            time_increment=dt,
        )

        # Initialize.
        for e in svr.selms(odd_plane=False):
            e.set_so0(0, np.sin(e.xctr))
            e.set_so1(0, np.cos(e.xctr))

        return nstep, xcrd, svr

    def setUp(self):

        self.resolution = 8
        self.nstep, self.xcrd, self.svr = self._build_solver(self.resolution)
        self.cycle = 10

    def test_nvar(self):

        self.assertEqual(1, self.svr.nvar)

    def test_initialized(self):

        v = [e.so0(0) for e in self.svr.selms(odd_plane=False)]
        self.assertEqual(v, np.sin(self.xcrd).tolist())

    def test_march(self):

        for it in range(self.nstep*self.cycle):
            self.svr.march_full()

        v = np.array([e.so0(0) for e in self.svr.selms(odd_plane=False)])
        np.testing.assert_allclose(v, np.sin(self.xcrd),
                                   rtol=1.e-14, atol=1.e-15)

    def test_march_fine_interface(self):

        def _march():

            self.svr.march_half_so0(odd_plane=False)
            self.svr.march_half_so1(odd_plane=False)
            self.svr.treat_boundary_so0()
            self.svr.treat_boundary_so1()
            self.svr.march_half_so0(odd_plane=True)
            self.svr.march_half_so1(odd_plane=True)

        svr2 = self._build_solver(self.resolution)[-1]

        for it in range(self.nstep*self.cycle):
            _march()
            svr2.march_full()

        v1 = np.array([e.so0(0) for e in self.svr.selms(odd_plane=False)])
        v2 = np.array([e.so0(0) for e in svr2.selms(odd_plane=False)])
        self.assertEqual(v1.tolist(), v2.tolist())

# vim: set et sw=4 ts=4:
