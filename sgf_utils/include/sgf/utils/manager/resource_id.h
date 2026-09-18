#pragma once

#include <concepts>
#include <stdint.h>
#include <string>

#include "fmt/format.h"

#include "sgf/utils/manager/define.h"

#define RESOURCE_ID_CONSTRUCTOR(T_RID)  \
    protected:                          \
        T_RID(                          \
            ID nId,                     \
            uint32_t nGen               \
        ):                              \
            ResourceId(nId, nGen)       \
        {                               \
        }

namespace sgf::utils {
    template <class T, typename T_ID = uint32_t>
    requires requires {
        { T::getTypeName() } -> std::same_as<std::string_view>;
    } && std::integral<T_ID>
    class ResourceId {
        FRIEND_RESOURCE_ID_GENERATOR;

    protected:
        const T_ID m_nId;
        const uint32_t m_nGen;

        ResourceId(
            T_ID nId,
            uint32_t nGen
        ):
            m_nId(nId),
            m_nGen(nGen)
        {
        }

    public:
        using ID = T_ID;

        inline T_ID getId() const {
            return m_nId;
        }

        inline uint32_t getGen() const {
            return m_nGen;
        }

        inline std::string toString() const {
            return fmt::format("{}Id: ({}, {})", T::getTypeName(), m_nId, m_nGen);
        }

        bool operator==(
            const ResourceId<T, T_ID>& other
        ) const {
            return m_nId == other.m_nId && m_nGen == other.m_nGen;
        }

        bool operator!=(
            const ResourceId<T, T_ID>& other
        ) const {
            return m_nId != other.m_nId || m_nGen != other.m_nGen;
        }
    };

    template <class T_RID>
    struct ResourceIdHasher {
        size_t operator()(
            const T_RID& id
        ) const noexcept {
            const size_t h1 = std::hash<typename T_RID::ID>{}(id.getId());
            const size_t h2 = std::hash<uint32_t>{}(id.getGen());
    
            return h1 ^ (h2 << 1);
        }
    };

    template <class T_RID>
    struct ResourceIdEqual {
        bool operator()(
            const T_RID& left,
            const T_RID& right
        ) const noexcept {
            return left == right;
        }
    };
}
