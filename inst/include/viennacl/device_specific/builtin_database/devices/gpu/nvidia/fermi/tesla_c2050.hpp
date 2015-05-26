#ifndef VIENNACL_DEVICE_SPECIFIC_BUILTIN_DATABASE_DEVICES_GPU_NVIDIA_FERMI_TESLA_C2050_HPP_
#define VIENNACL_DEVICE_SPECIFIC_BUILTIN_DATABASE_DEVICES_GPU_NVIDIA_FERMI_TESLA_C2050_HPP_

#include "viennacl/device_specific/templates/matrix_product_template.hpp"

#include "viennacl/device_specific/templates/row_wise_reduction_template.hpp"

#include "viennacl/device_specific/templates/matrix_axpy_template.hpp"

#include "viennacl/device_specific/templates/reduction_template.hpp"

#include "viennacl/device_specific/templates/vector_axpy_template.hpp"

#include "viennacl/device_specific/forwards.h"
#include "viennacl/device_specific/builtin_database/common.hpp"

namespace viennacl{
namespace device_specific{
namespace builtin_database{
namespace devices{
namespace gpu{
namespace nvidia{
namespace fermi{
namespace tesla_c2050{

inline void add_8B(database_type<matrix_product_template::parameters_type> & db, char_to_type<'T'>, char_to_type<'T'>)
{
  db.add_8B(nvidia_id, CL_DEVICE_TYPE_GPU, ocl::fermi, "Tesla C2050", matrix_product_template::parameters_type(1,4,32,32,8,1,2,FETCH_FROM_LOCAL,FETCH_FROM_GLOBAL_STRIDED,16,8));
}

inline void add_8B(database_type<matrix_product_template::parameters_type> & db, char_to_type<'T'>, char_to_type<'N'>)
{
  db.add_8B(nvidia_id, CL_DEVICE_TYPE_GPU, ocl::fermi, "Tesla C2050", matrix_product_template::parameters_type(1,16,32,32,4,1,4,FETCH_FROM_LOCAL,FETCH_FROM_GLOBAL_STRIDED,32,16));
}

inline void add_8B(database_type<matrix_product_template::parameters_type> & db, char_to_type<'N'>, char_to_type<'T'>)
{
  db.add_8B(nvidia_id, CL_DEVICE_TYPE_GPU, ocl::fermi, "Tesla C2050", matrix_product_template::parameters_type(1,4,128,64,4,1,4,FETCH_FROM_LOCAL,FETCH_FROM_GLOBAL_CONTIGUOUS,16,16));
}

inline void add_8B(database_type<matrix_product_template::parameters_type> & db, char_to_type<'N'>, char_to_type<'N'>)
{
  db.add_8B(nvidia_id, CL_DEVICE_TYPE_GPU, ocl::fermi, "Tesla C2050", matrix_product_template::parameters_type(1,16,16,16,4,1,4,FETCH_FROM_LOCAL,FETCH_FROM_LOCAL,16,16));
}

inline void add_4B(database_type<matrix_product_template::parameters_type> & db, char_to_type<'T'>, char_to_type<'T'>)
{
  db.add_4B(nvidia_id, CL_DEVICE_TYPE_GPU, ocl::fermi, "Tesla C2050", matrix_product_template::parameters_type(1,16,32,16,4,1,4,FETCH_FROM_LOCAL,FETCH_FROM_LOCAL,32,8));
}

inline void add_4B(database_type<matrix_product_template::parameters_type> & db, char_to_type<'T'>, char_to_type<'N'>)
{
  db.add_4B(nvidia_id, CL_DEVICE_TYPE_GPU, ocl::fermi, "Tesla C2050", matrix_product_template::parameters_type(1,16,32,16,4,1,4,FETCH_FROM_LOCAL,FETCH_FROM_LOCAL,32,8));
}

inline void add_4B(database_type<matrix_product_template::parameters_type> & db, char_to_type<'N'>, char_to_type<'T'>)
{
  db.add_4B(nvidia_id, CL_DEVICE_TYPE_GPU, ocl::fermi, "Tesla C2050", matrix_product_template::parameters_type(1,16,16,16,4,1,4,FETCH_FROM_LOCAL,FETCH_FROM_LOCAL,32,8));
}

inline void add_4B(database_type<matrix_product_template::parameters_type> & db, char_to_type<'N'>, char_to_type<'N'>)
{
  db.add_4B(nvidia_id, CL_DEVICE_TYPE_GPU, ocl::fermi, "Tesla C2050", matrix_product_template::parameters_type(1,16,32,16,4,1,4,FETCH_FROM_LOCAL,FETCH_FROM_LOCAL,32,8));
}

inline void add_8B(database_type<row_wise_reduction_template::parameters_type> & db, char_to_type<'T'>)
{
  db.add_8B(nvidia_id, CL_DEVICE_TYPE_GPU, ocl::fermi, "Tesla C2050", row_wise_reduction_template::parameters_type(1,1,128,2048,FETCH_FROM_GLOBAL_STRIDED));
}

inline void add_8B(database_type<row_wise_reduction_template::parameters_type> & db, char_to_type<'N'>)
{
  db.add_8B(nvidia_id, CL_DEVICE_TYPE_GPU, ocl::fermi, "Tesla C2050", row_wise_reduction_template::parameters_type(4,64,16,32,FETCH_FROM_GLOBAL_STRIDED));
}

inline void add_4B(database_type<row_wise_reduction_template::parameters_type> & db, char_to_type<'T'>)
{
  db.add_4B(nvidia_id, CL_DEVICE_TYPE_GPU, ocl::fermi, "Tesla C2050", row_wise_reduction_template::parameters_type(1,2,128,1024,FETCH_FROM_GLOBAL_STRIDED));
}

inline void add_4B(database_type<row_wise_reduction_template::parameters_type> & db, char_to_type<'N'>)
{
  db.add_4B(nvidia_id, CL_DEVICE_TYPE_GPU, ocl::fermi, "Tesla C2050", row_wise_reduction_template::parameters_type(2,64,8,512,FETCH_FROM_GLOBAL_STRIDED));
}

inline void add_8B(database_type<matrix_axpy_template::parameters_type> & db)
{
  db.add_8B(nvidia_id, CL_DEVICE_TYPE_GPU, ocl::fermi, "Tesla C2050", matrix_axpy_template::parameters_type(1,128,4,64,128,FETCH_FROM_GLOBAL_STRIDED));
}

inline void add_4B(database_type<matrix_axpy_template::parameters_type> & db)
{
  db.add_4B(nvidia_id, CL_DEVICE_TYPE_GPU, ocl::fermi, "Tesla C2050", matrix_axpy_template::parameters_type(1,64,4,128,128,FETCH_FROM_GLOBAL_STRIDED));
}

inline void add_8B(database_type<reduction_template::parameters_type> & db)
{
  db.add_8B(nvidia_id, CL_DEVICE_TYPE_GPU, ocl::fermi, "Tesla C2050", reduction_template::parameters_type(1,256,8192,FETCH_FROM_GLOBAL_STRIDED));
}

inline void add_4B(database_type<reduction_template::parameters_type> & db)
{
  db.add_4B(nvidia_id, CL_DEVICE_TYPE_GPU, ocl::fermi, "Tesla C2050", reduction_template::parameters_type(1,256,4096,FETCH_FROM_GLOBAL_STRIDED));
}

inline void add_8B(database_type<vector_axpy_template::parameters_type> & db)
{
  db.add_8B(nvidia_id, CL_DEVICE_TYPE_GPU, ocl::fermi, "Tesla C2050", vector_axpy_template::parameters_type(1,256,32768,FETCH_FROM_GLOBAL_STRIDED));
}

inline void add_4B(database_type<vector_axpy_template::parameters_type> & db)
{
  db.add_4B(nvidia_id, CL_DEVICE_TYPE_GPU, ocl::fermi, "Tesla C2050", vector_axpy_template::parameters_type(1,256,32768,FETCH_FROM_GLOBAL_STRIDED));
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
