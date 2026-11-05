#include <gtest/gtest.h>

#include "sgf/utils/manager/resource_manager.h"
#include "sgf/utils/manager/resource_pair.h"

class ResourcePairSuite: public testing::Test {
protected:
    class Foo: public sgf::utils::Resource {
        FRIEND_RESOURCE_MANAGER;

    public:
        struct Construct {
            int nNum;
        };

        static std::string_view getTypeName() { return "Foo"; }

    private:
        int m_nNum;

    protected:
        Foo(
            const Construct& construct
        ):
            m_nNum(construct.nNum)
        {
        }

    public:
        inline int getNum() const {
            return m_nNum;
        }

        inline void setNum(
            int nNum
        ) {
            m_nNum = nNum;
        }

        inline bool operator==(
            const Foo& rOther
        ) const {
            return m_nNum == rOther.m_nNum;
        }

        inline bool operator!=(
            const Foo& rOther
        ) const {
            return m_nNum != rOther.m_nNum;
        }
    };
    using FooId = sgf::utils::ResourceId<Foo>;
};

TEST_F(ResourcePairSuite, CreatePair) {
    sgf::utils::ResourceManager<Foo, FooId> oManager;
    FooId oId = oManager.create(Foo::Construct { .nNum = 1 });

    sgf::utils::ResourcePair<FooId, Foo> oPair(oId, oManager.getRef(oId));
}

TEST_F(ResourcePairSuite, GetIdAndValue) {
    sgf::utils::ResourceManager<Foo, FooId> oManager;
    FooId oId = oManager.create(Foo::Construct { .nNum = 1 });

    sgf::utils::ResourcePair<FooId, Foo> oPair(oId, oManager.getRef(oId));

    ASSERT_EQ(oId, oPair.id());
    ASSERT_EQ(oManager.getRef(oId), oPair.value());
}

TEST_F(ResourcePairSuite, CreatePairWithConstId) {
    sgf::utils::ResourceManager<Foo, FooId> oManager;
    FooId oId = oManager.create(Foo::Construct { .nNum = 1 });

    sgf::utils::ResourcePair<const FooId, Foo> oPair(oId, oManager.getRef(oId));

    ASSERT_EQ(oId, oPair.id());
    ASSERT_EQ(oManager.getRef(oId), oPair.value());
}

TEST_F(ResourcePairSuite, CreatePairWithConstIdAndConstValue) {
    sgf::utils::ResourceManager<Foo, FooId> oManager;
    FooId oId = oManager.create(Foo::Construct { .nNum = 1 });

    sgf::utils::ResourcePair<const FooId, const Foo> oPair(oId, oManager.getRef(oId));

    ASSERT_EQ(oId, oPair.id());
    ASSERT_EQ(oManager.getRef(oId), oPair.value());
}

TEST_F(ResourcePairSuite, CreateConstPairWithConstIdAndConstValue) {
    sgf::utils::ResourceManager<Foo, FooId> oManager;
    FooId oId = oManager.create(Foo::Construct { .nNum = 1 });

    const sgf::utils::ResourcePair<const FooId, const Foo> oPair(oId, oManager.getRef(oId));

    ASSERT_EQ(oId, oPair.id());
    ASSERT_EQ(oManager.getRef(oId), oPair.value());
}
