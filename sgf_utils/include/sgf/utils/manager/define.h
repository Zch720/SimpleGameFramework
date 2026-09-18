#pragma once

#include <concepts>
#include <stdint.h>
#include <string_view>
#include <type_traits>

namespace sgf::utils {
    class Resource;

    template <class T, typename T_ID>
    requires requires {
        { T::getTypeName() } -> std::same_as<std::string_view>;
    } && std::integral<T_ID>
    class ResourceId;

    template <class T, typename T_RID>
    requires std::is_class_v<T_RID> &&
        requires {
            typename T_RID::ID;
        } &&
        std::is_base_of_v<Resource, T> &&
        std::is_base_of_v<ResourceId<T, typename T_RID::ID>, T_RID>
    class ResourceIdGenerator;

    template <class T, class T_RID>
    requires std::is_class_v<T_RID> &&
        requires {
            typename T::Construct;
            typename T_RID::ID;
        } &&
        std::is_base_of_v<Resource, T> &&
        std::is_base_of_v<ResourceId<T, typename T_RID::ID>, T_RID>
    class ResourceManager;
}

#define FRIEND_RESOURCE_ID_GENERATOR                                    \
    template <class RIDG_T, class RIDG_T_RID>                           \
    requires std::is_class_v<RIDG_T_RID> &&                             \
        requires {                                                      \
            typename RIDG_T_RID::ID;                                    \
        } &&                                                            \
        std::is_base_of_v<sgf::utils::Resource, RIDG_T> &&              \
        std::is_base_of_v<                                              \
            sgf::utils::ResourceId<RIDG_T, typename RIDG_T_RID::ID>,    \
            RIDG_T_RID                                                  \
        >                                                               \
    friend class sgf::utils::ResourceIdGenerator;

#define FRIEND_RESOURCE_MANAGER                                     \
    template <class RM_T, class RM_T_RID>                           \
    requires std::is_class_v<RM_T_RID> &&                           \
        requires {                                                  \
            typename RM_T::Construct;                               \
            typename RM_T_RID::ID;                                  \
        } &&                                                        \
        std::is_base_of_v<sgf::utils::Resource, RM_T> &&            \
        std::is_base_of_v<                                          \
            sgf::utils::ResourceId<RM_T, typename RM_T_RID::ID>,    \
            RM_T_RID                                                \
        >                                                           \
    friend class sgf::utils::ResourceManager;
