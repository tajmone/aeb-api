/*
 * Copyright (C) 2001, Answers 2000 Limited
 * 48 Haven Green, Ealing, London W5 2NX
 *
 * Use of this file is governed by the Activ E-Book License File.
 */

/*
    DESCRIPTION
    -----------
    EXSCRIPT is a very simple sample extension - and
    extremely inelegant, but it shows all the features
    for extending the Activ E-Book Script Language.




    LIMITATIONS
    ------------
    1. If the parameter strings passed to EXSCRIPT.MSG are longer than 255 characters, then an
        error will be returned.

    2.  If the string passed to EXSCRIPT.ADDVAR is more than 255 characters, then an error
        will be returned.

    3,  Very limited functionality...


    CAPABILITIES
    ------------
    This implements the following:

    (1) Activ Script Command EXSCRIPT.MSG

        Usage:
        EXSCRIPT.MSG(s1,s2,s3,s4,s5,s6,s7,s8,s9,s10)
        - upto 10 parameters (all parameters are optional)
        - simply displays a message box



    (2) Activ Variables

        Initially creates  {exscript.tom}, {exscript.dick} and {exscript.harry}

        More variables can be created on-the-fly using EXSCRIPT.ADDVAR



    (3) Activ Script Command:   EXSCRIPT.ADDVAR

        Usage:
        EXSCRIPT.ADDVAR(value)

        - sets the next variable in sequence to the value, starting from {exscript.n3}
        - for example.  the first call would create {sxscript.n3}, the 2nd {exscript.n4} etc. up to n99

*/
/**********************************************************************/

#include <windows.h>
#include "../../include/aebapi.h"

#define STRING_TOO_LONG         "Parameter String Too Long! This is a demo and strings are limited to 255 characters in this demo."
#define UNKNOWN_VAR             "Unknown Variable Error"

/**********************************************************************/

/*
    Implementation functions and code for EXSCRIPT.MSG
*/


/* Build the output string */
static BOOL AddParam( char * szBuffer, int nCount, int nParam, const char * szPrompt, LPCSCRIPTPARAM lpParam, LPSCRIPTERRORBLOCK lpSEB )
{
    if ( nParam <= nCount )
    {
        if (
            ( lpParam->scriptparamtype ) == SCRIPTPARAMTYPE_EMPTY
            )
        {
            lpSEB->scripterror = SCRIPTERROR_OTHER ;
            lstrcpy( lpSEB->scriptmsg.szData, "Empty Parameter, runtime error?" ) ;
            return FALSE ;
        }

        int ll = lstrlen( lpParam->lpszValue ) ;

        if ( ll > 255 )
        {
            lpSEB->scripterror = SCRIPTERROR_OTHER ;
            lstrcpy( lpSEB->scriptmsg.szData, STRING_TOO_LONG ) ;
            return FALSE ;
        }

        lstrcat( szBuffer, szPrompt ) ;
        lstrcat( szBuffer, lpParam->lpszValue  ) ;
        lstrcat( szBuffer, "\n" ) ;

        return TRUE ;
    }

    return TRUE ;
}


