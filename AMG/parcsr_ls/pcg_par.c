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
#ifdef caliper
#include <caliper/cali.h>
#endif
/*--------------------------------------------------------------------------
 * hypre_ParKrylovCAlloc
 *--------------------------------------------------------------------------*/

char *
hypre_ParKrylovCAlloc( HYPRE_Int count,
                       HYPRE_Int elt_size )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return( hypre_CAlloc( count, elt_size ) );
}

/*--------------------------------------------------------------------------
 * hypre_ParKrylovFree
 *--------------------------------------------------------------------------*/

HYPRE_Int
hypre_ParKrylovFree( char *ptr )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   #endif
   HYPRE_Int ierr = 0;

   hypre_Free( ptr );

   #ifdef caliper
   CALI_MARK_FUNCTION_END;
   #endif
   return ierr;
}

/*--------------------------------------------------------------------------
 * hypre_ParKrylovCreateVector
 *--------------------------------------------------------------------------*/

void *
hypre_ParKrylovCreateVector( void *vvector )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   #endif
	hypre_ParVector *vector = (hypre_ParVector *) vvector;
   hypre_ParVector *new_vector;

   new_vector = hypre_ParVectorCreate( hypre_ParVectorComm(vector),
				       hypre_ParVectorGlobalSize(vector),	
                                       hypre_ParVectorPartitioning(vector) );
   hypre_ParVectorSetPartitioningOwner(new_vector,0);
   hypre_ParVectorInitialize(new_vector);

   #ifdef caliper
   CALI_MARK_FUNCTION_END;
   #endif
   return ( (void *) new_vector );
}

/*--------------------------------------------------------------------------
 * hypre_ParKrylovCreateVectorArray
 *--------------------------------------------------------------------------*/

void *
hypre_ParKrylovCreateVectorArray(HYPRE_Int n, void *vvector )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   #endif
   hypre_ParVector *vector = (hypre_ParVector *) vvector;
   hypre_ParVector **new_vector;
   HYPRE_Int i;

   new_vector = hypre_CTAlloc(hypre_ParVector*,n);
   for (i=0; i < n; i++)
   {
      new_vector[i] = hypre_ParVectorCreate( hypre_ParVectorComm(vector),
                                             hypre_ParVectorGlobalSize(vector),	
                                             hypre_ParVectorPartitioning(vector) );
      hypre_ParVectorSetPartitioningOwner(new_vector[i],0);
      hypre_ParVectorInitialize(new_vector[i]);
   }

   #ifdef caliper
   CALI_MARK_FUNCTION_END;
   #endif
   return ( (void *) new_vector );
}

/*--------------------------------------------------------------------------
 * hypre_ParKrylovDestroyVector
 *--------------------------------------------------------------------------*/

HYPRE_Int
hypre_ParKrylovDestroyVector( void *vvector )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   #endif
   hypre_ParVector *vector = (hypre_ParVector *) vvector;

   #ifdef caliper
   CALI_MARK_FUNCTION_END;
   #endif
   return( hypre_ParVectorDestroy( vector ) );
}

/*--------------------------------------------------------------------------
 * hypre_ParKrylovMatvecCreate
 *--------------------------------------------------------------------------*/

void *
hypre_ParKrylovMatvecCreate( void   *A,
                             void   *x )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   #endif
   void *matvec_data;

   matvec_data = NULL;

   #ifdef caliper
   CALI_MARK_FUNCTION_END;
   #endif
   return ( matvec_data );
}

/*--------------------------------------------------------------------------
 * hypre_ParKrylovMatvec
 *--------------------------------------------------------------------------*/

HYPRE_Int
hypre_ParKrylovMatvec( void   *matvec_data,
                       HYPRE_Complex  alpha,
                       void   *A,
                       void   *x,
                       HYPRE_Complex  beta,
                       void   *y           )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return ( hypre_ParCSRMatrixMatvec ( alpha,
                                       (hypre_ParCSRMatrix *) A,
                                       (hypre_ParVector *) x,
                                       beta,
                                       (hypre_ParVector *) y ) );
}

