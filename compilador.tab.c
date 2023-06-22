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
#line 6 "compilador.y"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"
#include "pilha.h"
#include "tabelaDeSimbolos.h"

int num_vars;
int num_bloco_vars;
PILHA TS;
SIMBOLO *simb;
SIMBOLO *l_elem;
char comando[30];
int nivel_lexico;
int desloc;
PILHA *l_elem_pilha;
PILHA *E, *T, *F;
PILHA *operacoes;
PILHA *rotulos;
PILHA *pilha_num_vars;
int num_params;
char erro[200];
char ident[30];
TIPOS tipo_aux;
SIMBOLO *proc = NULL;


#line 101 "compilador.tab.c"

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

#include "compilador.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAM = 3,                    /* PROGRAM  */
  YYSYMBOL_ABRE_PARENTESES = 4,            /* ABRE_PARENTESES  */
  YYSYMBOL_FECHA_PARENTESES = 5,           /* FECHA_PARENTESES  */
  YYSYMBOL_VIRGULA = 6,                    /* VIRGULA  */
  YYSYMBOL_PONTO_E_VIRGULA = 7,            /* PONTO_E_VIRGULA  */
  YYSYMBOL_DOIS_PONTOS = 8,                /* DOIS_PONTOS  */
  YYSYMBOL_PONTO = 9,                      /* PONTO  */
  YYSYMBOL_T_BEGIN = 10,                   /* T_BEGIN  */
  YYSYMBOL_T_END = 11,                     /* T_END  */
  YYSYMBOL_VAR = 12,                       /* VAR  */
  YYSYMBOL_IDENT = 13,                     /* IDENT  */
  YYSYMBOL_NUMERO = 14,                    /* NUMERO  */
  YYSYMBOL_ATRIBUICAO = 15,                /* ATRIBUICAO  */
  YYSYMBOL_LABEL = 16,                     /* LABEL  */
  YYSYMBOL_INTEGER = 17,                   /* INTEGER  */
  YYSYMBOL_BOOLEAN = 18,                   /* BOOLEAN  */
  YYSYMBOL_ABRE_CHAVES = 19,               /* ABRE_CHAVES  */
  YYSYMBOL_FECHA_CHAVES = 20,              /* FECHA_CHAVES  */
  YYSYMBOL_ABRE_COLCHETES = 21,            /* ABRE_COLCHETES  */
  YYSYMBOL_FECHA_COLCHETES = 22,           /* FECHA_COLCHETES  */
  YYSYMBOL_ARRAY = 23,                     /* ARRAY  */
  YYSYMBOL_OF = 24,                        /* OF  */
  YYSYMBOL_PROCEDURE = 25,                 /* PROCEDURE  */
  YYSYMBOL_FUNCTION = 26,                  /* FUNCTION  */
  YYSYMBOL_GOTO = 27,                      /* GOTO  */
  YYSYMBOL_IF = 28,                        /* IF  */
  YYSYMBOL_THEN = 29,                      /* THEN  */
  YYSYMBOL_ELSE = 30,                      /* ELSE  */
  YYSYMBOL_WHILE = 31,                     /* WHILE  */
  YYSYMBOL_DO = 32,                        /* DO  */
  YYSYMBOL_OR = 33,                        /* OR  */
  YYSYMBOL_AND = 34,                       /* AND  */
  YYSYMBOL_DIV = 35,                       /* DIV  */
  YYSYMBOL_SOMA = 36,                      /* SOMA  */
  YYSYMBOL_SUBTRACAO = 37,                 /* SUBTRACAO  */
  YYSYMBOL_MULTIPLICACAO = 38,             /* MULTIPLICACAO  */
  YYSYMBOL_IGUAL = 39,                     /* IGUAL  */
  YYSYMBOL_DIFERENTE = 40,                 /* DIFERENTE  */
  YYSYMBOL_MENOR = 41,                     /* MENOR  */
  YYSYMBOL_MAIOR = 42,                     /* MAIOR  */
  YYSYMBOL_MENOR_IGUAL = 43,               /* MENOR_IGUAL  */
  YYSYMBOL_MAIOR_IGUAL = 44,               /* MAIOR_IGUAL  */
  YYSYMBOL_NOT = 45,                       /* NOT  */
  YYSYMBOL_READ = 46,                      /* READ  */
  YYSYMBOL_WRITE = 47,                     /* WRITE  */
  YYSYMBOL_FORWARD = 48,                   /* FORWARD  */
  YYSYMBOL_LOWER_THAN_ELSE = 49,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 50,                  /* $accept  */
  YYSYMBOL_programa = 51,                  /* programa  */
  YYSYMBOL_52_1 = 52,                      /* $@1  */
  YYSYMBOL_bloco = 53,                     /* bloco  */
  YYSYMBOL_54_2 = 54,                      /* $@2  */
  YYSYMBOL_55_3 = 55,                      /* $@3  */
  YYSYMBOL_56_4 = 56,                      /* $@4  */
  YYSYMBOL_parte_declara_vars = 57,        /* parte_declara_vars  */
  YYSYMBOL_58_5 = 58,                      /* $@5  */
  YYSYMBOL_declara_vars = 59,              /* declara_vars  */
  YYSYMBOL_declara_var = 60,               /* declara_var  */
  YYSYMBOL_61_6 = 61,                      /* $@6  */
  YYSYMBOL_62_7 = 62,                      /* $@7  */
  YYSYMBOL_tipo = 63,                      /* tipo  */
  YYSYMBOL_lista_id_var = 64,              /* lista_id_var  */
  YYSYMBOL_lista_idents = 65,              /* lista_idents  */
  YYSYMBOL_parte_declara_subrotinas = 66,  /* parte_declara_subrotinas  */
  YYSYMBOL_declara_proc = 67,              /* declara_proc  */
  YYSYMBOL_68_8 = 68,                      /* $@8  */
  YYSYMBOL_declara_proc_extra = 69,        /* declara_proc_extra  */
  YYSYMBOL_70_9 = 70,                      /* $@9  */
  YYSYMBOL_param_formais = 71,             /* param_formais  */
  YYSYMBOL_72_10 = 72,                     /* $@10  */
  YYSYMBOL_secao_param_formais = 73,       /* secao_param_formais  */
  YYSYMBOL_74_11 = 74,                     /* $@11  */
  YYSYMBOL_75_12 = 75,                     /* $@12  */
  YYSYMBOL_76_13 = 76,                     /* $@13  */
  YYSYMBOL_77_14 = 77,                     /* $@14  */
  YYSYMBOL_lista_id_param = 78,            /* lista_id_param  */
  YYSYMBOL_comando_composto = 79,          /* comando_composto  */
  YYSYMBOL_comandos = 80,                  /* comandos  */
  YYSYMBOL_comando = 81,                   /* comando  */
  YYSYMBOL_comando_sem_rotulo = 82,        /* comando_sem_rotulo  */
  YYSYMBOL_83_15 = 83,                     /* $@15  */
  YYSYMBOL_identificador = 84,             /* identificador  */
  YYSYMBOL_comando_atribuicao = 85,        /* comando_atribuicao  */
  YYSYMBOL_86_16 = 86,                     /* $@16  */
  YYSYMBOL_chama_proc = 87,                /* chama_proc  */
  YYSYMBOL_88_17 = 88,                     /* $@17  */
  YYSYMBOL_lista_expressoes = 89,          /* lista_expressoes  */
  YYSYMBOL_90_18 = 90,                     /* $@18  */
  YYSYMBOL_expressao = 91,                 /* expressao  */
  YYSYMBOL_relacao = 92,                   /* relacao  */
  YYSYMBOL_expressao_simples = 93,         /* expressao_simples  */
  YYSYMBOL_94_19 = 94,                     /* $@19  */
  YYSYMBOL_operacao = 95,                  /* operacao  */
  YYSYMBOL_sinal = 96,                     /* sinal  */
  YYSYMBOL_termo = 97,                     /* termo  */
  YYSYMBOL_fator = 98,                     /* fator  */
  YYSYMBOL_99_20 = 99,                     /* $@20  */
  YYSYMBOL_comando_condicional = 100,      /* comando_condicional  */
  YYSYMBOL_101_21 = 101,                   /* $@21  */
  YYSYMBOL_if_then = 102,                  /* if_then  */
  YYSYMBOL_103_22 = 103,                   /* $@22  */
  YYSYMBOL_cond_else = 104,                /* cond_else  */
  YYSYMBOL_105_23 = 105,                   /* $@23  */
  YYSYMBOL_comando_repetitivo = 106,       /* comando_repetitivo  */
  YYSYMBOL_107_24 = 107,                   /* $@24  */
  YYSYMBOL_108_25 = 108,                   /* $@25  */
  YYSYMBOL_variavel = 109,                 /* variavel  */
  YYSYMBOL_comando_read = 110,             /* comando_read  */
  YYSYMBOL_parametros_leitura = 111,       /* parametros_leitura  */
  YYSYMBOL_comando_write = 112,            /* comando_write  */
  YYSYMBOL_parametros_escrita = 113        /* parametros_escrita  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   132

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  64
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  167

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   304


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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    55,    55,    55,    68,    69,    80,    68,   104,   105,
     105,   108,   109,   113,   116,   113,   124,   127,   133,   141,
     150,   151,   155,   156,   162,   161,   181,   182,   182,   211,
     212,   212,   220,   221,   222,   223,   222,   238,   239,   238,
     255,   264,   276,   278,   279,   280,   284,   285,   290,   289,
     306,   307,   308,   309,   310,   314,   315,   320,   319,   370,
     383,   383,   414,   414,   415,   416,   420,   420,   445,   450,
     455,   460,   465,   470,   478,   502,   518,   518,   536,   537,
     541,   545,   549,   555,   559,   566,   580,   603,   602,   644,
     656,   670,   679,   679,   692,   691,   714,   713,   731,   741,
     748,   740,   770,   786,   790,   820,   853,   856,   860
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
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAM",
  "ABRE_PARENTESES", "FECHA_PARENTESES", "VIRGULA", "PONTO_E_VIRGULA",
  "DOIS_PONTOS", "PONTO", "T_BEGIN", "T_END", "VAR", "IDENT", "NUMERO",
  "ATRIBUICAO", "LABEL", "INTEGER", "BOOLEAN", "ABRE_CHAVES",
  "FECHA_CHAVES", "ABRE_COLCHETES", "FECHA_COLCHETES", "ARRAY", "OF",
  "PROCEDURE", "FUNCTION", "GOTO", "IF", "THEN", "ELSE", "WHILE", "DO",
  "OR", "AND", "DIV", "SOMA", "SUBTRACAO", "MULTIPLICACAO", "IGUAL",
  "DIFERENTE", "MENOR", "MAIOR", "MENOR_IGUAL", "MAIOR_IGUAL", "NOT",
  "READ", "WRITE", "FORWARD", "LOWER_THAN_ELSE", "$accept", "programa",
  "$@1", "bloco", "$@2", "$@3", "$@4", "parte_declara_vars", "$@5",
  "declara_vars", "declara_var", "$@6", "$@7", "tipo", "lista_id_var",
  "lista_idents", "parte_declara_subrotinas", "declara_proc", "$@8",
  "declara_proc_extra", "$@9", "param_formais", "$@10",
  "secao_param_formais", "$@11", "$@12", "$@13", "$@14", "lista_id_param",
  "comando_composto", "comandos", "comando", "comando_sem_rotulo", "$@15",
  "identificador", "comando_atribuicao", "$@16", "chama_proc", "$@17",
  "lista_expressoes", "$@18", "expressao", "relacao", "expressao_simples",
  "$@19", "operacao", "sinal", "termo", "fator", "$@20",
  "comando_condicional", "$@21", "if_then", "$@22", "cond_else", "$@23",
  "comando_repetitivo", "$@24", "$@25", "variavel", "comando_read",
  "parametros_leitura", "comando_write", "parametros_escrita", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-130)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-93)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -130,    24,    17,  -130,    -7,    34,    33,  -130,    25,    42,
      44,  -130,  -130,    57,    56,  -130,  -130,    58,  -130,  -130,
      47,    72,  -130,    74,    76,    78,  -130,  -130,  -130,    28,
    -130,    -2,  -130,    79,    59,    82,  -130,    85,  -130,    86,
      90,  -130,    84,    89,  -130,  -130,    69,  -130,  -130,  -130,
    -130,  -130,  -130,  -130,    91,    95,     6,    12,     3,   100,
       3,  -130,    -2,     3,    87,   107,    67,    20,  -130,  -130,
    -130,  -130,  -130,  -130,     3,  -130,  -130,  -130,  -130,     5,
      88,    68,  -130,    18,  -130,  -130,    73,  -130,    75,  -130,
    -130,  -130,  -130,  -130,   109,  -130,  -130,    20,   113,   110,
     106,     3,     3,   116,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,  -130,  -130,  -130,  -130,  -130,  -130,     3,     5,  -130,
       5,     5,  -130,   111,  -130,     3,    94,    12,  -130,   118,
    -130,  -130,   106,  -130,    29,    77,  -130,  -130,  -130,  -130,
      12,    18,    18,    18,  -130,  -130,  -130,    12,  -130,  -130,
      54,   114,    59,  -130,  -130,  -130,  -130,    59,  -130,  -130,
       3,  -130,    20,  -130,    20,  -130,  -130
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,    21,     0,     0,
       0,     4,    20,     0,     8,     3,     5,     0,    22,    13,
       6,    10,    12,     0,     0,     0,    23,    11,    19,     0,
      24,    43,     7,     0,     0,    29,    48,     0,    99,     0,
       0,    50,     0,    45,    47,    54,     0,    53,    51,    52,
      18,    16,    17,    14,     0,     0,    59,    92,     0,     0,
       0,    42,    43,     0,    98,     0,    27,    32,    60,    57,
      49,    55,    56,    46,     0,    87,    89,    83,    84,     0,
       0,    66,    76,    75,    85,   105,     0,   108,     0,    44,
      94,    96,    93,    15,     0,    25,     4,    32,     0,     0,
       0,    65,     0,     0,   102,    91,   100,    82,    81,    79,
      80,    68,    69,    70,    71,    72,    73,     0,     0,    78,
       0,     0,   103,     0,   106,     0,     0,    92,    26,     0,
      33,    31,     0,    41,     0,     0,    64,    58,    90,    88,
      92,    67,    74,    77,    86,   104,   107,    92,    97,    28,
       0,     0,     0,    61,    62,   101,    95,     0,    40,    38,
       0,    35,    32,    63,    32,    39,    36
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -130,  -130,  -130,    30,  -130,  -130,  -130,  -130,  -130,  -130,
     108,  -130,  -130,  -129,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,  -130,  -130,   -95,  -130,  -130,  -130,  -130,    -4,   105,
      70,  -130,   -56,  -130,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,   -60,  -130,    14,  -130,   -77,   -68,   -57,   -74,  -130,
    -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,  -130,  -130,  -130
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    13,    14,    18,    25,    16,    17,    21,
      22,    23,    65,    53,    29,     8,    20,    26,    35,    95,
      96,    54,    55,    98,    99,   164,   100,   162,   134,    41,
      42,    43,    44,    56,    70,    71,   102,    72,   101,   135,
     160,    80,   117,    81,   120,   121,    82,    83,    84,   104,
      45,    46,    64,   126,    92,   127,    47,    58,   140,   139,
      48,    86,    49,    88
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      87,    73,   130,    90,   118,   105,     5,    74,    31,    74,
      68,    36,    37,   119,   103,   119,    75,    76,    75,    76,
       4,    69,    31,   159,     3,    36,   -92,    97,   161,    38,
       9,    10,   -34,   -37,    33,   151,    34,   152,     6,    77,
      78,   136,   137,    38,    39,    40,     7,   144,    79,    11,
      79,   107,   108,   109,    77,    78,   110,    12,    39,    40,
     151,   142,   157,   143,   118,   146,    15,   165,    -9,   166,
      19,   148,    24,   119,   119,   119,    51,    52,   122,   123,
     124,   125,   153,   154,   155,   -13,   -30,    28,    31,    30,
      59,   156,    50,    57,    60,    61,    62,    63,    66,    67,
     163,   107,   108,   109,    77,    78,   110,   111,   112,   113,
     114,   115,   116,    85,    93,    94,   128,    91,   131,   133,
     106,   138,   132,   147,   145,   149,   129,   158,   150,    27,
      32,   141,    89
};

static const yytype_uint8 yycheck[] =
{
      60,    57,    97,    63,    81,    79,    13,     4,    10,     4,
       4,    13,    14,    81,    74,    83,    13,    14,    13,    14,
       3,    15,    10,   152,     0,    13,    28,     7,   157,    31,
       5,     6,    12,    13,     6,     6,     8,     8,     4,    36,
      37,   101,   102,    31,    46,    47,    13,   121,    45,     7,
      45,    33,    34,    35,    36,    37,    38,    13,    46,    47,
       6,   118,     8,   120,   141,   125,     9,   162,    12,   164,
      12,   127,    25,   141,   142,   143,    17,    18,     5,     6,
       5,     6,     5,     6,   140,    13,     4,    13,    10,    13,
       4,   147,    13,     8,     4,    11,     7,    28,     7,     4,
     160,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    13,     7,    48,     7,    30,     5,    13,
      32,     5,    12,    29,    13,     7,    96,    13,   132,    21,
      25,   117,    62
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    51,    52,     0,     3,    13,     4,    13,    65,     5,
       6,     7,    13,    53,    54,     9,    57,    58,    55,    12,
      66,    59,    60,    61,    25,    56,    67,    60,    13,    64,
      13,    10,    79,     6,     8,    68,    13,    14,    31,    46,
      47,    79,    80,    81,    82,   100,   101,   106,   110,   112,
      13,    17,    18,    63,    71,    72,    83,     8,   107,     4,
       4,    11,     7,    28,   102,    62,     7,     4,     4,    15,
      84,    85,    87,    82,     4,    13,    14,    36,    37,    45,
      91,    93,    96,    97,    98,    13,   111,    91,   113,    80,
      91,    30,   104,     7,    48,    69,    70,     7,    73,    74,
      76,    88,    86,    91,    99,    98,    32,    33,    34,    35,
      38,    39,    40,    41,    42,    43,    44,    92,    95,    96,
      94,    95,     5,     6,     5,     6,   103,   105,     7,    53,
      73,     5,    12,    13,    78,    89,    91,    91,     5,   109,
     108,    93,    97,    97,    98,    13,    91,    29,    82,     7,
      78,     6,     8,     5,     6,    82,    82,     8,    13,    63,
      90,    63,    77,    91,    75,    73,    73
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    52,    51,    54,    55,    56,    53,    57,    58,
      57,    59,    59,    61,    62,    60,    63,    63,    64,    64,
      65,    65,    66,    66,    68,    67,    69,    70,    69,    71,
      72,    71,    73,    73,    74,    75,    73,    76,    77,    73,
      78,    78,    79,    80,    80,    80,    81,    81,    83,    82,
      82,    82,    82,    82,    82,    84,    84,    86,    85,    87,
      88,    87,    90,    89,    89,    89,    91,    91,    92,    92,
      92,    92,    92,    92,    93,    93,    94,    93,    95,    95,
      95,    95,    95,    96,    96,    97,    97,    99,    98,    98,
      98,    98,   101,   100,   103,   102,   105,   104,   104,   107,
     108,   106,   109,   110,   111,   111,   112,   113,   113
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     9,     0,     0,     0,     6,     0,     0,
       3,     2,     1,     0,     0,     6,     1,     1,     3,     1,
       3,     1,     0,     2,     0,     6,     2,     0,     3,     0,
       0,     4,     0,     2,     0,     0,     7,     0,     0,     6,
       3,     1,     3,     0,     3,     1,     3,     1,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     3,     0,
       0,     4,     0,     4,     1,     0,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     1,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     3,     1,
       3,     2,     0,     3,     0,     5,     0,     3,     0,     0,
       0,     6,     0,     4,     3,     1,     4,     3,     1
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
  case 2: /* $@1: %empty  */
