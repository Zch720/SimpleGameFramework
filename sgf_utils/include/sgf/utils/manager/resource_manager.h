#pragma once

#include <memory>
#include <type_traits>
#include <unordered_map>

#include <fmt/format.h>

#include "sgf/utils/exception/resource_not_found.h"
#include "sgf/utils/manager/resource.h"
#include "sgf/utils/manager/resource_id.h"
#include "sgf/utils/manager/resource_id_generator.h"

namespace sgf::utils {
    template <class T, class T_RID>
    requires std::is_class_v<T_RID> &&
        requires {
            typename T::Construct;
            typename T_RID::ID;
        } &&
        std::is_base_of_v<Resource, T> &&
        std::is_base_of_v<ResourceId<T, typename T_RID::ID>, T_RID>
    class ResourceManager {
    protected:
        std::unordered_map<
            T_RID,
            std::unique_ptr<T>,
            sgf::utils::ResourceIdHasher<T_RID>,
            sgf::utils::ResourceIdEqual<T_RID>
        > m_mapResources;
        ResourceIdGenerator<T, T_RID> m_oIdGenerator;

    public:
        bool isExist(
            const T_RID& rId
        ) const {
            return m_oIdGenerator.isValid(rId) &&
                m_mapResources.find(rId) != m_mapResources.end();
        }

        T& getRef(
            const T_RID& rId
        ) {
            if (!isExist(rId)) {
                throw ResourceNotFound(
                    fmt::format("Try to get {} with id {} from manager, but not found", T::getTypeName(), rId.toString())
                );
            }
            return *m_mapResources.at(rId);
        }

        const T& getRef(
            const T_RID& rId
        ) const {
            if (!isExist(rId)) {
                throw ResourceNotFound(
                    fmt::format("Try to get {} with id {} from manager, but not found", T::getTypeName(), rId.toString())
                );
            }
            return *m_mapResources.at(rId);
        }

        T_RID create(
            const typename T::Construct& rConstruct
        ) {
            T_RID id = m_oIdGenerator.getNewId();
            m_mapResources.insert(std::make_pair(id, std::unique_ptr<T>(new T(rConstruct))));
            return id;
        }

        void remove(
            const T_RID& rId
        ) {
            if (!isExist(rId)) {
                throw ResourceNotFound(
                    fmt::format("Try to remove {} with id {} in manager, but not found", T::getTypeName(), rId.toString())
                );
            }
            m_mapResources.erase(rId);
            m_oIdGenerator.removeId(rId);
        }

        void clear() {
            for (const std::pair<const T_RID, std::unique_ptr<T>>& rResource : m_mapResources) {
                m_oIdGenerator.removeId(rResource.first);
            }
            m_mapResources.clear();
        }
    };
}
