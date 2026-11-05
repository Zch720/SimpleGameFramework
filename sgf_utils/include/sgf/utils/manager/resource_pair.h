#pragma once

#include <type_traits>

#include "sgf/utils/manager/resource.h"
#include "sgf/utils/manager/resource_id.h"

namespace sgf::utils {
    template <class T_RID, class T>
    requires std::is_class_v<T_RID> &&
        requires {
            typename T_RID::ID;
        } &&
        std::is_base_of_v<Resource, std::remove_cvref_t<T>> &&
        std::is_base_of_v<ResourceId<std::remove_cvref_t<T>, typename T_RID::ID>, std::remove_cvref_t<T_RID>>
    class ResourcePair {
    private:
        T_RID& m_rId;
        T& m_rValue;

    public:
        ResourcePair(
            T_RID& rId,
            T& rValue
        ):
            m_rId(rId),
            m_rValue(rValue)
        {
        }

        inline const T_RID& id() const {
            return m_rId;
        }

        inline T& value() {
            return m_rValue;
        }

        inline const T& value() const {
            return m_rValue;
        }
    };
}