#line 55 "compilador.y"
             {
               nivel_lexico = 0;
               geraCodigo (NULL, "INPP");
             }
#line 1330 "compilador.tab.c"
    break;

  case 3: /* programa: $@1 PROGRAM IDENT ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA bloco PONTO  */
#line 61 "compilador.y"
                         {
               geraCodigo (NULL, "PARA");
             }
#line 1338 "compilador.tab.c"
    break;

  case 4: /* $@2: %empty  */
#line 68 "compilador.y"
        { num_bloco_vars = 0; }
#line 1344 "compilador.tab.c"
    break;

  case 5: /* $@3: %empty  */
#line 69 "compilador.y"
                            {
            empilha(pilha_num_vars, &num_bloco_vars);

            empilha(rotulos, prox_rotulo());

            // Gera DSVS com rotulo
            char *rotulo = buscaItem(rotulos, rotulos->tamanho -1);
            sprintf(comando, "DSVS %s", rotulo);
            geraCodigo(NULL, comando);
         }
#line 1359 "compilador.tab.c"
    break;

  case 6: /* $@4: %empty  */
#line 80 "compilador.y"
         {
            // Gera NADA com rotulo
            char *rotulo = desempilha(rotulos);
            geraCodigo(rotulo, "NADA");
            free(rotulo);
         }
