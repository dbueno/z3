#ifndef _DL2TS_RULE_REWRITER_H_
#define _DL2TS_RULE_REWRITER_H_

#include "ast/ast.h"
#include "ast/rewriter/rewriter.h"
#include "ast/bv_decl_plugin.h"
#include "ast/array_decl_plugin.h"

namespace dl2ts {
    class var_manager;

    class rule_rewriter_cfg : public default_rewriter_cfg {
        friend class rule_rw;
    public:
        rule_rewriter_cfg(ast_manager& m, var_manager& vm);
        ~rule_rewriter_cfg();

        br_status reduce_app(func_decl *f, unsigned num, expr *const *args,
                             expr_ref& result, proof_ref& result_pr);
    private:
        ast_manager& m;
        var_manager& m_vm;
        bv_util m_bv_util;
        array_util m_array_util;
        bool m_current; // next if false
        // XXX add bool_rewriter so that making n-ary AND is easy
    };

    // template class rewriter_tpl<rule_rewriter_cfg>;

    class rule_rw : public rewriter_tpl<rule_rewriter_cfg> {
    public:
        rule_rw(ast_manager& m, var_manager& vm)
            : rewriter_tpl<rule_rewriter_cfg>(m, m.proofs_enabled(), m_cfg),
            m_cfg(m, vm) {}

        void set_current(bool b) { m_cfg.m_current = b; }

    protected:
        rule_rewriter_cfg m_cfg;
    };
}

#endif

