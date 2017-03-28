#ifndef SETONE_H_INCLUDED
#define SETONE_H_INCLUDED

#include <vector>
#include <string>
#include <iostream>

class SetOne {

private:
   void static num_to_bin(int, std::vector<bool>&);
   std::vector<int> static bits_to_n(std::vector<bool>, int);
   //std::vector<char> hex_vals;

public:
   static const int BASE64_DIGIT_SZ = 6;
   static const int HEX_DIGIT_SZ = 4;
   std::vector<char> static get_hex_values();
   std::vector<bool> static hex_string_to_bits(std::string);
   // std::vector<bool> base64_string_to_bits(const std::string&);
   std::string static bits_to_base64_string(std::vector<bool>&);

   void static check_equality(std::string, std::string);
   void static check_equality(std::vector<bool>, std::vector<bool>);

   std::vector<bool> static xor_against(std::vector<bool>, std::vector<bool>);
   std::string static bits_to_hex_string(std::vector<bool>);
   // review bits_to_sixes

   /*
   template<class T>
   static void check_equality(T itb, T ite, T iter){
      typename T i;
      for (i = itb; i != ite; ++i) {
         std::cout << *i;
      }
         //std::cout << s1 << std::endl;
         //std::cout << s2 << std::endl;
         std::cout << "equal? ";
         //(s1 == s2) ? std::cout <<"YES" : std::cout <<"NO";
         std::cout << std::endl;

   }
   */

   //void check_equality(const std::vector<bool>&, const std::vector<bool>&);
   // void check_equality(const std::string&, const std::string&);


};


#endif // SETONE_H_INCLUDED
