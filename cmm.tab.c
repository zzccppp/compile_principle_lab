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
#line 1 "cmm.y"

#include <stdio.h>
#include "ast.h"
#include "lex.yy.h"
#define YYERROR_VERBOSE 1
extern int synError;

int yyerror(char*);
void printErrorMsg(char type, int lineno, char* msg);
pASTNode root;

#line 83 "cmm.tab.c"

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

#include "cmm.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_INT = 4,                        /* INT  */
  YYSYMBOL_FLOAT = 5,                      /* FLOAT  */
  YYSYMBOL_STRING_LITERAL = 6,             /* STRING_LITERAL  */
  YYSYMBOL_SEMI = 7,                       /* SEMI  */
  YYSYMBOL_COMMA = 8,                      /* COMMA  */
  YYSYMBOL_ASSIGNOP = 9,                   /* ASSIGNOP  */
  YYSYMBOL_RELOP = 10,                     /* RELOP  */
  YYSYMBOL_PLUS = 11,                      /* PLUS  */
  YYSYMBOL_MINUS = 12,                     /* MINUS  */
  YYSYMBOL_STAR = 13,                      /* STAR  */
  YYSYMBOL_DIV = 14,                       /* DIV  */
  YYSYMBOL_AND = 15,                       /* AND  */
  YYSYMBOL_OR = 16,                        /* OR  */
  YYSYMBOL_DOT = 17,                       /* DOT  */
  YYSYMBOL_NOT = 18,                       /* NOT  */
  YYSYMBOL_TYPE = 19,                      /* TYPE  */
  YYSYMBOL_LP = 20,                        /* LP  */
  YYSYMBOL_RP = 21,                        /* RP  */
  YYSYMBOL_LB = 22,                        /* LB  */
  YYSYMBOL_RB = 23,                        /* RB  */
  YYSYMBOL_LC = 24,                        /* LC  */
  YYSYMBOL_RC = 25,                        /* RC  */
  YYSYMBOL_STRUCT = 26,                    /* STRUCT  */
  YYSYMBOL_RETURN = 27,                    /* RETURN  */
  YYSYMBOL_IF = 28,                        /* IF  */
  YYSYMBOL_ELSE = 29,                      /* ELSE  */
  YYSYMBOL_WHILE = 30,                     /* WHILE  */
  YYSYMBOL_LOWER_THAN_ELSE = 31,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 32,                  /* $accept  */
  YYSYMBOL_Program = 33,                   /* Program  */
  YYSYMBOL_ExtDefList = 34,                /* ExtDefList  */
  YYSYMBOL_ExtDef = 35,                    /* ExtDef  */
  YYSYMBOL_ExtDecList = 36,                /* ExtDecList  */
  YYSYMBOL_Specifier = 37,                 /* Specifier  */
  YYSYMBOL_StructSpecifier = 38,           /* StructSpecifier  */
  YYSYMBOL_OptTag = 39,                    /* OptTag  */
  YYSYMBOL_Tag = 40,                       /* Tag  */
  YYSYMBOL_VarDec = 41,                    /* VarDec  */
  YYSYMBOL_FunDec = 42,                    /* FunDec  */
  YYSYMBOL_VarList = 43,                   /* VarList  */
  YYSYMBOL_ParamDec = 44,                  /* ParamDec  */
  YYSYMBOL_CompSt = 45,                    /* CompSt  */
  YYSYMBOL_StmtList = 46,                  /* StmtList  */
  YYSYMBOL_Stmt = 47,                      /* Stmt  */
  YYSYMBOL_DefList = 48,                   /* DefList  */
  YYSYMBOL_Def = 49,                       /* Def  */
  YYSYMBOL_DecList = 50,                   /* DecList  */
  YYSYMBOL_Dec = 51,                       /* Dec  */
  YYSYMBOL_PrimaryExp = 52,                /* PrimaryExp  */
  YYSYMBOL_PostfixExp = 53,                /* PostfixExp  */
  YYSYMBOL_UnaryExp = 54,                  /* UnaryExp  */
  YYSYMBOL_UnaryOp = 55,                   /* UnaryOp  */
  YYSYMBOL_MultiplicativeExp = 56,         /* MultiplicativeExp  */
  YYSYMBOL_AdditiveExp = 57,               /* AdditiveExp  */
  YYSYMBOL_RelationalExp = 58,             /* RelationalExp  */
  YYSYMBOL_AndExp = 59,                    /* AndExp  */
  YYSYMBOL_OrExp = 60,                     /* OrExp  */
  YYSYMBOL_AssignmentExp = 61,             /* AssignmentExp  */
  YYSYMBOL_Exp = 62,                       /* Exp  */
  YYSYMBOL_Args = 63                       /* Args  */
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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   142

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  130

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   286


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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    39,    39,    43,    44,    48,    49,    50,    51,    52,
      56,    57,    61,    62,    66,    67,    70,    71,    74,    77,
      78,    82,    83,    87,    88,    92,    96,   100,   101,   104,
     105,   106,   107,   108,   109,   110,   115,   116,   119,   120,
     123,   124,   127,   128,   153,   154,   155,   156,   157,   162,
     163,   164,   165,   166,   167,   172,   173,   178,   180,   185,
     186,   187,   192,   193,   194,   199,   200,   205,   206,   211,
     212,   218,   219,   224,   225,   229,   230
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
  "\"end of file\"", "error", "\"invalid token\"", "ID", "INT", "FLOAT",
  "STRING_LITERAL", "SEMI", "COMMA", "ASSIGNOP", "RELOP", "PLUS", "MINUS",
  "STAR", "DIV", "AND", "OR", "DOT", "NOT", "TYPE", "LP", "RP", "LB", "RB",
  "LC", "RC", "STRUCT", "RETURN", "IF", "ELSE", "WHILE", "LOWER_THAN_ELSE",
  "$accept", "Program", "ExtDefList", "ExtDef", "ExtDecList", "Specifier",
  "StructSpecifier", "OptTag", "Tag", "VarDec", "FunDec", "VarList",
  "ParamDec", "CompSt", "StmtList", "Stmt", "DefList", "Def", "DecList",
  "Dec", "PrimaryExp", "PostfixExp", "UnaryExp", "UnaryOp",
  "MultiplicativeExp", "AdditiveExp", "RelationalExp", "AndExp", "OrExp",
  "AssignmentExp", "Exp", "Args", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-72)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-18)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      79,   -72,    16,    24,   -72,    79,    51,   -72,    11,    20,
     -72,   -72,   -72,   -72,    52,   -72,    67,    -2,     3,    79,
      73,   -72,   104,   106,   -72,    79,   -72,   104,    92,    79,
     -72,   104,    97,   111,   -72,   -72,    98,    33,    37,    96,
     112,   -72,   -72,   100,   -72,    79,   -72,   -72,   -72,   -72,
     -72,   -72,   -72,    84,    84,   103,   105,   -72,    99,    33,
     -72,     1,   -72,    84,    -5,   102,   116,   113,   114,   -72,
      48,    84,   -72,   -72,   104,   -72,     4,    93,    84,    84,
     -72,   -72,    84,   124,    65,    61,    89,   -72,    84,    84,
      84,    84,    84,    84,    84,   -72,   -72,    84,   -72,   -72,
     -72,   -72,    70,    72,   -72,   -72,   -72,   -72,    74,   108,
     109,   -72,   -72,    -5,    -5,   102,   116,   113,   -72,    33,
      33,    84,   -72,   -72,   -72,   107,   -72,   -72,    33,   -72
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,    12,    16,     0,     2,     3,     0,    13,    18,     0,
      15,     1,     4,     9,    19,     6,     0,    10,     0,    36,
       0,     5,     0,     0,     8,    36,     7,     0,     0,    36,
      22,     0,     0,    24,    19,    11,     0,    27,    42,     0,
      40,    14,    37,    25,    21,     0,    20,    44,    45,    46,
      47,    57,    58,     0,     0,     0,     0,    30,     0,    27,
      49,    55,    59,     0,    62,    65,    67,    69,    71,    73,
       0,     0,    39,    38,     0,    23,     0,     0,     0,     0,
      26,    28,     0,     0,     0,     0,    55,    56,     0,     0,
       0,     0,     0,     0,     0,    35,    29,     0,    43,    41,
      48,    31,     0,     0,    72,    52,    51,    75,     0,     0,
       0,    60,    61,    63,    64,    66,    68,    70,    74,     0,
       0,     0,    53,    54,    50,    32,    34,    76,     0,    33
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -72,   -72,   128,   -72,   115,     2,   -72,   -72,   -72,   -26,
     -72,    90,   -72,   120,    75,   -44,    83,   -72,    55,   -72,
     -72,   -60,   -46,   -72,    25,    47,    49,    46,   -72,   -71,
     -38,   -72
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,    16,    27,     7,     9,    10,    17,
      18,    32,    33,    57,    58,    59,    28,    29,    39,    40,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,   108
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      98,    38,     6,    86,    24,    43,    22,     6,    88,    89,
      82,   104,    97,   107,   110,    76,    77,    87,    83,     8,
      23,    84,    31,    85,    11,   100,   118,    25,    86,    86,
      86,    86,    86,    86,    86,   -17,    47,    48,    49,    50,
     102,   103,   111,   112,    19,    51,    71,    31,    38,    95,
     127,    52,    13,    53,    14,    96,    97,    25,    15,    23,
      54,    55,   109,    56,    47,    48,    49,    50,    47,    48,
      49,    50,    20,    51,    21,   125,   126,    51,    97,    52,
      97,    53,   121,    52,   129,    53,   106,    47,    48,    49,
      50,   119,     1,   120,    30,   122,    51,    72,     1,     2,
     101,    97,    52,    73,    53,     2,    83,    34,    37,    84,
      36,    85,    42,    90,    91,   113,   114,    41,    44,    45,
      74,    46,    23,    78,    80,    79,    92,   105,    93,    99,
      94,   123,   124,    12,    81,    75,   128,    35,    26,   115,
     117,     0,   116
};

