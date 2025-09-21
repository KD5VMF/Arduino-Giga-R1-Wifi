#ifndef BASIC_H
#define BASIC_H

/*
 *
 *  $Id: basic.h,v 1.1 2023/09/27 15:23:20 stefan Exp stefan $
 *
 *  Stefan's basic interpreter 
 *
 *  See the licence file on 
 *  https://github.com/slviajero/tinybasic for copyright/left.
 *  (GNU GENERAL PUBLIC LICENSE, Version 3, 29 June 2007)
 *
 *  Author: Stefan Lenz, sl001@serverfabrik.de
 *
 *  basic.h are the core defintions and function protypes.
 *
 */

#include <stdint.h>      /* fixed-width integer types */
#include "language.h"    /* feature flags & numeric mode (defines number_t, etc.) */

/* 
 * A few of the buffers and vars come from hardware.h. These are
 * 
 * #define BUFSIZE         
 * #define STACKSIZE      
 * #define GOSUBDEPTH      
 * #define FORDEPTH        
 * #define LINECACHESIZE
 * 
 * They depend on the hardware architecture and are configured there.
 *
 */

/* Default sizes of arrays and strings if they are not DIMed */
#define ARRAYSIZEDEF    10
#define STRSIZEDEF      32

/* the maximum name length */
#define MAXNAME         32

/*
 * The tokens for the BASIC keywords
 *
 *  All single character operators are their own tokens
 *  ASCII values above 0x7f are used for tokens of keywords.
 *  EOL is a token. 
 * 
 *  The two byte tokens are possible to extend the language beyond 
 *  127 keywords.
 */
#define EOL          0
#define NUMBER       -127
#define LINENUMBER   -126
#define STRING       -125
#define VARIABLE     -124
#define STRINGVAR    -123
#define ARRAYVAR     -122
/* multi character tokens - BASEKEYWORD (3) */
#define GREATEREQUAL -121
#define LESSEREQUAL  -120
#define NOTEQUAL     -119
/* this is the Palo Alto Language Set (19) */
#define TPRINT  -118
#define TLET    -117
#define TINPUT  -116
#define TGOTO   -115
#define TGOSUB  -114
#define TRETURN -113
#define TIF     -112
#define TFOR    -111
#define TTO     -110
#define TSTEP   -109
#define TNEXT   -108
#define TSTOP   -107
#define TLIST   -106
#define TNEW    -105
#define TRUN    -104
#define TABS    -103
#define TRND    -102
#define TSIZE   -101
#define TREM    -100
/* this is the Apple 1 language set in addition to Palo Alto (14) */
#define TNOT    -99
#define TAND    -98
#define TOR     -97
#define TLEN    -96
#define TSGN    -95 
#define TPEEK   -94
#define TDIM    -93
#define TCLR    -92
#define THIMEM  -91
#define TTAB    -90
#define TTHEN   -89
#define TEND    -88
#define TPOKE   -87
/* Stefan's tinybasic additions (14) */
#define TCONT   -86
#define TSQR    -85
#define TPOW    -84
#define TMAP    -83
#define TDUMP   -82
#define TBREAK  -81
#define TSAVE   -80
#define TLOAD   -79
#define TGET    -78
#define TPUT    -77
#define TSET    -76
#define TCLS    -75
#define TLOCATE -74
#define TELSE   -73
/* Arduino functions (10) + TLED) */
#define TPINM   -72
#define TDWRITE -71
#define TDREAD  -70
#define TAWRITE -69
#define TAREAD  -68
#define TDELAY  -67
#define TMILLIS -66
#define TTONE   -65
#define TPULSE  -64
#define TAZERO  -63
#define TLED    -62
/* the DOS functions (5) */
#define TCATALOG -61
#define TDELETE  -60
#define TOPEN    -59
#define TCLOSE   -58
#define TFDISK   -57
/* low level access of internal routines (2) */
#define TUSR     -56
#define TCALL    -55
/* mathematical functions (7) */
#define TSIN     -54
#define TCOS     -53
#define TTAN     -52
#define TATAN    -51
#define TLOG     -50
#define TEXP     -49
#define TINT     -48
/* graphics - rudimentary (7) */
#define TCOLOR   -47
#define TPLOT    -46
#define TLINE    -45
#define TCIRCLE  -44
#define TRECT    -43
#define TFCIRCLE -42
#define TFRECT   -41
/* the Dartmouth extensions (6) */
#define TDATA    -40
#define TREAD    -39
#define TRESTORE -38
#define TDEF     -37
#define TFN      -36
#define TON      -35
/* darkarts (3) */
#define TMALLOC  -34
#define TFIND    -33
#define TEVAL    -32
/* iot extensions (9) */
#define TERROR   -31
#define TAVAIL   -30
#define TSTR     -29
#define TINSTR   -28
#define TVAL     -27
#define TNETSTAT -26
#define TSENSOR  -25
#define TWIRE    -24
#define TSLEEP   -23
/* events and interrupts */
#define TAFTER   -22
#define TEVERY   -21
#define TEVENT   -20
/* structured commands */
#define TWHILE   -19
#define TWEND    -18
#define TREPEAT  -17
#define TUNTIL   -16
#define TSWITCH  -15
#define TCASE    -14
#define TSWEND   -13
#define TDO      -12
#define TDEND    -11
/* multiline function extension */
#define TFEND    -10
/* multibyte token extension (currently unused) */
#define TEXT7    -9
#define TEXT6    -8
#define TEXT5    -7
#define TEXT4    -6
#define TEXT3    -5
#define TEXT2    -4 
#define TEXT1    -3
/* end of tokens */
/* constants used for some purposes other than token */
#define TBUFFER  -2
#define UNKNOWN  -1

