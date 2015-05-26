#ifndef VIENNACL_LINALG_OPENCL_KERNELS_VECTOR_HPP
#define VIENNACL_LINALG_OPENCL_KERNELS_VECTOR_HPP

#include "viennacl/tools/tools.hpp"

#include "viennacl/vector_proxy.hpp"

#include "viennacl/scheduler/forwards.h"
#include "viennacl/scheduler/io.hpp"
#include "viennacl/scheduler/preset.hpp"

#include "viennacl/ocl/kernel.hpp"
#include "viennacl/ocl/platform.hpp"
#include "viennacl/ocl/utils.hpp"

#include "viennacl/device_specific/execution_handler.hpp"

#include "viennacl/device_specific/builtin_database/vector_axpy.hpp"
#include "viennacl/device_specific/builtin_database/reduction.hpp"

/** @file viennacl/linalg/opencl/kernels/vector.hpp
 *  @brief OpenCL kernel file for vector operations */
namespace viennacl
{
namespace linalg
{
namespace opencl
{
namespace kernels
{

template<typename NumericT, typename ScalarT>
static void generate_inner_prod_impl(device_specific::execution_handler & handler, std::string const & prefix, device_specific::reduction_template::parameters_type const & parameters, vcl_size_t vector_num,
                                     viennacl::vector<NumericT> const * x, viennacl::vector<NumericT> const * y, ScalarT const* s)
{
  namespace ds = device_specific;
  ds::statements_container::data_type statements;
  for (unsigned int i = 0; i < vector_num; ++i)
    statements.push_back(scheduler::preset::inner_prod(s, x, y));
  handler.add(prefix, ds::reduction_template(parameters), ds::statements_container(statements,ds::statements_container::INDEPENDENT));
}



// main kernel class
/** @brief Main kernel class for generating OpenCL kernels for operations on/with viennacl::vector<> without involving matrices, multiple inner products, or element-wise operations other than addition or subtraction. */
template<typename NumericT>
class vector
{
private:

  template<typename ScalarT1, typename ScalarT2>
  static void generate_avbv_impl2(device_specific::execution_handler & handler, std::string const & prefix, device_specific::vector_axpy_template::parameters_type const & parameters, scheduler::operation_node_type ASSIGN_OP,
                                 viennacl::vector_base<NumericT> const * x, viennacl::vector_base<NumericT> const * y, ScalarT1 const * a,
                                 viennacl::vector_base<NumericT> const * z, ScalarT2 const * b)
  {
    namespace ds = device_specific;
    handler.add(prefix + "0000", ds::vector_axpy_template(parameters), scheduler::preset::avbv(ASSIGN_OP, x, y, a, false, false, z, b, false, false));
    handler.add(prefix + "1000", ds::vector_axpy_template(parameters), scheduler::preset::avbv(ASSIGN_OP, x, y, a, true, false, z, b, false, false));
    handler.add(prefix + "0100", ds::vector_axpy_template(parameters), scheduler::preset::avbv(ASSIGN_OP, x, y, a, false, true, z, b, false, false));
    handler.add(prefix + "1100", ds::vector_axpy_template(parameters), scheduler::preset::avbv(ASSIGN_OP, x, y, a, true, true, z, b, false, false));
    if (b)
    {
      handler.add(prefix + "0010", ds::vector_axpy_template(parameters), scheduler::preset::avbv(ASSIGN_OP, x, y, a, false, false, z, b, true, false));
      handler.add(prefix + "1010", ds::vector_axpy_template(parameters), scheduler::preset::avbv(ASSIGN_OP, x, y, a, true, false, z, b, true, false));
      handler.add(prefix + "0110", ds::vector_axpy_template(parameters), scheduler::preset::avbv(ASSIGN_OP, x, y, a, false, true, z, b, true, false));
      handler.add(prefix + "1110", ds::vector_axpy_template(parameters), scheduler::preset::avbv(ASSIGN_OP, x, y, a, true, true, z, b, true, false));

      handler.add(prefix + "0001", ds::vector_axpy_template(parameters), scheduler::preset::avbv(ASSIGN_OP, x, y, a, false, false, z, b, false, true));
      handler.add(prefix + "1001", ds::vector_axpy_template(parameters), scheduler::preset::avbv(ASSIGN_OP, x, y, a, true, false, z, b, false, true));
      handler.add(prefix + "0101", ds::vector_axpy_template(parameters), scheduler::preset::avbv(ASSIGN_OP, x, y, a, false, true, z, b, false, true));
      handler.add(prefix + "1101", ds::vector_axpy_template(parameters), scheduler::preset::avbv(ASSIGN_OP, x, y, a, true, true, z, b, false, true));

      handler.add(prefix + "0011", ds::vector_axpy_template(parameters), scheduler::preset::avbv(ASSIGN_OP, x, y, a, false, false, z, b, true, true));
      handler.add(prefix + "1011", ds::vector_axpy_template(parameters), scheduler::preset::avbv(ASSIGN_OP, x, y, a, true, false, z, b, true, true));
      handler.add(prefix + "0111", ds::vector_axpy_template(parameters), scheduler::preset::avbv(ASSIGN_OP, x, y, a, false, true, z, b, true, true));
      handler.add(prefix + "1111", ds::vector_axpy_template(parameters), scheduler::preset::avbv(ASSIGN_OP, x, y, a, true, true, z, b, true, true));
    }
  }

