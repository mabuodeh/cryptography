#include "SetOne.h"
#include <iostream>

int main () {
   // test for challenge 1
   /*
   std::string given = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
   std::string output = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

   std::vector<bool> hex_bits = SetOne::hex_string_to_bits(given);
   std::string bits_to_base64 = SetOne::bits_to_base64_string(hex_bits);
   SetOne::check_equality(bits_to_base64, output);
   */
   // test for challenge 2
   /*
   std::string first_hex = "1c0111001f010100061a024b53535009181c";
   std::string second_hex = "686974207468652062756c6c277320657965";
   std::string output = "746865206b696420646f6e277420706c6179";

   std::vector<bool> first_bits = SetOne::hex_string_to_bits(first_hex);
   std::vector<bool> second_bits = SetOne::hex_string_to_bits(second_hex);

   std::vector<bool> xor_bits = SetOne::xor_against(first_bits, second_bits);
   std::string xor_string = SetOne::bits_to_hex_string(xor_bits);

   SetOne::check_equality(xor_string, output);
   */

   return 0;
}
