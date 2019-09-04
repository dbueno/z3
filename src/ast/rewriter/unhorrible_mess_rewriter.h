/* vim: sw=4
 */
/*++
Copyright (c) 2006 Microsoft Corporation and Denis Bueno

Module Name:

    unhorrible_mess_rewriter.h

Abstract:

    Eliminate operations and constructs that aren't smtlib2-compliant, because
    Z3 makes a horrible mess of these.

Author:

    Denis Bueno (dbueno) 2019-09-04

Revision History:

--*/
#ifndef UNHORRIBLE_MESS_H_
#define UNHORRIBLE_MESS_H_

#include "ast/ast.h"
#include "ast/rewriter/rewriter.h"

class unhorrible_mess_cfg : public default_rewriter_cfg {
    ast_manager& m;
public:
    unhorrible_mess_cfg(ast_manager& m) : m(m) {}

    br_status reduce_app(func_decl *f, unsigned num, expr *const *args,
                         expr_ref& result, proof_ref& result_pr);
};

template class rewriter_tpl<unhorrible_mess_cfg>;

class unhorrible_mess_rw : public rewriter_tpl<unhorrible_mess_cfg> {
protected:
    unhorrible_mess_cfg  m_cfg;
public:
    unhorrible_mess_rw(ast_manager & m):
        rewriter_tpl<unhorrible_mess_cfg>(m, m.proofs_enabled(), m_cfg),
        m_cfg(m)
    {} 
};

#endif /* UNHORRIBLE_MESS_H_ */

