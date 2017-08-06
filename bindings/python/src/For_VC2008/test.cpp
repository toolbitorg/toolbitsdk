#include <iostream>
#include <typeinfo>
#include <limits>
#include <limits.h>
#include <signal.h>
#include <stddef.h>
#define __STDC_CONSTANT_MACROS
#define __STDC_LIMIT_MACROS
#include <stdint.h>
using ::std::cout;
using ::std::endl;
using ::std::numeric_limits;

int errors = 0;

template <class T>
const std::type_info& get_type(T arg) { return typeid(T); }
#define CHECK_TYPE(type, anticipated)   (cout << #type ":" << (get_type(type()) == typeid(anticipated) ? "pass" :(++errors,"fail")) << endl)
#define CHECK_CONSTANT(conatant, type)  (cout << #conatant ":" << (get_type(conatant(0))==typeid(type)?"pass":(++errors,"fail")) << endl)
#define CHECK_MAX(macro, type)          (cout << #macro ":" << (macro == numeric_limits<type>::max() ? "pass" :(++errors,"fail")) << endl)
#define CHECK_MIN(macro, type)          (cout << #macro ":" << (macro == numeric_limits<type>::min() ? "pass" :(++errors,"fail")) << endl)
#define CHECK_TYPEOF(value, type)        (cout << "typeof(" #value "):" << (get_type(value)==get_type(+(type)0)?"pass":(++errors,"fail")) << endl)

