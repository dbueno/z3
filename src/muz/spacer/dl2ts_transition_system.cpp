#include "muz/spacer/dl2ts_transition_system.h"
#include "muz/base/dl_rule_set.h"

using namespace dl2ts;

transition_system::transition_system(datalog::rule_set& rules, ast_manager& m)
    : m(m), m_vm(m), m_trans_conjs(m) {
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
}

void transition_system::print_vmt(std::ostream&) const {
}
