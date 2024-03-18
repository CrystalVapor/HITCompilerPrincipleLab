/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"

#include <stdio.h>
#include "C_Parser_Types.h"
#include "main.h"

#line 77 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "C_Parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_ID = 5,                         /* ID  */
  YYSYMBOL_SEMI = 6,                       /* SEMI  */
  YYSYMBOL_COMMA = 7,                      /* COMMA  */
  YYSYMBOL_ASSIGNOP = 8,                   /* ASSIGNOP  */
  YYSYMBOL_RELOP = 9,                      /* RELOP  */
  YYSYMBOL_PLUS = 10,                      /* PLUS  */
  YYSYMBOL_MINUS = 11,                     /* MINUS  */
  YYSYMBOL_STAR = 12,                      /* STAR  */
  YYSYMBOL_DIV = 13,                       /* DIV  */
  YYSYMBOL_AND = 14,                       /* AND  */
  YYSYMBOL_OR = 15,                        /* OR  */
  YYSYMBOL_DOT = 16,                       /* DOT  */
  YYSYMBOL_NOT = 17,                       /* NOT  */
  YYSYMBOL_TYPE = 18,                      /* TYPE  */
  YYSYMBOL_LP = 19,                        /* LP  */
  YYSYMBOL_RP = 20,                        /* RP  */
  YYSYMBOL_LB = 21,                        /* LB  */
  YYSYMBOL_RB = 22,                        /* RB  */
  YYSYMBOL_LC = 23,                        /* LC  */
  YYSYMBOL_RC = 24,                        /* RC  */
  YYSYMBOL_STRUCT = 25,                    /* STRUCT  */
  YYSYMBOL_RETURN = 26,                    /* RETURN  */
  YYSYMBOL_IF = 27,                        /* IF  */
  YYSYMBOL_ELSE = 28,                      /* ELSE  */
  YYSYMBOL_WHILE = 29,                     /* WHILE  */
  YYSYMBOL_YYACCEPT = 30,                  /* $accept  */
  YYSYMBOL_Program = 31,                   /* Program  */
  YYSYMBOL_ExtDefList = 32,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 33,                    /* ExtDef  */
  YYSYMBOL_ExtDecList = 34,                /* ExtDecList  */
  YYSYMBOL_Specifier = 35,                 /* Specifier  */
  YYSYMBOL_StructSpecifier = 36,           /* StructSpecifier  */
  YYSYMBOL_OptTag = 37,                    /* OptTag  */
  YYSYMBOL_Tag = 38,                       /* Tag  */
  YYSYMBOL_VarDec = 39,                    /* VarDec  */
  YYSYMBOL_FunDec = 40,                    /* FunDec  */
  YYSYMBOL_VarList = 41,                   /* VarList  */
  YYSYMBOL_ParamDec = 42,                  /* ParamDec  */
  YYSYMBOL_CompStm = 43,                   /* CompStm  */
  YYSYMBOL_StmtList = 44,                  /* StmtList  */
  YYSYMBOL_Stmt = 45,                      /* Stmt  */
  YYSYMBOL_DefList = 46,                   /* DefList  */
  YYSYMBOL_Def = 47,                       /* Def  */
  YYSYMBOL_DecList = 48,                   /* DecList  */
  YYSYMBOL_Dec = 49,                       /* Dec  */
  YYSYMBOL_Exp = 50,                       /* Exp  */
  YYSYMBOL_Args = 51                       /* Args  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   251

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  115

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   284


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    59,    59,    63,    64,    68,    69,    70,    71,    75,
      76,    81,    82,    86,    87,    91,    92,    96,   101,   102,
     106,   107,   111,   112,   116,   121,   125,   126,   130,   131,
     132,   133,   134,   135,   136,   141,   142,   146,   150,   151,
     155,   156,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     183,   184
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT", "ID",
  "SEMI", "COMMA", "ASSIGNOP", "RELOP", "PLUS", "MINUS", "STAR", "DIV",
  "AND", "OR", "DOT", "NOT", "TYPE", "LP", "RP", "LB", "RB", "LC", "RC",
  "STRUCT", "RETURN", "IF", "ELSE", "WHILE", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "VarList", "ParamDec", "CompStm",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-52)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-28)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      23,     8,   -52,     2,    17,   -52,    23,    33,   -52,   -52,
      24,    27,   -52,   -52,   -52,    34,   -52,    49,    -2,    43,
     -12,   222,   -52,    51,    68,   -12,   -52,    51,    52,   -12,
     -52,    51,    59,    76,   -52,   -52,    79,    41,     1,    85,
      95,   -52,   -52,    82,   -52,   -12,   -52,   109,   -52,   -52,
      97,    32,    32,    32,    32,    99,   111,   -52,    93,    41,
      84,    32,   -52,    51,   -52,   -52,    69,   223,    -5,   142,
      98,    32,    32,   -52,   -52,   -52,    32,    32,    32,    32,
      32,    32,    32,    32,   126,    32,   184,   -52,   -52,   113,
     112,   -52,   -52,   156,   170,   184,   217,   223,   223,    -5,
      -5,   210,   197,   -52,   127,    32,   -52,    58,    58,   -52,
     -52,   105,   -52,    58,   -52
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    11,    16,     0,     2,     0,     0,    12,     8,
      17,     0,    14,     1,     3,    18,     6,     0,     9,     0,
      36,     0,     5,     0,     0,    36,     7,     0,     0,    36,
      21,     0,     0,    23,    18,    10,     0,     0,    40,     0,
      38,    13,    35,    24,    20,     0,    19,     0,    58,    59,
      57,     0,     0,     0,     0,     0,     0,    29,     0,     0,
       0,     0,    37,     0,    22,    34,     0,    51,    52,     0,
       0,     0,     0,    25,    26,    28,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    41,    39,    54,    61,
       0,    50,    30,     0,     0,    42,    45,    46,    47,    48,
      49,    43,    44,    56,     0,     0,    53,     0,     0,    55,
      60,    31,    33,     0,    32
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -52,   -52,   139,   -52,   121,    12,   -52,   -52,   -52,   -23,
     -52,   101,   -52,   128,   100,   138,    53,   -52,   110,   -52,
     -51,    55
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,    17,    27,     8,    11,    12,    18,
      19,    32,    33,    57,    58,    59,    28,    29,    39,    40,
      60,    90
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      67,    68,    69,    70,    38,    23,     2,    10,    43,    61,
      86,    84,     7,     3,     9,    89,    85,    13,     7,    24,
      93,    94,    24,    -4,     1,    95,    96,    97,    98,    99,
     100,   101,   102,    31,   104,    48,    49,    50,    15,    16,
      38,     2,    47,    51,    48,    49,    50,   -15,     3,    52,
      20,    53,    51,    21,    89,    22,    34,    31,    52,    47,
      53,    48,    49,    50,    25,   -27,    25,    54,    55,    51,
      56,    36,    48,    49,    50,    52,    41,    53,    37,    44,
      51,    25,    42,    45,    54,    55,    52,    56,    53,    88,
      75,    62,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    46,    63,    24,    92,    85,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    65,    66,    73,    71,    85,
     105,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      72,   103,   106,   113,    85,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    35,    14,    64,    26,    85,   109,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    74,
     110,     0,    91,    85,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    87,     0,     0,   107,    85,    76,    77,
      78,    79,    80,    81,    82,    83,    84,     0,     0,     0,
     108,    85,    76,    77,    78,    79,    80,    81,    82,    83,
      84,     0,     0,     0,     0,    85,    77,    78,    79,    80,
      81,    82,     0,    84,     0,     0,     0,     0,    85,    77,
      78,    79,    80,    81,     0,     0,    84,    78,    79,    80,
      81,    85,     0,    84,     0,    80,    81,     0,    85,    84,
       2,     0,    30,     0,    85,   111,   112,     3,     0,     0,
       0,   114
};

static const yytype_int8 yycheck[] =
{
      51,    52,    53,    54,    27,     7,    18,     5,    31,     8,
      61,    16,     0,    25,     6,    66,    21,     0,     6,    21,
      71,    72,    21,     0,     1,    76,    77,    78,    79,    80,
      81,    82,    83,    21,    85,     3,     4,     5,     5,     6,
      63,    18,     1,    11,     3,     4,     5,    23,    25,    17,
      23,    19,    11,    19,   105,     6,     5,    45,    17,     1,
      19,     3,     4,     5,    23,    24,    23,    26,    27,    11,
      29,     3,     3,     4,     5,    17,    24,    19,    25,    20,
      11,    23,    29,     7,    26,    27,    17,    29,    19,    20,
       6,     6,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    22,     7,    21,     6,    21,     8,     9,    10,    11,
      12,    13,    14,    15,    16,     6,    19,    24,    19,    21,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      19,     5,    20,    28,    21,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    23,     6,    45,    19,    21,    22,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    59,
     105,    -1,    20,    21,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    63,    -1,    -1,    20,    21,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    -1,
      20,    21,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    -1,    -1,    -1,    -1,    21,     9,    10,    11,    12,
      13,    14,    -1,    16,    -1,    -1,    -1,    -1,    21,     9,
      10,    11,    12,    13,    -1,    -1,    16,    10,    11,    12,
      13,    21,    -1,    16,    -1,    12,    13,    -1,    21,    16,
      18,    -1,    20,    -1,    21,   107,   108,    25,    -1,    -1,
      -1,   113
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,    18,    25,    31,    32,    33,    35,    36,     6,
       5,    37,    38,     0,    32,     5,     6,    34,    39,    40,
      23,    19,     6,     7,    21,    23,    43,    35,    46,    47,
      20,    35,    41,    42,     5,    34,     3,    46,    39,    48,
      49,    24,    46,    39,    20,     7,    22,     1,     3,     4,
       5,    11,    17,    19,    26,    27,    29,    43,    44,    45,
      50,     8,     6,     7,    41,     6,    19,    50,    50,    50,
      50,    19,    19,    24,    44,     6,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    21,    50,    48,    20,    50,
      51,    20,     6,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,     5,    50,     7,    20,    20,    20,    22,
      51,    45,    45,    28,    45
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    30,    31,    32,    32,    33,    33,    33,    33,    34,
      34,    35,    35,    36,    36,    37,    37,    38,    39,    39,
      40,    40,    41,    41,    42,    43,    44,    44,    45,    45,
      45,    45,    45,    45,    45,    46,    46,    47,    48,    48,
      49,    49,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      51,    51
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     2,     1,
       3,     1,     1,     5,     2,     1,     0,     1,     1,     4,
       4,     3,     3,     1,     2,     4,     2,     0,     2,     1,
       3,     5,     7,     5,     2,     2,     0,     3,     1,     3,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     4,     3,     4,     3,     1,     1,     1,
       3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: ExtDefList  */
