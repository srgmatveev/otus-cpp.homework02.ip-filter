//
// Created by sergio on 06.07.18.
//

#pragma once

#include <string>
#include <vector>

const auto IP4_OCTETS_COUNT = 4;
const auto IP_OCTETS_COUNTS_ERROR = "IP-address must have " + std::to_string(IP4_OCTETS_COUNT) + " octets";

std::vector<std::string> split(const std::string &, char );

