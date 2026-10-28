# 0 "<stdin>"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "<stdin>"
# 29 "<stdin>"
# 1 "../py/mpconfig.h" 1
# 29 "../py/mpconfig.h"
# 1 "C:/msys64/ucrt64/lib/gcc/x86_64-w64-mingw32/16.1.0/include/stdint.h" 1 3
# 9 "C:/msys64/ucrt64/lib/gcc/x86_64-w64-mingw32/16.1.0/include/stdint.h" 3
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
# 1 "C:/msys64/ucrt64/include/stdint.h" 1 3
# 28 "C:/msys64/ucrt64/include/stdint.h" 3
# 1 "C:/msys64/ucrt64/include/crtdefs.h" 1 3
# 10 "C:/msys64/ucrt64/include/crtdefs.h" 3
# 1 "C:/msys64/ucrt64/include/corecrt.h" 1 3
# 10 "C:/msys64/ucrt64/include/corecrt.h" 3
# 1 "C:/msys64/ucrt64/include/_mingw.h" 1 3
# 10 "C:/msys64/ucrt64/include/_mingw.h" 3
# 1 "C:/msys64/ucrt64/include/_mingw_mac.h" 1 3
# 108 "C:/msys64/ucrt64/include/_mingw_mac.h" 3
             
# 117 "C:/msys64/ucrt64/include/_mingw_mac.h" 3
             
# 326 "C:/msys64/ucrt64/include/_mingw_mac.h" 3
       
# 405 "C:/msys64/ucrt64/include/_mingw_mac.h" 3
       
# 11 "C:/msys64/ucrt64/include/_mingw.h" 2 3
# 1 "C:/msys64/ucrt64/include/_mingw_secapi.h" 1 3
# 12 "C:/msys64/ucrt64/include/_mingw.h" 2 3
# 306 "C:/msys64/ucrt64/include/_mingw.h" 3
# 1 "C:/msys64/ucrt64/include/vadefs.h" 1 3
# 9 "C:/msys64/ucrt64/include/vadefs.h" 3
# 1 "C:/msys64/ucrt64/include/_mingw.h" 1 3
# 10 "C:/msys64/ucrt64/include/vadefs.h" 2 3




#pragma pack(push,_CRT_PACKING)
# 24 "C:/msys64/ucrt64/include/vadefs.h" 3
  typedef __builtin_va_list __gnuc_va_list;






  typedef __gnuc_va_list va_list;
# 103 "C:/msys64/ucrt64/include/vadefs.h" 3
#pragma pack(pop)
# 307 "C:/msys64/ucrt64/include/_mingw.h" 2 3
# 604 "C:/msys64/ucrt64/include/_mingw.h" 3
void __attribute__((__cdecl__)) __debugbreak(void);
extern __inline__ __attribute__((__always_inline__,__gnu_inline__)) void __attribute__((__cdecl__)) __debugbreak(void)
{



  __asm__ __volatile__("int {$}3":);





}
# 625 "C:/msys64/ucrt64/include/_mingw.h" 3
void __attribute__((__cdecl__)) __attribute__ ((__noreturn__)) __fastfail(unsigned int _Code);
extern __inline__ __attribute__((__always_inline__,__gnu_inline__)) void __attribute__((__cdecl__)) __attribute__ ((__noreturn__)) __fastfail(unsigned int _Code)
{




  __asm__ __volatile__("int {$}0x29"::"c"(_Code));






  __builtin_unreachable();
}
# 665 "C:/msys64/ucrt64/include/_mingw.h" 3
const char *__mingw_get_crt_info (void);
# 11 "C:/msys64/ucrt64/include/corecrt.h" 2 3




#pragma pack(push,_CRT_PACKING)
# 35 "C:/msys64/ucrt64/include/corecrt.h" 3
__extension__ typedef unsigned long long size_t;
# 45 "C:/msys64/ucrt64/include/corecrt.h" 3
__extension__ typedef long long ssize_t;






typedef size_t rsize_t;
# 62 "C:/msys64/ucrt64/include/corecrt.h" 3
__extension__ typedef long long intptr_t;
# 75 "C:/msys64/ucrt64/include/corecrt.h" 3
__extension__ typedef unsigned long long uintptr_t;
# 88 "C:/msys64/ucrt64/include/corecrt.h" 3
__extension__ typedef long long ptrdiff_t;
# 98 "C:/msys64/ucrt64/include/corecrt.h" 3
typedef unsigned short wchar_t;







typedef unsigned short wint_t;
typedef unsigned short wctype_t;





typedef int errno_t;




typedef long __time32_t;




__extension__ typedef long long __time64_t;
# 138 "C:/msys64/ucrt64/include/corecrt.h" 3
typedef __time64_t time_t;
# 157 "C:/msys64/ucrt64/include/corecrt.h" 3
__attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _invalid_parameter_noinfo(void);
__attribute__ ((__dllimport__)) __attribute__ ((__noreturn__)) void __attribute__((__cdecl__)) _invalid_parameter_noinfo_noreturn(void);
__attribute__ ((__dllimport__)) __attribute__ ((__noreturn__)) void __attribute__((__cdecl__)) _invoke_watson(const wchar_t *expression, const wchar_t *function_name, const wchar_t *file_name, unsigned int line_number, long long unsigned int reserved);
# 437 "C:/msys64/ucrt64/include/corecrt.h" 3
struct threadlocaleinfostruct;
struct threadmbcinfostruct;
typedef struct threadlocaleinfostruct *pthreadlocinfo;
typedef struct threadmbcinfostruct *pthreadmbcinfo;
struct __lc_time_data;

typedef struct localeinfo_struct {
  pthreadlocinfo locinfo;
  pthreadmbcinfo mbcinfo;
} _locale_tstruct,*_locale_t;



typedef struct tagLC_ID {
  unsigned short wLanguage;
  unsigned short wCountry;
  unsigned short wCodePage;
} LC_ID,*LPLC_ID;
# 473 "C:/msys64/ucrt64/include/corecrt.h" 3
#pragma pack(pop)
# 11 "C:/msys64/ucrt64/include/crtdefs.h" 2 3
# 29 "C:/msys64/ucrt64/include/stdint.h" 2 3



# 1 "C:/msys64/ucrt64/lib/gcc/x86_64-w64-mingw32/16.1.0/include/stddef.h" 1 3
# 1 "C:/msys64/ucrt64/include/stddef.h" 1 3
# 18 "C:/msys64/ucrt64/include/stddef.h" 3
  __attribute__ ((__dllimport__)) extern int *__attribute__((__cdecl__)) _errno(void);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _set_errno(int _Value);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _get_errno(int *_Value);


  __attribute__ ((__dllimport__)) extern unsigned long __attribute__((__cdecl__)) __threadid(void);

  __attribute__ ((__dllimport__)) extern uintptr_t __attribute__((__cdecl__)) __threadhandle(void);
# 2 "C:/msys64/ucrt64/lib/gcc/x86_64-w64-mingw32/16.1.0/include/stddef.h" 2 3
# 33 "C:/msys64/ucrt64/include/stdint.h" 2 3


typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned uint32_t;
__extension__ typedef long long int64_t;
__extension__ typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef unsigned char uint_least8_t;
typedef short int_least16_t;
typedef unsigned short uint_least16_t;
typedef int int_least32_t;
typedef unsigned uint_least32_t;
__extension__ typedef long long int_least64_t;
__extension__ typedef unsigned long long uint_least64_t;





typedef signed char int_fast8_t;
typedef unsigned char uint_fast8_t;
typedef short int_fast16_t;
typedef unsigned short uint_fast16_t;
typedef int int_fast32_t;
typedef unsigned int uint_fast32_t;
__extension__ typedef long long int_fast64_t;
__extension__ typedef unsigned long long uint_fast64_t;


