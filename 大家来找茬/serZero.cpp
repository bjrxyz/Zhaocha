//
// MATLAB Compiler: 4.17 (R2012a)
// Date: Tue Jun 18 06:37:17 2013
// Arguments: "-B" "macro_default" "-W" "cpplib:serZero" "setZero.m" "-T"
// "link:lib" 
//

#include <stdio.h>
#define EXPORTING_serZero 1
#include "serZero.h"

static HMCRINSTANCE _mcr_inst = NULL;


#if defined( _MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__) || defined(__LCC__)
#ifdef __LCC__
#undef EXTERN_C
#endif
#include <windows.h>

static char path_to_dll[_MAX_PATH];

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, void *pv)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        if (GetModuleFileName(hInstance, path_to_dll, _MAX_PATH) == 0)
            return FALSE;
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
    }
    return TRUE;
}
#endif
#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultPrintHandler(const char *s)
{
  return mclWrite(1 /* stdout */, s, sizeof(char)*strlen(s));
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultErrorHandler(const char *s)
{
  int written = 0;
  size_t len = 0;
  len = strlen(s);
  written = mclWrite(2 /* stderr */, s, sizeof(char)*len);
  if (len > 0 && s[ len-1 ] != '\n')
    written += mclWrite(2 /* stderr */, "\n", sizeof(char));
  return written;
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_serZero_C_API
#define LIB_serZero_C_API /* No special import/export declaration */
#endif

LIB_serZero_C_API 
bool MW_CALL_CONV serZeroInitializeWithHandlers(
    mclOutputHandlerFcn error_handler,
    mclOutputHandlerFcn print_handler)
{
    int bResult = 0;
  if (_mcr_inst != NULL)
    return true;
  if (!mclmcrInitialize())
    return false;
  if (!GetModuleFileName(GetModuleHandle("serZero"), path_to_dll, _MAX_PATH))
    return false;
    {
        mclCtfStream ctfStream = 
            mclGetEmbeddedCtfStream(path_to_dll);
        if (ctfStream) {
            bResult = mclInitializeComponentInstanceEmbedded(   &_mcr_inst,
                                                                error_handler, 
                                                                print_handler,
                                                                ctfStream);
            mclDestroyStream(ctfStream);
        } else {
            bResult = 0;
        }
    }  
    if (!bResult)
    return false;
  return true;
}

LIB_serZero_C_API 
bool MW_CALL_CONV serZeroInitialize(void)
{
  return serZeroInitializeWithHandlers(mclDefaultErrorHandler, mclDefaultPrintHandler);
}

LIB_serZero_C_API 
void MW_CALL_CONV serZeroTerminate(void)
{
  if (_mcr_inst != NULL)
    mclTerminateInstance(&_mcr_inst);
}

LIB_serZero_C_API 
void MW_CALL_CONV serZeroPrintStackTrace(void) 
{
  char** stackTrace;
  int stackDepth = mclGetStackTrace(&stackTrace);
  int i;
  for(i=0; i<stackDepth; i++)
  {
    mclWrite(2 /* stderr */, stackTrace[i], sizeof(char)*strlen(stackTrace[i]));
    mclWrite(2 /* stderr */, "\n", sizeof(char)*strlen("\n"));
  }
  mclFreeStackTrace(&stackTrace, stackDepth);
}


LIB_serZero_C_API 
bool MW_CALL_CONV mlxSetZero(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "setZero", nlhs, plhs, nrhs, prhs);
}

LIB_serZero_CPP_API 
void MW_CALL_CONV setZero(int nargout, mwArray& diff, const mwArray& xf, const mwArray& 
                          xl, const mwArray& yf, const mwArray& yl, const mwArray& 
                          diff_in1)
{
  mclcppMlfFeval(_mcr_inst, "setZero", nargout, 1, 5, &diff, &xf, &xl, &yf, &yl, &diff_in1);
}

