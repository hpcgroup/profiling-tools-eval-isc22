/*BHEADER**********************************************************************
 * Copyright (c) 2017,  Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * Written by Ulrike Yang (yang11@llnl.gov) et al. CODE-LLNL-738-322.
 * This file is part of AMG.  See files README and COPYRIGHT for details.
 *
 * AMG is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License (as published by the Free
 * Software Foundation) version 2.1 dated February 1999.
 *
 * This software is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the IMPLIED WARRANTY OF MERCHANTIBILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the terms and conditions of the
 * GNU General Public License for more details.
 *
 ***********************************************************************EHEADER*/



#include "_hypre_utilities.h"
#ifdef caliper
#include <caliper/cali.h>
#endif

HYPRE_Int hypre__global_error = 0;

/* Process the error with code ierr raised in the given line of the
   given source file. */
void hypre_error_handler(const char *filename, HYPRE_Int line, HYPRE_Int ierr, const char *msg)
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   #endif
   hypre_error_flag |= ierr;

#ifdef HYPRE_PRINT_ERRORS
   if (msg)
   {
      hypre_fprintf(
         stderr, "hypre error in file \"%s\", line %d, error code = %d - %s\n",
         filename, line, ierr, msg);
   }
   else
   {
      hypre_fprintf(
         stderr, "hypre error in file \"%s\", line %d, error code = %d\n",
         filename, line, ierr);
   }
#endif
   #ifdef caliper
   CALI_MARK_FUNCTION_END;
   #endif
}

HYPRE_Int HYPRE_GetError()
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return hypre_error_flag;
}

HYPRE_Int HYPRE_CheckError(HYPRE_Int ierr, HYPRE_Int hypre_error_code)
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return ierr & hypre_error_code;
}

void HYPRE_DescribeError(HYPRE_Int ierr, char *msg)
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   #endif
   if (ierr == 0)
      hypre_sprintf(msg,"[No error] ");

   if (ierr & HYPRE_ERROR_GENERIC)
      hypre_sprintf(msg,"[Generic error] ");

   if (ierr & HYPRE_ERROR_MEMORY)
      hypre_sprintf(msg,"[Memory error] ");

   if (ierr & HYPRE_ERROR_ARG)
      hypre_sprintf(msg,"[Error in argument %d] ", HYPRE_GetErrorArg());

   if (ierr & HYPRE_ERROR_CONV)
      hypre_sprintf(msg,"[Method did not converge] ");
   #ifdef caliper
   CALI_MARK_FUNCTION_END;
   #endif
}

HYPRE_Int HYPRE_GetErrorArg()
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return (hypre_error_flag>>3 & 31);
}

HYPRE_Int HYPRE_ClearAllErrors()
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   #endif
   hypre_error_flag = 0;
   #ifdef caliper
   CALI_MARK_FUNCTION_END;
   #endif
   return (hypre_error_flag != 0);
}

HYPRE_Int HYPRE_ClearError(HYPRE_Int hypre_error_code)
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   #endif
   hypre_error_flag &= ~hypre_error_code;
   #ifdef caliper
   CALI_MARK_FUNCTION_END;
   #endif
   return (hypre_error_flag & hypre_error_code);
}