__extension__ typedef long long intmax_t;
__extension__ typedef unsigned long long uintmax_t;
# 12 "C:/msys64/ucrt64/lib/gcc/x86_64-w64-mingw32/16.1.0/include/stdint.h" 2 3
#pragma GCC diagnostic pop
# 30 "../py/mpconfig.h" 2




# 1 "C:/msys64/ucrt64/lib/gcc/x86_64-w64-mingw32/16.1.0/include/limits.h" 1 3
# 34 "C:/msys64/ucrt64/lib/gcc/x86_64-w64-mingw32/16.1.0/include/limits.h" 3
# 1 "C:/msys64/ucrt64/lib/gcc/x86_64-w64-mingw32/16.1.0/include/syslimits.h" 1 3






#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
# 1 "C:/msys64/ucrt64/lib/gcc/x86_64-w64-mingw32/16.1.0/include/limits.h" 1 3
# 210 "C:/msys64/ucrt64/lib/gcc/x86_64-w64-mingw32/16.1.0/include/limits.h" 3
# 1 "C:/msys64/ucrt64/include/limits.h" 1 3
# 211 "C:/msys64/ucrt64/lib/gcc/x86_64-w64-mingw32/16.1.0/include/limits.h" 2 3
# 10 "C:/msys64/ucrt64/lib/gcc/x86_64-w64-mingw32/16.1.0/include/syslimits.h" 2 3
#pragma GCC diagnostic pop
# 35 "C:/msys64/ucrt64/lib/gcc/x86_64-w64-mingw32/16.1.0/include/limits.h" 2 3
# 35 "../py/mpconfig.h" 2
# 100 "../py/mpconfig.h"
# 1 "./mpconfigport.h" 1
# 111 "./mpconfigport.h"

# 111 "./mpconfigport.h"
typedef long mp_off_t;
# 120 "./mpconfigport.h"
# 1 "C:/msys64/ucrt64/include/malloc.h" 1 3
# 11 "C:/msys64/ucrt64/include/malloc.h" 3
#pragma pack(push,_CRT_PACKING)
# 52 "C:/msys64/ucrt64/include/malloc.h" 3
  
# 52 "C:/msys64/ucrt64/include/malloc.h" 3
 typedef struct _heapinfo {
    int *_pentry;
    size_t _size;
    int _useflag;
  } _HEAPINFO;



  __attribute__ ((__dllimport__)) unsigned int *__attribute__((__cdecl__)) __p__amblksiz(void);
# 94 "C:/msys64/ucrt64/include/malloc.h" 3
  void *__attribute__((__cdecl__)) calloc(size_t _NumOfElements,size_t _SizeOfElements);
  void __attribute__((__cdecl__)) free(void *_Memory);
  void *__attribute__((__cdecl__)) malloc(size_t _Size);
  void *__attribute__((__cdecl__)) realloc(void *_Memory,size_t _NewSize);

  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _aligned_free(void *_Memory);
  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _aligned_malloc(size_t _Size,size_t _Alignment);

  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _aligned_offset_malloc(size_t _Size,size_t _Alignment,size_t _Offset);
  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _aligned_realloc(void *_Memory,size_t _Size,size_t _Alignment);
  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _aligned_offset_realloc(void *_Memory,size_t _Size,size_t _Alignment,size_t _Offset);
  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _recalloc(void *_Memory,size_t _Count,size_t _Size);
  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _aligned_recalloc(void *_Memory,size_t _Count,size_t _Size,size_t _Alignment);
  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _aligned_offset_recalloc(void *_Memory,size_t _Count,size_t _Size,size_t _Alignment,size_t _Offset);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _aligned_msize(void *_Memory,size_t _Alignment,size_t _Offset);
# 129 "C:/msys64/ucrt64/include/malloc.h" 3
void * __mingw_aligned_malloc (size_t _Size, size_t _Alignment);
void __mingw_aligned_free (void *_Memory);
void * __mingw_aligned_offset_realloc (void *_Memory, size_t _Size, size_t _Alignment, size_t _Offset);
void * __mingw_aligned_offset_malloc (size_t, size_t, size_t);
void * __mingw_aligned_realloc (void *_Memory, size_t _Size, size_t _Offset);
size_t __mingw_aligned_msize (void *memblock, size_t alignment, size_t offset);



# 1 "C:/msys64/ucrt64/lib/gcc/x86_64-w64-mingw32/16.1.0/include/mm_malloc.h" 1 3
# 27 "C:/msys64/ucrt64/lib/gcc/x86_64-w64-mingw32/16.1.0/include/mm_malloc.h" 3
# 1 "C:/msys64/ucrt64/include/stdlib.h" 1 3
# 10 "C:/msys64/ucrt64/include/stdlib.h" 3
# 1 "C:/msys64/ucrt64/include/corecrt_wstdlib.h" 1 3
# 19 "C:/msys64/ucrt64/include/corecrt_wstdlib.h" 3
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wdupenv_s(wchar_t **_Buffer,size_t *_BufferSizeInWords,const wchar_t *_VarName);




  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _itow_s (int _Val,wchar_t *_DstBuf,size_t _SizeInWords,int _Radix);
 

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _ltow_s (long _Val,wchar_t *_DstBuf,size_t _SizeInWords,int _Radix);
 

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _ultow_s (unsigned long _Val,wchar_t *_DstBuf,size_t _SizeInWords,int _Radix);
 

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wgetenv_s(size_t *_ReturnSize,wchar_t *_DstBuf,size_t _DstSizeInWords,const wchar_t *_VarName);
 

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _i64tow_s(long long _Val,wchar_t *_DstBuf,size_t _SizeInWords,int _Radix);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _ui64tow_s(unsigned long long _Val,wchar_t *_DstBuf,size_t _SizeInWords,int _Radix);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wmakepath_s(wchar_t *_PathResult,size_t _SizeInWords,const wchar_t *_Drive,const wchar_t *_Dir,const wchar_t *_Filename,const wchar_t *_Ext);
 

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wputenv_s(const wchar_t *_Name,const wchar_t *_Value);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wsearchenv_s(const wchar_t *_Filename,const wchar_t *_EnvVar,wchar_t *_ResultPath,size_t _SizeInWords);
 

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wsplitpath_s(const wchar_t *_FullPath,wchar_t *_Drive,size_t _DriveSizeInWords,wchar_t *_Dir,size_t _DirSizeInWords,wchar_t *_Filename,size_t _FilenameSizeInWords,wchar_t *_Ext,size_t _ExtSizeInWords);
 
# 11 "C:/msys64/ucrt64/include/stdlib.h" 2 3
# 1 "C:/msys64/ucrt64/lib/gcc/x86_64-w64-mingw32/16.1.0/include/limits.h" 1 3
# 12 "C:/msys64/ucrt64/include/stdlib.h" 2 3
# 26 "C:/msys64/ucrt64/include/stdlib.h" 3
#pragma pack(push,_CRT_PACKING)
# 50 "C:/msys64/ucrt64/include/stdlib.h" 3
  typedef int (__attribute__((__cdecl__)) *_onexit_t)(void);
# 60 "C:/msys64/ucrt64/include/stdlib.h" 3
  typedef struct _div_t {
    int quot;
    int rem;
  } div_t;

  typedef struct _ldiv_t {
    long quot;
    long rem;
  } ldiv_t;





#pragma pack(4)
  typedef struct {
    unsigned char ld[10];
  } _LDOUBLE;
#pragma pack()



  typedef struct {
    double x;
  } _CRT_DOUBLE;

  typedef struct {
    float f;
  } _CRT_FLOAT;

       


  typedef struct {
    long double x;
  } _LONGDOUBLE;

       

#pragma pack(4)
  typedef struct {
    unsigned char ld12[12];
  } _LDBL12;
