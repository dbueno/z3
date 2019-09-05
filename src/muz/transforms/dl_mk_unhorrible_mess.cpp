
/*++
Copyright (c) 2006 Microsoft Corporation

Module Name:

    dl_mk_unhorrible_mess.cpp

Abstract:

    Rule transformer which checks for subsumption
    (currently just for subsumption with total relations)

Author:

    Krystof Hoder (t-khoder) 2011-10-01.

Revision History:

--*/

#include "muz/transforms/dl_mk_unhorrible_mess.h"
#include <sstream>
#include "ast/ast_pp.h"
#include "ast/rewriter/rewriter.h"
#include "ast/rewriter/rewriter_def.h"
#include "ast/rewriter/unhorrible_mess_rewriter.h"
#include "ast/ast_util.h"
#include "ast/expr_abstract.h"
#include "muz/base/fp_params.hpp"
#include "tactic/generic_model_converter.h"


namespace datalog {
    bool mk_unhorrible_mess::rewrite_rule(rule& r, rule_set& new_rules) {
        auto rw = unhorrible_mess_rw(m);
        expr_ref new_r(m);
        expr_ref_vector new_conjs(m);
        unsigned tail_size = r.get_tail_size();

        for (unsigned i = 0; i < tail_size; i++) {
            new_conjs.push_back(r.get_tail(i));
        }
        flatten_and(new_conjs);

        expr_ref new_body(m), body(m), head(m);
        
        body = m.mk_and(new_conjs.size(), new_conjs.c_ptr());
        rw(body, new_body);

        if (body->get_id() != new_body->get_id()) {
            head = r.get_head();
            new_r = m.mk_implies(new_body, head);
            proof_ref p(m);
            rm.mk_rule(new_r, p, new_rules, r.name());
            return true;
        } else {
            new_rules.add_rule(&r);
            return false;
        }
    }

    rule_set * mk_unhorrible_mess::operator()(rule_set const & source) {
        rule_set *rules = alloc(rule_set, m_context);
        rules->inherit_predicates(source);
        bool change = false;
        for (auto *rule : source) {
            if (m_context.canceled()) {
                change = false;
                break;
            }
            change |= rewrite_rule(*rule, *rules);
        }
        if (!change) {
            dealloc(rules);
            rules = nullptr;
        }
        return rules;
    }

};
