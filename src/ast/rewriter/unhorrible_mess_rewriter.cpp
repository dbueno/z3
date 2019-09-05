/* vim: sw=4
 */
/*++
Copyright (c) 2015 Microsoft Corporation

--*/

#include "ast/rewriter/unhorrible_mess_rewriter.h"
#include "ast/bv_decl_plugin.h"
#include "ast/rewriter/var_subst.h"
#include "ast/rewriter/rewriter_def.h"
#include <sstream>


br_status unhorrible_mess_cfg::reduce_app(
    func_decl *f, unsigned num, expr *const *args, expr_ref& result,
    proof_ref& result_pr) {
    switch (f->get_decl_kind()) {
    case OP_CONCAT:
        if (num > 2) {
            auto concat_rest = m_util.mk_concat(num-1, args+1);
            result = m_util.mk_concat(args[0], concat_rest);
            return BR_REWRITE2;
        }
        break;

    case OP_BUREM_I:
        result = m.mk_app(f->get_family_id(), OP_BUREM, args[0], args[1]);
        return BR_DONE;
    case OP_BSDIV_I:
        result = m.mk_app(f->get_family_id(), OP_BSDIV, args[0], args[1]);
        return BR_DONE;
    case OP_BUDIV_I:
        result = m.mk_app(f->get_family_id(), OP_BUDIV, args[0], args[1]);
        return BR_DONE;
    case OP_BSREM_I:
        result = m.mk_app(f->get_family_id(), OP_BSREM, args[0], args[1]);
        return BR_DONE;
    case OP_BSMOD_I:
        result = m.mk_app(f->get_family_id(), OP_BSMOD, args[0], args[1]);
        return BR_DONE;
    }
    return BR_FAILED;
}