#pragma pack()
# 113 "C:/msys64/ucrt64/include/stdlib.h" 3
__attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) ___mb_cur_max_func(void);
# 135 "C:/msys64/ucrt64/include/stdlib.h" 3
  typedef void (__attribute__((__cdecl__)) *_purecall_handler)(void);

  __attribute__ ((__dllimport__)) _purecall_handler __attribute__((__cdecl__)) _set_purecall_handler(_purecall_handler _Handler);
  __attribute__ ((__dllimport__)) _purecall_handler __attribute__((__cdecl__)) _get_purecall_handler(void);

  typedef void (__attribute__((__cdecl__)) *_invalid_parameter_handler)(const wchar_t *,const wchar_t *,const wchar_t *,unsigned int,uintptr_t);
  __attribute__ ((__dllimport__)) _invalid_parameter_handler __attribute__((__cdecl__)) _set_invalid_parameter_handler(_invalid_parameter_handler _Handler);
  __attribute__ ((__dllimport__)) _invalid_parameter_handler __attribute__((__cdecl__)) _get_invalid_parameter_handler(void);
# 151 "C:/msys64/ucrt64/include/stdlib.h" 3
  __attribute__ ((__dllimport__)) unsigned long *__attribute__((__cdecl__)) __doserrno(void);

  errno_t __attribute__((__cdecl__)) _set_doserrno(unsigned long _Value);
  errno_t __attribute__((__cdecl__)) _get_doserrno(unsigned long *_Value);
  __attribute__ ((__dllimport__)) char **__attribute__((__cdecl__)) __sys_errlist(void);
  __attribute__ ((__dllimport__)) int *__attribute__((__cdecl__)) __sys_nerr(void);



  __attribute__ ((__dllimport__)) char ***__attribute__((__cdecl__)) __p___argv(void);
  __attribute__ ((__dllimport__)) int *__attribute__((__cdecl__)) __p__fmode(void);
  __attribute__ ((__dllimport__)) int *__attribute__((__cdecl__)) __p___argc(void);
  __attribute__ ((__dllimport__)) wchar_t ***__attribute__((__cdecl__)) __p___wargv(void);
  __attribute__ ((__dllimport__)) char **__attribute__((__cdecl__)) __p__pgmptr(void);
  __attribute__ ((__dllimport__)) wchar_t **__attribute__((__cdecl__)) __p__wpgmptr(void);

  errno_t __attribute__((__cdecl__)) _get_pgmptr(char **_Value);
  errno_t __attribute__((__cdecl__)) _get_wpgmptr(wchar_t **_Value);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _set_fmode(int _Mode);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _get_fmode(int *_PMode);
# 221 "C:/msys64/ucrt64/include/stdlib.h" 3
  __attribute__ ((__dllimport__)) char ***__attribute__((__cdecl__)) __p__environ(void);
  __attribute__ ((__dllimport__)) wchar_t ***__attribute__((__cdecl__)) __p__wenviron(void);
# 234 "C:/msys64/ucrt64/include/stdlib.h" 3
  __attribute__ ((__dllimport__)) unsigned int *__attribute__((__cdecl__)) __p__osplatform(void);
  __attribute__ ((__dllimport__)) unsigned int *__attribute__((__cdecl__)) __p__osver(void);
  __attribute__ ((__dllimport__)) unsigned int *__attribute__((__cdecl__)) __p__winver(void);
  __attribute__ ((__dllimport__)) unsigned int *__attribute__((__cdecl__)) __p__winmajor(void);
  __attribute__ ((__dllimport__)) unsigned int *__attribute__((__cdecl__)) __p__winminor(void);
# 256 "C:/msys64/ucrt64/include/stdlib.h" 3
  errno_t __attribute__((__cdecl__)) _get_osplatform(unsigned int *_Value);
  errno_t __attribute__((__cdecl__)) _get_osver(unsigned int *_Value);
  errno_t __attribute__((__cdecl__)) _get_winver(unsigned int *_Value);
  errno_t __attribute__((__cdecl__)) _get_winmajor(unsigned int *_Value);
  errno_t __attribute__((__cdecl__)) _get_winminor(unsigned int *_Value);
# 274 "C:/msys64/ucrt64/include/stdlib.h" 3
  void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) exit(int _Code) __attribute__ ((__noreturn__));
  void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _exit(int _Code) __attribute__ ((__noreturn__));

  void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) quick_exit(int _Code) __attribute__ ((__noreturn__));




  void __attribute__((__cdecl__)) _Exit(int) __attribute__ ((__noreturn__));

  extern inline __attribute__((__gnu_inline__)) __attribute__ ((__noreturn__)) void __attribute__((__cdecl__)) _Exit(int status)
  { _exit(status); }



       

  void __attribute__((__cdecl__)) __attribute__ ((__noreturn__)) abort(void);
       



  __attribute__ ((__dllimport__)) unsigned int __attribute__((__cdecl__)) _set_abort_behavior(unsigned int _Flags,unsigned int _Mask);



  int __attribute__((__cdecl__)) abs(int _X);
  long __attribute__((__cdecl__)) labs(long _X);


  __extension__ long long __attribute__((__cdecl__)) _abs64(long long);

  extern __inline__ __attribute__((__always_inline__,__gnu_inline__)) long long __attribute__((__cdecl__)) _abs64(long long x) {
    return __builtin_llabs(x);
  }


  int __attribute__((__cdecl__)) atexit(void (__attribute__((__cdecl__)) *)(void));

  int __attribute__((__cdecl__)) at_quick_exit(void (__attribute__((__cdecl__)) *)(void));



  double __attribute__((__cdecl__)) atof(const char *_String);
  double __attribute__((__cdecl__)) _atof_l(const char *_String,_locale_t _Locale);

  int __attribute__((__cdecl__)) atoi(const char *_Str);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _atoi_l(const char *_Str,_locale_t _Locale);
  long __attribute__((__cdecl__)) atol(const char *_Str);
  __attribute__ ((__dllimport__)) long __attribute__((__cdecl__)) _atol_l(const char *_Str,_locale_t _Locale);


  void *__attribute__((__cdecl__)) bsearch(const void *_Key,const void *_Base,size_t _NumOfElements,size_t _SizeOfElements,int (__attribute__((__cdecl__)) *_PtFuncCompare)(const void *,const void *));
  void __attribute__((__cdecl__)) qsort(void *_Base,size_t _NumOfElements,size_t _SizeOfElements,int (__attribute__((__cdecl__)) *_PtFuncCompare)(const void *,const void *));

  unsigned short __attribute__((__cdecl__)) _byteswap_ushort(unsigned short _Short);
  unsigned long __attribute__((__cdecl__)) _byteswap_ulong (unsigned long _Long);
  __extension__ unsigned long long __attribute__((__cdecl__)) _byteswap_uint64(unsigned long long _Int64);
  div_t __attribute__((__cdecl__)) div(int _Numerator,int _Denominator);
  char *__attribute__((__cdecl__)) getenv(const char *_VarName) ;
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _itoa(int _Value,char *_Dest,int _Radix);
  __extension__ __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _i64toa(long long _Val,char *_DstBuf,int _Radix) ;
  __extension__ __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _ui64toa(unsigned long long _Val,char *_DstBuf,int _Radix) ;
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _atoi64(const char *_String);
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _atoi64_l(const char *_String,_locale_t _Locale);
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _strtoi64(const char *_String,char **_EndPtr,int _Radix);
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _strtoi64_l(const char *_String,char **_EndPtr,int _Radix,_locale_t _Locale);
  __extension__ __attribute__ ((__dllimport__)) unsigned long long __attribute__((__cdecl__)) _strtoui64(const char *_String,char **_EndPtr,int _Radix);
  __extension__ __attribute__ ((__dllimport__)) unsigned long long __attribute__((__cdecl__)) _strtoui64_l(const char *_String,char **_EndPtr,int _Radix,_locale_t _Locale);
  ldiv_t __attribute__((__cdecl__)) ldiv(long _Numerator,long _Denominator);
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _ltoa(long _Value,char *_Dest,int _Radix) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) mblen(const char *_Ch,size_t _MaxCount);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _mblen_l(const char *_Ch,size_t _MaxCount,_locale_t _Locale);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _mbstrlen(const char *_Str);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _mbstrlen_l(const char *_Str,_locale_t _Locale);

  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _mbstrnlen(const char *_Str,size_t _MaxCount);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _mbstrnlen_l(const char *_Str,size_t _MaxCount,_locale_t _Locale);

  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) mbtowc(wchar_t * __restrict__ _DstCh,const char * __restrict__ _SrcCh,size_t _SrcSizeInBytes);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _mbtowc_l(wchar_t * __restrict__ _DstCh,const char * __restrict__ _SrcCh,size_t _SrcSizeInBytes,_locale_t _Locale);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) mbstowcs(wchar_t * __restrict__ _Dest,const char * __restrict__ _Source,size_t _MaxCount);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _mbstowcs_l(wchar_t * __restrict__ _Dest,const char * __restrict__ _Source,size_t _MaxCount,_locale_t _Locale);
  int __attribute__((__cdecl__)) mkstemp(char *_TemplateName);
  char *__attribute__((__cdecl__)) mkdtemp(char *_TemplateName);
  int __attribute__((__cdecl__)) rand(void);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _set_error_mode(int _Mode);
  void __attribute__((__cdecl__)) srand(unsigned int _Seed);