#line 59 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(PROGRAM, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX); setParserTreeRoot((yyval.nodeIndex));}
#line 1214 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 3: /* ExtDefList: ExtDef ExtDefList  */
#line 63 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[2] = {(yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXT_DEF_LIST, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
#line 1220 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 4: /* ExtDefList: %empty  */
#line 64 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {(yyval.nodeIndex) = newParserNode(EXT_DEF_LIST, NO_LINE_NUMBER, 0, NULL, INVALID_NODE_INDEX);}
#line 1226 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 5: /* ExtDef: Specifier ExtDecList SEMI  */
#line 68 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXT_DEF, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1232 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 6: /* ExtDef: Specifier SEMI  */
#line 69 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[2] = {(yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXT_DEF, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
#line 1238 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 7: /* ExtDef: Specifier FunDec CompStm  */
#line 70 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXT_DEF, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1244 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 8: /* ExtDef: error SEMI  */
#line 71 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {reportSyntaxError(getParserNode((yyvsp[0].nodeIndex))->lineNum, "Wrong external definition");}
#line 1250 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 9: /* ExtDecList: VarDec  */
#line 75 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXT_DEC_LIST, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1256 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 10: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 76 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXT_DEC_LIST, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1262 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 11: /* Specifier: TYPE  */
#line 81 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(SPECIFIER, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1268 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 12: /* Specifier: StructSpecifier  */
#line 82 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(SPECIFIER, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1274 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 13: /* StructSpecifier: STRUCT OptTag LC DefList RC  */
#line 86 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[5] = {(yyvsp[-4].nodeIndex), (yyvsp[-3].nodeIndex), (yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(STRUCT_SPECIFIER, NO_LINE_NUMBER, 5, children, INVALID_NODE_INDEX);}
#line 1280 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 14: /* StructSpecifier: STRUCT Tag  */
#line 87 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[2] = {(yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(STRUCT_SPECIFIER, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
#line 1286 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 15: /* OptTag: ID  */
#line 91 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(OPT_TAG, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1292 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 16: /* OptTag: %empty  */
#line 92 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {(yyval.nodeIndex) = newParserNode(OPT_TAG, NO_LINE_NUMBER, 0, NULL, INVALID_NODE_INDEX);}
#line 1298 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 17: /* Tag: ID  */
#line 96 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(TAG, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1304 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 18: /* VarDec: ID  */
#line 101 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(VAR_DEC, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1310 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 19: /* VarDec: VarDec LB INT RB  */
#line 102 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[4] = {(yyvsp[-3].nodeIndex), (yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(VAR_DEC, NO_LINE_NUMBER, 4, children, INVALID_NODE_INDEX);}
#line 1316 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 20: /* FunDec: ID LP VarList RP  */
#line 106 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[4] = {(yyvsp[-3].nodeIndex), (yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(FUN_DEC, NO_LINE_NUMBER, 4, children, INVALID_NODE_INDEX);}
#line 1322 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 21: /* FunDec: ID LP RP  */
#line 107 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(FUN_DEC, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1328 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 22: /* VarList: ParamDec COMMA VarList  */
#line 111 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(VAR_LIST, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1334 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 23: /* VarList: ParamDec  */
#line 112 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(VAR_LIST, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1340 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 24: /* ParamDec: Specifier VarDec  */
#line 116 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[2] = {(yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(PARAM_DEC, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
#line 1346 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 25: /* CompStm: LC DefList StmtList RC  */
#line 121 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[4] = {(yyvsp[-3].nodeIndex), (yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(COMP_STM, NO_LINE_NUMBER, 4, children, INVALID_NODE_INDEX);}
#line 1352 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 26: /* StmtList: Stmt StmtList  */
#line 125 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[2] = {(yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(STMT_LIST, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
#line 1358 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 27: /* StmtList: %empty  */
#line 126 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {(yyval.nodeIndex) = newParserNode(STMT_LIST, NO_LINE_NUMBER, 0, NULL, INVALID_NODE_INDEX);}
#line 1364 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 28: /* Stmt: Exp SEMI  */
#line 130 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[2] = {(yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(STMT, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
#line 1370 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 29: /* Stmt: CompStm  */
#line 131 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(STMT, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1376 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 30: /* Stmt: RETURN Exp SEMI  */
#line 132 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(STMT, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1382 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 31: /* Stmt: IF LP Exp RP Stmt  */
#line 133 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[4] = {(yyvsp[-4].nodeIndex), (yyvsp[-3].nodeIndex), (yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex)}; (yyval.nodeIndex) = newParserNode(STMT, NO_LINE_NUMBER, 4, children, INVALID_NODE_INDEX);}
#line 1388 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 32: /* Stmt: IF LP Exp RP Stmt ELSE Stmt  */
#line 134 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[6] = {(yyvsp[-6].nodeIndex), (yyvsp[-5].nodeIndex), (yyvsp[-4].nodeIndex), (yyvsp[-3].nodeIndex), (yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex)}; (yyval.nodeIndex) = newParserNode(STMT, NO_LINE_NUMBER, 6, children, INVALID_NODE_INDEX);}
#line 1394 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 33: /* Stmt: WHILE LP Exp RP Stmt  */
#line 135 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[4] = {(yyvsp[-4].nodeIndex), (yyvsp[-3].nodeIndex), (yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex)}; (yyval.nodeIndex) = newParserNode(STMT, NO_LINE_NUMBER, 4, children, INVALID_NODE_INDEX);}
#line 1400 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 34: /* Stmt: error SEMI  */
#line 136 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {reportSyntaxError(getParserNode((yyvsp[0].nodeIndex))->lineNum, "Wrong statement");}
#line 1406 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 35: /* DefList: Def DefList  */
#line 141 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[2] = {(yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(DEF_LIST, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
#line 1412 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 36: /* DefList: %empty  */
#line 142 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {(yyval.nodeIndex) = newParserNode(DEF_LIST, NO_LINE_NUMBER, 0, NULL, INVALID_NODE_INDEX);}
#line 1418 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 37: /* Def: Specifier DecList SEMI  */
#line 146 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(DEF, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1424 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 38: /* DecList: Dec  */
#line 150 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(DEC_LIST, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1430 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 39: /* DecList: Dec COMMA DecList  */
#line 151 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(DEC_LIST, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1436 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 40: /* Dec: VarDec  */
#line 155 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(DEC, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1442 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 41: /* Dec: VarDec ASSIGNOP Exp  */
#line 156 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(DEC, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1448 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 42: /* Exp: Exp ASSIGNOP Exp  */
#line 162 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1454 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 43: /* Exp: Exp AND Exp  */
#line 163 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1460 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 44: /* Exp: Exp OR Exp  */
#line 164 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1466 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 45: /* Exp: Exp RELOP Exp  */
#line 165 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1472 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 46: /* Exp: Exp PLUS Exp  */
#line 166 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1478 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 47: /* Exp: Exp MINUS Exp  */
#line 167 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1484 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 48: /* Exp: Exp STAR Exp  */
#line 168 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1490 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 49: /* Exp: Exp DIV Exp  */
#line 169 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1496 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 50: /* Exp: LP Exp RP  */
#line 170 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1502 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 51: /* Exp: MINUS Exp  */
#line 171 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[2] = {(yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
#line 1508 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 52: /* Exp: NOT Exp  */
#line 172 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[2] = {(yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
#line 1514 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 53: /* Exp: ID LP Args RP  */
#line 173 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[4] = {(yyvsp[-3].nodeIndex), (yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 4, children, INVALID_NODE_INDEX);}
#line 1520 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 54: /* Exp: ID LP RP  */
#line 174 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1526 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 55: /* Exp: Exp LB Exp RB  */
#line 175 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[4] = {(yyvsp[-3].nodeIndex), (yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 4, children, INVALID_NODE_INDEX);}
#line 1532 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 56: /* Exp: Exp DOT ID  */
#line 176 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1538 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 57: /* Exp: ID  */
#line 177 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1544 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 58: /* Exp: INT  */
#line 178 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1550 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 59: /* Exp: FLOAT  */
#line 179 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1556 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 60: /* Args: Exp COMMA Args  */
#line 183 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(ARGS, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1562 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;

  case 61: /* Args: Exp  */
#line 184 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
                                    {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(ARGS, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1568 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"
    break;


#line 1572 "/home/crystal/compilerPriciple/Lab1/cmake-build-debug/C_Parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 187 "/home/crystal/compilerPriciple/Lab1/src/C_Parser.y"
