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
            std::cerr << "here's something to rewrite!" << std::endl;
        }
        break;

    case OP_BSDIV_I:
    case OP_BUDIV_I:
    case OP_BSREM_I:
    case OP_BUREM_I:
    case OP_BSMOD_I:
        std::cerr << "here's something else to rewrite!" << std::endl;
        break;
    }
    return BR_DONE;
}
