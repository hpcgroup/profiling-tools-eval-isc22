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

#include "_hypre_parcsr_ls.h"

/*--------------------------------------------------------------------------
 * HYPRE_ParCSRGMRESCreate
 *--------------------------------------------------------------------------*/

HYPRE_Int
HYPRE_ParCSRGMRESCreate( MPI_Comm comm, HYPRE_Solver *solver )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   #endif
   hypre_GMRESFunctions * gmres_functions;

   if (!solver)
   {
      hypre_error_in_arg(2);
   #ifdef caliper
   CALI_MARK_FUNCTION_END;
   #endif
      return hypre_error_flag;
   }
   gmres_functions =
      hypre_GMRESFunctionsCreate(
         hypre_CAlloc, hypre_ParKrylovFree, hypre_ParKrylovCommInfo,
         hypre_ParKrylovCreateVector,
         hypre_ParKrylovCreateVectorArray,
         hypre_ParKrylovDestroyVector, hypre_ParKrylovMatvecCreate,
         hypre_ParKrylovMatvec, hypre_ParKrylovMatvecDestroy,
         hypre_ParKrylovInnerProd, hypre_ParKrylovCopyVector,
         hypre_ParKrylovClearVector,
         hypre_ParKrylovScaleVector, hypre_ParKrylovAxpy,
         hypre_ParKrylovIdentitySetup, hypre_ParKrylovIdentity );
   *solver = ( (HYPRE_Solver) hypre_GMRESCreate( gmres_functions ) );

   #ifdef caliper
   CALI_MARK_FUNCTION_END;
   #endif
   return hypre_error_flag;
}

/*--------------------------------------------------------------------------
 * HYPRE_ParCSRGMRESDestroy
 *--------------------------------------------------------------------------*/

HYPRE_Int 
HYPRE_ParCSRGMRESDestroy( HYPRE_Solver solver )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return( hypre_GMRESDestroy( (void *) solver ) );
}

/*--------------------------------------------------------------------------
 * HYPRE_ParCSRGMRESSetup
 *--------------------------------------------------------------------------*/

HYPRE_Int 
HYPRE_ParCSRGMRESSetup( HYPRE_Solver solver,
                        HYPRE_ParCSRMatrix A,
                        HYPRE_ParVector b,
                        HYPRE_ParVector x      )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return( HYPRE_GMRESSetup( solver,
                             (HYPRE_Matrix) A,
                             (HYPRE_Vector) b,
                             (HYPRE_Vector) x ) );
}

/*--------------------------------------------------------------------------
 * HYPRE_ParCSRGMRESSolve
 *--------------------------------------------------------------------------*/

HYPRE_Int 
HYPRE_ParCSRGMRESSolve( HYPRE_Solver solver,
                        HYPRE_ParCSRMatrix A,
                        HYPRE_ParVector b,
                        HYPRE_ParVector x      )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return( HYPRE_GMRESSolve( solver,
                             (HYPRE_Matrix) A,
                             (HYPRE_Vector) b,
                             (HYPRE_Vector) x ) );
}

/*--------------------------------------------------------------------------
 * HYPRE_ParCSRGMRESSetKDim
 *--------------------------------------------------------------------------*/

HYPRE_Int
HYPRE_ParCSRGMRESSetKDim( HYPRE_Solver solver,
                          HYPRE_Int             k_dim    )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return( HYPRE_GMRESSetKDim( solver, k_dim ) );
}

/*--------------------------------------------------------------------------
 * HYPRE_ParCSRGMRESSetTol
 *--------------------------------------------------------------------------*/

HYPRE_Int
HYPRE_ParCSRGMRESSetTol( HYPRE_Solver solver,
                         HYPRE_Real         tol    )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return( HYPRE_GMRESSetTol( solver, tol ) );
}
/*--------------------------------------------------------------------------
 * HYPRE_ParCSRGMRESSetAbsoluteTol
 *--------------------------------------------------------------------------*/