/*--------------------------------------------------------------------------
 * hypre_ParKrylovMatvecT
 *--------------------------------------------------------------------------*/

HYPRE_Int
hypre_ParKrylovMatvecT(void   *matvec_data,
                       HYPRE_Complex  alpha,
                       void   *A,
                       void   *x,
                       HYPRE_Complex  beta,
                       void   *y           )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return ( hypre_ParCSRMatrixMatvecT( alpha,
                                       (hypre_ParCSRMatrix *) A,
                                       (hypre_ParVector *) x,
                                       beta,
                                       (hypre_ParVector *) y ) );
}

/*--------------------------------------------------------------------------
 * hypre_ParKrylovMatvecDestroy
 *--------------------------------------------------------------------------*/

HYPRE_Int
hypre_ParKrylovMatvecDestroy( void *matvec_data )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return 0;
}

/*--------------------------------------------------------------------------
 * hypre_ParKrylovInnerProd
 *--------------------------------------------------------------------------*/

HYPRE_Real
hypre_ParKrylovInnerProd( void *x, 
                          void *y )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return ( hypre_ParVectorInnerProd( (hypre_ParVector *) x,
                                      (hypre_ParVector *) y ) );
}


/*--------------------------------------------------------------------------
 * hypre_ParKrylovCopyVector
 *--------------------------------------------------------------------------*/

HYPRE_Int
hypre_ParKrylovCopyVector( void *x, 
                           void *y )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return ( hypre_ParVectorCopy( (hypre_ParVector *) x,
                                 (hypre_ParVector *) y ) );
}

/*--------------------------------------------------------------------------
 * hypre_ParKrylovClearVector
 *--------------------------------------------------------------------------*/

HYPRE_Int
hypre_ParKrylovClearVector( void *x )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return ( hypre_ParVectorSetConstantValues( (hypre_ParVector *) x, 0.0 ) );
}

/*--------------------------------------------------------------------------
 * hypre_ParKrylovScaleVector
 *--------------------------------------------------------------------------*/

HYPRE_Int
hypre_ParKrylovScaleVector( HYPRE_Complex  alpha,
                            void   *x     )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return ( hypre_ParVectorScale( alpha, (hypre_ParVector *) x ) );
}

/*--------------------------------------------------------------------------
 * hypre_ParKrylovAxpy
 *--------------------------------------------------------------------------*/

HYPRE_Int
hypre_ParKrylovAxpy( HYPRE_Complex alpha,
                     void   *x,
                     void   *y )
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return ( hypre_ParVectorAxpy( alpha, (hypre_ParVector *) x,
                                 (hypre_ParVector *) y ) );
}

/*--------------------------------------------------------------------------
 * hypre_ParKrylovCommInfo
 *--------------------------------------------------------------------------*/

HYPRE_Int
hypre_ParKrylovCommInfo( void   *A, HYPRE_Int *my_id, HYPRE_Int *num_procs)
{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   MPI_Comm comm = hypre_ParCSRMatrixComm ( (hypre_ParCSRMatrix *) A);
   hypre_MPI_Comm_size(comm,num_procs);
   hypre_MPI_Comm_rank(comm,my_id);
   return 0;
}

/*--------------------------------------------------------------------------
 * hypre_ParKrylovIdentitySetup
 *--------------------------------------------------------------------------*/

HYPRE_Int
hypre_ParKrylovIdentitySetup( void *vdata,
                              void *A,
                              void *b,
                              void *x     )

{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return 0;
}

/*--------------------------------------------------------------------------
 * hypre_ParKrylovIdentity
 *--------------------------------------------------------------------------*/

HYPRE_Int
hypre_ParKrylovIdentity( void *vdata,
                         void *A,
                         void *b,
                         void *x     )

{
   #ifdef caliper
   CALI_MARK_FUNCTION_BEGIN;
   CALI_MARK_FUNCTION_END;
   #endif
   return( hypre_ParKrylovCopyVector( b, x ) );
}