#line 1370 "compilador.tab.c"
    break;

  case 7: /* bloco: $@2 parte_declara_vars $@3 parte_declara_subrotinas $@4 comando_composto  */
#line 86 "compilador.y"
                          {
            int *temp = desempilha(pilha_num_vars);
            num_bloco_vars = (*temp);

            imprimeTS(&TS, TS_TAM);    // ---------- comentar dps
            deletaPorNivelLexico(&TS, nivel_lexico+1);

            if (num_bloco_vars > 0) {
               elimina(&TS, num_bloco_vars);
               sprintf(comando, "DMEM %d", num_bloco_vars);
               geraCodigo(NULL, comando);
            }
         }
#line 1388 "compilador.tab.c"
    break;

  case 9: /* $@5: %empty  */
#line 105 "compilador.y"
              { desloc = 0; }
#line 1394 "compilador.tab.c"
    break;

  case 13: /* $@6: %empty  */
#line 113 "compilador.y"
              { num_vars = 0; }
#line 1400 "compilador.tab.c"
    break;

  case 14: /* $@7: %empty  */
#line 116 "compilador.y"
              { 
                  /* Aloca memória pras variáveis */
                  sprintf(comando, "AMEM %d", num_vars);
                  geraCodigo(NULL, comando);
              }
#line 1410 "compilador.tab.c"
    break;

  case 16: /* tipo: INTEGER  */
