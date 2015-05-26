## RViennaCL: ViennaCL Headers for R  
[![Build Status](https://travis-ci.org/cdeterman/RViennaCL.svg)](https://travis-ci.org/cdeterman/RViennaCL) [![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/github/cdeterman/RViennaCL?branch=master)](https://ci.appveyor.com/project/cdeterman/RViennaCL)

This package provides [R](http://www.r-project.org) with access to
[ViennaCL](http://viennacl.sourceforge.net/) header files.  
[ViennaCL](http://viennacl.sourceforge.net/) provides a free C++ source 
library for simple computing on multi-core architectures (GPU, MIC) and
multi-core CPUs.  The library supports CUDA, OpenCL, and OpenMP.  It also
includes BLAS level 1-3 support and linear algebra solvers.

This package aims to provide a simple means of linking to the 
[ViennaCL](http://viennacl.sourceforge.net/) header files for use among CRAN
packages. Similar to the popular R package [BH](http://cran.r-project.org/web/packages/BH/index.html), 
by placing these libraries in this package, we offer a more
efficient distribution system for CRAN as replication of this code in the
sources of other packages is avoided.

It can be used via the `LinkingTo:` field in the `DESCRIPTION` field of an R
package --- and the R package infrastructure tools will then know how to set
include flags correctly on all architectures supported by R.

Note that this is only for the header only aspects of this package. If you wish
to link against the libviennacl shared object, you must create this file
separately and link against it. 

### Authors 

Charles Determan Jr.

