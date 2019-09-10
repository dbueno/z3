#include "muz/spacer/dl2ts_transition_system.h"
#include "muz/base/dl_rule_set.h"
#include "model/model_smt2_pp.h"

using namespace dl2ts;

transition_system::transition_system(datalog::rule_set& rules, ast_manager& m)
    : m(m), m_vm(m), m_trans_conjs(m), m_rule_rw(m, m_vm) {
    // Creats variables needed to translate rules
    for (auto *rule : rules) {
        auto rule_var_info = m_vm.mk_vars(rule);
        rule_var_info.display(std::cerr);
    }

    for (auto *rule : rules) {
        translate_rule(*rule);
    }
}

transition_system::~transition_system() {}


void transition_system::translate_rule(const datalog::rule& r) {
    for (unsigned i = 0; i < r.get_uninterpreted_tail_size(); i++) {
        m_rule_rw.set_current(true);
        expr_ref new_from(m);
        m_rule_rw(r.get_tail(i), new_from);
        std::cout << "rule emitted:" << "\n";
        std::cout << mk_pp(new_from, m) << "\n";
    }

    m_rule_rw.set_current(false);
    expr_ref new_to(m);
    m_rule_rw(r.get_head(), new_to);
}


void transition_system::print_vmt(std::ostream&) const {
}
