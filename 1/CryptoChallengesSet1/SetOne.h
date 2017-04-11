#ifndef SETONE_H_INCLUDED
#define SETONE_H_INCLUDED

#include <vector>
#include <string>
#include <iostream>
#include <map>

class SetOne {

private:
   //std::vector<char> hex_vals; function created, find how to make static, check how the if will work
public:
   static const int BASE64_DIGIT_SZ = 6;
   static const int HEX_QUART_DIGIT_SZ = 4;
   static const int HEX_OCTET_DIGIT_SZ = 8;

   // challenge 1
   std::string static hex_to_base64(std::string hex_string);
   // challenge 2
   std::string static xor_hex_strings(std::string first_hex, std::string second_hex);
   // challenge 3
   void static single_byte_xor(std::string, std::string &, std::string &, double &, const std::string &);
   // challenge 4
   void static multi_line_single_byte_xor(std::string, std::string &, std::string &, double &, const std::string &);


   /*
   / binary/numeric conversion functions
   */

   // Takes number, converts it to bits, then stores it in the boolean vector
   void static num_to_bin(int, std::vector<bool>&, int);
   // Gathers n bits from the boolean vector, and converts them to a number, then stores all numbers in a number vector
   void static bin_to_num(std::vector<bool>, std::vector<int>&, int);

   /*
   / Table and map generation functions
   */

   // Returns an array of hex values from 0 to f in a char vector (in order)
   // note: since we sometimes need the char value given an int, this needs some work
   std::map<char, int> static hex_num_map();
   std::map<int, char> static num_hex_map();
   // Returns a map of character frequencies
   std::map<std::string, double> static gen_word_freq_table(const std::string &);

   /*
   / Type to bits conversion
   */

   // Converts a hex string into bits, storing the bits in a boolean vector
   std::vector<bool> static hex_string_to_bits(std::string);
   // Converts a char string into bits, storing the bits in a boolean vector
   std::vector<bool> static bit_string_to_bits(std::string);
   // Given ASCII string, convert to bit vector
   std::vector<bool> static ascii_string_to_bits(std::string);


   /*
   / Bits to type conversion
   */

   // Given a boolean vector, convert it to a string of hex chars
   std::string static bits_to_hex_string(std::vector<bool>);
   // Given a vector of bits, return a string of base64 chars
   std::string static bits_to_base64_string(std::vector<bool>&);
   // Given a vector of bits, return a string of ascii chars
   std::string static bits_to_ascii_string(std::vector<bool>&);


   /*
   / Output functions
   */

   // Check whether two strings/bit vector are equal or not
   void static check_equality(std::string, std::string);
   void static check_equality(std::vector<bool>, std::vector<bool>);


   /*
   / Other functions
   */

   // Given two boolean vectors of equal size, xor them and return the resultant boolean vector
   std::vector<bool> static xor_against(std::vector<bool> main_vec, std::vector<bool> key);

   double static calc_word_frequency(const std::string&, const std::map<std::string, double> &);//,
                                     //const std::map<std::string, double> &);

   std::string static num_to_bit_string(int);

   // not used yet
   std::string static bit_string_pattern(int, std::string);
   std::vector<bool> static bit_pattern(std::vector<bool>::size_type, std::vector<bool>);

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
