#ifndef _DL2TS_TRANSITION_SYSTEM_H_
#define _DL2TS_TRANSITION_SYSTEM_H_

#include "muz/base/dl_rule.h"
#include "muz/spacer/dl2ts_var_manager.h"
#include "muz/spacer/dl2ts_rule_rewriter.h"
#include "ast/rewriter/rewriter_def.h"

namespace dl2ts {
    class transition_system {
    public:
        transition_system(datalog::rule_set& rules, ast_manager& m);
        ~transition_system();

        void print_vmt(std::ostream&) const;

    private:
        ast_manager& m;
        var_manager m_vm;
        expr_ref_vector m_trans_conjs;
        rule_rw m_rule_rw;

        void translate_rule(const datalog::rule&);
    };
}


#endif // _DL2TS_TRANSITION_SYSTEM_H_

