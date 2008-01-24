//----------------------------  grid_out_02.cc  ---------------------------
//    $Id$
//    Version: $Name$ 
//
//    Copyright (C) 2002, 2003, 2004, 2005, 2008 by the deal.II authors
//
//    This file is subject to QPL and may not be  distributed
//    without copyright and license information. Please refer
//    to the file deal.II/doc/license.html for the  text  and
//    further information on this license.
//
//----------------------------  grid_out_02.cc  ---------------------------

// test, if the grid is written correctly in dx format. the vertices have to be
// renumbered after coarsening, as the dx format uses an implicit vertex
// numbering.

#include "../tests.h"
#include <base/geometry_info.h>
#include <dofs/dof_handler.h>
#include <grid/tria.h>
#include <grid/tria_boundary.h>
#include <grid/tria_boundary_lib.h>
#include <grid/tria_accessor.h>
#include <grid/tria_iterator.h>
#include <grid/grid_out.h>
#include <grid/grid_generator.h>
#include <base/logstream.h>

#include <fstream>
#include <iomanip>


std::ofstream logfile("grid_out_02/output");


template <int dim>
void test ()
{  
  Triangulation<dim> tria;
  GridGenerator::hyper_cube (tria);
  tria.refine_global(2);
  
  GridOut grid_out;
  grid_out.write_dx (tria, logfile);

  typename Triangulation<dim>::active_cell_iterator cell=tria.begin_active();
  for (unsigned int i=0; i<GeometryInfo<dim>::children_per_cell; ++i)
    {
      cell->set_coarsen_flag();
      ++cell;
    }
  tria.execute_coarsening_and_refinement();
  grid_out.write_dx (tria, logfile);
}


int main ()
{
  deallog << std::setprecision (2);
  logfile << std::setprecision (2);
  deallog.attach(logfile);
  deallog.depth_console(0);
  deallog.threshold_double(1.e-10);

  test<2> ();
  test<3> ();
}

