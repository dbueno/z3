/*++
Copyright (c) 2013 Microsoft Corporation

Module Name:

    z3_rcf.h

Abstract:

    Additional APIs for handling elements of the Z3 real closed field that contains:
       - transcendental extensions
       - infinitesimal extensions
       - algebraic extensions

Author:

    Leonardo de Moura (leonardo) 2012-01-05

Notes:
    
--*/
#ifndef _Z3_RCF_H_
#define _Z3_RCF_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus
    
    /**
    \defgroup capi C API

    */

    /*@{*/

    /**
    @name Real Closed Fields API
    */
    /*@{*/

    /**
       \brief Delete a RCF numeral created using the RCF API.

       def_API('Z3_rcf_del', VOID, (_in(CONTEXT), _in(RCF_NUM)))
    */
    void Z3_API Z3_rcf_del(z3__in Z3_context c, z3__in Z3_rcf_num a);

    /**
       \brief Return a RCF rational using the given string.

       def_API('Z3_rcf_mk_rational', RCF_NUM, (_in(CONTEXT), _in(STRING)))
    */
    Z3_rcf_num Z3_API Z3_rcf_mk_rational(z3__in Z3_context c, z3__in Z3_string val);

    /**
       \brief Return a RCF small integer.

       def_API('Z3_rcf_mk_small_int', RCF_NUM, (_in(CONTEXT), _in(INT)))
    */
    Z3_rcf_num Z3_API Z3_rcf_mk_small_int(z3__in Z3_context c, z3__in int val);

    /**
       \brief Return Pi

       def_API('Z3_rcf_mk_pi', RCF_NUM, (_in(CONTEXT),))
    */
    Z3_rcf_num Z3_API Z3_rcf_mk_pi(z3__in Z3_context c);

    /**
       \brief Return e (Euler's constant)

       def_API('Z3_rcf_mk_e', RCF_NUM, (_in(CONTEXT),))
    */
    Z3_rcf_num Z3_API Z3_rcf_mk_e(z3__in Z3_context c);

    /**
       \brief Return a new infinitesimal that is smaller than all elements in the Z3 field.

       def_API('Z3_rcf_mk_infinitesimal', RCF_NUM, (_in(CONTEXT),))
    */
    Z3_rcf_num Z3_API Z3_rcf_mk_infinitesimal(z3__in Z3_context c);

    /**
       \brief Store in roots the roots of the polynomial <tt>a[n-1]*x^{n-1} + ... + a[0]</tt>.
       The output vector \c roots must have size \c n. 
       It returns the number of roots of the polynomial.

       \pre The input polynomial is not the zero polynomial. 

       def_API('Z3_rcf_mk_roots', UINT, (_in(CONTEXT), _in(UINT), _in_array(1, RCF_NUM), _out_array(1, RCF_NUM)))
    */
    unsigned Z3_API Z3_rcf_mk_roots(z3__in Z3_context c, z3__in unsigned n, __in_ecount(n) Z3_rcf_num const a[], __out_ecount(n) Z3_rcf_num roots[]);

    /**
       \brief Return the value a + b. 

       def_API('Z3_rcf_add', RCF_NUM, (_in(CONTEXT), _in(RCF_NUM), _in(RCF_NUM)))
    */
    Z3_rcf_num Z3_API Z3_rcf_add(z3__in Z3_context c, z3__in Z3_rcf_num a, z3__in Z3_rcf_num b);

    /**
       \brief Return the value a - b. 

       def_API('Z3_rcf_sub', RCF_NUM, (_in(CONTEXT), _in(RCF_NUM), _in(RCF_NUM)))
    */
    Z3_rcf_num Z3_API Z3_rcf_sub(z3__in Z3_context c, z3__in Z3_rcf_num a, z3__in Z3_rcf_num b);

    /**
       \brief Return the value a * b. 

       def_API('Z3_rcf_mul', RCF_NUM, (_in(CONTEXT), _in(RCF_NUM), _in(RCF_NUM)))
    */
    Z3_rcf_num Z3_API Z3_rcf_mul(z3__in Z3_context c, z3__in Z3_rcf_num a, z3__in Z3_rcf_num b);

    /**
       \brief Return the value a / b. 

       def_API('Z3_rcf_div', RCF_NUM, (_in(CONTEXT), _in(RCF_NUM), _in(RCF_NUM)))
    */
    Z3_rcf_num Z3_API Z3_rcf_div(z3__in Z3_context c, z3__in Z3_rcf_num a, z3__in Z3_rcf_num b);
    
    /**
       \brief Return the value -a

       def_API('Z3_rcf_neg', RCF_NUM, (_in(CONTEXT), _in(RCF_NUM)))
    */
    Z3_rcf_num Z3_API Z3_rcf_neg(z3__in Z3_context c, z3__in Z3_rcf_num a);

    /**
       \brief Return the value 1/a

       def_API('Z3_rcf_inv', RCF_NUM, (_in(CONTEXT), _in(RCF_NUM)))
    */
    Z3_rcf_num Z3_API Z3_rcf_inv(z3__in Z3_context c, z3__in Z3_rcf_num a);

    /**
       \brief Return the value a^k

       def_API('Z3_rcf_power', RCF_NUM, (_in(CONTEXT), _in(RCF_NUM), _in(UINT)))
    */
    Z3_rcf_num Z3_API Z3_rcf_power(z3__in Z3_context c, z3__in Z3_rcf_num a, z3__in unsigned k);

    /**
       \brief Return Z3_TRUE if a < b

       def_API('Z3_rcf_lt', BOOL, (_in(CONTEXT), _in(RCF_NUM), _in(RCF_NUM)))
    */
    Z3_bool Z3_API Z3_rcf_lt(z3__in Z3_context c, z3__in Z3_rcf_num a, z3__in Z3_rcf_num b);

    /**
       \brief Return Z3_TRUE if a > b

       def_API('Z3_rcf_gt', BOOL, (_in(CONTEXT), _in(RCF_NUM), _in(RCF_NUM)))
    */
    Z3_bool Z3_API Z3_rcf_gt(z3__in Z3_context c, z3__in Z3_rcf_num a, z3__in Z3_rcf_num b);

    /**
       \brief Return Z3_TRUE if a <= b

       def_API('Z3_rcf_le', BOOL, (_in(CONTEXT), _in(RCF_NUM), _in(RCF_NUM)))
    */
    Z3_bool Z3_API Z3_rcf_le(z3__in Z3_context c, z3__in Z3_rcf_num a, z3__in Z3_rcf_num b);

    /**
       \brief Return Z3_TRUE if a >= b

       def_API('Z3_rcf_ge', BOOL, (_in(CONTEXT), _in(RCF_NUM), _in(RCF_NUM)))
    */
    Z3_bool Z3_API Z3_rcf_ge(z3__in Z3_context c, z3__in Z3_rcf_num a, z3__in Z3_rcf_num b);

    /**
       \brief Return Z3_TRUE if a == b

       def_API('Z3_rcf_eq', BOOL, (_in(CONTEXT), _in(RCF_NUM), _in(RCF_NUM)))
    */
    Z3_bool Z3_API Z3_rcf_eq(z3__in Z3_context c, z3__in Z3_rcf_num a, z3__in Z3_rcf_num b);

    /**
       \brief Return Z3_TRUE if a != b

       def_API('Z3_rcf_neq', BOOL, (_in(CONTEXT), _in(RCF_NUM), _in(RCF_NUM)))
    */
    Z3_bool Z3_API Z3_rcf_neq(z3__in Z3_context c, z3__in Z3_rcf_num a, z3__in Z3_rcf_num b);

    /**
       \brief Convert the RCF numeral into a string.

       def_API('Z3_rcf_num_to_string', STRING, (_in(CONTEXT), _in(RCF_NUM), _in(BOOL), _in(BOOL)))
    */
    Z3_string Z3_API Z3_rcf_num_to_string(z3__in Z3_context c, z3__in Z3_rcf_num a, z3__in Z3_bool compact, z3__in Z3_bool html);

    /**
       \brief Convert the RCF numeral into a string in decimal notation.

       def_API('Z3_rcf_num_to_decimal_string', STRING, (_in(CONTEXT), _in(RCF_NUM), _in(UINT)))
    */
    Z3_string Z3_API Z3_rcf_num_to_decimal_string(z3__in Z3_context c, z3__in Z3_rcf_num a, z3__in unsigned prec);

    /**
       \brief Extract the "numerator" and "denominator" of the given RCF numeral.
       We have that a = n/d, moreover n and d are not represented using rational functions.

       def_API('Z3_rcf_get_numerator_denominator', VOID, (_in(CONTEXT), _in(RCF_NUM), _out(RCF_NUM), _out(RCF_NUM)))
    */
    void Z3_API Z3_rcf_get_numerator_denominator(z3__in Z3_context c, z3__in Z3_rcf_num a, z3__out Z3_rcf_num * n, z3__out Z3_rcf_num * d);

    /*@}*/
    /*@}*/

#ifdef __cplusplus
};
#endif // __cplusplus

#endif