# 388 "C:/msys64/ucrt64/include/stdlib.h" 3
  double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) strtod(const char * __restrict__ _Str,char ** __restrict__ _EndPtr);
  float __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) strtof(const char * __restrict__ nptr, char ** __restrict__ endptr);

  long double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) strtold(const char * __restrict__ , char ** __restrict__ );


  extern double __attribute__((__cdecl__)) __attribute__ ((__nothrow__))
  __strtod (const char * __restrict__ , char ** __restrict__);







  float __attribute__((__cdecl__)) __mingw_strtof (const char * __restrict__, char ** __restrict__);
  double __attribute__((__cdecl__)) __mingw_strtod (const char * __restrict__, char ** __restrict__);
  long double __attribute__((__cdecl__)) __mingw_strtold(const char * __restrict__, char ** __restrict__);

  __attribute__ ((__dllimport__)) float __attribute__((__cdecl__)) _strtof_l(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,_locale_t _Locale);
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _strtod_l(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,_locale_t _Locale);
  long __attribute__((__cdecl__)) strtol(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,int _Radix);
  __attribute__ ((__dllimport__)) long __attribute__((__cdecl__)) _strtol_l(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,int _Radix,_locale_t _Locale);
  unsigned long __attribute__((__cdecl__)) strtoul(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,int _Radix);
  __attribute__ ((__dllimport__)) unsigned long __attribute__((__cdecl__)) _strtoul_l(const char * __restrict__ _Str,char ** __restrict__ _EndPtr,int _Radix,_locale_t _Locale);


  int __attribute__((__cdecl__)) system(const char *_Command);

  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _ultoa(unsigned long _Value,char *_Dest,int _Radix) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) wctomb(char *_MbCh,wchar_t _WCh) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wctomb_l(char *_MbCh,wchar_t _WCh,_locale_t _Locale) ;
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) wcstombs(char * __restrict__ _Dest,const wchar_t * __restrict__ _Source,size_t _MaxCount) ;
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _wcstombs_l(char * __restrict__ _Dest,const wchar_t * __restrict__ _Source,size_t _MaxCount,_locale_t _Locale) ;
# 494 "C:/msys64/ucrt64/include/stdlib.h" 3
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _itow(int _Value,wchar_t *_Dest,int _Radix) ;
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _ltow(long _Value,wchar_t *_Dest,int _Radix) ;
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _ultow(unsigned long _Value,wchar_t *_Dest,int _Radix) ;

  double __attribute__((__cdecl__)) __mingw_wcstod(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr);
  float __attribute__((__cdecl__)) __mingw_wcstof(const wchar_t * __restrict__ nptr, wchar_t ** __restrict__ endptr);
  long double __attribute__((__cdecl__)) __mingw_wcstold(const wchar_t * __restrict__, wchar_t ** __restrict__);
