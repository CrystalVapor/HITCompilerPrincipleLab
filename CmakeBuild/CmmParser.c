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
#line 1 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"

#define NOINCLUDE_CMM_SCANNER_TAB_H
#include <stddef.h>
#include "CmmParserTypes.h"
#include "Structure/ParserNodes.h"
#include "ErrorReporter.h"
#undef NOINCLUDE_CMM_SCANNER_TAB_H

extern int yylineno;
extern int yylex();

#line 83 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"

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

#include "CmmParser.tab.h"
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
  YYSYMBOL_EQ = 9,                         /* EQ  */
  YYSYMBOL_NEQ = 10,                       /* NEQ  */
  YYSYMBOL_LE = 11,                        /* LE  */
  YYSYMBOL_LT = 12,                        /* LT  */
  YYSYMBOL_GE = 13,                        /* GE  */
  YYSYMBOL_GT = 14,                        /* GT  */
  YYSYMBOL_PLUS = 15,                      /* PLUS  */
  YYSYMBOL_MINUS = 16,                     /* MINUS  */
  YYSYMBOL_STAR = 17,                      /* STAR  */
  YYSYMBOL_DIV = 18,                       /* DIV  */
  YYSYMBOL_AND = 19,                       /* AND  */
  YYSYMBOL_OR = 20,                        /* OR  */
  YYSYMBOL_DOT = 21,                       /* DOT  */
  YYSYMBOL_NOT = 22,                       /* NOT  */
  YYSYMBOL_TYPE = 23,                      /* TYPE  */
  YYSYMBOL_LP = 24,                        /* LP  */
  YYSYMBOL_RP = 25,                        /* RP  */
  YYSYMBOL_LB = 26,                        /* LB  */
  YYSYMBOL_RB = 27,                        /* RB  */
  YYSYMBOL_LC = 28,                        /* LC  */
  YYSYMBOL_RC = 29,                        /* RC  */
  YYSYMBOL_STRUCT = 30,                    /* STRUCT  */
  YYSYMBOL_RETURN = 31,                    /* RETURN  */
  YYSYMBOL_IF = 32,                        /* IF  */
  YYSYMBOL_ELSE = 33,                      /* ELSE  */
  YYSYMBOL_WHILE = 34,                     /* WHILE  */
  YYSYMBOL_LELSE = 35,                     /* LELSE  */
  YYSYMBOL_pri3 = 36,                      /* pri3  */
  YYSYMBOL_pri2 = 37,                      /* pri2  */
  YYSYMBOL_pri1 = 38,                      /* pri1  */
  YYSYMBOL_pri0 = 39,                      /* pri0  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_Program = 41,                   /* Program  */
  YYSYMBOL_ExtDefList = 42,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 43,                    /* ExtDef  */
  YYSYMBOL_ExtDecList = 44,                /* ExtDecList  */
  YYSYMBOL_Specifier = 45,                 /* Specifier  */
  YYSYMBOL_StructSpecifier = 46,           /* StructSpecifier  */
  YYSYMBOL_OptTag = 47,                    /* OptTag  */
  YYSYMBOL_Tag = 48,                       /* Tag  */
  YYSYMBOL_VarDec = 49,                    /* VarDec  */
  YYSYMBOL_FunDec = 50,                    /* FunDec  */
  YYSYMBOL_VarList = 51,                   /* VarList  */
  YYSYMBOL_ParamDec = 52,                  /* ParamDec  */
  YYSYMBOL_CompStm = 53,                   /* CompStm  */
  YYSYMBOL_StmtList = 54,                  /* StmtList  */
  YYSYMBOL_Stmt = 55,                      /* Stmt  */
  YYSYMBOL_DefList = 56,                   /* DefList  */
  YYSYMBOL_Def = 57,                       /* Def  */
  YYSYMBOL_DecList = 58,                   /* DecList  */
  YYSYMBOL_Dec = 59,                       /* Dec  */
  YYSYMBOL_Exp = 60,                       /* Exp  */
  YYSYMBOL_Args = 61                       /* Args  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYLAST   337

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  130

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    74,    74,    78,    79,    83,    84,    85,    86,    88,
      89,    90,    91,    95,    96,    98,   103,   104,   108,   109,
     113,   114,   118,   123,   124,   126,   130,   131,   133,   137,
     138,   142,   144,   149,   153,   154,   158,   159,   160,   161,
     162,   163,   165,   171,   172,   176,   180,   181,   185,   186,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   216,   220,   221
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
  "SEMI", "COMMA", "ASSIGNOP", "EQ", "NEQ", "LE", "LT", "GE", "GT", "PLUS",
  "MINUS", "STAR", "DIV", "AND", "OR", "DOT", "NOT", "TYPE", "LP", "RP",
  "LB", "RB", "LC", "RC", "STRUCT", "RETURN", "IF", "ELSE", "WHILE",
  "LELSE", "pri3", "pri2", "pri1", "pri0", "$accept", "Program",
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

#define YYPACT_NINF (-51)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-36)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      60,     5,   -51,     8,    29,   -51,    60,    57,   -51,   -51,
      19,    21,   -51,   -51,   -51,    28,   -51,    53,    51,    16,
     -13,    80,   -51,   -51,    52,    70,   -51,   -51,   -13,   -51,
      52,    46,   -13,   -51,    52,    61,    66,    69,   -51,    62,
      50,    -7,    87,    95,   -51,   -51,    61,   -51,    41,   -51,
     103,   -51,   -51,    99,   110,   110,   110,   110,   100,   104,
     -51,    65,    50,   127,   110,   -51,    52,   -51,   110,   -51,
     -51,    96,   311,    -1,   205,   146,   110,   110,   -51,   -51,
     -51,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   124,   110,   262,   -51,   -51,   166,
     105,   -51,   -51,   224,   243,   262,   305,   305,   305,   305,
     305,   305,   311,   311,    -1,    -1,   298,   280,   -51,   185,
     110,   -51,    64,    64,   -51,   -51,    98,   -51,    64,   -51
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    16,    21,     0,     2,     0,    10,    17,    12,
      22,     0,    19,     1,     3,    23,     6,     9,    13,    11,
      44,     0,     5,    23,     0,     0,    15,     8,    44,     7,
       0,     0,    44,    27,     0,    32,    28,    30,    14,    25,
       0,    48,     0,    46,    18,    43,    31,    26,     0,    24,
       0,    71,    72,    70,     0,     0,     0,     0,     0,     0,
      37,     0,     0,     0,     0,    45,     0,    29,     0,    42,
      73,     0,    64,    65,     0,     0,     0,     0,    33,    34,
      36,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    47,    67,    75,
       0,    63,    38,     0,     0,    50,    53,    54,    56,    55,
      58,    57,    59,    60,    61,    62,    51,    52,    69,     0,
       0,    66,     0,     0,    68,    74,    39,    41,     0,    40
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -51,   -51,   143,   -51,    -9,     2,   -51,   -51,   -51,   -18,
     -51,   102,   -51,   132,   106,    -6,    -4,   -51,   122,   -51,
     -50,    49
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     4,     5,     6,    17,    30,     8,    11,    12,    18,
      19,    36,    37,    60,    61,    62,    31,    32,    42,    43,
      63,   100
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      70,    64,     7,    35,    72,    73,    74,    75,     7,    26,
       2,     9,    41,    10,    96,    38,    46,     3,    70,    25,
      94,    99,    27,    34,    40,    95,   103,   104,    45,    13,
      35,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,    28,   119,    23,   -20,    41,    20,
      34,    50,    21,    51,    52,    53,    23,    23,    24,    22,
      -4,     1,    15,    16,     2,    50,    54,    51,    52,    53,
      99,     3,    55,    39,    56,    44,    48,    25,    28,   -35,
      54,    57,    58,     2,    59,    23,    55,    25,    56,    49,
       3,    47,    28,    65,    78,    57,    58,    68,    59,    51,
      52,    53,    66,     2,    68,    33,    51,    52,    53,    69,
       3,    68,    54,    51,    52,    53,   126,   127,    55,    54,
      56,    98,   129,    71,    76,    55,    54,    56,    77,   118,
     121,   128,    55,    80,    56,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    14,
      67,    29,   102,    95,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    79,   125,
       0,     0,    95,   120,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    97,     0,
       0,     0,    95,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,     0,     0,     0,
       0,    95,   124,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,     0,     0,     0,
     101,    95,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,     0,     0,     0,   122,
      95,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,     0,     0,     0,   123,    95,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,     0,     0,     0,     0,    95,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
       0,    94,     0,     0,     0,     0,    95,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,     0,     0,    94,
      88,    89,    90,    91,    95,     0,    94,     0,    90,    91,
       0,    95,    94,     0,     0,     0,     0,    95
};

static const yytype_int16 yycheck[] =
{
      50,     8,     0,    21,    54,    55,    56,    57,     6,    18,
      23,     6,    30,     5,    64,    24,    34,    30,    68,    26,
      21,    71,     6,    21,    28,    26,    76,    77,    32,     0,
      48,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    28,    95,     5,    28,    66,    28,
      48,     1,    24,     3,     4,     5,     5,     5,     7,     6,
       0,     1,     5,     6,    23,     1,    16,     3,     4,     5,
     120,    30,    22,     3,    24,    29,     7,    26,    28,    29,
      16,    31,    32,    23,    34,     5,    22,    26,    24,    27,
      30,    25,    28,     6,    29,    31,    32,     1,    34,     3,
       4,     5,     7,    23,     1,    25,     3,     4,     5,     6,
      30,     1,    16,     3,     4,     5,   122,   123,    22,    16,
      24,    25,   128,    24,    24,    22,    16,    24,    24,     5,
      25,    33,    22,     6,    24,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,     6,
      48,    19,     6,    26,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    62,   120,
      -1,    -1,    26,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    66,    -1,
      -1,    -1,    26,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      -1,    26,    27,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    -1,    -1,    -1,
      25,    26,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    -1,    -1,    -1,    25,
      26,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    -1,    -1,    -1,    25,    26,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    -1,    -1,    -1,    -1,    26,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      -1,    21,    -1,    -1,    -1,    -1,    26,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    -1,    -1,    21,
      15,    16,    17,    18,    26,    -1,    21,    -1,    17,    18,
      -1,    26,    21,    -1,    -1,    -1,    -1,    26
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,    23,    30,    41,    42,    43,    45,    46,     6,
       5,    47,    48,     0,    42,     5,     6,    44,    49,    50,
      28,    24,     6,     5,     7,    26,    44,     6,    28,    53,
      45,    56,    57,    25,    45,    49,    51,    52,    44,     3,
      56,    49,    58,    59,    29,    56,    49,    25,     7,    27,
       1,     3,     4,     5,    16,    22,    24,    31,    32,    34,
      53,    54,    55,    60,     8,     6,     7,    51,     1,     6,
      60,    24,    60,    60,    60,    60,    24,    24,    29,    54,
       6,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    26,    60,    58,    25,    60,
      61,    25,     6,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,     5,    60,
       7,    25,    25,    25,    27,    61,    55,    55,    33,    55
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    43,    43,    43,
      43,    43,    43,    44,    44,    44,    45,    45,    46,    46,
      47,    47,    48,    49,    49,    49,    50,    50,    50,    51,
      51,    52,    52,    53,    54,    54,    55,    55,    55,    55,
      55,    55,    55,    56,    56,    57,    58,    58,    59,    59,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    61,    61
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     3,     2,
       1,     2,     2,     1,     3,     2,     1,     1,     5,     2,
       1,     0,     1,     1,     4,     3,     4,     3,     3,     3,
       1,     2,     1,     4,     2,     0,     2,     1,     3,     5,
       7,     5,     2,     2,     0,     3,     1,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     4,     3,     4,     3,
       1,     1,     1,     2,     3,     1
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
#line 74 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(PROGRAM, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX); setParserTreeRoot((yyval.nodeIndex));}
#line 1254 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 3: /* ExtDefList: ExtDef ExtDefList  */
#line 78 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[2] = {(yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXT_DEF_LIST, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
#line 1260 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 4: /* ExtDefList: %empty  */
#line 79 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {(yyval.nodeIndex) = newParserNode(EXT_DEF_LIST, NO_LINE_NUMBER, 0, NULL, INVALID_NODE_INDEX);}
#line 1266 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 5: /* ExtDef: Specifier ExtDecList SEMI  */
#line 83 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXT_DEF, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1272 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 6: /* ExtDef: Specifier SEMI  */
#line 84 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[2] = {(yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXT_DEF, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
#line 1278 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 7: /* ExtDef: Specifier FunDec CompStm  */
#line 85 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXT_DEF, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1284 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 8: /* ExtDef: Specifier FunDec SEMI  */
#line 86 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXT_DEF, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1290 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 9: /* ExtDef: Specifier ExtDecList  */
#line 88 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {reportError(getParserNode((yyvsp[-1].nodeIndex))->lineNum, MissingSemicolon, "Missing \";\"");}
#line 1296 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 10: /* ExtDef: Specifier  */
#line 89 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {reportError(getParserNode((yyvsp[0].nodeIndex))->lineNum, MissingSemicolon, "Missing \";\"");}
#line 1302 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 11: /* ExtDef: Specifier FunDec  */
#line 90 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {reportError(getParserNode((yyvsp[0].nodeIndex))->lineNum, MissingSemicolon, "Missing \";\"");}
#line 1308 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 12: /* ExtDef: error SEMI  */
#line 91 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {yyerrok; reportError(yylineno, UnexpectedDeclaration, "Unexpected Declaration");}
#line 1314 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 13: /* ExtDecList: VarDec  */
#line 95 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXT_DEC_LIST, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1320 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 14: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 96 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXT_DEC_LIST, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1326 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 15: /* ExtDecList: VarDec ExtDecList  */
#line 98 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {reportError(getParserNode((yyvsp[0].nodeIndex))->lineNum, MissingComma, "Missing \",\"");}
#line 1332 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 16: /* Specifier: TYPE  */
#line 103 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(SPECIFIER, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1338 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 17: /* Specifier: StructSpecifier  */
#line 104 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(SPECIFIER, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1344 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 18: /* StructSpecifier: STRUCT OptTag LC DefList RC  */
#line 108 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[5] = {(yyvsp[-4].nodeIndex), (yyvsp[-3].nodeIndex), (yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(STRUCT_SPECIFIER, NO_LINE_NUMBER, 5, children, INVALID_NODE_INDEX);}
#line 1350 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 19: /* StructSpecifier: STRUCT Tag  */
#line 109 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[2] = {(yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(STRUCT_SPECIFIER, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
#line 1356 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 20: /* OptTag: ID  */
#line 113 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(OPT_TAG, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1362 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 21: /* OptTag: %empty  */
#line 114 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {(yyval.nodeIndex) = newParserNode(OPT_TAG, NO_LINE_NUMBER, 0, NULL, INVALID_NODE_INDEX);}
#line 1368 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 22: /* Tag: ID  */
#line 118 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(TAG, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1374 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 23: /* VarDec: ID  */
#line 123 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(VAR_DEC, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1380 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 24: /* VarDec: VarDec LB INT RB  */
#line 124 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[4] = {(yyvsp[-3].nodeIndex), (yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(VAR_DEC, NO_LINE_NUMBER, 4, children, INVALID_NODE_INDEX);}
#line 1386 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 25: /* VarDec: VarDec LB INT  */
#line 126 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {reportError(getParserNode((yyvsp[-1].nodeIndex))->lineNum, MissingRightBracket, "Missing \"]\"");}
#line 1392 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 26: /* FunDec: ID LP VarList RP  */
#line 130 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[4] = {(yyvsp[-3].nodeIndex), (yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(FUN_DEC, NO_LINE_NUMBER, 4, children, INVALID_NODE_INDEX);}
#line 1398 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 27: /* FunDec: ID LP RP  */
#line 131 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(FUN_DEC, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1404 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 28: /* FunDec: ID LP VarList  */
#line 133 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {reportError(getParserNode((yyvsp[-1].nodeIndex))->lineNum, MissingRightParenthesis, "Missing \")\"");}
#line 1410 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 29: /* VarList: ParamDec COMMA VarList  */
#line 137 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(VAR_LIST, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1416 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 30: /* VarList: ParamDec  */
#line 138 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(VAR_LIST, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1422 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 31: /* ParamDec: Specifier VarDec  */
#line 142 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[2] = {(yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(PARAM_DEC, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
#line 1428 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 32: /* ParamDec: VarDec  */
#line 144 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {reportError(getParserNode((yyvsp[0].nodeIndex))->lineNum, MissingSpecifier, "Missing Specifier");}
#line 1434 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 33: /* CompStm: LC DefList StmtList RC  */
#line 149 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[4] = {(yyvsp[-3].nodeIndex), (yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(COMP_STM, NO_LINE_NUMBER, 4, children, INVALID_NODE_INDEX);}
#line 1440 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 34: /* StmtList: Stmt StmtList  */
#line 153 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[2] = {(yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(STMT_LIST, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
#line 1446 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 35: /* StmtList: %empty  */
#line 154 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {(yyval.nodeIndex) = newParserNode(STMT_LIST, NO_LINE_NUMBER, 0, NULL, INVALID_NODE_INDEX);}
#line 1452 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 36: /* Stmt: Exp SEMI  */
#line 158 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[2] = {(yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(STMT, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
#line 1458 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 37: /* Stmt: CompStm  */
#line 159 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(STMT, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1464 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 38: /* Stmt: RETURN Exp SEMI  */
#line 160 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(STMT, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1470 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 39: /* Stmt: IF LP Exp RP Stmt  */
#line 161 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[5] = {(yyvsp[-4].nodeIndex), (yyvsp[-3].nodeIndex), (yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(STMT, NO_LINE_NUMBER, 5, children, INVALID_NODE_INDEX);}
#line 1476 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 40: /* Stmt: IF LP Exp RP Stmt ELSE Stmt  */
#line 162 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[7] = {(yyvsp[-6].nodeIndex), (yyvsp[-5].nodeIndex), (yyvsp[-4].nodeIndex), (yyvsp[-3].nodeIndex), (yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(STMT, NO_LINE_NUMBER, 7, children, INVALID_NODE_INDEX);}
#line 1482 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 41: /* Stmt: WHILE LP Exp RP Stmt  */
#line 163 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[5] = {(yyvsp[-4].nodeIndex), (yyvsp[-3].nodeIndex), (yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(STMT, NO_LINE_NUMBER, 5, children, INVALID_NODE_INDEX);}
#line 1488 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 42: /* Stmt: error SEMI  */
#line 165 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {yyerrok; reportError(yylineno, UnexpectedStatement, "Unexpected Statement");}
#line 1494 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 43: /* DefList: Def DefList  */
#line 171 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[2] = {(yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(DEF_LIST, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
#line 1500 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 44: /* DefList: %empty  */
#line 172 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {(yyval.nodeIndex) = newParserNode(DEF_LIST, NO_LINE_NUMBER, 0, NULL, INVALID_NODE_INDEX);}
#line 1506 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 45: /* Def: Specifier DecList SEMI  */
#line 176 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(DEF, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1512 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 46: /* DecList: Dec  */
#line 180 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(DEC_LIST, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1518 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 47: /* DecList: Dec COMMA DecList  */
#line 181 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(DEC_LIST, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1524 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 48: /* Dec: VarDec  */
#line 185 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(DEC, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1530 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 49: /* Dec: VarDec ASSIGNOP Exp  */
#line 186 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(DEC, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1536 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 50: /* Exp: Exp ASSIGNOP Exp  */
#line 192 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1542 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 51: /* Exp: Exp AND Exp  */
#line 193 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1548 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 52: /* Exp: Exp OR Exp  */
#line 194 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1554 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 53: /* Exp: Exp EQ Exp  */
#line 195 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1560 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 54: /* Exp: Exp NEQ Exp  */
#line 196 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1566 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 55: /* Exp: Exp LT Exp  */
#line 197 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1572 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 56: /* Exp: Exp LE Exp  */
#line 198 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1578 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 57: /* Exp: Exp GT Exp  */
#line 199 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1584 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 58: /* Exp: Exp GE Exp  */
#line 200 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1590 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 59: /* Exp: Exp PLUS Exp  */
#line 201 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1596 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 60: /* Exp: Exp MINUS Exp  */
#line 202 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1602 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 61: /* Exp: Exp STAR Exp  */
#line 203 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1608 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 62: /* Exp: Exp DIV Exp  */
#line 204 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1614 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 63: /* Exp: LP Exp RP  */
#line 205 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1620 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 64: /* Exp: MINUS Exp  */
#line 206 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[2] = {(yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
#line 1626 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 65: /* Exp: NOT Exp  */
#line 207 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[2] = {(yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 2, children, INVALID_NODE_INDEX);}
#line 1632 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 66: /* Exp: ID LP Args RP  */
#line 208 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[4] = {(yyvsp[-3].nodeIndex), (yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 4, children, INVALID_NODE_INDEX);}
#line 1638 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 67: /* Exp: ID LP RP  */
#line 209 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1644 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 68: /* Exp: Exp LB Exp RB  */
#line 210 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[4] = {(yyvsp[-3].nodeIndex), (yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 4, children, INVALID_NODE_INDEX);}
#line 1650 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 69: /* Exp: Exp DOT ID  */
#line 211 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1656 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 70: /* Exp: ID  */
#line 212 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1662 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 71: /* Exp: INT  */
#line 213 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1668 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 72: /* Exp: FLOAT  */
#line 214 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(EXP, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1674 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 73: /* Exp: error Exp  */
#line 216 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {yyerrok; reportError(yylineno, UnexpectedExpression, "Unexpected Expression");}
#line 1680 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 74: /* Args: Exp COMMA Args  */
#line 220 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[3] = {(yyvsp[-2].nodeIndex), (yyvsp[-1].nodeIndex), (yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(ARGS, NO_LINE_NUMBER, 3, children, INVALID_NODE_INDEX);}
#line 1686 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;

  case 75: /* Args: Exp  */
#line 221 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
                                            {ParserNode_I children[1] = {(yyvsp[0].nodeIndex)}; (yyval.nodeIndex) = newParserNode(ARGS, NO_LINE_NUMBER, 1, children, INVALID_NODE_INDEX);}
#line 1692 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"
    break;


#line 1696 "/home/crystal/compilerPriciple/Lab1/CmakeBuild/CmmParser.c"

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

#line 224 "/home/crystal/compilerPriciple/Lab1/src/CmmParser.y"
