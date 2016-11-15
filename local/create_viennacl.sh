#!/bin/bash
## Charles Determan, 2015
##
## This is essentially mirrored from the BH package
## Given the size of ViennaCL compared to Boost may
## not need this script.

## Version Variables
##
## -- standard git checkout
pkgdir="${HOME}/RViennaCL"
## -- current ViennaCL version, placed eg in ${pkgdir}/local/
viennacltargz="ViennaCL-1.7.1.tar.gz"
date="2016-11-01"
## -- state if development version from github
dev=false

## Internal constants/variables
## local directory
localdir="${pkgdir}/local"
## Derive the root name from the tarball
viennaclVer=$(basename ${viennacltargz} ".tar.gz")
## Create ViennaCL root directory name
viennaclRoot="${localdir}/${viennaclVer}"
## Create tarball file name with full path
viennaclSources="${localdir}/${viennacltargz}"
## target directory for headers
pkgincl="${pkgdir}/inst/include"
## local files containing R package pieces
localfiles="${pkgdir}/local/files"

## Display current settings
echo "Using these settings:
Date:           ${date}
Version:        ${viennaclVer}
viennacltargz:    ${viennacltargz}
PkgDir:         ${pkgdir}
PkgIncl:        ${pkgincl}
LocalDir:       ${localdir}
LocalFiles:     ${localfiles}
ViennaCLroot:     ${viennaclRoot}
ViennaCLsources:  ${viennaclSources}
"

## Sanity checks
if [ ! -f "${viennaclSources}" ]; then
    echo "ViennaCL input file ${viennaclSources} missing, exiting." 
    exit 1
fi

if [ -d ${ViennaCLroot} ]; then
    echo "Old ViennaCLroot directory exists, removing it (ie ${viennaclRoot})."
    rm -rf ${viennaclRoot}
fi


if [ 'ls -A ${pkgincl}' ]; then 
    echo "Include directory contains files, removing them.";
    rm -rf ${pkgincl}/*
fi

echo "Unpacking ${viennacltargz} into LocalDIR (ie ${localdir})."
 (cd ${localdir} && mkdir ${viennaclVer} && tar xzf ${viennaclSources} -C ${viennaclVer})

echo "Copying ViennaCL files from ${viennaclRoot} into inst/incl Dir (ie ${pkgincl})"
if [ "$dev" = true ]; then
	echo "using development version"
	cp -r ${viennaclRoot}/viennacl-dev/viennacl/ ${pkgincl}
  #echo "copying CL files"
  #cp -r ${viennaclRoot}/viennacl-dev-master/CL/ ${pkgincl}
else
  echo "using released version"
	# cp -r ${viennaclRoot}/${viennaclVer}/viennacl/ ${pkgincl}
	cp -r ${viennaclRoot}/viennacl/ ${pkgincl}
  #echo "copying CL files"
  #cp -r ${viennaclRoot}/${viennaclVer}/viennacl/CL/ ${pkgincl}
fi

echo "Changing all std::cout/std::cerr to Rcpp equivalent"
cd ${pkgincl}
#python ${localdir}/rcpp_vcl_regex.py

grep -rl "std::cout" viennacl | xargs sed -i s@"std::cout"@"Rcpp::Rcout"@g
grep -rl "std::cerr" viennacl | xargs sed -i s@"std::cerr"@"Rcpp::Rcerr"@g

# grep -rl "// std::cout" viennacl | xargs sed -i s@"// std::cout"@"//std::cout"@g
# grep -rl "// std::cerr" viennacl | xargs sed -i s@"// std::cerr"@"//std::cerr"@g
# echo "removed spaces"
# grep -rl " std::cout" viennacl | xargs sed -i s@" std::cout"@"\n#ifndef NO_RCPP_OUTPUT\nRcpp::Rcout"@g
# echo "changed couts"
# grep -rl " std::cerr" viennacl | xargs sed -i s@" std::cerr"@"\n#ifndef NO_RCPP_OUTPUT\nRcpp::Rcerr"@g
# echo "change cerrs"
# grep -rl "std::endl;" viennacl | xargs sed -i "/^Rcpp/s@std::endl;@std::endl;\n#endif"@g
# echo "added endifs"
# grep -rl "std::endl;" viennacl | xargs sed -i "/^Rcpp.*break;$/s@break;@break;\n#endif"@g
# echo "added break endifs"
# grep -rl "Rcpp::Rcerr" viennacl | xargs sed -iE "/^Rcpp::Rcerr.*/s@;@;\n#endif@"

