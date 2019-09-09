#ifndef _DL2TS_TRANSITION_SYSTEM_H_
#define _DL2TS_TRANSITION_SYSTEM_H_

#include "muz/base/dl_rule.h"
#include "muz/spacer/dl2ts_var_manager.h"


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

        void translate_rule(const datalog::rule&);
    };
}


#endif // _DL2TS_TRANSITION_SYSTEM_H_

