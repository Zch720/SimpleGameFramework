#pragma once

#include <type_traits>

namespace sgf::type {
    template <typename T_GLM>
    struct SGFType;

    template <typename T_SGF>
    struct GLMType;

    template <typename T_GLM>
    using SGFType_t = typename SGFType<std::remove_cvref_t<T_GLM>>::type;

    template <typename T_SGF>
    using GLMType_t = typename GLMType<std::remove_cvref_t<T_SGF>>::type;

    template <typename T_GLM>
    SGFType_t<T_GLM>& toSGF(
        T_GLM& rValue
    ) noexcept {
        using T_SGF = SGFType_t<T_GLM>;
        static_assert(sizeof(T_SGF) == sizeof(T_GLM));
        return reinterpret_cast<T_SGF&>(rValue);
    }

    template <typename T_GLM>
    const SGFType_t<T_GLM>& toSGF(
        const T_GLM& rValue
    ) {
        using T_SGF = SGFType_t<T_GLM>;
        static_assert(sizeof(T_SGF) == sizeof(T_GLM));
        return reinterpret_cast<const T_SGF&>(rValue);
    }
    
    template <typename T_SGF>
    GLMType_t<T_SGF>& toGLM(
        T_SGF& rValue
    ) {
        using T_GLM = GLMType_t<T_SGF>;
        static_assert(sizeof(T_SGF) == sizeof(T_GLM));
        return reinterpret_cast<T_GLM&>(rValue);
    }
    
    template <typename T_SGF>
    const GLMType_t<T_SGF>& toGLM(
        const T_SGF& rValue
    ) {
        using T_GLM = GLMType_t<T_SGF>;
        static_assert(sizeof(T_SGF) == sizeof(T_GLM));
        return reinterpret_cast<const T_GLM&>(rValue);
    }
}