# ^std::cout.*(?<!std::endl;)$
#^Rcpp.*(?<!\bstd::endl;)$
#grep -rl " Rcpp::Rcerr.* std::endl;" viennacl | xargs sed -i s@"std::endl;"@"std::endl;\n#endif"@g

echo "Adding Rcpp.h to files"
#grep -rl "^namespace viennacl" viennacl | xargs sed -i s@"^namespace viennacl"@"#ifndef NO_RCPP_OUTPUT\n#include <Rcpp.h>\n#endif\nnamespace viennacl"@g
grep -rl "^namespace viennacl" viennacl | xargs sed -i s@"^namespace viennacl"@"#include <Rcpp.h>\nnamespace viennacl"@g

echo "shortening long device paths"
find . -type d -name "nvidia" -exec rename 's/nvidia/nv/g' {} +
find . -type d -name "fermi" -exec rename 's/fermi/f/g' {} +
find . -type d -name "kepler" -exec rename 's/kepler/k/g' {} +
find . -type d -name "maxwell" -exec rename 's/maxwell/m/g' {} +
find . -type d -name "evergreen" -exec rename 's/evergreen/ev/g' {} +
find . -type d -name "northern_islands" -exec rename 's/northern_islands/ni/g' {} +
find . -type d -name "southern_islands" -exec rename 's/southern_islands/si/g' {} +
find . -type d -name "volcanic_islands" -exec rename 's/volcanic_islands/vi/g' {} +
find . -depth -exec rename 's/geforce/ge/g' {} +

# grep -rl "nvidia" viennacl | xargs sed -i s@"nvidia"@"nv"@g
# grep -rl "nvidia" viennacl | xargs sed -i s@"nvidia"@"nv"@g
# grep -rl "northern_islands" viennacl | xargs sed -i s@"northern_islands"@"ni"@g
# grep -rl "southern_islands" viennacl | xargs sed -i s@"southern_islands"@"si"@g
# grep -rl "volcani_islands" viennacl | xargs sed -i s@"volcanic_islands"@"vi"@g

grep -rl "^#include.*nvidia" viennacl | xargs sed -i 's/nvidia\//nv\//g'
echo "nvidia complete"
grep -rl "^#include.*fermi" viennacl | xargs sed -i 's/fermi\//f\//g'
echo "fermi complete"
grep -rl "^#include.*maxwell" viennacl | xargs sed -i 's/maxwell\//m\//g'
echo "maxwell complete"
grep -rl "^#include.*kepler" viennacl | xargs sed -i 's/kepler\//k\//g'
echo "kepler complete"
grep -rl "^#include.*geforce" viennacl | xargs sed -i 's/\/geforce/\/ge/g'
echo "geforce complete"

grep -rl "^#include.*evergreen" viennacl | xargs sed -i 's/evergreen\//ev\//g'
grep -rl "^#include.*northern_islands" viennacl | xargs sed -i 's/northern_islands\//ni\//g'
grep -rl "^#include.*southern_islands" viennacl | xargs sed -i 's/southern_islands\//si\//g'
grep -rl "^#include.*volcanic_islands" viennacl | xargs sed -i 's/volcanic_islands\//vi\//g'
# grep -rl "^#include.*bar/" . | xargs sed -i 's/bar\//quz\//g'

## Post processing and cleanup
echo "Purging (temp. dir) ${viennaclRoot}"
rm -rf ${viennaclRoot}

echo "Now check with 'git status' and add and commit as needed."
