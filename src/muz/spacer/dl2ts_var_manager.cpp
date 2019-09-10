#include "dl2ts_var_manager.h"

#include "model/model_smt2_pp.h"

using namespace dl2ts;

//^----------------------------------------------------------------------------^

void rule_var_info::display(std::ostream& out) const {
    auto& m = m_vm->get_manager();
    out << mk_pp(m_rel_var, m) << "\n";
    out << mk_pp(m_rel_var_next, m) << "\n";

    for (unsigned i = 0; i < m_place_vars.size(); ++i) {
        out << "    "
            << mk_pp(m_place_vars[i], m) << "/"
            << mk_pp(m_place_vars_next[i], m) << "\n";
    }

    for (auto&& e : m_quant_inputs) {
        out << "    "
            << mk_pp(e, m) << "\n";
    }
}

//^----------------------------------------------------------------------------^

var_manager::var_manager(ast_manager& m) : m(m), m_th_bv(m), m_th_arr(m) {}

var_manager::~var_manager() {}


rule_var_info& var_manager::mk_vars(datalog::rule *r) {
    m_info_storage.push_back(rule_var_info(r, *this, m));
    auto& rule_info = m_info_storage.back();
    obj_map<sort, int> sort_counts;

    rule_info.m_rule_activation = m.mk_fresh_const("r-", m.mk_bool_sort());
    
    auto *decl = r->get_head()->get_decl();

    // Counts different sorts for the head relation
    for (unsigned i = 0; i < decl->get_arity(); ++i) {
        auto *arg_sort = decl->get_domain(i);
        sort_counts.insert_if_not_there(arg_sort, 0);
        sort_counts[arg_sort]++;
    }
    update_global_sort_counts(sort_counts);

    // Create relation var
    rule_info.m_rel_var =
        m.mk_const("at-" + decl->get_name().str(), m.mk_bool_sort());
    rule_info.m_rel_var_next = mk_next_var(rule_info.m_rel_var);

    rule_info.m_place_vars.reset();
    for (auto it = sort_counts.begin(), ie = sort_counts.end(); it != ie;
         ++it) {
        for (unsigned i = 0; i < it->get_value(); ++i) {
            auto name_str = get_sort_name(&it->get_key()) + "-place-" +
                std::to_string(i);
            auto *var= m.mk_const(name_str, &it->get_key());
            rule_info.m_place_vars.push_back(var);
            rule_info.m_place_vars_next.push_back(mk_next_var(var));
        }
    }

    ptr_vector<sort> sorts;
    r->get_vars(m, sorts);

    sort_counts.reset();
    // Counts the different sorts for the quantified variables
    for (unsigned i = 0; i < sorts.size(); sort_counts[sorts[i]]++, i++) {
        auto *s = sorts[i];
        sort_counts.insert_if_not_there(s, 0);
        auto name_str = get_sort_name(s) + "-input-" +
            std::to_string(sort_counts[s]);
        rule_info.m_quant_inputs.push_back(mk_input(name_str, s));
    }

    // XXX might need to reverse rule_info.m_quant_inputs to handle de-Bruijn
    // indices
    m_rule_info.insert(r, &rule_info);
    m_func_decl_info.insert(decl, &rule_info);
    
    return rule_info;
}


void var_manager::display(std::ostream&) const {

}


app * var_manager::mk_next_var(app *var) const {
    assert(var->get_decl()->get_arity() == 0);
    return m.mk_const(var->get_decl()->get_name().str() + "+",
                      var->get_decl()->get_range());
}

app *var_manager::mk_input(const std::string& name, sort *s) const {
    return m.mk_const(name, s);
}


std::string var_manager::get_sort_name(sort *s) const {
    if (m_th_bv.is_bv_sort(s)) {
        return "bv" + std::to_string(m_th_bv.get_bv_size(s));
    } else if (m.is_bool(s)) {
        return "bool";
    } else if (m_th_arr.is_array(s)) {
        auto domain_name = get_sort_name(get_array_domain(s, 0));
        auto range_name = get_sort_name(get_array_range(s));
        return "arr-" + domain_name + "-" + range_name;
    } else {
        assert(false);
    }
}

void var_manager::update_global_sort_counts(
    const obj_map<sort, int>& sort_counts) {
    for (auto it = sort_counts.begin(), ie = sort_counts.end(); it != ie;
         ++it) {
        m_sort_counts.insert_if_not_there(&it->get_key(), 0);
        m_sort_counts[&it->get_key()] =
            std::max(it->get_value(), m_sort_counts[&it->get_key()]);
    }
}
