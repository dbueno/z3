/*++
Copyright (c) 2006 Microsoft Corporation and Denis Bueno

Module Name:

    mk_unhorrible_mess.h

Abstract:

    Rule transformer which checks for subsumption
    (currently just for subsumption with total relations)

Author:

    Krystof Hoder (t-khoder) 2011-10-01.

Revision History:

--*/

#ifndef DL_MK_UNHORRIBLE_MESS_H_
#define DL_MK_UNHORRIBLE_MESS_H_

#include "muz/base/dl_context.h"
#include "muz/base/dl_rule_transformer.h"
#include "muz/base/dl_rule_subsumption_index.h"

namespace datalog {

    class mk_unhorrible_mess : public rule_transformer::plugin {
        ast_manager& m;
        context& m_context;
        rule_manager& rm;
    
        bool rewrite_rule(rule& r, rule_set& new_rules);
    public:
        mk_unhorrible_mess(context & ctx, unsigned priority)
            : plugin(priority, false),
            m(ctx.get_manager()),
            m_context(ctx),
            rm(ctx.get_rule_manager()) {}
        ~mk_unhorrible_mess() override {}

        rule_set * operator()(rule_set const & source) override;
    };

};

#endif /* DL_MK_UNHORRIBLE_MESS_H_ */