/* alternative implementation using positive token values */
#define TASC   1
#define TCHR   2
#define TRIGHT 3
#define TLEFT  4
#define TMID   5
#define TSPC   6

/* The editor and other helpers */
#define TEDIT  7
#define THELP  8

/* bitwise operations, avoid 10 as a token value */
#define TSHL   9
#define TSHR   11
#define TBIT   12

/* Extension tokens can be in the range from -128 upwards with HASLONGTOKENS */
#define TCAM   -128

/* BASEKEYWORD is used by the lexer. From this keyword on it tries to match. */
#define BASEKEYWORD -121

/*
 *  Interpreter states 
 */
#define SINT  0
#define SRUN  1
#define SERUN 2

/*
 *  the message catalog
 */
#define MFILE         0
#define MPROMPT       1
#define MGREET        2
#define MLINE         3
#define MNUMBER       4
#define MVARIABLE     5
#define MARRAY        6
#define MSTRING       7
#define MSTRINGVAR    8
#define EGENERAL      9
#define EUNKNOWN      10
#define ENUMBER       11
#define EDIVIDE       12
#define ELINE         13
#define EOUTOFMEMORY  14
#define ESTACK        15
#define EORANGE       16
#define ESTRING       17
#define EVARIABLE     18
#define ELOOP         19
#define EFILE         20
#define EFUN          21
#define EARGS         22
#define EEEPROM       23
#define ESDCARD       24
#define MBASICLANGSET 25
#define MLANGSET      26
#define MKEYWORDS     27

/*
 * code for variable numbers and addresses sizes
 */

#ifdef HASFLOAT
  #ifdef HAS64BIT
    typedef double     number_t;
    typedef long long  wnumber_t;
  #else
    typedef float      number_t;
    typedef long long  wnumber_t;
  #endif
#else
  #ifdef HAS64BIT
    typedef int64_t    number_t;
    typedef int64_t    wnumber_t;
  #elif defined(HAS32BITINT)
    typedef int32_t    number_t;
    typedef int32_t    wnumber_t;
  #else
    typedef int        number_t;
    typedef int        wnumber_t;
  #endif
#endif

/* default is 16bit addresses and max 64k memory, setting MEMSIZE in hardware.h overrides this */
#if !defined(MEMSIZE) || MEMSIZE < 65536
typedef uint16_t address_t; /* this type addresses memory */
#else
typedef uint32_t address_t; /* large memory systems */
#endif

typedef int8_t  mem_t;   /* a signed 8 bit type for the memory */
typedef int     index_t; /* this type counts at least 16 bit */

#ifndef HASLONGTOKENS
typedef int8_t  token_t; /* tokens up to 127 commands/data types */
#else
typedef int16_t token_t; /* extended token space */
#endif

/* ---- Buffers that depend on number_t must appear AFTER number_t is defined ---- */

/* Additional buffers and vars, VARSIZE only needed for Tinybasics */
#define SBUFSIZE   (16 * sizeof(number_t)) 
#define VARSIZE    26

/* the memreader function type, a function accessing memory has to have this shape */
typedef mem_t (*memreader_t)(address_t);
typedef void  (*memwriter_t)(address_t, mem_t);

/* the worker function type - experimental */
typedef void (*bworkfunction_t)();

