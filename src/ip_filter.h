//
// Created by sergio on 06.07.18.
//
#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include "addon_functions.h"
class ip_address {

public:

    explicit ip_address(std::vector<std::string> &vector);
    const uint get_ip_octet(int i) const;
    bool find_octets_in_ip(const size_t& octet) const;
    friend bool operator>(const ip_address& lhs,  const ip_address& rhs);
    std::string get_string();
    private:
    std::array<unsigned char , IP4_OCTETS_COUNT> ip;

};

class ip_addresses_pool {
public:
    using ip_pool_vector = std::vector<ip_address>;

    ip_pool_vector ip_pool{};

    explicit ip_addresses_pool() = default;


    void add_ip_address(std::vector<std::string> &&rhs);



    void sort_in_reverse_lexographic_order(ip_pool_vector&);

};


class ip_filter {
public:

    std::unique_ptr<ip_addresses_pool> pool_ptr;



    ip_filter() {
        pool_ptr = std::make_unique<ip_addresses_pool>();
    };


    void read(std::istream &in);

    void write(std::ostream &out);




};