#line 124 "compilador.y"
                      {
                  atualizaTipoVar(&TS, inteiro, num_vars);
               }
#line 1418 "compilador.tab.c"
    break;

  case 17: /* tipo: BOOLEAN  */
#line 127 "compilador.y"
                      {
                  atualizaTipoVar(&TS, booleano, num_vars);
               }
#line 1426 "compilador.tab.c"
    break;

  case 18: /* lista_id_var: lista_id_var VIRGULA IDENT  */
#line 134 "compilador.y"
              {
                  /* insere ultima variavel na tabela de simbolos */ 
                  insere(&TS, token, var_simples, criaVarSimples(tipo_indefinido, desloc), nivel_lexico);
                  num_bloco_vars++;
                  num_vars++;
                  desloc++;
              }
#line 1438 "compilador.tab.c"
    break;

  case 19: /* lista_id_var: IDENT  */
#line 141 "compilador.y"
                    {
                  /* insere variveis na tabela de simbolos */
                  insere(&TS, token, var_simples, criaVarSimples(tipo_indefinido, desloc), nivel_lexico);
                  num_bloco_vars++;
                  num_vars++;
                  desloc++;
               }
#line 1450 "compilador.tab.c"
    break;

  case 24: /* $@8: %empty  */
#line 162 "compilador.y"
            {
               char *rotulo;

               nivel_lexico++;

               // Adiciona procedimento à tabela de simbolos
               if (buscaSimbolo(&TS, token) == -1) {
                  empilha(rotulos, prox_rotulo());
                  rotulo = buscaItem(rotulos, rotulos->tamanho - 1);
                  insere(&TS, token, procedimento,
                     criaAtrProcedimento(rotulo), nivel_lexico);
               }

            }
#line 1469 "compilador.tab.c"
    break;

  case 26: /* declara_proc_extra: FORWARD PONTO_E_VIRGULA  */