/* the location type, this is the cursor on the actual interpreter location */
typedef struct { 
    address_t location; 
    token_t   token; 
} blocation_t;

/* string system */
typedef uint16_t stringlength_t;

typedef struct {
    address_t      address; 
    char*          ir; 
    stringlength_t length;
    address_t      strdim; 
    address_t      arraydim;
} string_t;

/* names and LHS objects */
typedef struct { 
    token_t token; 
    mem_t   c[MAXNAME]; 
    mem_t   l;
} name_t;

typedef struct { 
    name_t    name;
    address_t i;       /* substring start or first array index */
    address_t j;       /* second array index */
    address_t i2;      /* substring second value */
    mem_t     ps;      /* pure string flag */
} lhsobject_t;

/* heap objects */
typedef struct { 
    name_t    name; 
    address_t address; 
    address_t size; 
} heap_t;

/* FOR/loop state */
typedef struct {
    name_t    var;
    address_t varaddress; /* optional speed-up */
    address_t here;
    number_t  to;
    number_t  step;
} bloop_t;

/* accumulator */
typedef union { 
    number_t       n; 
    address_t      a; 
    index_t        i;
    stringlength_t s; 
    mem_t          c[sizeof(number_t)]; 
} accu_t;

/* timers */
typedef struct {
    mem_t         enabled;
    unsigned long last;
    unsigned long interval; 
    mem_t         type;
    address_t     linenumber;
} btimer_t;

/* events */
typedef struct {
    mem_t     enabled;
    mem_t     pin;
    mem_t     mode;
    mem_t     type;
    address_t linenumber;
    mem_t     active;
} bevent_t;

/* ============
 * Declarations
 * ============ */

/* Layer 0 */
void bintroutine0();
void bintroutine1();
void bintroutine2();
void bintroutine3();
mem_t enableevent(mem_t);
void disableevent(mem_t);
mem_t eventindex(mem_t);
mem_t addevent(mem_t, mem_t, mem_t, address_t);
void deleteevent(mem_t);
volatile bevent_t* findevent(mem_t);

address_t ballocmem(); 
void eload();
void esave();
char autorun();
void displaybanner();

/* Apple 1 heap-like vars */
address_t bmalloc(name_t*, address_t);
address_t bfind(name_t*);
address_t bfree(name_t*);
address_t blength (name_t*);

/* number variables */
number_t getvar(name_t*);
void setvar(name_t*, number_t);
void clrvars();

/* memory access helpers */
number_t getnumber(address_t, memreader_t);
address_t getaddress(address_t, memreader_t); 
stringlength_t getstrlength(address_t, memreader_t);
void setnumber(address_t, memwriter_t, number_t);
void setaddress(address_t, memwriter_t, address_t);
void setstrlength(address_t, memwriter_t, stringlength_t);

/* names */
address_t setname_heap(address_t, name_t*);
address_t setname_pgm(address_t, name_t*);
address_t getname(address_t, name_t*, memreader_t);
mem_t cmpname(name_t*, name_t*);
void zeroname(name_t*);
void zeroheap(heap_t*);

/* arrays/strings */
address_t createarray(name_t*, address_t, address_t);
void array(lhsobject_t*, mem_t, number_t*);
address_t createstring(name_t*, address_t, address_t);
void getstring(string_t*, name_t*, address_t, address_t);
void setstringlength(name_t*, address_t, address_t);

/* user extensions */
number_t getusrvar();
void setusrvar(number_t);
number_t getusrarray(address_t);
void setusrarray(address_t, number_t);
void makeusrstring();
number_t usrfunction(address_t, number_t);
void usrcall(address_t);

/* keywords/messages */
char* getkeyword(address_t);
char* getmessage(char);
token_t gettokenvalue(address_t);
void printmessage(char);

/* errors/debug */
void error(token_t);
void reseterror();
void debugtoken();
void bdebug(const char*);

/* arithmetic stack */
void push(number_t);
number_t pop();
address_t popaddress();
void drop();
void clearst();

/* READ/DATA */
void clrdata();

/* FOR/GOSUB stacks */
void pushforstack(name_t*, number_t, number_t);
void popforstack(name_t*, number_t*, number_t*);
void dropforstack();
void clrforstack();
void pushgosubstack(mem_t);
void popgosubstack();
void dropgosubstack();
void clrgosubstack();

/* location rewinds */
void pushlocation(blocation_t*);
void poplocation(blocation_t*); 

/* signals */
void signalon();
void signaloff();
void signalhandler(int);

