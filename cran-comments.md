## Test environments
* local windows install, R 3.4.2
* ubuntu 14.04 (on travis-ci), R 3.4.2
* win-builder (devel and release)

## R CMD check results

0 errors | 0 warnings | 1 note

* checking installed package size ... NOTE
  installed size is  5.3Mb
  sub-directories of 1Mb or more:
    include   5.3Mb
    
  This is a large header only package similar to the BH package.

## Reverse dependencies

* I have run R CMD check on the only downstream dependency (gpuR) of which
  I am also the author.
