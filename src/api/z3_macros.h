#ifndef z3__in
#define z3__in
#endif

#ifndef z3__out
#define z3__out
#endif

#ifndef __out_opt
#define __out_opt z3__out
#endif

#ifndef __ecount
#define __ecount(num_args)
#endif 

#ifndef __in_ecount
#define __in_ecount(num_args) z3__in __ecount(num_args)
#endif 

#ifndef __out_ecount
#define __out_ecount(num_args) z3__out __ecount(num_args)
#endif 

#ifndef __inout_ecount
#define __inout_ecount(num_args) z3__in z3__out __ecount(num_args)
#endif 

#ifndef __inout
#define __inout z3__in z3__out
#endif

#ifndef Z3_bool_opt
#define Z3_bool_opt Z3_bool
#endif

#ifndef Z3_API
#define Z3_API
#endif 

#ifndef DEFINE_TYPE
#define DEFINE_TYPE(T) typedef struct _ ## T *T
#endif

#ifndef DEFINE_VOID
#define DEFINE_VOID(T) typedef void* T
#endif

#ifndef BEGIN_MLAPI_EXCLUDE
#define BEGIN_MLAPI_EXCLUDE
#endif
#ifndef END_MLAPI_EXCLUDE
#define END_MLAPI_EXCLUDE
#endif