# 513 "C:/msys64/ucrt64/include/stdlib.h" 3
  double __attribute__((__cdecl__)) wcstod(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr);
  float __attribute__((__cdecl__)) wcstof(const wchar_t * __restrict__ nptr, wchar_t ** __restrict__ endptr);


  long double __attribute__((__cdecl__)) wcstold(const wchar_t * __restrict__, wchar_t ** __restrict__);

  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _wcstod_l(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,_locale_t _Locale);
  __attribute__ ((__dllimport__)) float __attribute__((__cdecl__)) _wcstof_l(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,_locale_t _Locale);
  long __attribute__((__cdecl__)) wcstol(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,int _Radix);
  __attribute__ ((__dllimport__)) long __attribute__((__cdecl__)) _wcstol_l(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,int _Radix,_locale_t _Locale);
  unsigned long __attribute__((__cdecl__)) wcstoul(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,int _Radix);
  __attribute__ ((__dllimport__)) unsigned long __attribute__((__cdecl__)) _wcstoul_l(const wchar_t * __restrict__ _Str,wchar_t ** __restrict__ _EndPtr,int _Radix,_locale_t _Locale);
  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wgetenv(const wchar_t *_VarName) ;


  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wsystem(const wchar_t *_Command);

  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _wtof(const wchar_t *_Str);
  __attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) _wtof_l(const wchar_t *_Str,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wtoi(const wchar_t *_Str);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wtoi_l(const wchar_t *_Str,_locale_t _Locale);
  __attribute__ ((__dllimport__)) long __attribute__((__cdecl__)) _wtol(const wchar_t *_Str);
  __attribute__ ((__dllimport__)) long __attribute__((__cdecl__)) _wtol_l(const wchar_t *_Str,_locale_t _Locale);

  __extension__ __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _i64tow(long long _Val,wchar_t *_DstBuf,int _Radix) ;
  __extension__ __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _ui64tow(unsigned long long _Val,wchar_t *_DstBuf,int _Radix) ;
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _wtoi64(const wchar_t *_Str);
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _wtoi64_l(const wchar_t *_Str,_locale_t _Locale);
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _wcstoi64(const wchar_t *_Str,wchar_t **_EndPtr,int _Radix);
  __extension__ __attribute__ ((__dllimport__)) long long __attribute__((__cdecl__)) _wcstoi64_l(const wchar_t *_Str,wchar_t **_EndPtr,int _Radix,_locale_t _Locale);
  __extension__ __attribute__ ((__dllimport__)) unsigned long long __attribute__((__cdecl__)) _wcstoui64(const wchar_t *_Str,wchar_t **_EndPtr,int _Radix);
  __extension__ __attribute__ ((__dllimport__)) unsigned long long __attribute__((__cdecl__)) _wcstoui64_l(const wchar_t *_Str ,wchar_t **_EndPtr,int _Radix,_locale_t _Locale);


  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _putenv(const char *_EnvString);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _wputenv(const wchar_t *_EnvString);
# 557 "C:/msys64/ucrt64/include/stdlib.h" 3
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _fullpath(char *_FullPath,const char *_Path,size_t _SizeInBytes);




  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _ecvt(double _Val,int _NumOfDigits,int *_PtDec,int *_PtSign) ;
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _fcvt(double _Val,int _NumOfDec,int *_PtDec,int *_PtSign) ;
  __attribute__ ((__dllimport__)) char *__attribute__((__cdecl__)) _gcvt(double _Val,int _NumOfDigits,char *_DstBuf) ;
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _atodbl(_CRT_DOUBLE *_Result,char *_Str);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _atoldbl(_LDOUBLE *_Result,char *_Str);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _atoflt(_CRT_FLOAT *_Result,char *_Str);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _atodbl_l(_CRT_DOUBLE *_Result,char *_Str,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _atoldbl_l(_LDOUBLE *_Result,char *_Str,_locale_t _Locale);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _atoflt_l(_CRT_FLOAT *_Result,char *_Str,_locale_t _Locale);
# 586 "C:/msys64/ucrt64/include/stdlib.h" 3
unsigned long __attribute__((__cdecl__)) _lrotl(unsigned long,int);
unsigned long __attribute__((__cdecl__)) _lrotr(unsigned long,int);





  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _makepath(char *_Path,const char *_Drive,const char *_Dir,const char *_Filename,const char *_Ext);
  _onexit_t __attribute__((__cdecl__)) _onexit(_onexit_t _Func);



  void __attribute__((__cdecl__)) perror(const char *_ErrMsg);

       
       


  __extension__ unsigned long long __attribute__((__cdecl__)) _rotl64(unsigned long long _Val,int _Shift);
  __extension__ unsigned long long __attribute__((__cdecl__)) _rotr64(unsigned long long Value,int Shift);
       
       
       
       


  unsigned int __attribute__((__cdecl__)) _rotr(unsigned int _Val,int _Shift);
  unsigned int __attribute__((__cdecl__)) _rotl(unsigned int _Val,int _Shift);
       
       
  __extension__ unsigned long long __attribute__((__cdecl__)) _rotr64(unsigned long long _Val,int _Shift);
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _searchenv(const char *_Filename,const char *_EnvVar,char *_ResultPath) ;
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _splitpath(const char *_FullPath,char *_Drive,char *_Dir,char *_Filename,char *_Ext) ;
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _swab(char *_Buf1,char *_Buf2,int _SizeInBytes);







  __attribute__ ((__dllimport__)) wchar_t *__attribute__((__cdecl__)) _wfullpath(wchar_t *_FullPath,const wchar_t *_Path,size_t _SizeInWords);



  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _wmakepath(wchar_t *_ResultPath,const wchar_t *_Drive,const wchar_t *_Dir,const wchar_t *_Filename,const wchar_t *_Ext);


  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _wperror(const wchar_t *_ErrMsg);

  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _wsearchenv(const wchar_t *_Filename,const wchar_t *_EnvVar,wchar_t *_ResultPath) ;
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _wsplitpath(const wchar_t *_FullPath,wchar_t *_Drive,wchar_t *_Dir,wchar_t *_Filename,wchar_t *_Ext) ;


  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _beep(unsigned _Frequency,unsigned _Duration) __attribute__ ((__deprecated__));

  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _seterrormode(int _Mode) __attribute__ ((__deprecated__));
  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) _sleep(unsigned long _Duration) __attribute__ ((__deprecated__));
# 664 "C:/msys64/ucrt64/include/stdlib.h" 3
  char *__attribute__((__cdecl__)) ecvt(double _Val,int _NumOfDigits,int *_PtDec,int *_PtSign) ;
  char *__attribute__((__cdecl__)) fcvt(double _Val,int _NumOfDec,int *_PtDec,int *_PtSign) ;
  char *__attribute__((__cdecl__)) gcvt(double _Val,int _NumOfDigits,char *_DstBuf) ;
  char *__attribute__((__cdecl__)) itoa(int _Val,char *_DstBuf,int _Radix) ;
  char *__attribute__((__cdecl__)) ltoa(long _Val,char *_DstBuf,int _Radix) ;
  int __attribute__((__cdecl__)) putenv(const char *_EnvString) ;



  void __attribute__((__cdecl__)) swab(char *_Buf1,char *_Buf2,int _SizeInBytes) ;


  char *__attribute__((__cdecl__)) ultoa(unsigned long _Val,char *_Dstbuf,int _Radix) ;
  _onexit_t __attribute__((__cdecl__)) onexit(_onexit_t _Func);





  typedef struct { __extension__ long long quot, rem; } lldiv_t;

  __extension__ lldiv_t __attribute__((__cdecl__)) lldiv(long long, long long);

  __extension__ long long __attribute__((__cdecl__)) llabs(long long);

  __extension__ extern inline __attribute__((__gnu_inline__)) long long __attribute__((__cdecl__)) llabs(long long _j) { return (_j >= 0 ? _j : -_j); }


  __extension__ long long __attribute__((__cdecl__)) strtoll(const char * __restrict__, char ** __restrict, int);
  __extension__ unsigned long long __attribute__((__cdecl__)) strtoull(const char * __restrict__, char ** __restrict__, int);


  __extension__ long long __attribute__((__cdecl__)) atoll (const char *);


  __extension__ long long __attribute__((__cdecl__)) wtoll (const wchar_t *);
  __extension__ char *__attribute__((__cdecl__)) lltoa (long long, char *, int);
  __extension__ char *__attribute__((__cdecl__)) ulltoa (unsigned long long , char *, int);
  __extension__ wchar_t *__attribute__((__cdecl__)) lltow (long long, wchar_t *, int);
  __extension__ wchar_t *__attribute__((__cdecl__)) ulltow (unsigned long long, wchar_t *, int);



  __extension__ extern inline __attribute__((__gnu_inline__)) char *__attribute__((__cdecl__)) lltoa (long long _n, char * _c, int _i) { return _i64toa (_n, _c, _i); }
  __extension__ extern inline __attribute__((__gnu_inline__)) char *__attribute__((__cdecl__)) ulltoa (unsigned long long _n, char * _c, int _i) { return _ui64toa (_n, _c, _i); }
  __extension__ extern inline __attribute__((__gnu_inline__)) long long __attribute__((__cdecl__)) wtoll (const wchar_t * _w) { return _wtoi64 (_w); }
  __extension__ extern inline __attribute__((__gnu_inline__)) wchar_t *__attribute__((__cdecl__)) lltow (long long _n, wchar_t * _w, int _i) { return _i64tow (_n, _w, _i); }
  __extension__ extern inline __attribute__((__gnu_inline__)) wchar_t *__attribute__((__cdecl__)) ulltow (unsigned long long _n, wchar_t * _w, int _i) { return _ui64tow (_n, _w, _i); }
# 721 "C:/msys64/ucrt64/include/stdlib.h" 3
#pragma pack(pop)

# 1 "C:/msys64/ucrt64/include/sec_api/stdlib_s.h" 1 3
# 9 "C:/msys64/ucrt64/include/sec_api/stdlib_s.h" 3
# 1 "C:/msys64/ucrt64/include/stdlib.h" 1 3
# 10 "C:/msys64/ucrt64/include/sec_api/stdlib_s.h" 2 3
# 19 "C:/msys64/ucrt64/include/sec_api/stdlib_s.h" 3
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _dupenv_s(char **_PBuffer,size_t *_PBufferSizeInBytes,const char *_VarName);




  __attribute__ ((__dllimport__)) void * __attribute__((__cdecl__)) bsearch_s(const void *_Key,const void *_Base,rsize_t _NumOfElements,rsize_t _SizeOfElements,int (__attribute__((__cdecl__)) * _PtFuncCompare)(void *, const void *, const void *), void *_Context);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) getenv_s(size_t *_ReturnSize,char *_DstBuf,rsize_t _DstSize,const char *_VarName);
 
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _itoa_s(int _Value,char *_DstBuf,size_t _Size,int _Radix);
 
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _i64toa_s(long long _Val,char *_DstBuf,size_t _Size,int _Radix);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _ui64toa_s(unsigned long long _Val,char *_DstBuf,size_t _Size,int _Radix);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _ltoa_s(long _Val,char *_DstBuf,size_t _Size,int _Radix);
 
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) mbstowcs_s(size_t *_PtNumOfCharConverted,wchar_t *_DstBuf,size_t _SizeInWords,const char *_SrcBuf,size_t _MaxCount);
 
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _mbstowcs_s_l(size_t *_PtNumOfCharConverted,wchar_t *_DstBuf,size_t _SizeInWords,const char *_SrcBuf,size_t _MaxCount,_locale_t _Locale);
 
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _ultoa_s(unsigned long _Val,char *_DstBuf,size_t _Size,int _Radix);
 
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) wctomb_s(int *_SizeConverted,char *_MbCh,rsize_t _SizeInBytes,wchar_t _WCh);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wctomb_s_l(int *_SizeConverted,char *_MbCh,size_t _SizeInBytes,wchar_t _WCh,_locale_t _Locale);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) wcstombs_s(size_t *_PtNumOfCharConverted,char *_Dst,size_t _DstSizeInBytes,const wchar_t *_Src,size_t _MaxCountInBytes);
 
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _wcstombs_s_l(size_t *_PtNumOfCharConverted,char *_Dst,size_t _DstSizeInBytes,const wchar_t *_Src,size_t _MaxCountInBytes,_locale_t _Locale);
 


  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _ecvt_s(char *_DstBuf,size_t _Size,double _Val,int _NumOfDights,int *_PtDec,int *_PtSign);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _fcvt_s(char *_DstBuf,size_t _Size,double _Val,int _NumOfDec,int *_PtDec,int *_PtSign);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _gcvt_s(char *_DstBuf,size_t _Size,double _Val,int _NumOfDigits);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _makepath_s(char *_PathResult,size_t _Size,const char *_Drive,const char *_Dir,const char *_Filename,const char *_Ext);
 
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _putenv_s(const char *_Name,const char *_Value);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _searchenv_s(const char *_Filename,const char *_EnvVar,char *_ResultPath,size_t _SizeInBytes);

  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _splitpath_s(const char *_FullPath,char *_Drive,size_t _DriveSize,char *_Dir,size_t _DirSize,char *_Filename,size_t _FilenameSize,char *_Ext,size_t _ExtSize);
 



  __attribute__ ((__dllimport__)) void __attribute__((__cdecl__)) qsort_s(void *_Base,size_t _NumOfElements,size_t _SizeOfElements,int (__attribute__((__cdecl__)) *_PtFuncCompare)(void *,const void *,const void *),void *_Context);
