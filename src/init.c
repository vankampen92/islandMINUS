#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME:
   Check these declarations against the C/Fortran source code.
*/

/* .C calls */
extern void MODEL_SELECTION_UPGMA_MacKENZIE_R_FUNCTION(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void MODEL_SELECTION_UPGMA_R_FUNCTION(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void R_SHLIB___mle_MacKenzie_NLLikelihood_Minimization(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void R_SHLIB___mle_MacKenzie_NLL_Uneven_Minimization(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
extern void R_SHLIB___mle_NLL_Uneven_Minimization(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);

static const R_CMethodDef CEntries[] = {
    {"MODEL_SELECTION_UPGMA_MacKENZIE_R_FUNCTION",        (DL_FUNC) &MODEL_SELECTION_UPGMA_MacKENZIE_R_FUNCTION,        24},
    {"MODEL_SELECTION_UPGMA_R_FUNCTION",                  (DL_FUNC) &MODEL_SELECTION_UPGMA_R_FUNCTION,                  20},
    {"R_SHLIB___mle_MacKenzie_NLLikelihood_Minimization", (DL_FUNC) &R_SHLIB___mle_MacKenzie_NLLikelihood_Minimization, 23},
    {"R_SHLIB___mle_MacKenzie_NLL_Uneven_Minimization",   (DL_FUNC) &R_SHLIB___mle_MacKenzie_NLL_Uneven_Minimization,   24},
    {"R_SHLIB___mle_NLL_Uneven_Minimization",             (DL_FUNC) &R_SHLIB___mle_NLL_Uneven_Minimization,             20},
    {NULL, NULL, 0}
};

void R_init_island(DllInfo *dll)
{
    R_registerRoutines(dll, CEntries, NULL, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
