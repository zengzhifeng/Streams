#ifndef SPECIALIZATIONS_BOOL_STREAM_H
#define SPECIALIZATIONS_BOOL_STREAM_H

#include <functional>

#include "SpecializationMacros.h"
#define OPERATOR_OVERRIDE(method) \
    template<typename F> \
    decltype(auto) method (F&& f) \
        { return Super :: method (std::forward<F>(f)); } \
    decltype(auto) method () \
        { return Super :: method (to_bool); }

namespace stream {

template<typename T>
class StreamImpl<T, Bool> : public virtual StreamImpl<T, Common> {

private:
    PRIVATE_USINGS;

public:
    PUBLIC_USINGS;
    PUBLIC_CONSTRUCTORS;

    MOVE_SEMANTICS(Bool);

    OPERATOR_OVERRIDE(filter);
    OPERATOR_OVERRIDE(take_while);
    OPERATOR_OVERRIDE(drop_while);

    OPERATOR_OVERRIDE(any);
    OPERATOR_OVERRIDE(all);
    OPERATOR_OVERRIDE(none);

    /* Bool specific specializations */

    decltype(auto) filter_not() { return Super::filter(not_(to_bool));     }
    decltype(auto) take_until() { return Super::take_while(not_(to_bool)); }
    decltype(auto) drop_until() { return Super::drop_until(not_(to_bool)); }

    decltype(auto) not_all() {
        this->check_vacant("not_all");
        return !Super::all(to_bool);
    }

    FRIENDS;

private:
    PRIVATE_CONSTRUCTORS;
};

} /* namesapce stream */

#undef OPERATOR_OVERRIDE
#include "UndefSpecializationMacros.h"

#endif