/* Prepare a message and display it */
static void DoMessage(
                        HWND hWnd,              /* [in] - top level window for container */
                        LPCSTR pszCommand,      /* [in] - command */
                        int nParamCount,        /* [in] - the number of parameters actually used - may be zero */
                        LPCSCRIPTPARAM lpParam1,       /* [in] - parameter */
                        LPCSCRIPTPARAM lpParam2,       /* [in] - parameter */
                        LPCSCRIPTPARAM lpParam3,       /* [in] - parameter */
                        LPCSCRIPTPARAM lpParam4,       /* [in] - parameter */
                        LPCSCRIPTPARAM lpParam5,       /* [in] - parameter */
                        LPCSCRIPTPARAM lpParam6,       /* [in] - parameter */
                        LPCSCRIPTPARAM lpParam7,       /* [in] - parameter */
                        LPCSCRIPTPARAM lpParam8,       /* [in] - parameter */
                        LPCSCRIPTPARAM lpParam9,       /* [in] - parameter */
                        LPCSCRIPTPARAM lpParam10,      /* [in] - parameter */
                        LPSCRIPTERRORBLOCK lpSEB/* [out] - error message */
                        )
{

    BOOL bOK = TRUE ;
    char szMessage[32768] ; /* This is plenty long enough for 10X255 + prompts */

    wsprintf( szMessage, "Command = %s\nParamCount = %d\n", nParamCount ) ;


    bOK = bOK && AddParam( szMessage, nParamCount, 1, "Parameter 1 = ", lpParam1, lpSEB ) ;
    bOK = bOK && AddParam( szMessage, nParamCount, 2, "Parameter 2 = ", lpParam2, lpSEB ) ;
    bOK = bOK && AddParam( szMessage, nParamCount, 3, "Parameter 3 = ", lpParam3, lpSEB ) ;
    bOK = bOK && AddParam( szMessage, nParamCount, 4, "Parameter 4 = ", lpParam4, lpSEB ) ;
    bOK = bOK && AddParam( szMessage, nParamCount, 5, "Parameter 5 = ", lpParam5, lpSEB ) ;
    bOK = bOK && AddParam( szMessage, nParamCount, 6, "Parameter 6 = ", lpParam6, lpSEB ) ;
    bOK = bOK && AddParam( szMessage, nParamCount, 7, "Parameter 7 = ", lpParam7, lpSEB ) ;
    bOK = bOK && AddParam( szMessage, nParamCount, 8, "Parameter 8 = ", lpParam8, lpSEB ) ;
    bOK = bOK && AddParam( szMessage, nParamCount, 9, "Parameter 9 = ", lpParam9, lpSEB ) ;
    bOK = bOK && AddParam( szMessage, nParamCount, 10, "Parameter 10 = ", lpParam10, lpSEB ) ;


    if ( bOK )
    {
        MessageBox( hWnd, szMessage, "EXSCRIPT", MB_OK | MB_DEFBUTTON1 | MB_ICONINFORMATION ) ;
    }

}


/**********************************************************************/

/*
    Implementation functions and code for Variables
*/

#define MAXVARIABLE 100

typedef struct tagMYVARIABLE
{
    char szVariable[256] ;
    char szValue[256] ;
} MYVARIABLE ;


static int nVariableCount = 0 ;
static MYVARIABLE myVariable[MAXVARIABLE] ;

/* Create a new variable */
static BOOL AddVar(
                        LPCSCRIPTPARAM lpParam1,      /* [in] - parameter */
                        LPSCRIPTERRORBLOCK lpSEB/* [out] - error message */
                        )
{
    int ll = lstrlen( lpParam1->lpszValue ) ;

    if ( ll > 255 )
    {
        /* the string must be < 255 characters */
        lpSEB->scripterror = SCRIPTERROR_OTHER ;
        lstrcpy( lpSEB->scriptmsg.szData, STRING_TOO_LONG ) ;
        return FALSE ;
    }


    if ( nVariableCount < MAXVARIABLE )
    {
        wsprintf(
            myVariable[nVariableCount].szVariable,
            "n%d",
            nVariableCount ) ;

        lstrcpy( myVariable[nVariableCount].szValue, lpParam1->lpszValue ) ;
        nVariableCount++ ;

        return TRUE ;

    }  else
    {
        /* This returns an error when you to 100 variables */
        lpSEB->scripterror = SCRIPTERROR_OTHER ;
        lstrcpy( lpSEB->scriptmsg.szData, "This demo supports up to 100 variables, the limit has been reached." ) ;
    }

    return FALSE ;
}


/* Return array index of variable, or -1 if not found */
static int FindVar( const char * szVariable )
{
    if ( nVariableCount == 0 ) return -1 ; /* There aren't any variables! */

    for ( int vv = 0 ; vv < nVariableCount ; vv++ )
    {
        if ( 0==lstrcmp(szVariable,myVariable[vv].szVariable))
        {
            return vv ;
        }
    }

    return -1 ; /* Unknown variable */
}


/* Initialization of first elements */
static void InitVar( void )
{

    nVariableCount = 3 ;

    lstrcpy( myVariable[0].szVariable, "tom" ) ;
    lstrcpy( myVariable[0].szValue, "Thomas" ) ;
    lstrcpy( myVariable[1].szVariable, "dick" ) ;
    lstrcpy( myVariable[1].szValue, "Richard" ) ;
    lstrcpy( myVariable[2].szVariable, "harry" ) ;
    lstrcpy( myVariable[2].szValue, "Harold" ) ;
}