#line 181 "compilador.y"
                                            { nivel_lexico--; }
#line 1475 "compilador.tab.c"
    break;

  case 27: /* $@9: %empty  */
#line 182 "compilador.y"
              {
               char *rotulo;

               // Gera ENPR k com rotulo
               rotulo = buscaItem(rotulos, rotulos->tamanho - 1);
               sprintf(comando, "ENPR %d", nivel_lexico);
               geraCodigo(rotulo, comando);

            }
#line 1489 "compilador.tab.c"
    break;

  case 28: /* declara_proc_extra: $@9 bloco PONTO_E_VIRGULA  */
#line 191 "compilador.y"
            {
               char *rotulo;

               SIMBOLO *simb = retornaUltimo(&TS, procedimento);
               PROCEDIMENTO *proc = simb->atributos;

               // Gera RTPR
               sprintf(comando, "RTPR %d, %d", nivel_lexico, proc->num_params);
               geraCodigo(NULL, comando);

               elimina(&TS, proc->num_params);

               nivel_lexico--;

               rotulo = desempilha(rotulos);
               // free(rotulo);
            }
#line 1511 "compilador.tab.c"
    break;

  case 30: /* $@10: %empty  */
#line 212 "compilador.y"
               { desloc = 0; }
#line 1517 "compilador.tab.c"
    break;

  case 31: /* param_formais: $@10 ABRE_PARENTESES secao_param_formais FECHA_PARENTESES  */
#line 213 "compilador.y"
             {
               // atualiza deslocamento e adiciona parametros ao procedimento na tabela de simbolos
               atualizaDesloc(&TS, desloc);
             }
#line 1526 "compilador.tab.c"
    break;

  case 34: /* $@11: %empty  */
#line 222 "compilador.y"
                     {num_vars = 0;}
#line 1532 "compilador.tab.c"
    break;

  case 35: /* $@12: %empty  */
#line 223 "compilador.y"
                   {
                     switch (simbolo) {
                        case simb_integer:
                           atualizaTipoVar(&TS, inteiro, num_vars);
                           break;
                        case simb_boolean:
                           atualizaTipoVar(&TS, booleano, num_vars);
                           break;
                        default:
                           break;
                     }

                     atualizaTipoParametro(&TS, referencia, num_vars);
                   }
#line 1551 "compilador.tab.c"
    break;

  case 37: /* $@13: %empty  */
#line 238 "compilador.y"
                     {num_vars = 0;}
#line 1557 "compilador.tab.c"
    break;

  case 38: /* $@14: %empty  */
#line 239 "compilador.y"
                   {
                     switch (simbolo) {
                        case simb_integer:
                           atualizaTipoVar(&TS, inteiro, num_vars);
                           break;
                        case simb_boolean:
                           atualizaTipoVar(&TS, booleano, num_vars);
                           break;
                        default:
                           break;
                     }
                   }
#line 1574 "compilador.tab.c"
    break;

  case 40: /* lista_id_param: lista_id_param VIRGULA IDENT  */
#line 256 "compilador.y"
              {
                  // Adiciona à tabela de simbolos como indefinido
                  insere(&TS, token, param_formal,
                     criaParamFormal(tipo_indefinido, 0, valor), nivel_lexico);

                  num_vars++;
                  desloc++;
              }
#line 1587 "compilador.tab.c"
    break;

  case 41: /* lista_id_param: IDENT  */
#line 264 "compilador.y"
                    {
                  // Adiciona à tabela de simbolos como indefinido
                  insere(&TS, token, param_formal,
                     criaParamFormal(tipo_indefinido, 0, valor), nivel_lexico);

                  num_vars++;
                  desloc++;
               }
#line 1600 "compilador.tab.c"
    break;

  case 48: /* $@15: %empty  */
#line 290 "compilador.y"
                  {
                     SIMBOLO *simb;
                     int idx = buscaSimbolo(&TS, token);

                     if(idx == -1)
                        imprimeErro("Simbolo não existe");
                     
                     simb = buscaItem(&TS, idx);

                     if(!checaCategoria(simb))
                        imprimeErro("Símbolo não corresponde a variável simples, parâmetro formal, procedimento formal ou função");

                     /* armazena simbolo para posteriormente gerar ARMZ */
                     l_elem = simb;
                  }
#line 1620 "compilador.tab.c"
    break;

  case 57: /* $@16: %empty  */
#line 320 "compilador.y"
                  {
                     empilha(l_elem_pilha, l_elem->id);
                  }
#line 1628 "compilador.tab.c"
    break;

  case 58: /* comando_atribuicao: ATRIBUICAO $@16 expressao  */
#line 324 "compilador.y"
                  {
                     int idx = buscaSimbolo(&TS, desempilha(l_elem_pilha));
                     if(idx == -1)
                        imprimeErro("Simbolo não existe");

                     l_elem = buscaItem(&TS, idx);
                     TIPOS *t1 = desempilha(E);

                     VAR_SIMPLES *VS;
                     PARAM_FORMAL *PF;
                     FUNCAO *FUN;

                     if (l_elem->categoria == var_simples) {
                           VS = l_elem->atributos;
                           if(VS->tipo != (*t1))
                              imprimeErro("Tipos não correspondem");
                           sprintf(comando, "ARMZ %d,%d", l_elem->nivel_lex, VS->deslocamento);
                     }
                     else if (l_elem->categoria == param_formal){
                           PF = l_elem->atributos;
                           if (PF->tipo != (*t1))
                              imprimeErro("Tipos não correspondem");
                           
                           if (PF->parametro == valor)
                              sprintf(comando, "ARMZ %d,%d", l_elem->nivel_lex, PF->deslocamento);
                           else if (PF->parametro == referencia)
                              sprintf(comando, "ARMI %d,%d", l_elem->nivel_lex, PF->deslocamento);
                           else
                              imprimeErro("Tipo de passsagem de parâmetro inválido");
                     }
                     else if (l_elem->categoria == funcao) {
                        FUN = l_elem->atributos;
                        if(FUN->tipo != (*t1))
                           imprimeErro("Tipos não correspondem");
                        sprintf(comando, "ARMZ %d,%d", l_elem->nivel_lex, FUN->deslocamento);
                     }
                     else
                        imprimeErro("Categoria inválida");

                     geraCodigo(NULL, comando);
                     l_elem = NULL;
                  }
