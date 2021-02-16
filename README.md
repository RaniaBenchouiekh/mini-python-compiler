# mini-python-compiler

A mini Python compiler in C language. Lexical analysis using the [Flex](https://github.com/westes/flex/) tool, and syntax-semantic analysis using the [Bison](https://www.gnu.org/software/bison/) tool. Intermediate code is also generated as well as optimized code and machine code (Assembly).

## Work Phases

#### Lexical Analysis

Its goal is to associate each word of the source program with the lexical category to which it belongs, and to generate the ST (Symbols Table). For this, the different lexical entities are defined using regular expressions, and a corresponding FLEX program is generated.

#### Syntaxic-Semantic Analysis

To implement the syntaxico-semantic analyzer, it was necessary to write the grammar which generates the language defined. The associated grammar is [LALR](https://web.cs.dal.ca/~sjackson/lalr1.html). The BISON tool is a bottom-up analyzer which operates on LALR grammars. The different grammar rules as well as the priority rules for the operatorsare specified in the BISON file in order to resolve the conflicts. Semantic routines are associated with the rules in the BISON file.

#### Symbols Table Managment

The Symbol Table is created during the lexical analysis phase. It must group together all the variables and constants defined by the programmer with all the information necessary for the compilation process, such as the nature (variable, constant or array), the type, the size of the array (the size is equal to 1 for simple variables and constants). This table is implemented as a hash table. It is updated as the compilation progresses. We can search for and insert elements in the ST. Array-type structured variables also appear in the ST.

#### Code Optimization

We consider four types of successive transformations applied to the intermediate code.
- Copy spread

For example, replacing :
``` bash
t1 = t2
t3 = t4 * t1
```
with : 
``` bash
t1 = t2
t3 = t4 * t2
```

- Expression spread

For example, replacing :
``` bash
t1 = expr
t2 = t3 * t1
```
with : 
``` bash
t1 = exp
t2 = t3 * expr
```

- Elimination of redundant expressions

For example, replacing :
``` bash
t1 = 4 * j
t2 = 4 * j
```
with : 
``` bash
t1 = 4 * j
t2 = t1
```

- Algebraic simplification

For example, replacing :
``` bash
t1 + 1 - 1
```
with : 
``` bash
t1
```

- Elimination of unnecessary code

#### Generating Intermediate Code 

The intermediate code is generated in the form of quadruples. For example, the instruction :

``` bash
x = y + z
```

is translated by the quadruplet :

``` bash
(+, y, z, x)
```

The generated quadruplets go through the optimization phase.

#### Generating Machine Code

The machine code is generated in Assembly Language.

#### Error Managment

It is necessary to display the appropriate error messages at each step of the compilation process. Thus, when a lexical or syntactic error is detected by your compiler, it is indicated as precisely as possible, by its nature and its location in the source file. The following format is adopted for this signage:

```bash
error-Type, line line-number, column column-number, entity-that-generated-the-error.
```



