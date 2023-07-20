 * Activ E-Book and Activ E-Book Compiler API
 *
 * Version 4.00
 *
 * Copyright (C) 2001, Answers 2000 Limited
 * 48 Haven Green, Ealing, London W5 2NX
 *
 * Use of this file is governed by the Activ E-Book License File.

ACTIV E-BOOK COMPILER API
=========================

UNPACKING
=========

1. We recommend that you unpack this ZIP file into

C:\ebook\api

2. The ZIP file will unpack contain subdirectories:

C:\ebook\api\include            C++ Header Files
C:\ebook\api\sample             Sample Extensions
C:\ebook\api\sample\exscript    Sample Extension that adds
                                Activ Script commands and Activ Variables

3. Additional samples will be added in future versions.


COMPILING
=========

1. In order to compile the sample you will need Microsoft Visual C++ version
6.  Other C++ compilers may work, but we can not guarantee this. Consult
your compiler's manual if you are not using Microsoft Visual C++.

2. Within each sample subdirectory is a project file set up to build
the project.  Each project will create a DLL component in the
subdirectory: C:\ebook\release


BASICS
======

1. Each extension is a DLL module that adds functions either to the compiler
itself, or to both the compiler and E-Book runtime. This extensions
potentially have two modes of operation:

(i) It can be loaded by the compiler

(ii) It can be loaded by E-Books

2. All extensions should use file names that end in .AEA, for example,
the exscript sample extension, compiles into EXSCRIPT.AEA.

3. In order for the compiler to be aware that a particular extension is
present on a user's system, this fact must be indicated in the aebconfig.ini.
To list your extension add a section to this file containing the path
to your extension.  You should use your own application (section) in the
INI file (any name that begins with EXTENSION may be used), and use the
LOAD key to indicate the path.

For example:

[EXTENSION-EXSCRIPT]
LOAD=C:\EBOOK\RELEASE\EXSCRIPT.AEA

When you are developing you can create this information manually. However for
your final product we recommend that your installation program creates the
appropriate key.

4. When the compiler starts it will attempt to load all extensions listed
in the aebconfig.ini file as described above.  These extensions will only
be unloaded when the compiler exits.  Therefore if you recompile your
extension, you will need to close the compiler (Or otherwise you will get
a share violation error - you can not recompile a running program) and
restart it.

5. Extensions which can be used as part of the E-Book runtime will be
listed in the compiler's Edit Add-Ins dialog box.  The user is thus able
to select which extensions will be used in his project.

6. When a E-Book is compiled containing an extension a copy of the .AEA file
is included as part of the E-Book.  When the E-Book runs this file is
unpacked into a temporary file and loaded by the E-Book runtime.  When the
E-Book exits, the DLL is unloaded and the temporary file deleted.


EXTENSION CODE
==============

1. The best way to understand the C++ code in the extensions is to examine
the sample(s).

2. Each extension is DLL that exports various functions. The compiler and/or
E-Book runtime calls these functions at appropriate points, and the functions
then implement the functionality of the extension.

3. The names and parameters of these functions are specified in detail in the
AEBAPI.H file. As indicated in this file, some functions are optional.

4. Here is a list of the functions:

Function                        Required?       Description (see AEBAPI.H for more details)
--------                        ---------       -------------------------------------------
AEB_GetName                     REQUIRED        Returns the (user visible) name of the extension.
AEB_GetVersion                  REQUIRED        Returns the (user visible) version of the extension.
AEB_Init                        REQUIRED        Called immediately after the extension is loaded by the compiler or E-Book runtime.
AEB_Exit                        REQUIRED        Called immediately before the extension is unloaded by the compiler or E-Book runtime.
AEB_IsRuntime                   REQUIRED        Indicates if the extension is only loaded by the compiler or can be included within the E-Book runtime.
AEB_IsInterface                 REQUIRED        Indicates if the extension supports a particular set of interface functions.

AEB_InfoDlg                     OPTIONAL        Required if AEB_IsRuntime returns true: display info/setup options dialog for the extension.

AEB_ScriptInit                  OPTIONAL        Required if AEB_IsInterface indicates support for AEBINTERFACE_SCRIPT: Called when an Activ Script starts running.
AEB_ScriptExit                  OPTIONAL        Required if AEB_IsInterface indicates support for AEBINTERFACE_SCRIPT: Called when an Activ Script finishes running.
AEB_ScriptGetKey                OPTIONAL        Required if AEB_IsInterface indicates support for AEBINTERFACE_SCRIPT: Specifies first part of the name for Activ Script commands and Activ Variables created by this extension.
AEB_ScriptCommand               OPTIONAL        Required if AEB_IsInterface indicates support for AEBINTERFACE_SCRIPT: Implements new Activ Script commands
AEB_ScriptGetVarName            OPTIONAL        Required if AEB_IsInterface indicates support for AEBINTERFACE_SCRIPT: Implements new Activ Variables
AEB_ScriptGetVarValueLen        OPTIONAL        Required if AEB_IsInterface indicates support for AEBINTERFACE_SCRIPT: Implements new Activ Variables
AEB_ScriptGetVarValue           OPTIONAL        Required if AEB_IsInterface indicates support for AEBINTERFACE_SCRIPT: Implements new Activ Variables
