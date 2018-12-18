//
// Created by dguco on 18-10-18.
//

#include <iostream>
#include <tuple>
#include <vector>
#include "exhiredis/rstl/rmap.hpp"
#include "exhiredis/rstl/rscript.hpp"
#include "exhiredis/concurrent/thread_pool.hpp"

using namespace std;
using namespace exhiredis;

template<class T = int>
class Children
{
public:

    T
    Value()
    {
        return value;
    }
private:
    T value;
};

class Test: public std::enable_shared_from_this<Test>
{
public:
    Test()
    {
    }
    shared_ptr<Test> getPtr()
    {
        return shared_from_this();
    }
};

class Test1
{
public:
    Test1()
    {

    }

    Test1(const Test1 &test)
    {
        printf("Test1 copy\n");
    }

    Test1(const Test1 &&test)
    {
        printf("Test1 move\n");
    }

    Test1 &operator=(const Test1 &test)
    {
        printf("Test1 operator=\n");
    }
};

class Test2: public Test
{

};

future<int> &&
getFuture()
{
    return async([]
                 { return 0; });
}

void
testStr()
{
    char *str = "2\0e";
    string string1 = str;
    string string2;
    string2.assign(str, 3);
    printf("name1 = %s,len = %d\n", string1.c_str(), string1.length());
    printf("name2 = %s,len = %d\n", string2.c_str(), string2.length());
    const char *str1 = string2.c_str();
    int i = 0;
    printf("=========================\n");
    while (i < string2.length()) {
        printf("%c", str1[i]);
        i++;
    }
    printf("\n");
}

void
testMap(shared_ptr<CRedisConnection> conn)
{
//    RMap<RInt, RInt> *rMap = new RMap<RInt, RInt>("TestMap", conn);
//    const RInt key = RInt(1);
//    const RInt value = RInt(10);
//    rMap->Put(key, value);
//    shared_ptr<RInt> res = rMap->Get(key);
//    printf("-------------------\n");
//    int intva = res->Value();
//    printf("res  = %d \n", intva);
}

int
main()
{
    vector<Test1> vector1;
    vector1.push_back(std::move(Test1()));
    vector1.push_back(std::move(Test1()));
    vector1.push_back(std::move(Test1()));

    for (auto it : vector1) {

    }

    CLog::CreateInstance();
    shared_ptr<CRedisConnection> conn = make_shared<CRedisConnection>();
    conn->Connect("127.0.0.1", 6379);
    //	testStr( );
    testMap(conn);
    RScript *rScript = new RScript(conn);
    string cmd = "if (redis.call('exists', KEYS[1]) == 0) then " \
        "redis.call('hset', KEYS[1], ARGV[2], 1); " \
        "redis.call('pexpire', KEYS[1], ARGV[1]); " \
        "return true; " \
        "end; " \
        "if (redis.call('hexists', KEYS[1], ARGV[2]) == 1) then " \
        "redis.call('hincrby', KEYS[1], ARGV[2], 1); " \
        "redis.call('pexpire', KEYS[1], ARGV[1]); " \
        "return true; " \
        "end; " \
        "return redis.call('pttl', KEYS[1]);";
    auto res = rScript->EvalReturnInt(cmd.c_str(), {"TestLock:lock1"}, {"100", "3132"});
    atomic_bool aBool;
    aBool.exchange(1);
    printf("res = %ld\n", *(res.get()));
}