AESTE FreeRTOS Port
=================== 
This is a port of the upstream FreeRTOS operating system to AESTE
platforms.

The purpose of maintaining this port is as a record/archive of the
upstream code. It will also be our main repository for any
customisations made to the upstream code.


Historical Summary
------------------
* R2012-01-30 - Bump to FreeRTOSV7.1.0 - compiles clean.

* R2011-08-19 - Reorganised the port code into the FreeRTOS
  subdirectory. Change the DEMO code to incorporate critical section
  of stdout.

* R2011-08-13 - Working kernel.


Code Organisation
-----------------
This repository is organised using the structure proposed at nvie.com
with two main public branches:

* master - holds the tagged public release code. Track this branch if
  you only wish to receive hotfixes and work on stable code.

* develop - holds the active development branch. Track this branch if
  you wish to stay updated with all the latest developments and work
  on unstable code.

If you wish to contribute to the development of this port, please fork
this repository, make your changes and perform a pull request.


Upstream Repository 
------------------- 
This repository is a fork of the upstream FreeRTOS SVN repository
hosted at Sourceforge.


Reporting Bugs
--------------
Any bugs spotted in the upstream code should be reported to the
upstream source. Any bugs for our custom code should be reported using
the issues page at the github repository.

