#include "../../include/sgf/contexts.h"

namespace sgf {
    template <typename... Ts>
    Contexts<Ts...>::Contexts(Ts&... ctxs):
        contexts(ctxs...)
    {
    }

    template <typename... Ts>
    template <typename... Us>
    Contexts<Ts...>::Contexts(Contexts<Us...>& other):
        contexts(other.template get<Ts>()...)
    {
    }
    
    template <typename... Ts>
    template <typename T>
    T& Contexts<Ts...>::get() {
        return std::get<T&>(contexts);
    }
    
    template <typename... Ts>
    template <typename T>
    const T& Contexts<Ts...>::get() const {
        return std::get<T&>(contexts);
    }
}