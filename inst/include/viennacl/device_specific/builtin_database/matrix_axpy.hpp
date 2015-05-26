#ifndef VIENNACL_DEVICE_SPECIFIC_BUILTIN_DATABASE_MATRIX_AXPY_HPP_
#define VIENNACL_DEVICE_SPECIFIC_BUILTIN_DATABASE_MATRIX_AXPY_HPP_

/* =========================================================================
   Copyright (c) 2010-2014, Institute for Microelectronics,
                            Institute for Analysis and Scientific Computing,
                            TU Wien.
   Portions of this software are copyright by UChicago Argonne, LLC.

                            -----------------
                  ViennaCL - The Vienna Computing Library
                            -----------------

   Project Head:    Karl Rupp                   rupp@iue.tuwien.ac.at

   (A list of authors and contributors can be found in the PDF manual)

   License:         MIT (X11), see file LICENSE in the base directory
============================================================================= */

#include "viennacl/device_specific/builtin_database/devices/gpu/amd/northern_islands/barts.hpp"

#include "viennacl/device_specific/builtin_database/devices/gpu/nvidia/fermi/tesla_c2050.hpp"

#include "viennacl/device_specific/builtin_database/devices/gpu/nvidia/fermi/geforce_gtx_470.hpp"

#include "viennacl/device_specific/builtin_database/devices/gpu/nvidia/maxwell/geforce_gtx_750_ti.hpp"

#include "viennacl/device_specific/builtin_database/devices/gpu/amd/northern_islands/scrapper.hpp"

#include "viennacl/device_specific/builtin_database/devices/gpu/nvidia/tesla/geforce_gtx_260.hpp"

#include "viennacl/device_specific/builtin_database/devices/gpu/amd/southern_islands/tahiti.hpp"
#include "viennacl/device_specific/builtin_database/devices/gpu/amd/northern_islands/devastator.hpp"

#include "viennacl/device_specific/builtin_database/devices/gpu/nvidia/kepler/tesla_k20m.hpp"
#include "viennacl/device_specific/builtin_database/devices/gpu/nvidia/fermi/geforce_gtx_580.hpp"

#include "viennacl/device_specific/builtin_database/devices/gpu/amd/volcanic_islands/hawaii.hpp"

#include "viennacl/device_specific/builtin_database/devices/gpu/amd/evergreen/cypress.hpp"
#include "viennacl/device_specific/builtin_database/devices/gpu/amd/evergreen/cedar.hpp"

#include "viennacl/ocl/device_utils.hpp"

#include "viennacl/scheduler/forwards.h"

#include "viennacl/device_specific/forwards.h"
#include "viennacl/device_specific/builtin_database/common.hpp"

#include "viennacl/device_specific/builtin_database/devices/accelerator/fallback.hpp"
#include "viennacl/device_specific/builtin_database/devices/cpu/fallback.hpp"
#include "viennacl/device_specific/builtin_database/devices/gpu/fallback.hpp"

/** @file viennacl/device_specific/builtin_database/matrix_axpy.hpp
*
* Initializes the device database with the provided profiles. Updated semi-automatically.
*/

namespace viennacl
{
namespace device_specific
{
namespace builtin_database
{

inline database_type<matrix_axpy_template::parameters_type> init_matrix_axpy()
{
  database_type<matrix_axpy_template::parameters_type> result;

  devices::accelerator::fallback::add_4B(result);
  devices::accelerator::fallback::add_8B(result);

  devices::cpu::fallback::add_4B(result);
  devices::cpu::fallback::add_8B(result);

  devices::gpu::fallback::add_4B(result);
  devices::gpu::fallback::add_8B(result);
  devices::gpu::amd::evergreen::cedar::add_4B(result);
  devices::gpu::amd::evergreen::cypress::add_4B(result);
  devices::gpu::amd::evergreen::cypress::add_8B(result);
  devices::gpu::amd::volcanic_islands::hawaii::add_4B(result);
  devices::gpu::amd::volcanic_islands::hawaii::add_8B(result);
  devices::gpu::nvidia::fermi::geforce_gtx_580::add_4B(result);
  devices::gpu::nvidia::fermi::geforce_gtx_580::add_8B(result);
  devices::gpu::nvidia::kepler::tesla_k20m::add_4B(result);
  devices::gpu::nvidia::kepler::tesla_k20m::add_8B(result);
  devices::gpu::amd::southern_islands::tahiti::add_4B(result);
  devices::gpu::amd::southern_islands::tahiti::add_8B(result);
  devices::gpu::amd::northern_islands::devastator::add_4B(result);
  devices::gpu::nvidia::tesla::geforce_gtx_260::add_4B(result);
  devices::gpu::nvidia::tesla::geforce_gtx_260::add_8B(result);
  devices::gpu::amd::northern_islands::scrapper::add_4B(result);
  devices::gpu::nvidia::maxwell::geforce_gtx_750_ti::add_4B(result);
  devices::gpu::nvidia::maxwell::geforce_gtx_750_ti::add_8B(result);
  devices::gpu::nvidia::fermi::geforce_gtx_470::add_4B(result);
  devices::gpu::nvidia::fermi::geforce_gtx_470::add_8B(result);
  devices::gpu::nvidia::fermi::tesla_c2050::add_4B(result);
  devices::gpu::nvidia::fermi::tesla_c2050::add_8B(result);
  devices::gpu::amd::northern_islands::barts::add_4B(result);

  return result;
}

static database_type<matrix_axpy_template::parameters_type> matrix_axpy = init_matrix_axpy();

template<class NumericT>
matrix_axpy_template::parameters_type const & matrix_axpy_params(ocl::device const & device)
{
  return get_parameters<NumericT>(matrix_axpy, device);
}

}
}
}
#endif