/**********************************************************************/

/*
 *       Functions Required in All Activ E-Book Extensions
 */

BOOL AEBAPI AEB_IsInterface(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd,              /* [in] - top level window for container */
                        int nHostMajorVersion,  /* [in] - major version number of host E-Book/Compiler, e.g. 4 if the version is 4.0 */
                        int nHostMinorVersion,  /* [in] - minor version number of host E-Book/Compiler, e.g. 0 if the version were 4.0, 1 iof the version were 4.01 etc, 10 if the version were 4.10 */
                        AEBINTERFACE aebinterface   /* [in] - the interface */
                        )
{
    if ( aebinterface == AEBINTERFACE_SCRIPT ) return TRUE ; /* We are a script extension */

    return FALSE ;
}

BOOL AEBAPI AEB_IsRuntime(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd,              /* [in] - top level window for container */
                        int nHostMajorVersion,  /* [in] - major version number of host E-Book/Compiler, e.g. 4 if the version is 4.0 */
                        int nHostMinorVersion   /* [in] - minor version number of host E-Book/Compiler, e.g. 0 if the version were 4.0, 1 iof the version were 4.01 etc, 10 if the version were 4.10 */
                        )
{
    return TRUE ;
}


void AEBAPI AEB_GetName(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd,              /* [in] - top level window for container */
                        LPAEBSSTR pszName       /* [out] - name */
                        )
{
    lstrcpy( pszName->szData, "EXSCRIPT" ) ;
}



void AEBAPI AEB_GetVersion(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd,              /* [in] - top level window for container */
                        LPAEBSSTR pszVersion    /* [out] - version */
                        )
{
    lstrcpy( pszVersion->szData, "4.00" ) ;
}


void AEBAPI AEB_Init(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd              /* [in] - top level window for container */
                        )
{
    InitVar() ;
}

void AEBAPI AEB_Exit(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd              /* [in] - top level window for container */
                        )
{
}


/**********************************************************************/

/*
 * Functions required in Activ E-Book Extensions which are runtime components
 * (return TRUE to AEB_IsRuntime)
 */



#ifdef OLDHAT
/*
    AEB_SetLoad

    Purpose:
    This function is called by the compiler user interface
    when the user elects to add the extension to his project
    or remove it.  Typically you will do nothing in this procedure,
    but you can if you want...

    Return:
    None
*/
void AEBAPI AEB_SetLoad(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd,              /* [in] - top level window for container */
                        BOOL bLoad,             /* [in] - true if the component will be loaded, FALSE if being removed */
                        LPCSTR lpszSourceDir    /* [in] - main source directory */
                        ) ;
typedef void AEBAPI (*PFNAEB_SETLOAD)(LONG,PFNAEB_HOSTGETFUNC,HWND,BOOL,LPCSTR) ;
#endif

#ifdef OLDHAT
void AEBAPI AEB_SetLoad(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd,              /* [in] - top level window for container */
                        BOOL bLoad,             /* [in] - true if the component will be loaded, FALSE if being removed */
                        LPCSTR lpszSourceDir    /* [in] - main source directory */
                        )
{
    // no code req'd
}
#endif

BOOL AEBAPI AEB_InfoDlg(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd,              /* [in] - top level window for container */
                        BOOL bLoad,             /* [in] - true if the component will be loaded, FALSE if being removed */
                        LPCSTR lpszSourceDir    /* [in] - main source directory */
                        )
{
    char szBuffer[8192] ;
    lstrcpy( szBuffer, "EXSCRIPT INFO DIALOG\n\nWe could put a setup dialog here but I'm lazy!\n\n" ) ;
    if ( bLoad )
    {
        lstrcat( szBuffer, "Load=Yes\n\n" ) ;
    } else
    {
        lstrcat( szBuffer, "Load=No\n\n" ) ;
    }

    lstrcat( szBuffer, "Source Dir:\n" ) ;
    lstrcat( szBuffer, lpszSourceDir ) ;

    MessageBox( hWnd,
        szBuffer,
        "EXSCRIPT Test DLL",
        MB_OK | MB_ICONINFORMATION ) ;
    return TRUE ;
}


