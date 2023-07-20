# Activ E-Book Compiler API

[![Activ E-Book API version][API badge]][API link]&nbsp;
[![Activ E-Book Compiler version][AEB badge]][Activ E-Book Compiler]&nbsp;
[![Activ E-Book API license][license badge]][license.txt]&nbsp;

The Activ E-Book and [Activ E-Book Compiler] API, created by [Answers 2000 Ltd].

- https://github.com/tajmone/aeb-api

-----

**Table of Contents**

<!-- MarkdownTOC autolink="true" bracket="round" autoanchor="false" lowercase="only_ascii" uri_encoding="true" levels="1,2,3" -->

- [Project Contents](#project-contents)
- [About](#about)
- [Acknowledgement](#acknowledgement)
- [License](#license)

<!-- /MarkdownTOC -->

-----

# Project Contents

- [`/api/`][api/]
    + [`/include/`][include/]
        * [`aebapi.h`][aebapi.h] — API headers.
    + [`/sample/`][sample/]
        * [`/exscript/`][exscript/] — sample E-Book extension (C++).
            - [`exscript.cpp`][exscript.cpp]
            - [`exscript.dsp`][exscript.dsp]
            - [`exscript.dsw`][exscript.dsw]
            - [`exscript.ncb`][exscript.ncb]
            - [`exscript.opt`][exscript.opt]
            - [`exscript.plg`][exscript.plg]
    + [`readme.txt`][readme.txt] — API documentation.
- [`license.txt`][license.txt] — Activ E-Book License file.


# About

[Activ E-Book Compiler] is a commercial application by [Answers 2000 Ltd] to create portable HTML E-Books in executable format for MS Windows.

The Activ E-Book and Activ E-Book Compiler API allows end users to create DLL modules to extend the functionality of either the compiler
itself, or of both the compiler and the generated E-Books. An example of such extensions is the [Advanced Multimedia Extension] for Activ E-Book Compiler, also by [Answers 2000 Ltd].

The Activ E-Book API files in this repository are the official API, obtained from [Answers 2000 Ltd] customer service, and reproduced in this repository with their explicit permission, as a public service to other Activ E-Book users.

I'm not affiliated to [Answers 2000 Ltd], I'm just an [Activ E-Book Compiler] end user who created this repository as a private initiative.


# Acknowledgement

I wish to thank [Sunil Tanna] from [Answers 2000 Ltd]  (and creator of [Activ E-Book Compiler]) for having granted me permission to share the Activ E-Book API on GitHub, and for his relentless customer support in over twenty years as an Activ E-Book Compiler end user.


# License

- [`license.txt`][license.txt] — Activ E-Book License file.

The Activ E-Book and Activ E-Book Compiler API is Copyright &copy; by [Answers 2000 Ltd] and is governed by the **Activ E-Book License**, which is here reproduced in the [`license.txt`][license.txt] file — i.e. the same `license.txt` file which you'll find in your Activ E-Book Compiler installation folder.

The API in this repository was published with explicit permission from [Answers 2000 Ltd]. For any uses beyond those mentioned in the [Activ E-Book License][license.txt], you'll need to contact [Activ E-Book Compiler] customer support.

<!-----------------------------------------------------------------------------
                               REFERENCE LINKS
------------------------------------------------------------------------------>

[Activ E-Book Compiler]: https://www.ebookcompiler.com "Activ E-Book Compiler website"
[Answers 2000 Ltd]: http://www.ans2000.com "Answers 2000 Limited website"
[Advanced Multimedia Extension]: https://www.ebookpower.com "Advanced Multimedia Extension for Activ E-Book Compiler"
[Sunil Tanna]: https://www.suniltanna.com "Sunil Tanna's website"

<!-- files & folders -->

[api/]: ./api/
[readme.txt]: ./api/readme.txt

[include/]: ./api/include
[aebapi.h]: ./api/include/aebapi.h

[sample/]: ./api/sample
[exscript/]: ./api/sample/exscript
[exscript.cpp]: ./api/sample/exscript/exscript.cpp
[exscript.dsp]: ./api/sample/exscript/exscript.dsp
[exscript.dsw]: ./api/sample/exscript/exscript.dsw
[exscript.ncb]: ./api/sample/exscript/exscript.ncb
[exscript.opt]: ./api/sample/exscript/exscript.opt
[exscript.plg]: ./api/sample/exscript/exscript.plg

[license.txt]: ./license.txt "Activ E-Book License File"

<!-- badges -->

[AEB badge]: https://img.shields.io/badge/Activ_E--Book_Compiler-4.22_Plus-yellow
[API badge]: https://img.shields.io/badge/Activ_E--Book_API-4.00-yellow
[API link]: https://github.com/tajmone/aeb-api "Activ E-Book API version"
[license badge]: https://img.shields.io/badge/license-Activ_E--Book_License-blue

<!-- EOF -->
