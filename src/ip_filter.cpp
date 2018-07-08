//
// Created by sergio on 06.07.18.
//
#include <iostream>
#include <algorithm>
#include <iterator>
#include "ip_filter.h"
#include "addon_functions.h"


ip_address::ip_address(std::vector<std::string> &&vector) {

    auto &&tmp_string_vec = std::move(vector);

    if (tmp_string_vec.size() != IP4_OCTETS_COUNT)
        throw std::invalid_argument(IP_OCTETS_COUNTS_ERROR);


    std::transform(tmp_string_vec.begin(), tmp_string_vec.end(),
                   ip.begin(),
                   [](const auto &tmp) {

                   unsigned long tmp_octet{0};
                       try {
                           tmp_octet = std::stoul(tmp);
                       } catch (std::exception &e) {

                           throw std::invalid_argument("IP-address octets must be from digits in [0..255]");
                       }
                       if (tmp_octet > 255) throw std::invalid_argument("IP-address octets must be in [0..255]");
                       return tmp_octet;
                   }
    );


}

const uint ip_address::get_ip_octet(int i) const {

    return static_cast<uint>(ip.at(static_cast<unsigned long>(i)));
}


const std::string ip_address::get_string() {
    std::string str = std::to_string(ip.at(0))+"."+ std::to_string(ip.at(1))+
                      "."+std::to_string(ip.at(2))+"."+std::to_string(ip.at(3));
    return str;
}

std::ostream &operator<<(std::ostream &out, const ip_address &ip_address) {
    for ( auto i = 0; i < IP4_OCTETS_COUNT; i++ ) {

        std::cout << ip_address.get_ip_octet(i);

        if (i < (IP4_OCTETS_COUNT - 1)) {
            std::cout << ".";
        }

    }

}


bool operator>(const ip_address &lhs, const ip_address &rhs) {

    return lhs.ip > rhs.ip;
}

bool ip_address::find_octets_in_ip(size_t &&octet) const {


    for ( auto &i : ip ) {
        if (i == octet) { return true; }

    }
    return false;
}


void ip_filter::read(std::istream &in) {
    try {

        for ( std::string line; std::getline(in, line); ) {
            std::vector<std::string> v = split(line, '\t');

            this->pool_ptr->add_ip_address(std::move(split(v.at(0), '.')));

        }
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }


}


void ip_filter::write(std::ostream &out) {


    this->pool_ptr->sort_in_reverse_lexographic_order(this->pool_ptr->ip_pool);

    std::copy(pool_ptr->ip_pool.cbegin(), pool_ptr->ip_pool.cend(),
              std::ostream_iterator<ip_address>(std::cout, "\n")
    );


    std::copy_if(pool_ptr->ip_pool.cbegin(), pool_ptr->ip_pool.cend(),
                 std::ostream_iterator<ip_address>(std::cout, "\n"),
                 [](const ip_address &tmp_addr) {

                     return (tmp_addr.get_ip_octet(0) == 1);
                 }
    );

    std::copy_if(pool_ptr->ip_pool.cbegin(), pool_ptr->ip_pool.cend(),
                 std::ostream_iterator<ip_address>(std::cout, "\n"),
                 [](const ip_address &tmp_addr) {

                     return (tmp_addr.get_ip_octet(0) == 46) and (tmp_addr.get_ip_octet(1) == 70);
                 }
    );

    std::copy_if(pool_ptr->ip_pool.cbegin(), pool_ptr->ip_pool.cend(),
                 std::ostream_iterator<ip_address>(std::cout, "\n"),
                 [](const ip_address &tmp_addr) {
                     return tmp_addr.find_octets_in_ip(46);
                 }
    );

}


void ip_addresses_pool::add_ip_address(std::vector<std::string> &&rhs) {


    auto &&tmp_vec = std::move(rhs);

    if (tmp_vec.size() != IP4_OCTETS_COUNT)
        throw std::invalid_argument(IP_OCTETS_COUNTS_ERROR);


    ip_pool.emplace_back(ip_address(std::move(tmp_vec)));


}

void ip_addresses_pool::sort_in_reverse_lexographic_order(ip_addresses_pool::ip_pool_vector &pool_vector) {

    std::sort(pool_vector.begin(), pool_vector.end(), std::greater<>());

}


