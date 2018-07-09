//
// Created by sergio on 02.07.18.
//

#include <gmock/gmock.h>
#include "ip_filter.h"



using namespace testing;

class IP_Filter_Test : public Test {

public:
    ip_filter ipFilter;
};




TEST_F(IP_Filter_Test, IP_Address_what_contain_correct_octets) {

    std::string testData{"47.15.15.12\n"};
    std::stringbuf str_buf(testData);
    std::istream in_stream(&str_buf);

    ipFilter.read(in_stream);
    ip_address &ip = *(ipFilter.pool_ptr->ip_pool.begin());


    ASSERT_THAT(ip.get_string(), Eq("47.15.15.12"));
}

TEST_F(IP_Filter_Test, IP_Addresses_which_containes_correct_octets) {

    std::string testData{"47.15.15.12\n"
                         "15.26.17.18\n"
                         "1.13.14.15\n"};

    std::stringbuf str_buf(testData);
    std::istream in_stream(&str_buf);

    std::vector<std::string> out_vec{"47.15.15.12",
                                     "15.26.17.18",
                                     "1.13.14.15"};


    ipFilter.read(in_stream);

    for ( auto i = 0; i < ipFilter.pool_ptr->ip_pool.size(); i++ ) {

        ASSERT_THAT(ipFilter.pool_ptr->ip_pool.at(i).get_string(), out_vec.at(i));

    }

}


TEST(IP_Address_Test, IP_Address_contain_wrong_char_octets) {

    std::vector<std::string> testData{"10","47","b","25"};
    ASSERT_THROW(ip_address ip_address(std::move(testData)),std::invalid_argument);
}