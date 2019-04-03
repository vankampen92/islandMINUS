#include <MODEL.h>

void R_SHLIB___mle_MacKenzie_NLLikelihood_Minimization(double * , int * , int * ,
                                                       double * , int * ,
                                                       int * ,
                                                       double * , double * ,
                                                       double * , double * ,
                                                       double * , double * ,
                                                       double * , double * ,
                                                       int * ,
                                                       int * ,
                                                       int * , int * ,
                                                       double * ,
                                                       int * ,
                                                       double * ,
                                                       int *, int * );

void R_SHLIB___mle_MacKenzie_NLLikelihood_Minimization(double * Presence_Data,
						       int * S, int * N,
						       double * Time_Vector,
						       int * Transects,
						       int * T,
						       double * Colonization,
						       double * C_Range,
						       double * Extinction,
						       double * E_Range,
						       double * Detectability,
						       double * D_Range,
						       double * Phi_Time_0,
						       double * P_Range,
						       int * No_of_PARAMETERS,
						       int * No_of_PARAMETERS_MAX,
						       int * Index,
						       int * Discretization,
						       double * Tolerance,
						       int * No_of_ITERATIONS,
						       double * Value,
						       int * Verbose,
						       int * Minimization )
{
  /* This function is just a wrapper for a GSL minimization algorithm:
     This wrapper is designed to be compiled as a shared library to be compatible
     with R (see mle_MacKenzie.c to look for the function this wrapper comes from).
     In essence, all the hazel comes from the fact that the funcion bellow only
     accepts a first argument (of type pointer to Parameter_Fitting) to pass on
     data matrices and other model parameters.

        GSL_Minimization_Simplex( Parameter_Fitting * F,
				  gsl_vector * Initial_Guess,
				  gsl_vector * Solution,
				  double ( * Function) (const gsl_vector *, void * ) )

     Input arguments:
     .  No_of_PARAMETERS to define the dimension of the subparameter space where
        the search will be conducted.
     .  N, number of temporal observations (no of columns in Presence matrix)
     .  S, number of species (no of rows in Presence matrix)
     .  T, number of sampling times
     .  Presence, presence 1/0 data matrix.
     .  Time_Vector, double array containing sampling times
     .  Transects, integer array containing the number of transects per sampling time.
     .  Verbose, 1/0: more/less output information during optimization.
     .  Minimization, 1/0: if Minimization is 1, the function conducts mle. If it is
        0, no optimization is performed and, simply, the NLL evaluation at the input
	model parameter values is returned.

     Output arguments:
     .  Colonization, maximum likelihood estimate of the colonization rate
     .  Extinction, maximum likelihood estimate of the extinction rate
     .  Detectability, maximum likelihood estimate of the detection probability
     .  Phi_0_Time_0, maximum likelihood estimate of the probability of species presence
        at time 0.
     .  Value, the value of the NLL at the point of the Colonization and Extinctin
     mle estimates
  */
  int i,j,k,m;

  double ** Presence = (double **)calloc( (* S), sizeof(double *) );
  for (m = 0; m < (* S); m++)
	Presence[m] = (double *)calloc( (* N), sizeof(double) );

  k = 0;
  for( m=0; m < (* S); m++ )
    for( j=0; j < (* N); j++ ) {
      Presence[m][j] = Presence_Data[k];
      if( Presence[m][j] == 0 || Presence[m][j] == 1)
            k++;
      else {
        Rprintf(" Error in the initial Presence Data\n");
        Rprintf(" Some matrix entries are not either 0 or 1\n");
        Rprintf(" This function does not allow missing values (no flags are allowed)\n");
        Rprintf(" The program will exit\n");
        // error(0, 0, "Program has aborted");
        Rprintf("Program has aborted\n"); error(0,0,"Program aborted");
      }
    }

  SP_Matrix_Data  * Data = (SP_Matrix_Data *)calloc( 1, sizeof(SP_Matrix_Data) );
  Data->Presence = Presence;
  Data->No_of_SPECIES = (* S);
  Data->No_of_TIMES   = (* T);
  Data->Time_Vector   = Time_Vector;
  Data->Transects     = Transects;
  Data->Total_No_of_TRANSECTS = (* N);

  Parameter_Model * P = (Parameter_Model *)calloc(1, sizeof(Parameter_Model) );
  P->No_of_SPECIES     = (* S);
  P->No_of_COLUMNS     = (* N);
  P->Colonization_Rate = (* Colonization);     /* Key 0 */
  P->Extinction_Rate   = (* Extinction );      /* Key 1 */
  P->Detectability_Value = (* Detectability);  /* Key 2 */
  P->Phi_0               = (* Phi_Time_0);     /* Key 3 */
  P->RATES               = 1;                  /* Rates are true Rates!!! */

  Parameter_Space * Space = (Parameter_Space *)calloc(1, sizeof(Parameter_Space) );
  Parameter_Space_Alloc_R_SHLIB( Space, (* No_of_PARAMETERS), Discretization );

  // int No_C, No_E, No_D, No_P;
  // Parameter_Index_Checking_Ordering(Index, Discretization, (* No_of_PARAMETERS_MAX),
  //                                   &No_C, &No_E, &No_D, &No_P );
  // double Acc_C, Acc_E, Acc_D, Acc_P;
  // Acc_C = (C_Range[1] - C_Range[0])/((double)No_C - 1.0);
  // Acc_E = (E_Range[1] - E_Range[0])/((double)No_E - 1.0);
  // Acc_D = (D_Range[1] - D_Range[0])/((double)No_D - 1.0);
  // Acc_P = (P_Range[1] - P_Range[0])/((double)No_P - 1.0);
  // Parameter_Space_Accuracies_R_SHLIB( Space, Acc_C, Acc_E, Acc_D, Acc_P );

  // Fake discretization to define and setup parameter accuracies...
  // Accuracies are not used anymore!!!
  int No_C, No_E, No_D, No_P;  No_C = No_E = No_D = No_P = 100;
  double Acc_C, Acc_E, Acc_D, Acc_P;
  Acc_C = (C_Range[1] - C_Range[0])/((double)No_C - 1.0);
  Acc_E = (E_Range[1] - E_Range[0])/((double)No_E - 1.0);
  Acc_D = (D_Range[1] - D_Range[0])/((double)No_D - 1.0);
  Acc_P = (P_Range[1] - P_Range[0])/((double)No_P - 1.0);
  Parameter_Space_Accuracies_R_SHLIB( Space, Acc_C, Acc_E, Acc_D, Acc_P );
  // End fake discretization

  Parameter_Space_Boundaries_R_SHLIB( Space, C_Range, E_Range, D_Range, P_Range );
  Parameter_Space_Initialization_R_SHLIB( Space,
					                                (*Tolerance), (*No_of_ITERATIONS),
                                          (*No_of_PARAMETERS),
                                          Index, Discretization);

  Parameter_Fitting * F = (Parameter_Fitting*)calloc(1,sizeof(Parameter_Fitting));
  F->P      = P;
  F->Data   = Data;
  F->Space  = Space;
  F->Verbose = (*Verbose); // 1: Verbose // 0: Non Verbose

  gsl_vector * x = gsl_vector_alloc((*No_of_PARAMETERS));
  Parameter_Model_into_Vector_Entries ( P, x,
					Space->Parameter_Index, (*No_of_PARAMETERS) );

  if( (*Minimization) == 1 )
    (* Value) = GSL_Minimization_Simplex( F, x, x,
					&GSL_MacKenzie_NLLikelihood_Function );
  else if ( (*Minimization) == 0 )
    (* Value) = GSL_MacKenzie_NLLikelihood_Function(x, F);
  else
    Rprintf(" Error in 1/0 Minimization input argument!\n ---> Minimization = %d\n",
	   (*Minimization) );

  Vector_Entries_into_Parameter_Model ( x, P,
					Space->Parameter_Index, (*No_of_PARAMETERS) );

  (* Colonization)  = P->Colonization_Rate   ;     /* Key 0 */
  (* Extinction )   = P->Extinction_Rate     ;     /* Key 1 */
  (* Detectability) = P->Detectability_Value ;     /* Key 2 */
  (* Phi_Time_0)    = P->Phi_0               ;     /* Key 3 */

  for(m=0; m< (* S); m++) free(Presence[m]);
  free(Presence);

  free(P);                         // Parameter Model Free
  Parameter_Space_Free(Space, (* No_of_PARAMETERS));     // Parameter Space Free
  free (Data); free (F); gsl_vector_free(x);
}
