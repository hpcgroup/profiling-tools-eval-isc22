#BHEADER**********************************************************************
# Copyright (c) 2017,  Lawrence Livermore National Security, LLC.
# Produced at the Lawrence Livermore National Laboratory.
# Written by Ulrike Yang (yang11@llnl.gov) et al. CODE-LLNL-738-322.
# This file is part of AMG.  See files COPYRIGHT and README for details.
#
# AMG is free software; you can redistribute it and/or modify it under the
# terms of the GNU Lesser General Public License (as published by the Free
# Software Foundation) version 2.1 dated February 1999.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the IMPLIED WARRANTY OF MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the terms and conditions of the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#
#EHEADER**********************************************************************



.SUFFIXES:
.SUFFIXES: .c .o
                                                                                               
srcdir = .
                                                                                               
include ../Makefile.include
                                                                                               
CFLAGS = \
 -I..\
 -I../utilities\
 -I../IJ_mv\
 -I../seq_mv\
 -I../parcsr_mv\
 -I../parcsr_ls\
 -I../krylov\
 ${INCLUDE_CFLAGS}\
 -DHYPRE_TIMING
                                                                                               
LFLAGS =\
 -L.\
 -L../parcsr_ls\
 -L../parcsr_mv\
 -L../IJ_mv\
 -L../seq_mv\
 -L../krylov\
 -L../utilities\
 -lparcsr_ls\
 -lparcsr_mv\
 -lseq_mv\
 -lIJ_mv\
 -lkrylov\
 -lHYPRE_utilities\
 ${INCLUDE_LFLAGS}

EXEC_NAME=
ifeq ($(TOOL), WITH_CALIPER)
	EXEC_NAME=caliper
else ifeq ($(TOOL), WITH_HPCTOOLKIT) 
	EXEC_NAME=hpctoolkit
else ifeq ($(TOOL), WITH_TIMEMORY) 
	EXEC_NAME=timemory
else ifeq ($(TOOL), WITH_TAU) 
	EXEC_NAME=tau
else ifeq ($(TOOL), WITH_SCOREP) 
	EXEC_NAME=scorep
else ifeq ($(TOOL), WITH_TAU_SOURCE) 
	EXEC_NAME=tau-source
else ifeq ($(TOOL), WITH_TAU_COMPILER) 
	EXEC_NAME=tau-compiler
endif

##################################################################
# Targets
##################################################################
                                                                                                                                         
all: amg$(EXEC_NAME).exe
                                                                                                                                         
clean:
	@rm -f *.o *.inst.* *.pdb *.a
                                                                                                                                         
veryclean: clean
	@rm -f *.o *.inst.* *.pdb *.a amg${EXEC_NAME}.exe
                                                                                                                                         
##################################################################
# Rules
##################################################################
                                                                                                                                         
amg$(EXEC_NAME).exe: amg.o
	@echo  "Linking" $@ "... "
ifeq (${EXEC_NAME},)
	${CC} -o amg amg.o ${LFLAGS}
else 
	${CC} -o amg$(EXEC_NAME).exe amg.o ${LFLAGS}
endif
##################################################################
# Generic rules
##################################################################
                                                                                                                                         
.c.o:
ifeq (${EXEC_NAME},)
	${CC} -o $@ -c ${CFLAGS} $<
else 
	${CC} -o $@ -c ${CFLAGS} $<
endif
