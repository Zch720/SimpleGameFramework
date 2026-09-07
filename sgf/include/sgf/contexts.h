#pragma once

#include <tuple>

namespace sgf {
    template <typename... Ts>
    class Contexts {
    private:
        std::tuple<Ts&...> contexts;

    public:
        Contexts(Ts&... ctxs);

        template<typename... Us>
        Contexts(Contexts<Us...>& other);

        template <typename T>
        T& get();

        template <typename T>
        const T& get() const;
    };
}

#include "../../template_src/sgf/contexts.tpp"
