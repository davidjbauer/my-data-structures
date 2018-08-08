#include "LinkedList.h"
#include "HashMap.h"
#include "BST.h"
#include "gtest/gtest.h"
#include <unordered_set>

TEST(BST_Test,BST_sanity)
{
    auto bst = std::make_unique<BST>();
}

TEST(BST_Test,insert_sanity)
{
    auto bst = std::make_unique<BST>();
    bst->insert(3);
    bst->insert(100);
    bst->insert(42);
    EXPECT_EQ(bst->nodes,3);
}

TEST(BST_Test,insert_find)
{
    auto bst = std::make_unique<BST>();
    bst->insert(3);
    bst->insert(100);
    bst->insert(42);
    EXPECT_EQ(bst->find(3),true);
    EXPECT_EQ(bst->find(42),true);
    EXPECT_EQ(bst->find(100),true);
    EXPECT_EQ(bst->find(420),false);
    EXPECT_EQ(bst->find(69),false);
}


// TEST(IntHashMap_Test,IntHashMap_sanity)
// {
//     auto hash_f = new IntHashFunction();
//     auto hash = std::make_unique<IntHashMap<IntHashFunction>>(*hash_f);
//     EXPECT_EQ(hash->buckets,5);
//     EXPECT_EQ(hash->filled,0);
//     delete hash_f;
// }

// TEST(IntHashMap_Test,add_sanity)
// {
//     struct MyHash {
//         int operator()(const int &key) const
//         {
//             return (int)std::hash<int>{}(key);
//         }
//     };
//     auto hash_f = new MyHash();
//     auto hash = new IntHashMap<MyHash>(*hash_f);
//     EXPECT_EQ(hash->buckets,5);
//     EXPECT_EQ(hash->filled,0);
//     hash->add(4,6);
//     EXPECT_EQ(hash->filled,1);
//     hash->add(32,69);
//     EXPECT_EQ(hash->filled,2);
//     delete hash_f;
//     delete hash;
// }



TEST(LinkedList_int_Test,push_front_)
{
    auto ll = std::make_unique<LinkedList<int>>();
    ll->push_front(3);
    EXPECT_EQ(ll->length,1);
    ll->push_front(6);
    EXPECT_EQ(ll->length,2);
    EXPECT_EQ(ll->head->value,6);
    EXPECT_EQ(ll->head->next->value,3);
    EXPECT_EQ(ll->head->next->next,nullptr);
}

TEST(LinkedList_int_Test,push_back_)
{
    auto ll = std::make_unique<LinkedList<int>>();
    ll->push_front(3);
    EXPECT_EQ(ll->length,1);
    ll->push_back(6);
    EXPECT_EQ(ll->length,2);
    EXPECT_EQ(ll->head->value,3);
    EXPECT_EQ(ll->head->next->value,6);
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
    EXPECT_EQ(ll->head->value,6);
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

TEST(LinkedList_int_Test,copy_constructor_)
{
    LinkedList<int>* ll = new LinkedList<int>;
    ll->push_front(4);
    ll->push_front(3);
    ll->push_front(2);
    ll->push_front(1);
    auto mm = new LinkedList<int>(ll);
    auto a = mm->pop_front();
    auto b = mm->pop_front();
    EXPECT_EQ(a,1);
    EXPECT_EQ(b,2);
    delete ll;
    delete mm;
}

TEST(LinkedList_int_Test,sorted_)
{
    LinkedList<int>* ll = new LinkedList<int>;
    ll->push_front(2);
    ll->push_front(5);
    ll->push_front(3);
    ll->push_front(1);
    ll->push_front(6);
    //ll->push_front(1);
    //ll->push_front(1);
    //ll->push_front(2);
    //ll->push_front(1045);
    auto mm = ll->sorted();
    EXPECT_EQ(mm->pop_front(),1);
    EXPECT_EQ(mm->pop_front(),2);
    EXPECT_EQ(mm->pop_front(),3);
    EXPECT_EQ(mm->pop_front(),5);
    EXPECT_EQ(mm->pop_front(),6);
    // EXPECT_EQ(mm->pop_front(),2);
    // EXPECT_EQ(mm->pop_front(),6);
    // EXPECT_EQ(mm->pop_front(),32);
    // EXPECT_EQ(mm->pop_front(),1045);
    delete ll;
    delete mm;
}

TEST(LinkedList_int_Test,sorted_print)
{
    LinkedList<int>* ll = new LinkedList<int>;
    ll->push_front(2);
    ll->push_front(5);
    ll->push_front(3);
    ll->push_front(1);
    ll->push_front(6);
    ll->print();
    auto mm = ll->sorted();
    mm->print();
    // EXPECT_EQ(mm->pop_front(),2);
    // EXPECT_EQ(mm->pop_front(),6);
    // EXPECT_EQ(mm->pop_front(),32);
    // EXPECT_EQ(mm->pop_front(),1045);
    delete ll;
    delete mm;
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}