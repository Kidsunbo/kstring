#include <string>
#include <iostream>
#include <gtest/gtest.h>
#include "kstring.h"


TEST(construct, empty){
    kie::string s;
    ASSERT_EQ(s.to_std_string(), "");
    ASSERT_EQ(s.to_std_string_view(), "");
    ASSERT_STREQ(s.to_c_str(), "");
    ASSERT_EQ(s.empty(), true);
    ASSERT_EQ(s.is_full(), true);
    ASSERT_EQ(s.capacity(), 0);
    ASSERT_EQ(s.length(), 0);
}

TEST(construct, move){
    kie::string s = "dummy";
    kie::string ss = std::move(s);
    ASSERT_EQ(s.to_std_string(), "");
    ASSERT_EQ(s.to_std_string_view(), "");
    ASSERT_STREQ(s.to_c_str(), "");
    ASSERT_EQ(s.empty(), true);
    ASSERT_EQ(s.is_full(), true);
    ASSERT_EQ(s.capacity(), 0);
    ASSERT_EQ(s.length(), 0);

    ASSERT_EQ(ss.to_std_string(), "dummy");
    ASSERT_EQ(ss.to_std_string_view(), "dummy");
    ASSERT_EQ(ss.capacity(), 5);
    ASSERT_STREQ(ss.to_c_str(), "dummy");
    ASSERT_EQ(ss.empty(), false);
    ASSERT_EQ(ss.is_full(), false);
    ASSERT_EQ(ss.capacity(), 10);
    ASSERT_EQ(ss.length(), 5);
}

TEST(construct, copy){
    kie::string s = "dummy";
    kie::string ss = s;
    ASSERT_EQ(ss.to_std_string(), "dummy");
    ASSERT_EQ(ss.to_std_string_view(), "dummy");
    ASSERT_TRUE(ss.to_c_str() != s.to_c_str());
    ASSERT_EQ(ss.empty(), false);
    ASSERT_EQ(ss.is_full(), false);
    ASSERT_EQ(ss.capacity(), 10);
    ASSERT_EQ(ss.length(), 5);
}

TEST(append, empty){
    kie::string s = "dummy";
    ASSERT_FALSE(s.append(""));
    ASSERT_EQ(s, kie::string{"dummy"});
    ASSERT_FALSE(s.append(kie::string{}));
    ASSERT_EQ(s, kie::string{"dummy"});
    ASSERT_TRUE(s.append(" hello"));
    ASSERT_EQ(s, kie::string{"dummy hello"});
}