int main()
{
  CHECK_TYPE(int8_t, signed char);
  CHECK_TYPE(uint8_t, unsigned char);
  CHECK_TYPE(int_least8_t, signed char);
  CHECK_TYPE(uint_least8_t, unsigned char);
  CHECK_TYPE(int_fast8_t, signed char);
  CHECK_TYPE(uint_fast8_t, unsigned char);

  CHECK_CONSTANT(INT8_C,int);
  CHECK_CONSTANT(UINT8_C,int);

  CHECK_MAX(INT8_MAX, signed char);
  CHECK_MIN(INT8_MIN, signed char);
  CHECK_MAX(UINT8_MAX, unsigned char);
  CHECK_MAX(INT_LEAST8_MAX, signed char);
  CHECK_MIN(INT_LEAST8_MIN, signed char);
  CHECK_MAX(UINT_LEAST8_MAX, unsigned char);
  CHECK_MAX(INT_FAST8_MAX, signed char);
  CHECK_MIN(INT_FAST8_MIN, signed char);
  CHECK_MAX(UINT_FAST8_MAX, unsigned char);

  CHECK_TYPEOF(INT8_MAX, signed char);
  CHECK_TYPEOF(INT8_MIN, signed char);
  CHECK_TYPEOF(UINT8_MAX, unsigned char);
  CHECK_TYPEOF(INT_LEAST8_MAX, signed char);
  CHECK_TYPEOF(INT_LEAST8_MIN, signed char);
  CHECK_TYPEOF(UINT_LEAST8_MAX, unsigned char);
  CHECK_TYPEOF(INT_FAST8_MAX, signed char);
  CHECK_TYPEOF(INT_FAST8_MIN, signed char);
  CHECK_TYPEOF(UINT_FAST8_MAX, unsigned char);

  cout << endl;

  CHECK_TYPE(int16_t, signed short);
  CHECK_TYPE(uint16_t, unsigned short);
  CHECK_TYPE(int_least16_t, signed short);
  CHECK_TYPE(uint_least16_t, unsigned short);
  CHECK_TYPE(int_fast16_t, signed short);
  CHECK_TYPE(uint_fast16_t, unsigned short);

  CHECK_CONSTANT(INT16_C,int);
  CHECK_CONSTANT(UINT16_C,int);

  CHECK_MAX(INT16_MAX, signed short);
  CHECK_MIN(INT16_MIN, signed short);
  CHECK_MAX(UINT16_MAX, unsigned short);
  CHECK_MAX(INT_LEAST16_MAX, signed short);
  CHECK_MIN(INT_LEAST16_MIN, signed short);
  CHECK_MAX(UINT_LEAST16_MAX, unsigned short);
  CHECK_MAX(INT_FAST16_MAX, signed short);
  CHECK_MIN(INT_FAST16_MIN, signed short);
  CHECK_MAX(UINT_FAST16_MAX, unsigned short);

  CHECK_TYPEOF(INT16_MAX, signed short);
  CHECK_TYPEOF(INT16_MIN, signed short);
  CHECK_TYPEOF(UINT16_MAX, unsigned short);
  CHECK_TYPEOF(INT_LEAST16_MAX, signed short);
  CHECK_TYPEOF(INT_LEAST16_MIN, signed short);
  CHECK_TYPEOF(UINT_LEAST16_MAX, unsigned short);
  CHECK_TYPEOF(INT_FAST16_MAX, signed short);
  CHECK_TYPEOF(INT_FAST16_MIN, signed short);
  CHECK_TYPEOF(UINT_FAST16_MAX, unsigned short);

  cout << endl;

  CHECK_TYPE(int32_t, signed int);
  CHECK_TYPE(uint32_t, unsigned int);
  CHECK_TYPE(int_least32_t, signed int);
  CHECK_TYPE(uint_least32_t, unsigned int);
  CHECK_TYPE(int_fast32_t, signed int);
  CHECK_TYPE(uint_fast32_t, unsigned int);

  CHECK_CONSTANT(INT32_C,int);
  CHECK_CONSTANT(UINT32_C,unsigned int);

  CHECK_MAX(INT32_MAX, signed int);
  CHECK_MIN(INT32_MIN, signed int);
  CHECK_MAX(UINT32_MAX, unsigned int);
  CHECK_MAX(INT_LEAST32_MAX, signed int);
  CHECK_MIN(INT_LEAST32_MIN, signed int);
  CHECK_MAX(UINT_LEAST32_MAX, unsigned int);
  CHECK_MAX(INT_FAST32_MAX, signed int);
  CHECK_MIN(INT_FAST32_MIN, signed int);
  CHECK_MAX(UINT_FAST32_MAX, unsigned int);

  CHECK_TYPEOF(INT32_MAX, signed int);
  CHECK_TYPEOF(INT32_MIN, signed int);
  CHECK_TYPEOF(UINT32_MAX, unsigned int);
  CHECK_TYPEOF(INT_LEAST32_MAX, signed int);
  CHECK_TYPEOF(INT_LEAST32_MIN, signed int);
  CHECK_TYPEOF(UINT_LEAST32_MAX, unsigned int);
  CHECK_TYPEOF(INT_FAST32_MAX, signed int);
  CHECK_TYPEOF(INT_FAST32_MIN, signed int);
  CHECK_TYPEOF(UINT_FAST32_MAX, unsigned int);

  cout << endl;

  CHECK_TYPE(int64_t, signed __int64);
  CHECK_TYPE(uint64_t, unsigned __int64);
  CHECK_TYPE(int_least64_t, signed __int64);
  CHECK_TYPE(uint_least64_t, unsigned __int64);
  CHECK_TYPE(int_fast64_t, signed __int64);
  CHECK_TYPE(uint_fast64_t, unsigned __int64);

  CHECK_CONSTANT(INT64_C,signed __int64);
  CHECK_CONSTANT(UINT64_C,unsigned __int64);

  CHECK_MAX(INT64_MAX, signed __int64);
  CHECK_MIN(INT64_MIN, signed __int64);
  CHECK_MAX(UINT64_MAX, unsigned __int64);
  CHECK_MAX(INT_LEAST64_MAX, signed __int64);
  CHECK_MIN(INT_LEAST64_MIN, signed __int64);
  CHECK_MAX(UINT_LEAST64_MAX, unsigned __int64);
  CHECK_MAX(INT_FAST64_MAX, signed __int64);
  CHECK_MIN(INT_FAST64_MIN, signed __int64);
  CHECK_MAX(UINT_FAST64_MAX, unsigned __int64);

  CHECK_TYPEOF(INT64_MAX, signed __int64);
  CHECK_TYPEOF(INT64_MIN, signed __int64);
  CHECK_TYPEOF(UINT64_MAX, unsigned __int64);
  CHECK_TYPEOF(INT_LEAST64_MAX, signed __int64);
  CHECK_TYPEOF(INT_LEAST64_MIN, signed __int64);
  CHECK_TYPEOF(UINT_LEAST64_MAX, unsigned __int64);
  CHECK_TYPEOF(INT_FAST64_MAX, signed __int64);
  CHECK_TYPEOF(INT_FAST64_MIN, signed __int64);
  CHECK_TYPEOF(UINT_FAST64_MAX, unsigned __int64);

  cout << endl;

#if _INTEGRAL_MAX_BITS >= 128
  CHECK_TYPE(int128_t, signed __int128);
  CHECK_TYPE(uint128_t, unsigned __int128);

  CHECK_MAX(INT128_MAX, signed __int128);
  CHECK_MIN(INT128_MIN, signed __int128);
  CHECK_MAX(UINT128_MIN, unsigned __int128);

  CHECK_TYPEOF(INT128_MAX, signed __int128);
  CHECK_TYPEOF(INT128_MIN, signed __int128);
  CHECK_TYPEOF(UINT128_MAX, unsigned __int128);

  cout << endl;
#endif

#if PTRDIFF_MAX == INT_MAX && PTRDIFF_MIN == INT_MIN
  CHECK_MAX(PTRDIFF_MAX, ptrdiff_t);
  CHECK_MIN(PTRDIFF_MIN, ptrdiff_t);
  CHECK_TYPEOF(PTRDIFF_MAX, ptrdiff_t);
  CHECK_TYPEOF(PTRDIFF_MIN, ptrdiff_t);
#else
  cout << "PTRDIFF_MAX/_MIN:fail" << endl;
#endif
  cout << endl;

#if SIG_ATOMIC_MAX == INT_MAX && SIG_ATOMIC_MIN == INT_MIN
  CHECK_MAX(SIG_ATOMIC_MAX, sig_atomic_t);
  CHECK_MIN(SIG_ATOMIC_MIN, sig_atomic_t);
  CHECK_TYPEOF(SIG_ATOMIC_MAX, sig_atomic_t);
  CHECK_TYPEOF(SIG_ATOMIC_MIN, sig_atomic_t);
#else
  cout << "SIG_ATOMIC_MAX/_MIN:fail" << endl;
#endif
  cout << endl;

#if SIZE_MAX == UINT_MAX
  CHECK_MAX(SIZE_MAX, size_t);
  CHECK_TYPEOF(SIZE_MAX, size_t);
#else
  cout << "SIZE_MAX:fail" << endl;
#endif
  cout << endl;

#if WCHAR_MAX == 0xffff && WCHAR_MIN == 0
  CHECK_MAX(WCHAR_MAX, wchar_t);
  CHECK_MIN(WCHAR_MIN, wchar_t);
  CHECK_TYPEOF(WCHAR_MAX, wchar_t);
  CHECK_TYPEOF(WCHAR_MIN, wchar_t);
#else
  cout << "WCHAR_MAX/_MIN:fail" << endl;
#endif
  cout << endl;

#if WINT_MAX == 0xffff && WINT_MIN == 0
  CHECK_MAX(WINT_MAX, wint_t);
  CHECK_MIN(WINT_MIN, wint_t);
  CHECK_TYPEOF(WINT_MAX, wint_t);
  CHECK_TYPEOF(WINT_MIN, wint_t);
#else
  cout << "WINT_MAX/_MIN:fail" << endl;
#endif
  cout << endl;

  cout << "error count: " << errors << endl;
}

