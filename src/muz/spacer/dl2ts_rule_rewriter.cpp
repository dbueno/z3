#include "muz/spacer/dl2ts_rule_rewriter.h"

#include "ast/rewriter/var_subst.h"
#include "ast/rewriter/rewriter_def.h"
#include "muz/spacer/dl2ts_var_manager.h"

using namespace dl2ts;

rule_rewriter_cfg::rule_rewriter_cfg(ast_manager& m, var_manager& vm)
    : m(m), m_vm(vm), m_bv_util(m), m_bool_rw(m), m_array_util(m) {}

rule_rewriter_cfg::~rule_rewriter_cfg() {}

br_status rule_rewriter_cfg::reduce_app(func_decl *f,
                                        unsigned num, expr *const *args,
                                        expr_ref& result,
                                        proof_ref& result_pr) {
    if (m.is_considered_uninterpreted(f)) {
        rule_var_info *info = nullptr;
        if (m_vm.get_rule_info(f, info)) {
            // This code is getting hit for the query but then there's an
            // uninitialized rule info. Why?
            std::cerr << "Processing func_decl " << mk_pp(f, m) << "\n";
            // replace R(a1,...,an) with the Boolean at-var and the place vars
            // equal to the arguments
            auto& rel_pred = m_current ? info->m_rel_var : info->m_rel_var_next;
            assert(info->m_place_vars.size() == num);
            expr_ref_vector conjs(m);
            conjs.push_back(rel_pred);
            for (unsigned i = 0; i < num; i++) {
                auto place_var = m_current ? info->m_place_vars[i] :
                    info->m_place_vars_next[i];
                conjs.push_back(m.mk_eq(place_var.get(), args[i]));
            }
            m_bool_rw.mk_and(conjs.size(), conjs.c_ptr(), result);
            return BR_DONE;
        }
    }

    return BR_FAILED;
}
