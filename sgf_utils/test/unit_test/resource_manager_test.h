#include <gtest/gtest.h>

#include "sgf/utils/manager/resource_id.h"
#include "sgf/utils/manager/resource_manager.h"

class ManagerSuite: public testing::Test {
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
    };
    using FooId = sgf::utils::ResourceId<Foo>;
};

TEST_F(ManagerSuite, CreateManager) {
    sgf::utils::ResourceManager<Foo, FooId>();
}

TEST_F(ManagerSuite, AddObject) {
    sgf::utils::ResourceManager<Foo, FooId> oManager;

    FooId oId = oManager.create(Foo::Construct { .nNum = 10 });
    Foo& rObj = oManager.getRef(oId);


    ASSERT_TRUE(oManager.isExist(oId));
    ASSERT_EQ(10, rObj.getNum());
}

TEST_F(ManagerSuite, AddTwoObject) {
    sgf::utils::ResourceManager<Foo, FooId> oManager;

    FooId oId1 = oManager.create(Foo::Construct { .nNum = 10 });
    FooId oId2 = oManager.create(Foo::Construct { .nNum = 20 });
    Foo& rObj1 = oManager.getRef(oId1);
    Foo& rObj2 = oManager.getRef(oId2);

    ASSERT_TRUE(oManager.isExist(oId1));
    ASSERT_EQ(10, rObj1.getNum());
    ASSERT_TRUE(oManager.isExist(oId2));
    ASSERT_EQ(20, rObj2.getNum());
}

TEST_F(ManagerSuite, RemoveObject) {
    sgf::utils::ResourceManager<Foo, FooId> oManager;
    FooId oId = oManager.create(Foo::Construct { .nNum = 10 });

    oManager.remove(oId);

    ASSERT_FALSE(oManager.isExist(oId));
}

TEST_F(ManagerSuite, TwoObjectRemoveFirst) {
    sgf::utils::ResourceManager<Foo, FooId> oManager;

    FooId oId1 = oManager.create(Foo::Construct { .nNum = 10 });
    FooId oId2 = oManager.create(Foo::Construct { .nNum = 20 });

    oManager.remove(oId1);

    ASSERT_FALSE(oManager.isExist(oId1));
    ASSERT_TRUE(oManager.isExist(oId2));
}

TEST_F(ManagerSuite, TwoObjectRemoveBoth) {
    sgf::utils::ResourceManager<Foo, FooId> oManager;

    FooId oId1 = oManager.create(Foo::Construct { .nNum = 10 });
    FooId oId2 = oManager.create(Foo::Construct { .nNum = 20 });

    oManager.remove(oId1);
    oManager.remove(oId2);

    ASSERT_FALSE(oManager.isExist(oId1));
    ASSERT_FALSE(oManager.isExist(oId2));
}

TEST_F(ManagerSuite, GetRemovedObjectShouldThrowException) {
    sgf::utils::ResourceManager<Foo, FooId> oManager;
    FooId oId = oManager.create(Foo::Construct { .nNum = 10 });

    oManager.remove(oId);

    ASSERT_THROW(oManager.getRef(oId), sgf::utils::ResourceNotFound);
}

TEST_F(ManagerSuite, ClearObject) {
    sgf::utils::ResourceManager<Foo, FooId> oManager;
    FooId oId = oManager.create(Foo::Construct { .nNum = 10 });

    oManager.clear();

    ASSERT_FALSE(oManager.isExist(oId));
}

TEST_F(ManagerSuite, ClearMultipleObject) {
    sgf::utils::ResourceManager<Foo, FooId> oManager;

    FooId oId1 = oManager.create(Foo::Construct { .nNum = 10 });
    FooId oId2 = oManager.create(Foo::Construct { .nNum = 20 });
    FooId oId3 = oManager.create(Foo::Construct { .nNum = 30 });

    oManager.clear();

    ASSERT_FALSE(oManager.isExist(oId1));
    ASSERT_FALSE(oManager.isExist(oId2));
    ASSERT_FALSE(oManager.isExist(oId3));
}
