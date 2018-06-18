#include "LinkedList.h"
#include "gtest/gtest.h"

TEST(LinkedList_int_Test,push_front_)
{
    auto ll = std::make_unique<LinkedList<int>>();
    ll->push_front(3);
    EXPECT_EQ(ll->length,1);
    ll->push_front(6);
    EXPECT_EQ(ll->length,2);
    EXPECT_EQ(ll->head->data,6);
    EXPECT_EQ(ll->head->next->data,3);
    EXPECT_EQ(ll->head->next->next,nullptr);
}

TEST(LinkedList_int_Test,push_back_)
{
    auto ll = std::make_unique<LinkedList<int>>();
    ll->push_front(3);
    EXPECT_EQ(ll->length,1);
    ll->push_back(6);
    EXPECT_EQ(ll->length,2);
    EXPECT_EQ(ll->head->data,3);
    EXPECT_EQ(ll->head->next->data,6);
    EXPECT_EQ(ll->head->next->next,nullptr);
}

TEST(LinkedList_int_Test,pop_front_)
{
    auto ll = std::make_unique<LinkedList<int>>();
    ll->push_front(6);
    ll->push_front(7);
    ll->push_front(8);
    auto val = ll->pop_front();
    EXPECT_EQ(val,8);
    val = ll->pop_front();
    EXPECT_EQ(val,7);
    EXPECT_EQ(ll->head->data,6);
}

TEST(LinkedList_int_Test,empty_)
{
    auto ll = std::make_unique<LinkedList<int>>();
    EXPECT_EQ(ll->empty(),true);
    ll->push_front(3);
    EXPECT_EQ(ll->empty(),false);
    ll->pop_front();
    EXPECT_EQ(ll->empty(),true);
}

TEST(LinkedList_int_Test,clear_)
{
    auto ll = std::make_unique<LinkedList<int>>();
    ll->push_front(4);
    ll->push_front(3);
    ll->push_front(2);
    ll->push_front(1);
    ll->clear();
    EXPECT_EQ(ll->empty(),true);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}