/* output */
void outcr();
void outspc();
void outsc(const char*);
void outscf(const char *, index_t);

/* runtime console hooks */
void consolelog(char*);
void consolelognum(int);

/* names */
void outname(name_t*);

/* number I/O */
address_t parsenumber(char*, number_t*);
address_t parsenumbern(char*, number_t*); /* hex,oct,bin */
address_t parsenumber2(char*, number_t*);
address_t writenumber(char*, wnumber_t); 
address_t writenumbern(char*, wnumber_t, mem_t); /* hex,oct,bin */
address_t writenumber2(char*, number_t);
address_t tinydtostrf(number_t, index_t, char*);
int innumber(number_t*, char*, address_t);
void outnumber(number_t);

/* Layer 1 */
void whitespaces();
void nexttoken();

char nomemory(number_t);
void storetoken(); 
mem_t memread(address_t);
mem_t memread2(address_t);
void memwrite2(address_t, mem_t);
mem_t beread(address_t);
void beupdate(address_t, mem_t);
void gettoken();
void firstline();
void nextline();

void clrlinecache();
void addlinecache(address_t, address_t);
address_t findinlinecache(address_t);
void findline(address_t);
address_t myline(address_t);
void moveblock(address_t, address_t, address_t);
void zeroblock(address_t, address_t);
void diag();
void storeline();

char termsymbol();
char expect(token_t, mem_t);
char expectexpr();
void parsearguments();
void parsenarguments(char);
void parsesubscripts();
void parsefunction(void (*)(), short);
void parseoperator(void (*)());
void parsesubstring();

/* math/other */
void xabs();
void xsgn();
void xpeek();
void xmap();
number_t rnd(); 
void xrnd();
void sqr();
void xpow();
number_t bpow(number_t, number_t);

/* strings */
void parsestringvar(string_t*, lhsobject_t*);
char stringvalue(string_t*);
void streval();

/* float funcs */
void xsin();
void xcos();
void xtan();
void xatan();
void xlog();
void xexp();
void xint();

/* expressions */
void factor();
void power();
void term();
void addexpression();
void compexpression();
void notexpression();
void andexpression();
void expression();

/* rtc string */
void rtcmkstr();

/* Layer 2 core */
void xprint();
void getstringtobuffer(string_t*, char*, stringlength_t);
void lefthandside(lhsobject_t*);
void assignnumber(lhsobject_t, number_t);
void assignstring(string_t*, string_t*, stringlength_t);
void assignment();
void showprompt();
void xinput();
void xgoto();
void xreturn();
void xif();

/* FOR/NEXT */
void findnextcmd();
void findbraket(token_t, token_t);
void xfor();
void xbreak();
void xcont();
void xnext();

/* WHILE/WEND */
void xwhile();
void xwend();

/* REPEAT/UNTIL */
void xrepeat();
void xuntil();

/* misc control */
void outputtoken();
void xlist();
void xrun();
void xnew();
void xrem();
void xclr();
void xdim();
void xpoke();
void xtab();
void xdump();
void dumpmem(address_t, address_t, char);
void xlocate();

/* file & i/o */
void stringtobuffer(char*, string_t*);
void getfilename(char*, char);
void xsave();
void xload(const char*);
void xget();
void xput();
void xset();
void xnetstat();

/* Arduino I/O */
void xaread();
void xdread();
void xdwrite();
void xawrite();
void xpinm();
void xdelay();
void xtone();
void btone(int);
void bpulsein();

/* graphics */
void xcolor();
void xplot();
void xline();
void xrect();
void xcircle();
void xfrect();
void xfcircle();

/* darkarts */
void xmalloc();
void xfind();
void xeval();

/* IoT */
void xavail();
void xfsensor();
void xsleep();
void xwire();
void xfwire();

/* timers/events */
void xafter();
void xevent();

/* File I/O helpers */
char streq(const char*, char*);
void xcatalog();
void xdelete();
void xopen();
void xfopen();
void xclose();
void xfdisk();

/* low level */
void xcall();
void xusr();

/* dartmouth */
void xdata();
void nextdatarecord();
void xread();
void xrestore();
void xdef();
void xfn(mem_t);
void xon();

/* timers driver */
void xtimer();
void resettimer(btimer_t*);

/* structured */
void xswitch();
void xcase();
void xendswitch();

/* editor */
void xedit(); 

/* camera meta */
void xcam();

/* statement loop */
void statement();

/* extensions */
void bsetup();
void bloop();

#endif /* BASIC_H */