#line 1675 "compilador.tab.c"
    break;

  case 59: /* chama_proc: %empty  */
#line 370 "compilador.y"
          {
            if (l_elem->categoria != procedimento) {
               sprintf(erro, "Simbolo %s não procedimento", l_elem->id);
               imprimeErro(erro);
            }

            PROCEDIMENTO *atrProc = l_elem->atributos;

            sprintf(comando, "CHPR %s, %d", atrProc->rotulo, nivel_lexico);
            geraCodigo(NULL, comando);

            l_elem = NULL;
          }
#line 1693 "compilador.tab.c"
    break;

  case 60: /* $@17: %empty  */
#line 383 "compilador.y"
                            { proc = l_elem; num_params = 1; }
#line 1699 "compilador.tab.c"
    break;

  case 61: /* chama_proc: ABRE_PARENTESES $@17 lista_expressoes FECHA_PARENTESES  */
#line 384 "compilador.y"
          {
            if (l_elem->categoria != procedimento) {
               sprintf(erro, "Simbolo %s não procedimento", l_elem->id);
               imprimeErro(erro);
            }

            PROCEDIMENTO *atrProc = l_elem->atributos;

            TIPOS *tipo;
            PARAM_FORMAL *atrParam;
            for (int i = 0; i < atrProc->num_params; i++) {
               tipo = desempilha(E);
               atrParam = atrProc->parametros[i]->atributos;

               if ((*tipo) != atrParam->tipo) {
                  sprintf(erro, "Tipo incompatível - Esperava %s e recebeu %s", imprimeTipo(atrParam->tipo), imprimeTipo((*tipo)));
                  imprimeErro(erro);
               }
            }

            sprintf(comando, "CHPR %s, %d", atrProc->rotulo, nivel_lexico);
            geraCodigo(NULL, comando);

            l_elem = NULL;
            proc = NULL;
          }
#line 1730 "compilador.tab.c"
    break;

  case 62: /* $@18: %empty  */
#line 414 "compilador.y"
                                           { num_params++; }
#line 1736 "compilador.tab.c"
    break;

  case 67: /* expressao: expressao_simples relacao expressao_simples  */
#line 421 "compilador.y"
   {
      fprintf(stderr, "DEBUG - Regra E = E <> E\n");
      // E <> E
      TIPOS *t1, *t2;
      t1 = desempilha(E);
      t2 = desempilha(E);

      if((*t1) != (*t2))
         imprimeErro("Tipos não correspondem");

      (*t1) = booleano;
      empilha(E, t1);

      operacoes_t *op = desempilha(operacoes);
      sprintf(comando, "%s", opToString((*op)));
      geraCodigo(NULL, comando);

      // free(t1);
      // free(t2);
   }
#line 1761 "compilador.tab.c"
    break;

  case 68: /* relacao: IGUAL  */
#line 446 "compilador.y"
         {
            operacoes_t op = op_igual;
            empilha(operacoes, &op);
         }
#line 1770 "compilador.tab.c"
    break;

  case 69: /* relacao: DIFERENTE  */
#line 451 "compilador.y"
         {
            operacoes_t op = op_diferente;
            empilha(operacoes, &op);
         }
#line 1779 "compilador.tab.c"
    break;

  case 70: /* relacao: MENOR  */
#line 456 "compilador.y"
         {
            operacoes_t op = op_menor;
            empilha(operacoes, &op);
         }
#line 1788 "compilador.tab.c"
    break;

  case 71: /* relacao: MAIOR  */
#line 461 "compilador.y"
         {
            operacoes_t op = op_maior;
            empilha(operacoes, &op);
         }
#line 1797 "compilador.tab.c"
    break;

  case 72: /* relacao: MENOR_IGUAL  */
#line 466 "compilador.y"
         {
            operacoes_t op = op_menor_igual;
            empilha(operacoes, &op);
         }
#line 1806 "compilador.tab.c"
    break;

  case 73: /* relacao: MAIOR_IGUAL  */
#line 471 "compilador.y"
         {
            operacoes_t op = op_maior_igual;
            empilha(operacoes,  &op);
         }
#line 1815 "compilador.tab.c"
    break;

  case 74: /* expressao_simples: expressao_simples operacao termo  */
#line 479 "compilador.y"
                  {
                     fprintf(stderr, "DEBUG - Regra E = E + T\n");
                     // E = E + T
                     TIPOS *t1, *t2;
                     t1 = desempilha(E);
                     t2 = desempilha(T);

                     if ((*t1) != (*t2))
                        imprimeErro("Tipos não correspondem");

                     // #ifdef DEBUG
                     // fprintf(stderr, "DEBUG - Empilhando t1: %s em E\n", tipoToString((*t1)));
                     // #endif

                     empilha(E, t1);

                     operacoes_t *op = desempilha(operacoes);
                     sprintf(comando, "%s", opToString((*op)));
                     geraCodigo(NULL, comando);

                     // free(t1);
                     // free(t2);
                  }
#line 1843 "compilador.tab.c"
    break;

  case 75: /* expressao_simples: termo  */
#line 503 "compilador.y"
                  {
                     // fprintf(stderr, "DEBUG - Regra E = T 27\n");
                     // E = T
                     TIPOS *t1;
                     t1 = desempilha(T);

                     // #ifdef DEBUG
                     // fprintf(stderr, "DEBUG - Desempilhando t1: %s de T\n", imprimeTipo((*t1)));
                     // fprintf(stderr, "DEBUG - Empilhando t1: %s em E\n", imprimeTipo((*t1)));
                     // #endif

                     empilha(E, t1);
                     // fprintf(stderr, "free");
                     // free(t1);
                  }
#line 1863 "compilador.tab.c"
    break;

  case 76: /* $@19: %empty  */
#line 518 "compilador.y"
                       { if (proc) checaParam(); }
#line 1869 "compilador.tab.c"
    break;

  case 77: /* expressao_simples: sinal $@19 termo  */
#line 519 "compilador.y"
               {
                  // E = -T
                  TIPOS *t1;
                  t1 = desempilha(T);

                  empilha(E, t1);

                  operacoes_t *op = desempilha(operacoes);
                  if ((*op) == op_subt) {
                     sprintf(comando, "INVR");
                     geraCodigo(NULL, comando);
                  }

                  // free(t1);
               }
