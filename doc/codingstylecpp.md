C++ Coding Style                          {#codingstylecpp}
================

# File Name

## Source File Structure

Due a limitation of the Doxygen parser in all examples on this guide, we use `/*
*` with a blank separating a Doxygen comment block. Also we use a `\@` to mark
Doxygen commands. In real code you should remove the blank between asterisks and
remove the bar before the `@` mark.

The first block in a source file is the Copyright notices and the GPL 3 copying
permission statement. This block can be copied from `doc/gpl3_header` file.

The C++ source code use an 80 characters row length as limit. All the source
code should wrap itself to this limit whenever it doesn't break the readability
of it.

We use a C++ single line comment with dashes until the 80 character limits to
separate source code sections. It is called a separation line in the rest of
this guide. An example of separation line is:

~~~~~~~~~~{.cpp}
//------------------------------------------------------------------------------
~~~~~~~~~~

Indentation is 4 spaces. We don't use tabs in the source code. Also, trailing
whitespace is never allowed. This includes lines with nothing but spaces, as
well as spaces being the last characters on a line with non-whitespace
characters.

After the GPL statement, there is a Doxygen file documentation block with at
least file name, brief, author and date commands.

The rest of the source file is the source code itself.

All the source files are ended with a separation line.

### Header File Example

~~~~~~~~~~{.cpp}
/*------------------------------------------------------------------------------
    Copyright 2014, HexWorld Authors.

    INCLUDE GPL HEADER FILE
------------------------------------------------------------------------------*/
/* * \@file chunk.hpp
    \@brief Chunk Class Definition.
    \@author Luis Cabellos
    \@date 2013-08-05
*/
//------------------------------------------------------------------------------
#ifndef CHUNK_HPP_
#define CHUNK_HPP_

//------------------------------------------------------------------------------
#include "types.hpp"

//------------------------------------------------------------------------------
class Chunk{
public:
private:
};
//------------------------------------------------------------------------------
#endif//CHUNK_HPP_

//------------------------------------------------------------------------------
~~~~~~~~~~

### Source File Example

~~~~~~~~~~{.cpp}
/*------------------------------------------------------------------------------
    Copyright 2014, HexWorld Authors.

    INCLUDE GPL HEADER FILE
------------------------------------------------------------------------------*/
/* * \@file chunk.cpp
    \@brief Chunk class definition.
    \@author Luis Cabellos
    \@date 2013-08-05
*/
//------------------------------------------------------------------------------
#include "chunk.hpp"

//------------------------------------------------------------------------------
Chunk::Chunk(){
    // function
}

//------------------------------------------------------------------------------
~~~~~~~~~~