/**********************************************************************/

/*
 *      Functions Required in Activ Script Extensions
 *
 *      These extensions must return AEBTYPE_SCRIPT when GetType
 *      is called.
 */

void AEBAPI AEB_ScriptInit(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd              /* [in] - top level window for container */
                        )
{
}

void AEBAPI AEB_ScriptExit(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd              /* [in] - top level window for container */
                        )
{
}


void AEBAPI AEB_ScriptGetKey(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd,              /* [in] - top level window for container */
                        LPAEBSSTR pszScriptKey  /* [out] - script key */
                        )
{
    lstrcpy( pszScriptKey->szData, "EXSCRIPT" ) ;
}


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
                        )
{
/*
    EXSCRIPT.MSG command
*/
    if ( 0 == lstrcmp(pszCommand,"MSG"))
    {
        DoMessage(
                        hWnd,
                        pszCommand,
                        nParamCount,
                        lpParam1,
                        lpParam2,
                        lpParam3,
                        lpParam4,
                        lpParam5,
                        lpParam6,
                        lpParam7,
                        lpParam8,
                        lpParam9,
                        lpParam10,
                        lpSEB
                        ) ;

        return ;
    }

/*
    EXSCRIPT.ADDVAR
*/
    else if ( 0 == lstrcmp(pszCommand,"ADDVAR"))
    {
        /* Check 1 and only 1 parameter */
        if ( nParamCount != 1 )
        {
            lpSEB->scripterror = SCRIPTERROR_PARAMCOUNT ;
            return ;
        }

        /* Check Parameter is a string */
        if ( ( lpParam1->scriptparamtype ) != SCRIPTPARAMTYPE_STR )
        {
            lpSEB->scripterror = SCRIPTERROR_PARAMTYPE ;
            return ;
        }


        BOOL bOK = AddVar( lpParam1, lpSEB ) ;

        /* Set up return */

        if ( bOK )
        {
            (*pbVarChange) = TRUE ; /* We created a new variable */
        }
        return ;

    }


/*
    Command has not been handled by now - must be a syntax error
*/
    (*pbVarChange) = FALSE ; /* No new variables as a result of this call */
    lpSEB->scripterror = SCRIPTERROR_SYNTAX ;
    return ;
}



/*
        ScriptGetVarName

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
                        )
{
    static int nVarPos = 0 ; /* Where are we in the array of variables */



    if ( bGetFirst )
    {
        nVarPos = 0 ;
    }


    if ( nVarPos >= nVariableCount )
    {
        return FALSE ; /* Reached the end ? */
    }


    lstrcpy( pszVariable->szData,  myVariable[nVarPos].szVariable ) ;
    nVarPos++ ;
    return TRUE ;
}



/*
        ScriptGetVarValueLen
        ScriptGetVarValue

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
                        )
{
    int nFind = FindVar( pszVariable ) ;

    if ( nFind == -1 )
    {
        /* Non existent variable - this should never happen */
        (*pnLen) = lstrlen(UNKNOWN_VAR) ;
    } else
    {
        /* Return the length of the value */
        (*pnLen) = lstrlen(  myVariable[nFind].szValue ) ;
    }
}


void AEBAPI AEB_ScriptGetVarValue(
                        LONG lReserved,         /* [in] - not to used */
                        PFNAEB_HOSTGETFUNC pfnHostGetFunc, /* [in] - call back to host */
                        HWND hWnd,              /* [in] - top level window for container */
                        LPCSTR pszVariable,     /* [in] - variable name */
                        LPSTR pszBuffer         /* [out] - value */
                        )
{
    int nFind = FindVar( pszVariable ) ;

    if ( nFind == -1 )
    {
        /* Non existent variable - this should never happen */
        lstrcpy( pszBuffer, UNKNOWN_VAR ) ;
    } else
    {
        /* Return the length of the value */
        lstrcpy( pszBuffer, myVariable[nFind].szValue ) ;
    }
}



/**********************************************************************/