#line 1889 "compilador.tab.c"
    break;

  case 79: /* operacao: DIV  */
#line 537 "compilador.y"
         {
      operacoes_t op = op_div;
      empilha(operacoes, &op);
   }
#line 1898 "compilador.tab.c"
    break;

  case 80: /* operacao: MULTIPLICACAO  */
#line 541 "compilador.y"
                   {
      operacoes_t op = op_mult;
      empilha(operacoes, &op);
   }
#line 1907 "compilador.tab.c"
    break;

  case 81: /* operacao: AND  */
#line 545 "compilador.y"
         {
      operacoes_t op = op_and;
      empilha(operacoes, &op);
   }
#line 1916 "compilador.tab.c"
    break;

  case 82: /* operacao: OR  */
#line 549 "compilador.y"
        {
      operacoes_t op = op_or;
      empilha(operacoes, &op);
   }
#line 1925 "compilador.tab.c"
    break;

  case 83: /* sinal: SOMA  */
#line 555 "compilador.y"
            {
         operacoes_t op = op_soma;
         empilha(operacoes, &op);
      }
#line 1934 "compilador.tab.c"
    break;

  case 84: /* sinal: SUBTRACAO  */
#line 559 "compilador.y"
                  {
         operacoes_t op = op_subt;
         empilha(operacoes, &op);
      }
#line 1943 "compilador.tab.c"
    break;

  case 85: /* termo: fator  */
#line 567 "compilador.y"
         {
            fprintf(stderr, "DEBUG - Regra T = F 28\n");
            TIPOS *t1;
            t1 = desempilha(F);

            // #ifdef DEBUG
            // fprintf(stderr, "DEBUG - Desempilhando t1: %s de F\n", imprimeTipo((*t1)));
            // fprintf(stderr, "DEBUG - Empilhando t1: %s em T\n", imprimeTipo((*t1)));
            // #endif

            empilha(T, t1);
            // free(t1);
         }
#line 1961 "compilador.tab.c"
    break;

  case 86: /* termo: termo operacao fator  */
#line 581 "compilador.y"
         {
            // T = T + F
            TIPOS *t1, *t2;
            t1 = desempilha(T);
            t2 = desempilha(F);

            if ((*t1) != (*t2))
               imprimeErro("Tipos não correspondem");

            empilha(T, t1);

            operacoes_t *op = desempilha(operacoes);
            sprintf(comando, "%s", opToString((*op)));
            geraCodigo(NULL, comando);

            // free(t1);
            // free(t2);
         }
#line 1984 "compilador.tab.c"
    break;

  case 87: /* $@20: %empty  */
#line 603 "compilador.y"
         {
            fprintf(stderr, "DEBUG - Regra fator\n");
            int idx = buscaSimbolo(&TS, token);
            SIMBOLO *simb;
            VAR_SIMPLES *VS;
            PARAM_FORMAL *PF;
            FUNCAO *func;

            if (idx == -1)
               imprimeErro("Simbolo inexistente");

            simb = buscaItem(&TS, idx);
            if (simb->categoria == var_simples){
               VS = simb->atributos;
               tipo_aux = VS->tipo;
            }
            else if(simb->categoria == param_formal){
               PF = simb->atributos;
               tipo_aux = PF->tipo;
            }

            else if(simb->categoria == funcao){
               func = simb->atributos;
               tipo_aux = func->tipo;
            }

            else{
               sprintf(erro, "Simbolo %s não é variável simples, parâmetro formal ou função", token);
               imprimeErro(erro);
            }
            
            strncpy(ident, token, strlen(token));
            ident[strlen(token)] = '\0';

            // #ifdef DEBUG
            fprintf(stderr, "DEBUG - Empilhando tipo de %s em F\n", simb->id);
            // #endif

            empilha(F, &tipo_aux);
         }
#line 2029 "compilador.tab.c"
    break;

  case 89: /* fator: NUMERO  */
#line 644 "compilador.y"
               {
         /* carrega constante */
         fprintf(stderr, "REGRA NUMERO\n");
         sprintf(comando, "CRCT %s", token);
         geraCodigo(NULL, comando);

         // if (proc) checaParam();

         /* empilha o tipo inteiro */
         tipo_aux = inteiro;
         empilha(F, &tipo_aux);
      }
#line 2046 "compilador.tab.c"
    break;

  case 90: /* fator: ABRE_PARENTESES expressao FECHA_PARENTESES  */
#line 657 "compilador.y"
         {
            // vem de um fator, precisamos desempilhar de E e colocar em F
            fprintf(stderr, "DEBUG - Regra expressão com parênteses\n");
            TIPOS *t1;
            t1 = desempilha(E);

            // fprintf(stderr, "empilha aqui\n");

            empilha(F, t1);
            // free(t1);
         }
#line 2062 "compilador.tab.c"
    break;

  case 92: /* $@21: %empty  */
#line 679 "compilador.y"
                     {
                        empilha(rotulos, prox_rotulo());
                        empilha(rotulos, prox_rotulo());
                     }
#line 2071 "compilador.tab.c"
    break;

  case 93: /* comando_condicional: $@21 if_then cond_else  */
#line 684 "compilador.y"
                     {
                        free(desempilha(rotulos));
                        free(desempilha(rotulos));
                     }
#line 2080 "compilador.tab.c"
    break;

  case 94: /* $@22: %empty  */
#line 692 "compilador.y"
         {
            // verifica se expressão é booleana
            TIPOS *t1;
            t1 = desempilha(E);

            if ((*t1) != booleano){
               imprimeErro("Expressão não é booleana");
            }

            // free(t1);

            // Gera DSVF com rotulo
            char *rotulo = buscaItem(rotulos, rotulos->tamanho - 1);
            fprintf(stderr, "rotulo %s\n", rotulo);
            sprintf(comando, "DSVF %s", rotulo);
            geraCodigo(NULL, comando);
         }
#line 2102 "compilador.tab.c"
    break;

  case 96: /* $@23: %empty  */
