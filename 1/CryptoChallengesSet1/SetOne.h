#ifndef SETONE_H_INCLUDED
#define SETONE_H_INCLUDED

#include <vector>
#include <string>
#include <iostream>

class SetOne {

private:
   // Takes number, converts it to bits, then stores it in the boolean vector
   void static num_to_bin(int, std::vector<bool>&);
   // Gathers n bits from the boolean vector, and converts them to a number, then stores all numbers in a number vector
   std::vector<int> static bin_to_num(std::vector<bool>, int);

   //std::vector<char> hex_vals; function created, find how to make static, check how the if will work

public:
   static const int BASE64_DIGIT_SZ = 6;
   static const int HEX_QUART_DIGIT_SZ = 4;
   static const int HEX_OCTET_DIGIT_SZ = 8;

   // Returns an array of hex values from 0 to f in a char array (in order)
   std::vector<char> static get_hex_values();
   // Converts a hex string into bits, storing the bits in a boolean array
   std::vector<bool> static hex_string_to_bits(std::string);

   // Given a boolean vector, convert it to a string of hex chars
   std::string static bits_to_hex_string(std::vector<bool>);
   // Given a vector of bits, return a string of base64 chars
   std::string static bits_to_base64_string(std::vector<bool>&);

   // Check whether two strings/bit vector are equal or not
   void static check_equality(std::string, std::string);
   void static check_equality(std::vector<bool>, std::vector<bool>);

   // Given two boolean vectors of equal size, xor them and return the resultant boolean vector
   std::vector<bool> static xor_against(std::vector<bool>, std::vector<bool>);

   // review bits_to_sixes


   // std::vector<bool> base64_string_to_bits(const std::string&);
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

};


#endif // SETONE_H_INCLUDED