static const yytype_int16 yycheck[] =
{
      71,    27,     0,    63,     1,    31,     8,     5,    13,    14,
       9,    82,     8,    84,    85,    53,    54,    63,    17,     3,
      22,    20,    20,    22,     0,    21,    97,    24,    88,    89,
      90,    91,    92,    93,    94,    24,     3,     4,     5,     6,
      78,    79,    88,    89,    24,    12,     9,    45,    74,     1,
     121,    18,     1,    20,     3,     7,     8,    24,     7,    22,
      27,    28,     1,    30,     3,     4,     5,     6,     3,     4,
       5,     6,    20,    12,     7,   119,   120,    12,     8,    18,
       8,    20,     8,    18,   128,    20,    21,     3,     4,     5,
       6,    21,    19,    21,    21,    21,    12,     1,    19,    26,
       7,     8,    18,     7,    20,    26,    17,     3,    25,    20,
       4,    22,    29,    11,    12,    90,    91,    25,    21,     8,
       8,    23,    22,    20,    25,    20,    10,     3,    15,    74,
      16,    23,    23,     5,    59,    45,    29,    22,    18,    92,
      94,    -1,    93
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    19,    26,    33,    34,    35,    37,    38,     3,    39,
      40,     0,    34,     1,     3,     7,    36,    41,    42,    24,
      20,     7,     8,    22,     1,    24,    45,    37,    48,    49,
      21,    37,    43,    44,     3,    36,     4,    48,    41,    50,
      51,    25,    48,    41,    21,     8,    23,     3,     4,     5,
       6,    12,    18,    20,    27,    28,    30,    45,    46,    47,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,     9,     1,     7,     8,    43,    62,    62,    20,    20,
      25,    46,     9,    17,    20,    22,    53,    54,    13,    14,
      11,    12,    10,    15,    16,     1,     7,     8,    61,    50,
      21,     7,    62,    62,    61,     3,    21,    61,    63,     1,
      61,    54,    54,    56,    56,    57,    58,    59,    61,    21,
      21,     8,    21,    23,    23,    47,    47,    61,    29,    47
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    35,    35,    35,
      36,    36,    37,    37,    38,    38,    39,    39,    40,    41,
      41,    42,    42,    43,    43,    44,    45,    46,    46,    47,
      47,    47,    47,    47,    47,    47,    48,    48,    49,    49,
      50,    50,    51,    51,    52,    52,    52,    52,    52,    53,
      53,    53,    53,    53,    53,    54,    54,    55,    55,    56,
      56,    56,    57,    57,    57,    58,    58,    59,    59,    60,
      60,    61,    61,    62,    62,    63,    63
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     2,     3,     3,     2,
       1,     3,     1,     1,     5,     2,     0,     1,     1,     1,
       4,     4,     3,     3,     1,     2,     4,     0,     2,     2,
       1,     3,     5,     7,     5,     2,     0,     2,     3,     3,
       1,     3,     1,     3,     1,     1,     1,     1,     3,     1,
       4,     3,     3,     4,     4,     1,     2,     1,     1,     1,
       3,     3,     1,     3,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3
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

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Program: ExtDefList  */
#line 39 "cmm.y"
                  { (yyval.node) = newInternalNode((yyloc).first_line, "Program", 1, (yyvsp[0].node)); root = (yyval.node); }
#line 1337 "cmm.tab.c"
    break;

  case 3: /* ExtDefList: %empty  */
#line 43 "cmm.y"
                 { (yyval.node) = 0; }
#line 1343 "cmm.tab.c"
    break;

  case 4: /* ExtDefList: ExtDef ExtDefList  */
#line 44 "cmm.y"
                              { (yyval.node) = newInternalNode((yyloc).first_line, "ExtDefList", 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1349 "cmm.tab.c"
    break;

  case 5: /* ExtDef: Specifier ExtDecList SEMI  */
#line 48 "cmm.y"
                                { (yyval.node) = newInternalNode((yyloc).first_line, "ExtDef", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1355 "cmm.tab.c"
    break;

  case 6: /* ExtDef: Specifier SEMI  */
#line 49 "cmm.y"
                        { (yyval.node) = newInternalNode((yyloc).first_line, "ExtDef", 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1361 "cmm.tab.c"
    break;

  case 7: /* ExtDef: Specifier FunDec CompSt  */
#line 50 "cmm.y"
                                 { (yyval.node) = newInternalNode((yyloc).first_line, "ExtDef", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1367 "cmm.tab.c"
    break;

  case 8: /* ExtDef: Specifier FunDec error  */
#line 51 "cmm.y"
                               { }
#line 1373 "cmm.tab.c"
    break;

  case 9: /* ExtDef: Specifier error  */
#line 52 "cmm.y"
                        { synError = 1; printErrorMsg('B', (yylsp[0]).first_line, "missing ; (in Specifier)"); }
#line 1379 "cmm.tab.c"
    break;

  case 10: /* ExtDecList: VarDec  */
#line 56 "cmm.y"
                  { (yyval.node) = newInternalNode((yyloc).first_line, "ExtDecList", 1, (yyvsp[0].node)); }
#line 1385 "cmm.tab.c"
    break;

  case 11: /* ExtDecList: VarDec COMMA ExtDecList  */
#line 57 "cmm.y"
                                     { (yyval.node) = newInternalNode((yyloc).first_line, "ExtDecList", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1391 "cmm.tab.c"
    break;

  case 12: /* Specifier: TYPE  */
#line 61 "cmm.y"
               { (yyval.node) = newInternalNode((yyloc).first_line, "Specifier", 1, (yyvsp[0].node)); }
#line 1397 "cmm.tab.c"
    break;

  case 13: /* Specifier: StructSpecifier  */
#line 62 "cmm.y"
                            { (yyval.node) = newInternalNode((yyloc).first_line, "Specifier", 1, (yyvsp[0].node)); }
#line 1403 "cmm.tab.c"
    break;

  case 14: /* StructSpecifier: STRUCT OptTag LC DefList RC  */
#line 66 "cmm.y"
                                            { (yyval.node) = newInternalNode((yyloc).first_line, "StructSpecifier", 5, (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1409 "cmm.tab.c"
    break;

  case 15: /* StructSpecifier: STRUCT Tag  */
#line 67 "cmm.y"
                             { (yyval.node) = newInternalNode((yyloc).first_line, "StructSpecifier", 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1415 "cmm.tab.c"
    break;

  case 16: /* OptTag: %empty  */
#line 70 "cmm.y"
               { (yyval.node) = 0; }
#line 1421 "cmm.tab.c"
    break;

  case 17: /* OptTag: ID  */
#line 71 "cmm.y"
            { (yyval.node) = newInternalNode((yyloc).first_line, "OptTag", 1, (yyvsp[0].node)); }
#line 1427 "cmm.tab.c"
    break;

  case 18: /* Tag: ID  */
#line 74 "cmm.y"
         { (yyval.node) = newInternalNode((yyloc).first_line, "Tag", 1, (yyvsp[0].node)); }
#line 1433 "cmm.tab.c"
    break;

  case 19: /* VarDec: ID  */
#line 77 "cmm.y"
            { (yyval.node) = newInternalNode((yyloc).first_line, "VarDec", 1, (yyvsp[0].node)); }
#line 1439 "cmm.tab.c"
    break;

  case 20: /* VarDec: VarDec LB INT RB  */
#line 78 "cmm.y"
                          { (yyval.node) = newInternalNode((yyloc).first_line, "VarDec", 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1445 "cmm.tab.c"
    break;

  case 21: /* FunDec: ID LP VarList RP  */
#line 82 "cmm.y"
                         { (yyval.node) = newInternalNode((yyloc).first_line, "FunDec", 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1451 "cmm.tab.c"
    break;

  case 22: /* FunDec: ID LP RP  */
#line 83 "cmm.y"
                 { (yyval.node) = newInternalNode((yyloc).first_line, "FunDec", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1457 "cmm.tab.c"
    break;

  case 23: /* VarList: ParamDec COMMA VarList  */
#line 87 "cmm.y"
                               { (yyval.node) = newInternalNode((yyloc).first_line, "VarList", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1463 "cmm.tab.c"
    break;

  case 24: /* VarList: ParamDec  */
#line 88 "cmm.y"
                   { (yyval.node) = newInternalNode((yyloc).first_line, "VarList", 1, (yyvsp[0].node)); }
#line 1469 "cmm.tab.c"
    break;

  case 25: /* ParamDec: Specifier VarDec  */
#line 92 "cmm.y"
                          { (yyval.node) = newInternalNode((yyloc).first_line, "ParamDec", 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1475 "cmm.tab.c"
    break;

  case 26: /* CompSt: LC DefList StmtList RC  */
#line 96 "cmm.y"
                              { (yyval.node) = newInternalNode((yyloc).first_line, "CompSt", 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1481 "cmm.tab.c"
    break;

  case 27: /* StmtList: %empty  */
#line 100 "cmm.y"
               { (yyval.node) = 0; }
#line 1487 "cmm.tab.c"
    break;

  case 28: /* StmtList: Stmt StmtList  */
#line 101 "cmm.y"
                         { (yyval.node) = newInternalNode((yyloc).first_line, "StmtList", 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1493 "cmm.tab.c"
    break;

  case 29: /* Stmt: Exp SEMI  */
#line 104 "cmm.y"
                { (yyval.node) = newInternalNode((yyloc).first_line, "Stmt", 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1499 "cmm.tab.c"
    break;

  case 30: /* Stmt: CompSt  */
#line 105 "cmm.y"
              { (yyval.node) = newInternalNode((yyloc).first_line, "Stmt", 1, (yyvsp[0].node)); }
#line 1505 "cmm.tab.c"
    break;

  case 31: /* Stmt: RETURN Exp SEMI  */
#line 106 "cmm.y"
                       { (yyval.node) = newInternalNode((yyloc).first_line, "Stmt", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1511 "cmm.tab.c"
    break;

  case 32: /* Stmt: IF LP Exp RP Stmt  */
#line 107 "cmm.y"
                                               { (yyval.node) = newInternalNode((yyloc).first_line, "Stmt", 5, (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1517 "cmm.tab.c"
    break;

  case 33: /* Stmt: IF LP Exp RP Stmt ELSE Stmt  */
#line 108 "cmm.y"
                                   { (yyval.node) = newInternalNode((yyloc).first_line, "Stmt", 6, (yyvsp[-6].node), (yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node)); }
#line 1523 "cmm.tab.c"
    break;

  case 34: /* Stmt: WHILE LP Exp RP Stmt  */
#line 109 "cmm.y"
                            { (yyval.node) = newInternalNode((yyloc).first_line, "Stmt", 5, (yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1529 "cmm.tab.c"
    break;

  case 35: /* Stmt: Exp error  */
#line 110 "cmm.y"
                { synError = 1; printErrorMsg('B', (yylsp[0]).first_line, "missing ; (in Exp)"); }
#line 1535 "cmm.tab.c"
    break;

  case 36: /* DefList: %empty  */
#line 115 "cmm.y"
              { (yyval.node) = 0; }
#line 1541 "cmm.tab.c"
    break;

  case 37: /* DefList: Def DefList  */
#line 116 "cmm.y"
                      { (yyval.node) = newInternalNode((yyloc).first_line, "DefList", 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1547 "cmm.tab.c"
    break;

  case 38: /* Def: Specifier DecList SEMI  */
#line 119 "cmm.y"
                             { (yyval.node) = newInternalNode((yyloc).first_line, "Def", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1553 "cmm.tab.c"
    break;

  case 39: /* Def: Specifier DecList error  */
#line 120 "cmm.y"
                              { synError = 1; printErrorMsg('B', (yylsp[0]).first_line, "missing ; (in Def)"); }
#line 1559 "cmm.tab.c"
    break;

  case 40: /* DecList: Dec  */
#line 123 "cmm.y"
              { (yyval.node) = newInternalNode((yyloc).first_line, "DecList", 1, (yyvsp[0].node)); }
#line 1565 "cmm.tab.c"
    break;

  case 41: /* DecList: Dec COMMA DecList  */
#line 124 "cmm.y"
                            { (yyval.node) = newInternalNode((yyloc).first_line, "DecList", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1571 "cmm.tab.c"
    break;

  case 42: /* Dec: VarDec  */
#line 127 "cmm.y"
             { (yyval.node) = newInternalNode((yyloc).first_line, "Dec", 1, (yyvsp[0].node)); }
#line 1577 "cmm.tab.c"
    break;

  case 43: /* Dec: VarDec ASSIGNOP AssignmentExp  */
#line 128 "cmm.y"
                                    { (yyval.node) = newInternalNode((yyloc).first_line, "Dec", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1583 "cmm.tab.c"
    break;

  case 44: /* PrimaryExp: ID  */
#line 153 "cmm.y"
               { (yyval.node) = newInternalNode((yyloc).first_line, "Exp", 1, (yyvsp[0].node)); }
#line 1589 "cmm.tab.c"
    break;

  case 45: /* PrimaryExp: INT  */
#line 154 "cmm.y"
                 { (yyval.node) = newInternalNode((yyloc).first_line, "Exp", 1, (yyvsp[0].node)); }
#line 1595 "cmm.tab.c"
    break;

  case 46: /* PrimaryExp: FLOAT  */
#line 155 "cmm.y"
                   { (yyval.node) = newInternalNode((yyloc).first_line, "Exp", 1, (yyvsp[0].node)); }
#line 1601 "cmm.tab.c"
    break;

  case 47: /* PrimaryExp: STRING_LITERAL  */
#line 156 "cmm.y"
                            { (yyval.node) = newInternalNode((yyloc).first_line, "Exp", 1, (yyvsp[0].node)); }
#line 1607 "cmm.tab.c"
    break;

  case 48: /* PrimaryExp: LP Exp RP  */
#line 157 "cmm.y"
                        { (yyval.node) = newInternalNode((yyloc).first_line, "Exp", 3, (yyvsp[-2].node)); }
#line 1613 "cmm.tab.c"
    break;

  case 49: /* PostfixExp: PrimaryExp  */
#line 162 "cmm.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1619 "cmm.tab.c"
    break;

  case 50: /* PostfixExp: PostfixExp LB AssignmentExp RB  */
#line 163 "cmm.y"
                                            { (yyval.node) = newInternalNode((yyloc).first_line, "Exp", 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1625 "cmm.tab.c"
    break;

  case 51: /* PostfixExp: PostfixExp LP RP  */
#line 164 "cmm.y"
                              { (yyval.node) = newInternalNode((yyloc).first_line, "Exp", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1631 "cmm.tab.c"
    break;

  case 52: /* PostfixExp: PostfixExp DOT ID  */
#line 165 "cmm.y"
                                { (yyval.node) = newInternalNode((yyloc).first_line, "Exp", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1637 "cmm.tab.c"
    break;

  case 53: /* PostfixExp: PostfixExp LP Args RP  */
#line 166 "cmm.y"
                                   { (yyval.node) = newInternalNode((yyloc).first_line, "Exp", 4, (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1643 "cmm.tab.c"
    break;

  case 54: /* PostfixExp: PostfixExp LB error RB  */
#line 167 "cmm.y"
                                   { synError = 1; printErrorMsg('B', (yylsp[-1]).first_line, "error in []");}
#line 1649 "cmm.tab.c"
    break;

  case 55: /* UnaryExp: PostfixExp  */
#line 172 "cmm.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1655 "cmm.tab.c"
    break;

  case 56: /* UnaryExp: UnaryOp UnaryExp  */
#line 173 "cmm.y"
                            { (yyval.node) = newInternalNode((yyloc).first_line, "Exp", 2, (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1661 "cmm.tab.c"
    break;

  case 57: /* UnaryOp: MINUS  */
#line 178 "cmm.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1667 "cmm.tab.c"
    break;

  case 58: /* UnaryOp: NOT  */
#line 180 "cmm.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1673 "cmm.tab.c"
    break;

  case 59: /* MultiplicativeExp: UnaryExp  */
#line 185 "cmm.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1679 "cmm.tab.c"
    break;

  case 60: /* MultiplicativeExp: MultiplicativeExp STAR UnaryExp  */
#line 186 "cmm.y"
                                                    { (yyval.node) = newInternalNode((yyloc).first_line, "Exp", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1685 "cmm.tab.c"
    break;

  case 61: /* MultiplicativeExp: MultiplicativeExp DIV UnaryExp  */
#line 187 "cmm.y"
                                                   { (yyval.node) = newInternalNode((yyloc).first_line, "Exp", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1691 "cmm.tab.c"
    break;

  case 62: /* AdditiveExp: MultiplicativeExp  */
#line 192 "cmm.y"
                              { (yyval.node) = (yyvsp[0].node); }
#line 1697 "cmm.tab.c"
    break;

  case 63: /* AdditiveExp: AdditiveExp PLUS MultiplicativeExp  */
#line 193 "cmm.y"
                                                 { (yyval.node) = newInternalNode((yyloc).first_line, "Exp", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1703 "cmm.tab.c"
    break;

  case 64: /* AdditiveExp: AdditiveExp MINUS MultiplicativeExp  */
#line 194 "cmm.y"
                                                  { (yyval.node) = newInternalNode((yyloc).first_line, "Exp", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1709 "cmm.tab.c"
    break;

  case 65: /* RelationalExp: AdditiveExp  */
#line 199 "cmm.y"
                          { (yyval.node) = (yyvsp[0].node); }
#line 1715 "cmm.tab.c"
    break;

  case 66: /* RelationalExp: RelationalExp RELOP AdditiveExp  */
#line 200 "cmm.y"
                                                { (yyval.node) = newInternalNode((yyloc).first_line, "Exp", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1721 "cmm.tab.c"
    break;

  case 67: /* AndExp: RelationalExp  */
#line 205 "cmm.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 1727 "cmm.tab.c"
    break;

  case 68: /* AndExp: AndExp AND RelationalExp  */
#line 206 "cmm.y"
                                  { (yyval.node) = newInternalNode((yyloc).first_line, "Exp", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1733 "cmm.tab.c"
    break;

  case 69: /* OrExp: AndExp  */
#line 211 "cmm.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 1739 "cmm.tab.c"
    break;

  case 70: /* OrExp: OrExp OR AndExp  */
#line 212 "cmm.y"
                        { (yyval.node) = newInternalNode((yyloc).first_line, "Exp", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1745 "cmm.tab.c"
    break;

  case 71: /* AssignmentExp: OrExp  */
#line 218 "cmm.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1751 "cmm.tab.c"
    break;

  case 72: /* AssignmentExp: PostfixExp ASSIGNOP AssignmentExp  */
#line 219 "cmm.y"
                                                  { (yyval.node) = newInternalNode((yyloc).first_line, "Exp", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1757 "cmm.tab.c"
    break;

  case 73: /* Exp: AssignmentExp  */
#line 224 "cmm.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1763 "cmm.tab.c"
    break;

  case 74: /* Exp: Exp COMMA AssignmentExp  */
#line 225 "cmm.y"
                              { (yyval.node) = newInternalNode((yyloc).first_line, "Exp", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1769 "cmm.tab.c"
    break;

  case 75: /* Args: AssignmentExp  */
#line 229 "cmm.y"
                   { (yyval.node) = newInternalNode((yyloc).first_line, "Args", 1, (yyvsp[0].node)); }
#line 1775 "cmm.tab.c"
    break;

  case 76: /* Args: Args COMMA AssignmentExp  */
#line 230 "cmm.y"
                                { (yyval.node) = newInternalNode((yyloc).first_line, "Args", 3, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node)); }
#line 1781 "cmm.tab.c"
    break;


#line 1785 "cmm.tab.c"

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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 233 "cmm.y"


int yyerror(char *s) {
  synError = 1;
  fprintf(stderr, "Error type B at line %d: %s.\n", yylineno, s);
  return 0;
}

void printErrorMsg(char type, int lineno, char* msg) {
  fprintf(stderr, "Error type %c at line %d: %s.\n", type,lineno,msg);
}