# 724 "C:/msys64/ucrt64/include/stdlib.h" 2 3
# 1 "C:/msys64/ucrt64/include/malloc.h" 1 3
# 725 "C:/msys64/ucrt64/include/stdlib.h" 2 3
# 28 "C:/msys64/ucrt64/lib/gcc/x86_64-w64-mingw32/16.1.0/include/mm_malloc.h" 2 3

# 1 "C:/msys64/ucrt64/include/errno.h" 1 3
# 30 "C:/msys64/ucrt64/lib/gcc/x86_64-w64-mingw32/16.1.0/include/mm_malloc.h" 2 3


static __inline__ void *
_mm_malloc (size_t __size, size_t __align)
{
  void * __malloc_ptr;
  void * __aligned_ptr;


  if (__align & (__align - 1))
    {

      (*_errno()) = 22;

      return ((void *) 0);
    }

  if (__size == 0)
    return ((void *) 0);





    if (__align < 2 * sizeof (void *))
      __align = 2 * sizeof (void *);

  __malloc_ptr = malloc (__size + __align);
  if (!__malloc_ptr)
    return ((void *) 0);


  __aligned_ptr = (void *) (((size_t) __malloc_ptr + __align)
       & ~((size_t) (__align) - 1));


  ((void **) __aligned_ptr)[-1] = __malloc_ptr;

  return __aligned_ptr;
}

static __inline__ void
_mm_free (void *__aligned_ptr)
{
  if (__aligned_ptr)
    free (((void **) __aligned_ptr)[-1]);
}
# 139 "C:/msys64/ucrt64/include/malloc.h" 2 3





  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _resetstkoflw (void);

  __attribute__ ((__dllimport__)) unsigned long __attribute__((__cdecl__)) _set_malloc_crt_max_wait(unsigned long _NewValue);







  __attribute__ ((__dllimport__)) void *__attribute__((__cdecl__)) _expand(void *_Memory,size_t _NewSize);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _msize(void *_Memory);
# 167 "C:/msys64/ucrt64/include/malloc.h" 3
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _get_sbh_threshold(void);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _set_sbh_threshold(size_t _NewValue);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _set_amblksiz(size_t _Value);
  __attribute__ ((__dllimport__)) errno_t __attribute__((__cdecl__)) _get_amblksiz(size_t *_Value);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _heapadd(void *_Memory,size_t _Size);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _heapchk(void);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _heapmin(void);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _heapset(unsigned int _Fill);
  __attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) _heapwalk(_HEAPINFO *_EntryInfo);
  __attribute__ ((__dllimport__)) size_t __attribute__((__cdecl__)) _heapused(size_t *_Used,size_t *_Commit);
  __attribute__ ((__dllimport__)) intptr_t __attribute__((__cdecl__)) _get_heap_handle(void);
# 190 "C:/msys64/ucrt64/include/malloc.h" 3
  static __inline void *_MarkAllocaS(void *_Ptr,unsigned int _Marker) {
    if(_Ptr) {
      *((unsigned int*)_Ptr) = _Marker;
      _Ptr = (char*)_Ptr + 16;
    }
    return _Ptr;
  }
# 218 "C:/msys64/ucrt64/include/malloc.h" 3
  static __inline void __attribute__((__cdecl__)) _freea(void *_Memory) {
    unsigned int _Marker;
    if(_Memory) {
      _Memory = (char*)_Memory - 16;
      _Marker = *(unsigned int *)_Memory;
      if(_Marker==0xDDDD) {
 free(_Memory);
      }





    }
  }
# 264 "C:/msys64/ucrt64/include/malloc.h" 3
#pragma pack(pop)
# 121 "./mpconfigport.h" 2
# 162 "./mpconfigport.h"

# 162 "./mpconfigport.h"
extern const struct _mp_print_t mp_stdout_print;
# 101 "../py/mpconfig.h" 2
# 195 "../py/mpconfig.h"
typedef intptr_t mp_int_t;
typedef uintptr_t mp_uint_t;
# 977 "../py/mpconfig.h"
typedef double mp_float_t;
# 1090 "../py/mpconfig.h"
typedef long long mp_timestamp_t;
# 30 "<stdin>" 2





QCFG(BYTES_IN_LEN, (1))
QCFG(BYTES_IN_HASH, (1))

Q()
Q(*)
Q(_)
Q(/)





