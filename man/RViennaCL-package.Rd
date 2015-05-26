\name{RViennaCL-package}
\alias{RViennaCL-package}
\alias{RViennaCL}
\docType{package}
\title{
The ViennaCL C++ Library Headers
}
\description{
This package provides easy access for R packages to the ViennaCL library header
files.  The ViennaCL home page provides the following description:

The Vienna Computing Library (ViennaCL) is a free open-source scientific computing library written in C++ and provides CUDA, OpenCL and OpenMP computing backends. It enables simple, high-level access to the vast computing resources available on parallel architectures such as GPUs and is primarily focused on common linear algebra operations (BLAS levels 1, 2 and 3) and the solution of large systems of equations by means of iterative methods with optional preconditioners.
}
\details{
\tabular{ll}{
Package: \tab RViennaCL\cr
Type: \tab Package\cr
Version: \tab 1.6.2-0\cr
Date: \tab 2015-05-26\cr
License: \tab GPL-3\cr
}
  ViennaCL provides free, portable C++ source
  libraries with a large part implemented as template headers.
  As done with the BH package, I have placed these libraries in
  this package as a more efficient distribution system for CRAN.
  The idea is that you can write a package that depends on the
  ViennaCL library and yet you do not need to distribute a copy 
  of this code with your package.

  Bug reports can also be registered at the GitHub issue tracker at
  \url{https://github.com/cdeterman/RViennaCL/issues}.
}
\author{
\packageAuthor{RViennaCL}

Maintainer: \packageMaintainer{RViennaCL}
}
\references{
http://viennacl.sourceforge.net/
}
\keyword{ package }
\examples{
#None
}
