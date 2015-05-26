#ifndef VIENNACL_DEVICE_SPECIFIC_BUILTIN_DATABASE_COMMON_HPP_
#define VIENNACL_DEVICE_SPECIFIC_BUILTIN_DATABASE_COMMON_HPP_

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

/** @file viennacl/device_specific/builtin_database/common.hpp
*
* Common routines such as device lookup for the built-in device database.
*/

#include "viennacl/ocl/device_utils.hpp"

#include "viennacl/scheduler/forwards.h"

#include "viennacl/device_specific/forwards.h"

namespace viennacl
{
namespace device_specific
{
namespace builtin_database
{

using scheduler::FLOAT_TYPE;
using scheduler::DOUBLE_TYPE;
using namespace viennacl::ocl;

template<class ParamT>
class database_type
{
public:

  //Because it would be too easy to use nested maps directly.
  //THANKS, VISUAL STUDIO.
  struct expression_t{ typedef std::map<scheduler::statement_node_numeric_type, ParamT> map_t; map_t d; };
  struct device_name_t{ typedef std::map<device_name_type, expression_t> map_t; map_t d; };
  struct device_architecture_t{ typedef std::map<ocl::device_architecture_family, device_name_t> map_t; map_t d; };
  struct device_type_t{ typedef std::map<device_type, device_architecture_t> map_t; map_t d; };
  struct type{ typedef std::map<vendor_id_type, device_type_t> map_t; map_t d; };
  type map;

  database_type<ParamT> & operator()(vendor_id_type p0, device_type p1, ocl::device_architecture_family p2, device_name_type p3, scheduler::statement_node_numeric_type p4, ParamT const & p5)
  {
    map.d[p0].d[p1].d[p2].d[p3].d.insert(std::make_pair(p4, p5));
    return *this;
  }

  database_type<ParamT> & add_1B(vendor_id_type p0, device_type p1, ocl::device_architecture_family p2, device_name_type p3, ParamT const & p5)
  {
    return (*this)(p0, p1, p2, p3, scheduler::CHAR_TYPE, p5)
        (p0, p1, p2, p3, scheduler::UCHAR_TYPE, p5);
  }

  database_type<ParamT> & add_2B(vendor_id_type p0, device_type p1, ocl::device_architecture_family p2, device_name_type p3, ParamT const & p5)
  {
    return (*this)(p0, p1, p2, p3, scheduler::SHORT_TYPE, p5)
        (p0, p1, p2, p3, scheduler::USHORT_TYPE, p5)
        (p0, p1, p2, p3, scheduler::HALF_TYPE, p5);
  }

  database_type<ParamT> & add_4B(vendor_id_type p0, device_type p1, ocl::device_architecture_family p2, device_name_type p3, ParamT const & p5)
  {
    return (*this)(p0, p1, p2, p3, scheduler::INT_TYPE, p5)
        (p0, p1, p2, p3, scheduler::UINT_TYPE, p5)
        (p0, p1, p2, p3, scheduler::FLOAT_TYPE, p5);
  }

  database_type<ParamT> & add_8B(vendor_id_type p0, device_type p1, ocl::device_architecture_family p2, device_name_type p3, ParamT const & p5)
  {
    return (*this)(p0, p1, p2, p3, scheduler::LONG_TYPE, p5)
        (p0, p1, p2, p3, scheduler::ULONG_TYPE, p5)
        (p0, p1, p2, p3, scheduler::DOUBLE_TYPE, p5);
  }

  ParamT const & at(vendor_id_type p0, device_type p1, ocl::device_architecture_family p2, device_name_type p3, scheduler::statement_node_numeric_type p4) const
  {
    return map.d.at(p0).d.at(p1).d.at(p2).d.at(p3).d.at(p4);
  }


};


/** @brief Get the profile for a device and a descriptor
*
* There are built-in defaults for CPUs, Accelerators, GPUs.
*/
template<class NumericT, class ParamT>
inline ParamT const & get_parameters(database_type<ParamT> const & database, viennacl::ocl::device const & device)
{
  scheduler::statement_node_numeric_type numeric_type = scheduler::statement_node_numeric_type(scheduler::result_of::numeric_type_id<NumericT>::value);

  device_type dev_type = device.type();
  vendor_id_type vendor_id = device.vendor_id();
  ocl::device_architecture_family device_architecture = device.architecture_family();
  std::string const & device_name = device.name();


  /*-Vendor ID-*/
  //  std::cout << "Looking up vendor ID..." << std::endl;
  typename database_type<ParamT>::type::map_t::const_iterator vendor_it = database.map.d.find(vendor_id);
  //Vendor not recognized =>  device type default
  if (vendor_it==database.map.d.end())
    return database.at(ocl::unknown_id, dev_type, ocl::unknown, "", numeric_type);

  /*-Device Type-*/
  //  std::cout << "Looking up device type..." << std::endl;
  typename database_type<ParamT>::device_type_t::map_t::const_iterator device_type_it = vendor_it->second.d.find(dev_type);
  //Device type not recognized for this vendor => device type default
  if (device_type_it==vendor_it->second.d.end())
    return database.at(ocl::unknown_id, dev_type, ocl::unknown, "", numeric_type);

  /*-Device Architecture-*/
  //  std::cout << "Looking up device architecture..." << std::endl;
  typename database_type<ParamT>::device_architecture_t::map_t::const_iterator architecture_it = device_type_it->second.d.find(device_architecture);
  //Architecture not found. We try to find the closest architecture available.
  if (architecture_it==device_type_it->second.d.end())
  {
    typename database_type<ParamT>::device_architecture_t::map_t::const_iterator current_it = device_type_it->second.d.begin();
    architecture_it = current_it;
    int closest_arch = current_it->first - device_architecture;
    while (current_it!=device_type_it->second.d.end())
    {
      int arch_diff = std::abs(static_cast<int>(current_it->first) - static_cast<int>(device_architecture));
      if (arch_diff < closest_arch)
      {
        architecture_it = current_it;
        closest_arch = arch_diff;
      }
      current_it++;
    }
  }

  /*-Device Name-*/
  //  std::cout << "Looking up device name..." << std::endl;
  typename database_type<ParamT>::device_name_t::map_t::const_iterator device_name_it = architecture_it->second.d.find(device_name);
  //Name not found. We just take the first device for the architecture
  if (device_name_it==architecture_it->second.d.end())
  {
    device_name_it = architecture_it->second.d.begin();
  }

  //  std::cout << "Looking up expression name.." << std::endl;
  /*-Expression-*/
  typename database_type<ParamT>::expression_t::map_t::const_iterator expression_it = device_name_it->second.d.find(numeric_type);
  //Expression not found => Vendor default
  if (expression_it==device_name_it->second.d.end())
    return database.at(ocl::unknown_id, dev_type, ocl::unknown, "", numeric_type);

  //  std::cout << "Device found in the database! Getting profile..." << std::endl;
  //Everything okay. Return specific profile//
  return expression_it->second;
}


}
}
}
#endif
