/*
 * Activ E-Book and Activ E-Book Compiler API
 *
 * Version 4.00
 *
 * Copyright (C) 2001, Answers 2000 Limited
 * 48 Haven Green, Ealing, London W5 2NX
 *
 * Use of this file is governed by the Activ E-Book License File.
 */

/**********************************************************************/

/* C++ compatibility */
#if __cplusplus
extern "C" {
#endif

/* Callable function - Visual C++ language extension */
#define AEBAPI      __declspec(dllexport)

/**********************************************************************/

/*
 * General Constant & Type Definitions
 */


/* Short String */
#define AEBSSTR_LEN     256
typedef struct tagAEBSSTR
{
        char szData[AEBSSTR_LEN] ; /* must be NUL terminated */
} AEBSSTR;
typedef AEBSSTR * LPAEBSSTR ;

/* Long String */
#define AEBLSTR_LEN     8192
typedef struct tagAEBLSTR
{
        char szData[AEBLSTR_LEN] ; /* must be NUL terminated */
} AEBLSTR ;
typedef AEBLSTR * LPAEBLSTR ;



/**********************************************************************/

/*
 *      Functions Supported by Host Application (the E-Book or Compiler)
 */


typedef int HOSTFUNC ;

/*
        AEB_HostGetFunc

        Purpose:
        Get a function pointer to a function in the host app

        Return:
        Pointer to the function in the host - or NULL if the host does
        not implement that function.
*/

FARPROC AEBAPI AEB_HostGetFunc( HOSTFUNC hostfunc ) ;
typedef FARPROC AEBAPI (*PFNAEB_HOSTGETFUNC)( HOSTFUNC ) ;

/**********************************************************************/

/*
 *       Functions Required in All Activ E-Book Extensions
 */

/* Extension Types */
typedef int AEBINTERFACE ;
#define AEBINTERFACE_SCRIPT          1




/*
        AEB_GetName

        Purpose:
        What is the (user visible) name of the extension

        Return:
        None
*/
void AEBAPI AEB_GetName(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd,              /* [in] - top level window for container */
                        LPAEBSSTR pszName       /* [out] - name */
                        ) ;
typedef void AEBAPI (*PFNAEB_GETNAME)(LONG,PFNAEB_HOSTGETFUNC,HWND,LPAEBSSTR) ;

/*
        AEB_GetVersion

        Purpose:
        What is the (user visible) version of of the extension

        Return:
        None
*/
void AEBAPI AEB_GetVersion(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd,              /* [in] - top level window for container */
                        LPAEBSSTR pszVersion    /* [out] - version */
                        ) ;

typedef void AEBAPI (*PFNAEB_GETVERSION)(LONG,PFNAEB_HOSTGETFUNC,HWND,LPAEBSSTR) ;


/*
        AEB_Init

        Purpose:
        Called when the Extension has been loaded

        Return:
        None
*/
void AEBAPI AEB_Init(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd              /* [in] - top level window for container */
                        ) ;
typedef void AEBAPI (*PFNAEB_INIT)(LONG,PFNAEB_HOSTGETFUNC,HWND) ;

/*
        AEB_Exit

        Purpose:
        Called when the Extension is about to be unloaded

        Return:
        None
*/
void AEBAPI AEB_Exit(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd              /* [in] - top level window for container */
                        ) ;
typedef void AEBAPI (*PFNAEB_EXIT)(LONG,PFNAEB_HOSTGETFUNC,HWND) ;


/*
        AEB_IsRuntime

        Purpose:
        Does the extension operate at runtime (i.e. should we be able to compile it into E-Books)

        Return:
        TRUE yes, FALSE if no
*/
BOOL AEBAPI AEB_IsRuntime(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd,              /* [in] - top level window for container */
                        int nHostMajorVersion,  /* [in] - major version number of host E-Book/Compiler, e.g. 4 if the version is 4.0 */
                        int nHostMinorVersion  /* [in] - minor version number of host E-Book/Compiler, e.g. 0 if the version were 4.0, 1 iof the version were 4.01 etc, 10 if the version were 4.10 */
                        ) ;
typedef BOOL AEBAPI (*PFNAEB_ISRUNTIME)(LONG,PFNAEB_HOSTGETFUNC,HWND,int,int) ;


/*
        AEB_IsInterface

        Purpose:
        Does the extension support a particular interface

        Return:
        TRUE if yes, FALSE if no
*/
BOOL AEBAPI AEB_IsInterface(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd,              /* [in] - top level window for container */
                        int nHostMajorVersion,  /* [in] - major version number of host E-Book/Compiler, e.g. 4 if the version is 4.0 */
                        int nHostMinorVersion,  /* [in] - minor version number of host E-Book/Compiler, e.g. 0 if the version were 4.0, 1 iof the version were 4.01 etc, 10 if the version were 4.10 */
                        AEBINTERFACE aebinterface       /* [in] - the interface */
                        ) ;
typedef BOOL AEBAPI (*PFNAEB_ISINTERFACE)(LONG,PFNAEB_HOSTGETFUNC,HWND,int,int,AEBINTERFACE) ;



/**********************************************************************/

/*
 * Functions required in Activ E-Book Extensions which are runtime components
 * (return TRUE to AEB_IsRuntime)
 */


/*
    AEB_InfoDlg

    Purpose:
    This function is called by the compiler user interface
    when the user requests information on an extension.
    The current load status and source directory are passed
    as parameters.

    Return:
    Return TRUE if you display a dialog (example: a custom
    setup dialog or about box), or FALSE if you want the
    contain to show a simple message box.
*/
BOOL AEBAPI AEB_InfoDlg(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd,              /* [in] - top level window for container */
                        BOOL bLoad,             /* [in] - true if the component will be loaded, FALSE if being removed */
                        LPCSTR lpszSourceDir    /* [in] - main source directory */
                        ) ;
typedef BOOL AEBAPI (*PFNAEB_INFODLG)(LONG,PFNAEB_HOSTGETFUNC,HWND,BOOL,LPCSTR) ;




/**********************************************************************/

/*
 *      Functions Required in Activ Script Extensions
 *
 *      These extensions must support AEBINTERFACE_SCRIPT (indicated when AEB_IsInterface)
 */

/*
        Script Errors
*/
typedef int                     SCRIPTERROR ;
#define SCRIPTERROR_OK          0
#define SCRIPTERROR_SYNTAX      1
#define SCRIPTERROR_PARAMCOUNT  2
#define SCRIPTERROR_PARAMTYPE   3
#define SCRIPTERROR_OTHER       32767

typedef struct tagSCRIPTERRORBLOCK
{
        SCRIPTERROR     scripterror ;
        AEBLSTR         scriptmsg ;
} SCRIPTERRORBLOCK ;
typedef SCRIPTERRORBLOCK *      LPSCRIPTERRORBLOCK ;

/*
        Script Parameters
*/

typedef int                     SCRIPTPARAMTYPE ;
#define SCRIPTPARAMTYPE_EMPTY       0
#define SCRIPTPARAMTYPE_INT         1
#define SCRIPTPARAMTYPE_STR         2

/* Script Param */
typedef struct tagSCRIPTPARAM
{
        SCRIPTPARAMTYPE scriptparamtype ;

        LPCSTR lpszValue ; // value as a string, valid for SCRIPTPARAM_INT and SCRIPTPARAM_STR
        int nValue ; // value as integer (0 otherwise)
} SCRIPTPARAM ;

typedef SCRIPTPARAM *                   LPSCRIPTPARAM ;
typedef const SCRIPTPARAM *             LPCSCRIPTPARAM ;


/*
        AEB_ScriptInit

        Purpose:
        Called when a script starts running

        Return:
        None
*/
void AEBAPI AEB_ScriptInit(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd              /* [in] - top level window for container */
                        ) ;
typedef void AEBAPI (*PFNAEB_SCRIPTINIT)(LONG,PFNAEB_HOSTGETFUNC,HWND) ;

/*
        AEB_ScriptExit

        Purpose:
        Called when a script has just finished running

        Return:
        None
*/
void AEBAPI AEB_ScriptExit(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd              /* [in] - top level window for container */
                        ) ;
typedef void AEBAPI (*PFNAEB_SCRIPTEXIT)(LONG,PFNAEB_HOSTGETFUNC,HWND) ;






/*
        AEB_ScriptGetKey

        Purpose:
        What is the "Script Key" for the extension.

                All Activ Variables supported by this extension will
                begin with the lower-cased version of the Script Key.

                All Activ Script commands supported by this extension
                will begin with upper-cased version of the Script Key.

                You may return an upper or lower case version of the
                key it doesn't matter.

                For example:
                - You indicate the script key is "MultiMedia"
                - You will be passed Script commands beginning with
                  "MULTIMEDIA.".  For example you would be passed
                  MULTIMEDIA.PLAY or MULTIMEDIA.STOP or MULTIMEDIA.XYZ
                  (and it's up to you to determine if it's valid or not)
                - You will be asked for a list of all variables beginning
                  if "multimedia.".   When you give the variable name in
                  the extension you just give the variable after the period.
                  So if you say there's a variable called "fred", the user
                  will refer to this in the script as {multimedia.fred}

        Return:
        None
*/
void AEBAPI AEB_ScriptGetKey(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd,              /* [in] - top level window for container */
                        LPAEBSSTR pszScriptKey  /* [out] - script key */
                        ) ;
typedef void AEBAPI (*PFNAEB_SCRIPTGETKEY)(LONG,PFNAEB_HOSTGETFUNC,HWND,LPAEBSSTR) ;

/*
        AEB_ScriptCommand

        Purpose:
        Process a script command. You are passed the name of the command,
        the number of parameters, the type and value of the parameters
        (only use those specified)

        Set the flag pointed to by pbVarChange to
        - TRUE if the list of variable names supported by this extension has
          changed as a result of this call.
          You will only need to use this option if you are creating or
          deleting variables on-the-fly as a result of Activ Script commands
        - FALSE if the list of variable names supported by this extension has
          not changed as a result of this call.  In most cases you will want
          to use this option.

        Set the number pointed to by pScriptError to
        - SCRIPTERROR_OK if you process the command successfully
        - SCRIPTERROR_SYNTAX if you don't know the command
        - SCRIPTERROR_PARAMCOUNT if there are the wrong number of parameters
        - SCRIPT
        - SCRIPTERROR_OTHER if you wish to return a customized error thru pszError

        Return:
        None
*/
void AEBAPI AEB_ScriptCommand(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd,              /* [in] - top level window for container */
                        LPCSTR pszCommand,      /* [in] - command */
                        int nParamCount,        /* [in] - the number of parameters actually used - may be zero */
                        LPCSCRIPTPARAM lpParam1,/* [in] - parameters */
                        LPCSCRIPTPARAM lpParam2,/* [in] - parameters */
                        LPCSCRIPTPARAM lpParam3,/* [in] - parameters */
                        LPCSCRIPTPARAM lpParam4,/* [in] - parameters */
                        LPCSCRIPTPARAM lpParam5,/* [in] - parameters */
                        LPCSCRIPTPARAM lpParam6,/* [in] - parameters */
                        LPCSCRIPTPARAM lpParam7,/* [in] - parameters */
                        LPCSCRIPTPARAM lpParam8,/* [in] - parameters */
                        LPCSCRIPTPARAM lpParam9,/* [in] - parameters */
                        LPCSCRIPTPARAM lpParam10,/* [in] - parameters */
                        BOOL * pbVarChange,     /* [out] - have variable names changed as a result of this call */
                        LPSCRIPTERRORBLOCK lpSEB/* [out] - error message */
                        ) ;
typedef void AEBAPI (*PFNAEB_SCRIPTCOMMAND)(LONG,PFNAEB_HOSTGETFUNC,HWND,
                                            LPCSTR,int,
                                            LPCSCRIPTPARAM,LPCSCRIPTPARAM,LPCSCRIPTPARAM,LPCSCRIPTPARAM,LPCSCRIPTPARAM,
                                            LPCSCRIPTPARAM,LPCSCRIPTPARAM,LPCSCRIPTPARAM,LPCSCRIPTPARAM,LPCSCRIPTPARAM,
                                            BOOL *,
                                            LPSCRIPTERRORBLOCK
                                            ) ;

/*
        AEB_ScriptGetVarName

        Purpose:
        Get list of variable names.

        This function is called repeatedly by the E-Book.
        - First you are called with bGetFirst = TRUE (to get the first variable name)
        - Next you are called repeatedly with bGetFirst = FALSE (to get 2nd, 3rd, 4th etc.)
        - You should return TRUE if a variable name was returned through pszVariable
          or FALSE if not.
        - If you return TRUE you must place the variable name in pszVariable.
        - If you return FALSE you can leave pszVariable unchanged.

        Return:
        See above.
*/
BOOL AEBAPI AEB_ScriptGetVarName(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd,              /* [in] - top level window for container */
                        BOOL bGetFirst,         /* [in] - TRUE = get first, FALSE = get next */
                        LPAEBSSTR pszVariable   /* [out] - variable name */
                        ) ;
typedef BOOL AEBAPI (*PFNAEB_SCRIPTGETVARNAME)(LONG,PFNAEB_HOSTGETFUNC,HWND,BOOL,LPAEBSSTR) ;

/*
        AEB_ScriptGetVarValueLen
        AEB_ScriptGetVarValue

        Purpose:
        Get the value of a variable.

        The E-Book calls both these functions to retrieve the value of
        a variable.

        ScriptGetVarValueLen allows the E-Book to determine the amount
        of storage it needs to allocate to store the value of the variable.
        You should require the size of the string to this call through
        pnLen.

        ScriptGetVarValue is called by the E-Book after it has allocated
        a buffer to store the variable.  You should fill this buffer
        with the value of the variable.
*/
void AEBAPI AEB_ScriptGetVarValueLen(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd,              /* [in] - top level window for container */
                        LPCSTR pszVariable,     /* [in] - variable name */
                        int * pnLen             /* [out] - length of value */
                        ) ;
typedef void AEBAPI (*PFNAEB_SCRIPTGETVARVALUELEN)(LONG,PFNAEB_HOSTGETFUNC,HWND,LPCSTR,int *) ;

void AEBAPI AEB_ScriptGetVarValue(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd,              /* [in] - top level window for container */
                        LPCSTR pszVariable,     /* [in] - variable name */
                        LPSTR pszBuffer         /* [out] - value */
                        ) ;
typedef void AEBAPI (*PFNAEB_SCRIPTGETVARVALUE)(LONG,PFNAEB_HOSTGETFUNC,HWND,LPCSTR,LPSTR) ;

/**********************************************************************/

/* C++ compatibility */
#ifdef __cplusplus
}
#endif
