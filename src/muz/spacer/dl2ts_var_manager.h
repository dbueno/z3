#ifndef _DL2TS_VAR_MANAGER_H_
#define _DL2TS_VAR_MANAGER_H_


#include "muz/base/dl_rule.h"
#include "ast/bv_decl_plugin.h"
#include "ast/array_decl_plugin.h"


namespace dl2ts {
    class var_manager;

    // each rule needs primary inputs to stand for each quantified variable
    // each relation in datalog needs to have state variables allocated for it:
    // for the relation itself (m_rel_var) and for the places (m_place_vars)

    struct rule_var_info {
        const datalog::rule *     m_rule;
        obj_ref<app, ast_manager> m_rule_activation;
        expr_ref_vector           m_place_vars;
        expr_ref_vector           m_place_vars_next;
        obj_ref<app, ast_manager> m_rel_var;
        obj_ref<app, ast_manager> m_rel_var_next;
        expr_ref_vector           m_quant_inputs;
        var_manager *             m_vm;

        rule_var_info(datalog::rule *r, var_manager& vm, ast_manager& m)
            : m_rule(r), m_rule_activation(m),
            m_place_vars(m), m_place_vars_next(m), m_rel_var(m),
            m_rel_var_next(m),
            m_quant_inputs(m), m_vm(&vm) {}

        app *get_relation() const { return m_rule->get_head(); }
        
        void display(std::ostream&) const;
    };

    //^------------------------------------------------------------------------^
    
    class var_manager {
    public:
        var_manager(ast_manager& m);
        
        ~var_manager();

        // make state and input variables for the rule
        rule_var_info& mk_vars(datalog::rule *r);

        rule_var_info *get_rule_info(const datalog::rule *r) {
            return m_rule_info[r];
        }

        bool get_rule_info(const func_decl *f, rule_var_info*& info) {
            return m_func_decl_info.find(f, info);
        }

        ast_manager& get_manager() const { return m; }

        void display(std::ostream&) const;

    private:
        ast_manager&          m;
        bv_util               m_th_bv;
        array_util            m_th_arr;
        obj_map<sort, int>    m_sort_counts;
        vector<rule_var_info> m_info_storage;
        obj_map<const datalog::rule, rule_var_info*>
                              m_rule_info;
        obj_map<const func_decl, rule_var_info*>
                              m_func_decl_info;

        // obj_map<sort, vector<expr*>> m_places_by_sort;

        app *mk_next_var(app *) const;

        app *mk_input(const std::string& name, sort *) const;

        std::string get_sort_name(sort *) const;

        void update_global_sort_counts(const obj_map<sort, int>&);
    };
}

#endif // _DL2TS_VAR_MANAGER_H_