  template<typename ScalarT>
  static void generate_avbv_impl(device_specific::execution_handler & handler, std::string const & prefix, device_specific::vector_axpy_template::parameters_type const & parameters, scheduler::operation_node_type ASSIGN_OP,
                                 viennacl::vector_base<NumericT> const * x, viennacl::vector_base<NumericT> const * y, ScalarT const * ha, viennacl::scalar<NumericT> const * da,
                                 viennacl::vector_base<NumericT> const * z, ScalarT const * hb, viennacl::scalar<NumericT> const * db)
  {
    //x ASSIGN_OP a*y
    generate_avbv_impl2(handler, prefix + "hv_", parameters, ASSIGN_OP, x, y, ha, (viennacl::vector<NumericT>*)NULL, (NumericT*)NULL);
    generate_avbv_impl2(handler, prefix + "dv_", parameters, ASSIGN_OP, x, y, da, (viennacl::vector<NumericT>*)NULL, (NumericT*)NULL);

    //x ASSIGN_OP a*y + b*z
    generate_avbv_impl2(handler, prefix + "hvhv_", parameters, ASSIGN_OP, x, y, ha, z, hb);
    generate_avbv_impl2(handler, prefix + "dvhv_", parameters, ASSIGN_OP, x, y, da, z, hb);
    generate_avbv_impl2(handler, prefix + "hvdv_", parameters, ASSIGN_OP, x, y, ha, z, db);
    generate_avbv_impl2(handler, prefix + "dvdv_", parameters, ASSIGN_OP, x, y, da, z, db);
  }

public:
  static device_specific::execution_handler & execution_handler(viennacl::ocl::context & ctx)
  {
    static std::map<cl_context, device_specific::execution_handler> handlers_map;
    cl_context h = ctx.handle().get();
    if (handlers_map.find(h) == handlers_map.end())
    {
      viennacl::ocl::DOUBLE_PRECISION_CHECKER<NumericT>::apply(ctx);

      namespace ds = viennacl::device_specific;
      viennacl::ocl::device const & device = ctx.current_device();
      handlers_map.insert(std::make_pair(h, ds::execution_handler(viennacl::ocl::type_to_string<NumericT>::apply() + "_vector", ctx, device)));
      ds::execution_handler & handler = handlers_map.at(h);

      viennacl::vector<NumericT> x;
      viennacl::vector<NumericT> y;
      viennacl::scalar_vector<NumericT> scalary(0,0,viennacl::context(ctx));
      viennacl::vector<NumericT> z;
      viennacl::scalar<NumericT> da;
      viennacl::scalar<NumericT> db;
      NumericT ha;
      NumericT hb;

      ds::vector_axpy_template::parameters_type vector_axpy_params = ds::builtin_database::vector_axpy_params<NumericT>(device);
      ds::reduction_template::parameters_type     reduction_params = ds::builtin_database::reduction_params<NumericT>(device);

      generate_avbv_impl(handler, "assign_", vector_axpy_params, scheduler::OPERATION_BINARY_ASSIGN_TYPE, &x, &y, &ha, &da, &z, &hb, &db);
      generate_avbv_impl(handler, "ip_add_", vector_axpy_params, scheduler::OPERATION_BINARY_INPLACE_ADD_TYPE, &x, &y, &ha, &da, &z, &hb, &db);

      handler.add("plane_rotation", ds::vector_axpy_template(vector_axpy_params), scheduler::preset::plane_rotation(&x, &y, &ha, &hb));
      handler.add("swap", ds::vector_axpy_template(vector_axpy_params), scheduler::preset::swap(&x, &y));
      handler.add("assign_cpu", ds::vector_axpy_template(vector_axpy_params), scheduler::preset::assign_cpu(&x, &scalary));

      generate_inner_prod_impl(handler, "inner_prod", reduction_params, 1, &x, &y, &da);

      handler.add("norm_1", ds::reduction_template(reduction_params), scheduler::preset::norm_1(&da, &x));
      bool is_float_or_double = is_floating_point<NumericT>::value;
      if (is_float_or_double) //BIND_TO_HANDLE for optimization (will load x once in the internal inner product)
        handler.add("norm_2", ds::reduction_template(reduction_params, ds::BIND_TO_HANDLE), scheduler::preset::norm_2(&da, &x));
      handler.add("norm_inf", ds::reduction_template(reduction_params), scheduler::preset::norm_inf(&da, &x));
      handler.add("index_norm_inf", ds::reduction_template(reduction_params), scheduler::preset::index_norm_inf(&da, &x));
      handler.add("sum", ds::reduction_template(reduction_params), scheduler::preset::sum(&da, &x));
      handler.add("max", ds::reduction_template(reduction_params), scheduler::preset::max(&da, &x));
      handler.add("min", ds::reduction_template(reduction_params), scheduler::preset::min(&da, &x));
    }
    return handlers_map.at(h);
  }
};

// main kernel class
/** @brief Main kernel class for generating OpenCL kernels for operations on/with viennacl::vector<> without involving matrices, multiple inner products, or element-wise operations other than addition or subtraction. */
template<typename NumericT>
class vector_multi_inner_prod
{
public:
  static device_specific::execution_handler & execution_handler(viennacl::ocl::context & ctx)
  {
    static std::map<cl_context, device_specific::execution_handler> handlers_map;
    cl_context h = ctx.handle().get();
    if (handlers_map.find(h) == handlers_map.end())
    {
      viennacl::ocl::DOUBLE_PRECISION_CHECKER<NumericT>::apply(ctx);

      namespace ds = viennacl::device_specific;

      viennacl::ocl::device const & device = ctx.current_device();
      handlers_map.insert(std::make_pair(h, ds::execution_handler(viennacl::ocl::type_to_string<NumericT>::apply() + "_vector_multi_inner_prod", ctx, device)));
      ds::execution_handler & handler = handlers_map.at(h);

      ds::reduction_template::parameters_type reduction_params = ds::builtin_database::reduction_params<NumericT>(device);

      //Dummy holders for the statements
      viennacl::vector<NumericT> x;
      viennacl::vector<NumericT> y;
      viennacl::vector<NumericT> res;
      viennacl::vector_range< viennacl::vector_base<NumericT> > da(res, viennacl::range(0,1));

      generate_inner_prod_impl(handler, "inner_prod_1", reduction_params, 1, &x, &y, &da);
      generate_inner_prod_impl(handler, "inner_prod_2", reduction_params, 2, &x, &y, &da);
      generate_inner_prod_impl(handler, "inner_prod_3", reduction_params, 3, &x, &y, &da);
      generate_inner_prod_impl(handler, "inner_prod_4", reduction_params, 4, &x, &y, &da);
      generate_inner_prod_impl(handler, "inner_prod_8", reduction_params, 8, &x, &y, &da);
    }
    return handlers_map.at(h);
  }
};

// main kernel class
/** @brief Main kernel class for generating OpenCL kernels for elementwise operations other than addition and subtraction on/with viennacl::vector<>. */
template<typename NumericT>
struct vector_element
{

public:
  static device_specific::execution_handler & execution_handler(viennacl::ocl::context & ctx)
  {
    static std::map<cl_context, device_specific::execution_handler> handlers_map;
    cl_context h = ctx.handle().get();
    if (handlers_map.find(h) == handlers_map.end())
    {
      viennacl::ocl::DOUBLE_PRECISION_CHECKER<NumericT>::apply(ctx);

      namespace ds = viennacl::device_specific;
      using namespace scheduler;
      using device_specific::tree_parsing::operator_string;

      std::string numeric_string = viennacl::ocl::type_to_string<NumericT>::apply();
      viennacl::ocl::device const & device = ctx.current_device();
      handlers_map.insert(std::make_pair(h, ds::execution_handler(viennacl::ocl::type_to_string<NumericT>::apply() + "_vector_element", ctx, device)));
      ds::execution_handler & handler = handlers_map.at(h);
      ds::vector_axpy_template::parameters_type vector_axpy_params = ds::builtin_database::vector_axpy_params<NumericT>(device);

      viennacl::vector<NumericT> x;
      viennacl::vector<NumericT> y;
      viennacl::vector<NumericT> z;

      // unary operations
#define VIENNACL_ADD_UNARY(OPTYPE) handler.add(operator_string(OPTYPE), ds::vector_axpy_template(vector_axpy_params),scheduler::preset::unary_element_op(&x, &y, OPTYPE))
      if (numeric_string == "float" || numeric_string == "double")
      {
        VIENNACL_ADD_UNARY(OPERATION_UNARY_ACOS_TYPE);
        VIENNACL_ADD_UNARY(OPERATION_UNARY_ASIN_TYPE);
        VIENNACL_ADD_UNARY(OPERATION_UNARY_ATAN_TYPE);
        VIENNACL_ADD_UNARY(OPERATION_UNARY_CEIL_TYPE);
        VIENNACL_ADD_UNARY(OPERATION_UNARY_COS_TYPE);
        VIENNACL_ADD_UNARY(OPERATION_UNARY_COSH_TYPE);
        VIENNACL_ADD_UNARY(OPERATION_UNARY_EXP_TYPE);
        VIENNACL_ADD_UNARY(OPERATION_UNARY_FABS_TYPE);
        VIENNACL_ADD_UNARY(OPERATION_UNARY_FLOOR_TYPE);
        VIENNACL_ADD_UNARY(OPERATION_UNARY_LOG_TYPE);
        VIENNACL_ADD_UNARY(OPERATION_UNARY_LOG10_TYPE);
        VIENNACL_ADD_UNARY(OPERATION_UNARY_SIN_TYPE);
        VIENNACL_ADD_UNARY(OPERATION_UNARY_SINH_TYPE);
        VIENNACL_ADD_UNARY(OPERATION_UNARY_SQRT_TYPE);
        VIENNACL_ADD_UNARY(OPERATION_UNARY_TAN_TYPE);
        VIENNACL_ADD_UNARY(OPERATION_UNARY_TANH_TYPE);
      }
      else
      {
        VIENNACL_ADD_UNARY(OPERATION_UNARY_ABS_TYPE);
      }
#undef VIENNACL_ADD_UNARY

      // binary operations
#define VIENNACL_ADD_BINARY(OPTYPE) handler.add(operator_string(OPTYPE), ds::vector_axpy_template(vector_axpy_params),scheduler::preset::binary_element_op(&x, &y, &z, OPTYPE))
      VIENNACL_ADD_BINARY(OPERATION_BINARY_ELEMENT_DIV_TYPE);
      VIENNACL_ADD_BINARY(OPERATION_BINARY_ELEMENT_PROD_TYPE);
      if (numeric_string == "float" || numeric_string == "double")
      {
        VIENNACL_ADD_BINARY(OPERATION_BINARY_ELEMENT_POW_TYPE);
      }
#undef VIENNACL_ADD_BINARY

    }
    return handlers_map.at(h);
  }
};

}  // namespace kernels
}  // namespace opencl
}  // namespace linalg
}  // namespace viennacl
#endif