Q(%#o)
Q(%#x)




Q({:#b})
Q( )
Q(\n)

Q(maximum recursion depth exceeded)

Q(<module>)
Q(<lambda>)
Q(<listcomp>)
Q(<dictcomp>)
Q(<setcomp>)
Q(<genexpr>)
Q(<string>)
Q(<stdin>)
Q(utf-8)
# 83 "<stdin>"
Q(string.templatelib)


Q(ArithmeticError)

Q(ArithmeticError)

Q(AssertionError)

Q(AssertionError)

Q(AssertionError)

Q(AttributeError)

Q(AttributeError)

Q(BaseException)

Q(BaseException)

Q(BaseException)

Q(EOFError)

Q(EOFError)

Q(Ellipsis)

Q(Ellipsis)

Q(Exception)

Q(Exception)

Q(GeneratorExit)

Q(GeneratorExit)

Q(ImportError)

Q(ImportError)

Q(IndentationError)

Q(IndentationError)

Q(IndexError)

Q(IndexError)

Q(Interpolation)

Q(Interpolation)

Q(Interpolation)

Q(KeyError)

Q(KeyError)

Q(KeyboardInterrupt)

Q(KeyboardInterrupt)

Q(LookupError)

Q(LookupError)

Q(MemoryError)

Q(MemoryError)

Q(NameError)

Q(NameError)

Q(None)

Q(NoneType)

Q(NotImplementedError)

Q(NotImplementedError)

Q(OSError)

Q(OSError)

Q(OverflowError)

Q(OverflowError)

Q(RuntimeError)

Q(RuntimeError)

Q(StopAsyncIteration)

Q(StopAsyncIteration)

Q(StopAsyncIteration)

Q(StopIteration)

Q(StopIteration)

Q(SyntaxError)

Q(SyntaxError)

Q(SystemExit)

Q(SystemExit)

Q(Template)

Q(Template)

Q(Template)

Q(TypeError)

Q(TypeError)

Q(UnicodeError)

Q(UnicodeError)

Q(ValueError)

Q(ValueError)

Q(ViperTypeError)

Q(ViperTypeError)

Q(ZeroDivisionError)

Q(ZeroDivisionError)

Q(_0x0a_)

Q(__add__)

Q(__aenter__)

Q(__aenter__)

Q(__aexit__)

Q(__aexit__)

Q(__aiter__)

Q(__anext__)

Q(__bases__)

Q(__bool__)

Q(__build_class__)

Q(__call__)

Q(__class__)

Q(__class__)

Q(__class__)

Q(__class__)

Q(__class__)

Q(__class__)

Q(__class__)

Q(__complex__)

Q(__contains__)

Q(__contains__)

Q(__delitem__)

Q(__delitem__)

Q(__dict__)

Q(__dict__)

Q(__dict__)

Q(__dict__)

Q(__enter__)

Q(__enter__)

Q(__eq__)

Q(__eq__)

Q(__exit__)

Q(__exit__)

Q(__float__)

Q(__ge__)

Q(__getattr__)

Q(__getattr__)

Q(__getattr__)

Q(__getattr__)

Q(__getitem__)

Q(__getitem__)

Q(__getitem__)

Q(__getitem__)

Q(__gt__)

Q(__hash__)

Q(__iadd__)

Q(__import__)

Q(__init__)

Q(__init__)

Q(__init__)

Q(__int__)

Q(__isub__)

Q(__iter__)

Q(__le__)

Q(__len__)

Q(__lt__)

Q(__main__)

Q(__main__)

Q(__module__)

Q(__name__)

Q(__name__)

Q(__name__)

Q(__name__)

Q(__name__)

Q(__name__)

Q(__name__)

Q(__name__)

Q(__name__)

Q(__name__)

Q(__name__)

Q(__name__)

Q(__name__)

Q(__ne__)

Q(__new__)

Q(__new__)

Q(__new__)

Q(__next__)

Q(__next__)

Q(__next__)

Q(__next__)

Q(__path__)

Q(__path__)

Q(__path__)

Q(__path__)

Q(__qualname__)

Q(__repl_print__)

Q(__repl_print__)

Q(__repr__)

Q(__repr__)

Q(__reversed__)

Q(__setitem__)

Q(__setitem__)

Q(__str__)

Q(__sub__)

Q(__template__)

Q(__traceback__)

Q(_brace_open__colon__hash_b_brace_close_)

Q(_lt_dictcomp_gt_)

Q(_lt_dictcomp_gt_)

Q(_lt_dictcomp_gt_)

Q(_lt_genexpr_gt_)

Q(_lt_genexpr_gt_)

Q(_lt_genexpr_gt_)

Q(_lt_lambda_gt_)

Q(_lt_lambda_gt_)

Q(_lt_lambda_gt_)

Q(_lt_listcomp_gt_)

Q(_lt_listcomp_gt_)

Q(_lt_listcomp_gt_)

Q(_lt_module_gt_)

Q(_lt_module_gt_)

Q(_lt_module_gt_)

Q(_lt_module_gt_)

Q(_lt_setcomp_gt_)

Q(_lt_setcomp_gt_)

Q(_lt_setcomp_gt_)

Q(_lt_string_gt_)

Q(_percent__hash_o)

Q(_percent__hash_x)

Q(_space_)

Q(_star_)

Q(_star_)

Q(_star_)

Q(a0)

Q(a0)

Q(a1)

Q(a1)

Q(a10)

Q(a11)

Q(a12)

Q(a13)

Q(a14)

Q(a15)

Q(a2)

Q(a2)

Q(a3)

Q(a3)

Q(a4)

Q(a4)

Q(a5)

Q(a5)

Q(a6)

Q(a6)

Q(a7)

Q(a7)

Q(a8)

Q(a9)

Q(abs)

Q(abs_)

Q(acos)

Q(add)

Q(add)

Q(add)

Q(add)

Q(add)

Q(add_n)

Q(addi)

Q(addi)

Q(addi_n)

Q(addmi)

Q(addx2)

Q(addx4)

Q(addx8)

Q(align)

Q(all)

Q(and_)

Q(and_)

Q(and_)

Q(andi)

Q(any)

Q(append)

Q(append)

Q(args)

Q(ascii)

Q(asin)

Q(asm_rv32)

Q(asm_thumb)

Q(asm_xtensa)

Q(asr)

Q(atan)

Q(atan2)

Q(auipc)

Q(b)

Q(ball)

Q(bany)

Q(bbc)

Q(bbci)

Q(bbs)

Q(bbsi)

Q(bcc)

Q(bccz)

Q(beq)

Q(beq)

Q(beqz)

Q(beqz_n)

Q(bge)

Q(bge)

Q(bgeu)

Q(bgeu)

Q(bgez)

Q(big)

Q(bin)

Q(bit_branch)

Q(bl)

Q(blt)

Q(blt)

Q(bltu)

Q(bltu)

Q(bltz)

Q(bnall)

Q(bne)

Q(bne)

Q(bnez)

Q(bnez_n)

Q(bnone)

Q(bool)

Q(bool)

Q(bool)

Q(bool)

Q(bool)

Q(bound_method)

Q(builtins)

Q(builtins)

Q(bx)

Q(bytearray)

Q(bytearray)

Q(bytecode)

Q(byteorder)

Q(bytes)

Q(bytes)

Q(bytes)

Q(c_add)

Q(c_addi)

Q(c_addi4spn)

Q(c_and)

Q(c_andi)

Q(c_beqz)

Q(c_bnez)

Q(c_ebreak)

Q(c_j)

Q(c_jal)

Q(c_jalr)

Q(c_jr)

Q(c_li)

Q(c_lui)

Q(c_lw)

Q(c_lwsp)

Q(c_mv)

Q(c_nop)

Q(c_or)

Q(c_slli)

Q(c_srai)

Q(c_srli)

Q(c_sub)

Q(c_sw)

Q(c_swsp)

Q(c_xor)

Q(calcsize)

Q(call0)

Q(call0)

Q(call0)

Q(call0)

Q(callable)

Q(callx0)

Q(ceil)

Q(chr)

Q(classmethod)

Q(classmethod)

Q(clear)

Q(clear)

Q(clear)

Q(close)

Q(close)

Q(closure)

Q(clz)

Q(cm_mva01s)

Q(cm_mva01s)

Q(cm_mvsa01)

Q(cm_mvsa01)

Q(cm_pop)

Q(cm_popret)

Q(cm_popretz)

Q(cm_push)

Q(cm_push)

Q(cm_push)

Q(cmp)

Q(complex)

Q(complex)

Q(const)

Q(const)

Q(conversion)

Q(conversion)

Q(copy)

Q(copy)

Q(copy)

Q(copysign)

Q(cos)

Q(count)

Q(count)

Q(count)

Q(cpsid)

Q(cpsie)

Q(csrrc)

Q(csrrci)

Q(csrrs)

Q(csrrsi)

Q(csrrw)

Q(csrrwi)

Q(data)

Q(decode)

Q(default)

Q(degrees)

Q(delattr)

Q(deleter)

Q(dict)

Q(dict)

Q(dict_view)

Q(difference)

Q(difference_update)

Q(dir)

Q(discard)

Q(div)

Q(divmod)

Q(divu)

Q(doc)

Q(e)

Q(ebreak)

Q(ecall)

Q(encode)

Q(end)

Q(endswith)

Q(enumerate)

Q(enumerate)

Q(errno)

Q(eval)

Q(exec)

Q(exp)

Q(expression)

Q(expression)

Q(extend)

Q(extend)

Q(fabs)

Q(filter)

Q(filter)

Q(find)

Q(float)

Q(float)

Q(floor)

Q(fmod)

Q(format)

Q(format_spec)

Q(format_spec)

Q(frexp)

Q(from_bytes)

Q(fromkeys)

Q(function)

Q(function)

Q(function)

Q(function)

Q(function)

Q(function)

Q(function)

Q(function)

Q(function)

Q(function)

Q(function)

Q(generator)

Q(generator)

Q(generator)

Q(get)

Q(getattr)

Q(getter)

Q(globals)

Q(gp)

Q(hasattr)

Q(hash)

Q(heap_lock)

Q(heap_unlock)

Q(hex)

Q(id)

Q(imag)

Q(index)

Q(index)

Q(index)

Q(inf)

Q(insert)

Q(int)

Q(int)

Q(int)

Q(int)

Q(int)

Q(integer)

Q(integer)

Q(integer)

Q(interpolations)

Q(interpolations)

Q(intersection)

Q(intersection_update)

Q(isalpha)

Q(isdigit)

Q(isdisjoint)

Q(isfinite)

Q(isinf)

Q(isinstance)

Q(islower)

Q(isnan)

Q(isspace)

Q(issubclass)

Q(issubset)

Q(issuperset)

Q(isupper)

Q(items)

Q(iter)

Q(iterable)

Q(iterator)

Q(iterator)

Q(iterator)

Q(iterator)

Q(iterator)

Q(j)

Q(jal)

Q(jalr)

Q(join)

Q(jx)

Q(key)

Q(key)

Q(keys)

Q(keys)

Q(l16si)

Q(l16ui)

Q(l32i)

Q(l32i_n)

Q(l32r)

Q(l32r)

Q(l32r)

Q(l32r)

Q(l8ui)

Q(la)

Q(label)

Q(label)

Q(lb)

Q(lbu)

Q(ldexp)

Q(ldr)

Q(ldrb)

Q(ldrex)

Q(ldrh)

Q(len)

Q(length)

Q(lh)

Q(lhu)

Q(li)

Q(list)

Q(list)

Q(little)

Q(little)

Q(locals)

Q(location)

Q(location)

Q(log)

Q(lower)

Q(lsl)

Q(lsr)

Q(lstrip)

Q(lui)

Q(lw)

Q(map)

Q(map)

Q(math)

Q(math)

Q(math)

Q(max)

Q(maximum_space_recursion_space_depth_space_exceeded)

Q(micropython)

Q(micropython)

Q(micropython)

Q(min)

Q(modf)

Q(module)

Q(mov)

Q(mov)

Q(mov)

Q(mov_n)

Q(movi)

Q(movi_n)

Q(movt)

Q(movw)

Q(movwt)

Q(mrs)

Q(mul)

Q(mulh)

Q(mulhsu)

Q(mulhu)

Q(mull)

Q(mv)

Q(nan)

Q(native)

Q(neg)

Q(next)

Q(nop)

Q(nop)

Q(nop_n)

Q(nsa)

Q(nsau)

Q(object)

Q(object)

Q(object)

Q(object)

Q(object)

Q(oct)

Q(offset)

Q(opt_level)

Q(or_)

Q(or_)

Q(ord)

Q(ori)

Q(pack)

Q(pack_into)

Q(pend_throw)

Q(pi)

Q(pop)

Q(pop)

Q(pop)

Q(pop)

Q(popitem)

Q(pow)

Q(pow)

Q(print)

Q(property)

Q(property)

Q(ptr)

Q(ptr)

Q(ptr16)

Q(ptr16)

Q(ptr32)

Q(ptr32)

Q(ptr8)

Q(ptr8)

Q(push)

Q(ra)

Q(radians)

Q(range)

Q(range)

Q(range)

Q(rbit)

Q(real)

Q(register)

Q(rem)

Q(remove)

Q(remove)

Q(remu)

Q(replace)

Q(repr)

Q(ret)

Q(ret_n)

Q(reverse)

Q(reverse)

Q(reversed)

Q(reversed)

Q(rfind)

Q(rindex)

Q(round)

Q(rsplit)

Q(rstrip)

Q(s0)

Q(s1)

Q(s10)

Q(s11)

Q(s16i)

Q(s2)

Q(s3)

Q(s32i)

Q(s32i_n)

Q(s4)

Q(s5)

Q(s6)

Q(s7)

Q(s8)

Q(s8i)

Q(s9)

Q(sb)

Q(sdiv)

Q(send)

Q(send)

Q(sep)

Q(set)

Q(set)

Q(setattr)

Q(setdefault)

Q(setter)

Q(sh)

Q(sh1add)

Q(sh2add)

Q(sh3add)

Q(signed)

Q(sin)

Q(slice)

Q(slice)

Q(sll)

Q(sll)

Q(slli)

Q(slli)

Q(slt)

Q(slti)

Q(sltiu)

Q(sltu)

Q(sort)

Q(sorted)

Q(sp)

Q(split)

Q(sqrt)

Q(sra)

Q(sra)

Q(srai)

Q(srai)

Q(src)

Q(srl)

Q(srl)

Q(srli)

Q(srli)

Q(ssa8b)

Q(ssa8l)

Q(ssai)

Q(ssl)

Q(ssr)

Q(start)

Q(start)

Q(startswith)

Q(staticmethod)

Q(staticmethod)

Q(step)

Q(stop)

Q(str)

Q(str)

Q(str)

Q(str)

Q(str)

Q(strb)

Q(strex)

Q(strh)

Q(string)

Q(string)

Q(string_dot_templatelib)

Q(strings)

Q(strings)

Q(strip)

Q(struct)

Q(struct)

Q(sub)

Q(sub)

Q(sub)

Q(sub)

Q(subx2)

Q(subx4)

Q(subx8)

Q(sum)

Q(super)

Q(super)

Q(super)

Q(sw)

Q(symmetric_difference)

Q(symmetric_difference_update)

Q(t0)

Q(t1)

Q(t2)

Q(t3)

Q(t4)

Q(t5)

Q(t6)

Q(tan)

Q(target)

Q(target)

Q(tau)

Q(templatelib)

Q(throw)

Q(throw)

Q(to_bytes)

Q(tp)

Q(trunc)

Q(tuple)

Q(tuple)

Q(type)

Q(type)

Q(udiv)

Q(uint)

Q(uint)

Q(uint)

Q(union)

Q(unpack)

Q(unpack_from)

Q(update)

Q(update)

Q(upper)

Q(utf8)

Q(utf_hyphen_8)

Q(utf_hyphen_8)

Q(utf_hyphen_8)

Q(value)

Q(value)

Q(value)

Q(values)

Q(values)

Q(vcmp)

Q(vcvt_f32_s32)

Q(vcvt_s32_f32)

Q(viper)

Q(vldr)

Q(vmov)

Q(vmrs)

Q(vneg)

Q(vsqrt)

Q(vstr)

Q(wfi)

Q(x0)

Q(x1)

Q(x10)

Q(x11)

Q(x12)

Q(x13)

Q(x14)

Q(x15)

Q(x16)

Q(x17)

Q(x18)

Q(x19)

Q(x2)

Q(x20)

Q(x21)

Q(x22)

Q(x23)

Q(x24)

Q(x25)

Q(x26)

Q(x27)

Q(x28)

Q(x29)

Q(x3)

Q(x30)

Q(x31)

Q(x4)

Q(x5)

Q(x6)

Q(x7)

Q(x8)

Q(x9)

Q(xor)

Q(xor)

Q(xori)

Q(zero)

Q(zip)

Q(zip)

Q(zip)
