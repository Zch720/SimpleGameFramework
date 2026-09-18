#pragma once

#include <queue>
#include <vector>

#include "sgf/utils/manager/resource_id.h"

namespace sgf::utils {
    template <class T, class T_RID>
    requires std::is_class_v<T_RID> &&
        requires {
            typename T_RID::ID;
        } &&
        std::is_base_of_v<Resource, T> &&
        std::is_base_of_v<ResourceId<T, typename T_RID::ID>, T_RID>
    class ResourceIdGenerator {
    private:
        std::queue<typename T_RID::ID> m_queReleased = {};
        std::vector<uint32_t> m_vecGeneration = { 0 };

    public:
        bool isValid(const T_RID& rId) const {
            return rId.getId() != 0 &&
                   rId.getId() < m_vecGeneration.size() &&
                   rId.getGen() == m_vecGeneration[rId.getId()];
        }

        T_RID getNewId() {
            if (m_queReleased.empty()) {
                m_vecGeneration.push_back(1);
                return T_RID((typename T_RID::ID)(m_vecGeneration.size()) - 1, 1);
            } else {
                uint32_t id = m_queReleased.front();
                m_queReleased.pop();
                return T_RID(id, m_vecGeneration[id]);
            }
        }

        bool removeId(const T_RID& rId) {
            if (!isValid(rId)) {
                return false;
            }
            m_queReleased.push(rId.getId());
            ++m_vecGeneration[rId.getId()];
            return true;
        }
    };
}
