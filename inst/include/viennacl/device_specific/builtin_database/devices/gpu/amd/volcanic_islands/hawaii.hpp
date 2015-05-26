#ifndef VIENNACL_DEVICE_SPECIFIC_BUILTIN_DATABASE_DEVICES_GPU_AMD_VOLCANIC_ISLANDS_HPP_
#define VIENNACL_DEVICE_SPECIFIC_BUILTIN_DATABASE_DEVICES_GPU_AMD_VOLCANIC_ISLANDS_HPP_

#include "viennacl/device_specific/templates/matrix_product_template.hpp"

#include "viennacl/device_specific/templates/row_wise_reduction_template.hpp"

#include "viennacl/device_specific/templates/reduction_template.hpp"

#include "viennacl/device_specific/templates/matrix_axpy_template.hpp"

#include "viennacl/device_specific/templates/vector_axpy_template.hpp"

#include "viennacl/device_specific/forwards.h"
#include "viennacl/device_specific/builtin_database/common.hpp"

namespace viennacl{
namespace device_specific{
namespace builtin_database{
namespace devices{
namespace gpu{
namespace amd{
namespace volcanic_islands{
namespace hawaii{

inline void add_8B(database_type<matrix_product_template::parameters_type> & db, char_to_type<'T'>, char_to_type<'T'>)
{
  db.add_8B(amd_id, CL_DEVICE_TYPE_GPU, ocl::volcanic_islands, "Hawaii", matrix_product_template::parameters_type(1,8,16,32,4,1,4,FETCH_FROM_LOCAL,FETCH_FROM_LOCAL,16,16));
}

inline void add_8B(database_type<matrix_product_template::parameters_type> & db, char_to_type<'T'>, char_to_type<'N'>)
{
  db.add_8B(amd_id, CL_DEVICE_TYPE_GPU, ocl::volcanic_islands, "Hawaii", matrix_product_template::parameters_type(1,8,16,32,4,1,4,FETCH_FROM_LOCAL,FETCH_FROM_LOCAL,16,16));
}

inline void add_8B(database_type<matrix_product_template::parameters_type> & db, char_to_type<'N'>, char_to_type<'T'>)
{
  db.add_8B(amd_id, CL_DEVICE_TYPE_GPU, ocl::volcanic_islands, "Hawaii", matrix_product_template::parameters_type(2,8,8,8,6,1,6,FETCH_FROM_LOCAL,FETCH_FROM_LOCAL,8,8));
}

inline void add_8B(database_type<matrix_product_template::parameters_type> & db, char_to_type<'N'>, char_to_type<'N'>)
{
  db.add_8B(amd_id, CL_DEVICE_TYPE_GPU, ocl::volcanic_islands, "Hawaii", matrix_product_template::parameters_type(1,16,16,16,2,1,8,FETCH_FROM_LOCAL,FETCH_FROM_LOCAL,16,16));
}

inline void add_4B(database_type<matrix_product_template::parameters_type> & db, char_to_type<'T'>, char_to_type<'T'>)
{
  db.add_4B(amd_id, CL_DEVICE_TYPE_GPU, ocl::volcanic_islands, "Hawaii", matrix_product_template::parameters_type(1,1,2,64,8,2,4,FETCH_FROM_GLOBAL_CONTIGUOUS,FETCH_FROM_GLOBAL_STRIDED,0,0));
}

inline void add_4B(database_type<matrix_product_template::parameters_type> & db, char_to_type<'T'>, char_to_type<'N'>)
{
  db.add_4B(amd_id, CL_DEVICE_TYPE_GPU, ocl::volcanic_islands, "Hawaii", matrix_product_template::parameters_type(1,16,16,16,2,1,4,FETCH_FROM_LOCAL,FETCH_FROM_LOCAL,16,16));
}

inline void add_4B(database_type<matrix_product_template::parameters_type> & db, char_to_type<'N'>, char_to_type<'T'>)
{
  db.add_4B(amd_id, CL_DEVICE_TYPE_GPU, ocl::volcanic_islands, "Hawaii", matrix_product_template::parameters_type(2,16,16,16,6,1,6,FETCH_FROM_LOCAL,FETCH_FROM_LOCAL,16,16));
}

inline void add_4B(database_type<matrix_product_template::parameters_type> & db, char_to_type<'N'>, char_to_type<'N'>)
{
  db.add_4B(amd_id, CL_DEVICE_TYPE_GPU, ocl::volcanic_islands, "Hawaii", matrix_product_template::parameters_type(1,64,64,4,2,4,8,FETCH_FROM_GLOBAL_STRIDED,FETCH_FROM_LOCAL,64,4));
}

inline void add_8B(database_type<row_wise_reduction_template::parameters_type> & db, char_to_type<'T'>)
{
  db.add_8B(amd_id, CL_DEVICE_TYPE_GPU, ocl::volcanic_islands, "Hawaii", row_wise_reduction_template::parameters_type(1,1,128,512,FETCH_FROM_GLOBAL_STRIDED));
}

inline void add_8B(database_type<row_wise_reduction_template::parameters_type> & db, char_to_type<'N'>)
{
  db.add_8B(amd_id, CL_DEVICE_TYPE_GPU, ocl::volcanic_islands, "Hawaii", row_wise_reduction_template::parameters_type(8,32,8,32768,FETCH_FROM_GLOBAL_STRIDED));
}

inline void add_4B(database_type<row_wise_reduction_template::parameters_type> & db, char_to_type<'T'>)
{
  db.add_4B(amd_id, CL_DEVICE_TYPE_GPU, ocl::volcanic_islands, "Hawaii", row_wise_reduction_template::parameters_type(1,1,128,4096,FETCH_FROM_GLOBAL_STRIDED));
}

inline void add_4B(database_type<row_wise_reduction_template::parameters_type> & db, char_to_type<'N'>)
{
  db.add_4B(amd_id, CL_DEVICE_TYPE_GPU, ocl::volcanic_islands, "Hawaii", row_wise_reduction_template::parameters_type(4,32,8,32768,FETCH_FROM_GLOBAL_STRIDED));
}

inline void add_8B(database_type<reduction_template::parameters_type> & db)
{
  db.add_8B(amd_id, CL_DEVICE_TYPE_GPU, ocl::volcanic_islands, "Hawaii", reduction_template::parameters_type(1,256,128,FETCH_FROM_GLOBAL_STRIDED));
}

inline void add_4B(database_type<reduction_template::parameters_type> & db)
{
  db.add_4B(amd_id, CL_DEVICE_TYPE_GPU, ocl::volcanic_islands, "Hawaii", reduction_template::parameters_type(1,128,512,FETCH_FROM_GLOBAL_STRIDED));
}

inline void add_8B(database_type<matrix_axpy_template::parameters_type> & db)
{
  db.add_8B(amd_id, CL_DEVICE_TYPE_GPU, ocl::volcanic_islands, "Hawaii", matrix_axpy_template::parameters_type(1,64,2,16,16,FETCH_FROM_GLOBAL_STRIDED));
}

inline void add_4B(database_type<matrix_axpy_template::parameters_type> & db)
{
  db.add_4B(amd_id, CL_DEVICE_TYPE_GPU, ocl::volcanic_islands, "Hawaii", matrix_axpy_template::parameters_type(1,64,4,4,64,FETCH_FROM_GLOBAL_STRIDED));
}

inline void add_8B(database_type<vector_axpy_template::parameters_type> & db)
{
  db.add_8B(amd_id, CL_DEVICE_TYPE_GPU, ocl::volcanic_islands, "Hawaii", vector_axpy_template::parameters_type(1,64,8192,FETCH_FROM_GLOBAL_STRIDED));
}

inline void add_4B(database_type<vector_axpy_template::parameters_type> & db)
{
  db.add_4B(amd_id, CL_DEVICE_TYPE_GPU, ocl::volcanic_islands, "Hawaii", vector_axpy_template::parameters_type(1,256,32768,FETCH_FROM_GLOBAL_STRIDED));
}

}
}
}
}
}
}
}
}
#endif
