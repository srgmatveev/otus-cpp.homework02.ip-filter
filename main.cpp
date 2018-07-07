#include <iostream>
#include <memory>
#include"version.h"
#include "ip_filter.h"



int main(int argc, char const* argv[]) {

  auto ip_f_ptr = std::make_unique<ip_filter>();

  ip_f_ptr->read(std::cin);
  ip_f_ptr->write(std::cout);

  return 0;

}