#line 714 "compilador.y"
         {
            char *rotulo;
            // Gera DSVS com primeiro rotulo
            rotulo = buscaItem(rotulos, rotulos->tamanho-2);
            sprintf(comando, "DSVS %s", rotulo);
            geraCodigo(NULL, comando);

            // Gera NADA com segundo rotulo
            rotulo = buscaItem(rotulos, rotulos->tamanho-1);
            geraCodigo(rotulo, "NADA");
         }
#line 2118 "compilador.tab.c"
    break;

  case 97: /* cond_else: ELSE $@23 comando_sem_rotulo  */
#line 726 "compilador.y"
         {
            // Gera NADA com primeiro rotulo
            char *rotulo = buscaItem(rotulos, rotulos->tamanho-2);
            geraCodigo(rotulo, "NADA");
         }
#line 2128 "compilador.tab.c"
    break;

  case 98: /* cond_else: %empty  */
#line 732 "compilador.y"
         {
            // Gera NADA com segundo rotulo
            char *rotulo = buscaItem(rotulos, rotulos->tamanho-1);
            geraCodigo(rotulo, "NADA");
         }
#line 2138 "compilador.tab.c"
    break;

  case 99: /* $@24: %empty  */
#line 741 "compilador.y"
                     {
                        char *rotulo = prox_rotulo();
                        empilha(rotulos, rotulo);
                        empilha(rotulos, prox_rotulo());
                        geraCodigo(rotulo, "NADA");
                     }
#line 2149 "compilador.tab.c"
    break;

  case 100: /* $@25: %empty  */
#line 748 "compilador.y"
                     {
                        char *rotulo = buscaItem(rotulos, rotulos->tamanho-1);
                        sprintf(comando, "DSVF %s", rotulo);
                        geraCodigo(NULL, comando);
                     }
#line 2159 "compilador.tab.c"
    break;

  case 101: /* comando_repetitivo: WHILE $@24 expressao DO $@25 comando_sem_rotulo  */
#line 754 "compilador.y"
                     {
                        char *rotulo;
                        rotulo = buscaItem(rotulos, rotulos->tamanho-2);
                        sprintf(comando, "DSVS %s", rotulo);
                        geraCodigo(NULL, comando);
                        rotulo = desempilha(rotulos);
                        geraCodigo(rotulo, "NADA");

                        free(rotulo);
                        rotulo = desempilha(rotulos);
                        free(rotulo);
                     }
#line 2176 "compilador.tab.c"
    break;

  case 102: /* variavel: %empty  */
#line 770 "compilador.y"
           {
      int idx = buscaSimbolo(&TS, ident);
      SIMBOLO *simb;

      if (idx == -1)
         imprimeErro("Simbolo inexistente");

      simb = buscaItem(&TS, idx);
      comandoCarrega(simb);
   }
#line 2191 "compilador.tab.c"
    break;

  case 104: /* parametros_leitura: parametros_leitura VIRGULA IDENT  */
#line 791 "compilador.y"
            {
               SIMBOLO *item;
               VAR_SIMPLES *VS;
               PARAM_FORMAL *PF;

               int idx = buscaSimbolo(&TS, token);
               if (idx == -1)
                  imprimeErro("[ERRO] read() - Simbolo inexistente");

               geraCodigo(NULL, "LEIT");

               item = buscaItem(&TS, idx);

               if (item->categoria == var_simples) {
                     VS = item->atributos;
                     sprintf(comando, "ARMZ %d,%d", item->nivel_lex, VS->deslocamento);
               }
               else if (item->categoria == param_formal){
                     PF = item->atributos;
                     if (PF->parametro == valor)
                        sprintf(comando, "ARMZ %d,%d", item->nivel_lex, PF->deslocamento);
                     else if (PF->parametro == referencia)
                        sprintf(comando, "ARMI %d,%d", item->nivel_lex, PF->deslocamento);
               }
               else
                  imprimeErro("[ERRO] read() - Item lido nao eh variavel simples nem parametro formal");

               geraCodigo(NULL, comando);
            }
#line 2225 "compilador.tab.c"
    break;

  case 105: /* parametros_leitura: IDENT  */
#line 821 "compilador.y"
            {
               SIMBOLO *item;
               VAR_SIMPLES *VS;
               PARAM_FORMAL *PF;

               int idx = buscaSimbolo(&TS, token);
               if (idx == -1)
                  imprimeErro("[ERRO] read() - Simbolo inexistente");

               geraCodigo(NULL, "LEIT");

               item = buscaItem(&TS, idx);

               if (item->categoria == var_simples) {
                     VS = item->atributos;
                     sprintf(comando, "ARMZ %d,%d", item->nivel_lex, VS->deslocamento);
               }
               else if (item->categoria == param_formal){
                     PF = item->atributos;
                     if (PF->parametro == valor)
                        sprintf(comando, "ARMZ %d,%d", item->nivel_lex, PF->deslocamento);
                     else if (PF->parametro == referencia)
                        sprintf(comando, "ARMI %d,%d", item->nivel_lex, PF->deslocamento);
               }
               else
                  imprimeErro("[ERRO] read() - Item lido nao eh variavel simples nem parametro formal");

               geraCodigo(NULL, comando);
            }
#line 2259 "compilador.tab.c"
    break;

  case 107: /* parametros_escrita: parametros_escrita VIRGULA expressao  */
#line 857 "compilador.y"
            {
               geraCodigo(NULL, "IMPR");
            }
#line 2267 "compilador.tab.c"
    break;

  case 108: /* parametros_escrita: expressao  */
#line 861 "compilador.y"
            {
               geraCodigo(NULL, "IMPR");
            }
#line 2275 "compilador.tab.c"
    break;


#line 2279 "compilador.tab.c"

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

#line 866 "compilador.y"


int main (int argc, char** argv) {
   FILE* fp;
   extern FILE* yyin;

   if (argc<2 || argc>2) {
         printf("usage compilador <arq>a %d\n", argc);
         return(-1);
      }

   fp=fopen (argv[1], "r");
   if (fp == NULL) {
      printf("usage compilador <arq>b\n");
      return(-1);
   }


/* -------------------------------------------------------------------
 *  Inicia a Tabela de S�mbolos
 * ------------------------------------------------------------------- */

   inicializaTS(&TS, TS_TAM);
   inicializaPilhas();

   yyin=fp;
   yyparse();

   return 0;
}