HYPRE_Int
HYPRE_ParCSRGMRESSetAbsoluteTol( HYPRE_Solver solver,
                                 HYPRE_Real         a_tol    )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return( HYPRE_GMRESSetAbsoluteTol( solver, a_tol ) );
}

/*--------------------------------------------------------------------------
 * HYPRE_ParCSRGMRESSetMinIter
 *--------------------------------------------------------------------------*/

HYPRE_Int
HYPRE_ParCSRGMRESSetMinIter( HYPRE_Solver solver,
                             HYPRE_Int          min_iter )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return( HYPRE_GMRESSetMinIter( solver, min_iter ) );
}

/*--------------------------------------------------------------------------
 * HYPRE_ParCSRGMRESSetMaxIter
 *--------------------------------------------------------------------------*/

HYPRE_Int
HYPRE_ParCSRGMRESSetMaxIter( HYPRE_Solver solver,
                             HYPRE_Int          max_iter )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return( HYPRE_GMRESSetMaxIter( solver, max_iter ) );
}

/*--------------------------------------------------------------------------
 * HYPRE_ParCSRGMRESSetStopCrit - OBSOLETE
 *--------------------------------------------------------------------------*/

HYPRE_Int
HYPRE_ParCSRGMRESSetStopCrit( HYPRE_Solver solver,
                              HYPRE_Int          stop_crit )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return( HYPRE_GMRESSetStopCrit( solver, stop_crit ) );
}

/*--------------------------------------------------------------------------
 * HYPRE_ParCSRGMRESSetPrecond
 *--------------------------------------------------------------------------*/

HYPRE_Int
HYPRE_ParCSRGMRESSetPrecond( HYPRE_Solver          solver,
                             HYPRE_PtrToParSolverFcn  precond,
                             HYPRE_PtrToParSolverFcn  precond_setup,
                             HYPRE_Solver          precond_solver )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return( HYPRE_GMRESSetPrecond( solver,
                                  (HYPRE_PtrToSolverFcn) precond,
                                  (HYPRE_PtrToSolverFcn) precond_setup,
                                  precond_solver ) );
}

/*--------------------------------------------------------------------------
 * HYPRE_ParCSRGMRESGetPrecond
 *--------------------------------------------------------------------------*/

HYPRE_Int
HYPRE_ParCSRGMRESGetPrecond( HYPRE_Solver  solver,
                             HYPRE_Solver *precond_data_ptr )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return( HYPRE_GMRESGetPrecond( solver, precond_data_ptr ) );
}

/*--------------------------------------------------------------------------
 * HYPRE_ParCSRGMRESSetLogging
 *--------------------------------------------------------------------------*/

HYPRE_Int
HYPRE_ParCSRGMRESSetLogging( HYPRE_Solver solver,
                             HYPRE_Int logging)
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return( HYPRE_GMRESSetLogging( solver, logging ) );
}

/*--------------------------------------------------------------------------
 * HYPRE_ParCSRGMRESSetPrintLevel
 *--------------------------------------------------------------------------*/

HYPRE_Int
HYPRE_ParCSRGMRESSetPrintLevel( HYPRE_Solver solver,
                                HYPRE_Int print_level)
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return( HYPRE_GMRESSetPrintLevel( solver, print_level ) );
}

/*--------------------------------------------------------------------------
 * HYPRE_ParCSRGMRESGetNumIterations
 *--------------------------------------------------------------------------*/

HYPRE_Int
HYPRE_ParCSRGMRESGetNumIterations( HYPRE_Solver  solver,
                                   HYPRE_Int    *num_iterations )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return( HYPRE_GMRESGetNumIterations( solver, num_iterations ) );
}

/*--------------------------------------------------------------------------
 * HYPRE_ParCSRGMRESGetFinalRelativeResidualNorm
 *--------------------------------------------------------------------------*/

HYPRE_Int
HYPRE_ParCSRGMRESGetFinalRelativeResidualNorm( HYPRE_Solver  solver,
                                               HYPRE_Real   *norm   )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return( HYPRE_GMRESGetFinalRelativeResidualNorm( solver, norm ) );
}
