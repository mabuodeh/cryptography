#include "SetOne.h"
#include <iostream>
#include <fstream>

const std::string DIR = "text_files/";

int main () {

   // Test for challenge 1
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

   // test for challenge 3
   /*
   std::string given = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

   std::vector<bool> bits = SetOne::hex_string_to_bits(given);
   std::vector<char> hex_vals = SetOne::get_hex_values();
   std::string final_sentence;
   double final_freq = 0.0;
   std::string final_key;
   for (int i = 0; i < 127; ++i) {
   //   int i = 0x58;
      std::string char_bits_string = SetOne::num_to_bit_string(i);
      std::vector<bool> char_bits = SetOne::bit_string_to_bit_vec(char_bits_string);
      std::vector<bool> bit_pattern = SetOne::bit_pattern(bits.size()/8, char_bits);
      std::vector<bool> xor_bits = SetOne::xor_against(bits, bit_pattern);
      // std::cout << (SetOne::bits_to_base64_string(xor_bits)) << std::endl;
      std::cout << std::endl << "Key: ";
      for (std::vector<bool>::iterator it = char_bits.begin(); it != char_bits.end(); ++it)
         std::cout << *it;
      std::string gen_sentence = SetOne::bits_to_ascii_string(xor_bits);
      std::cout << std::endl << "Value: " << gen_sentence << std::endl;

      double temp_freq = SetOne::calc_word_frequency(gen_sentence);
      std::cout << "temp_freq: " << temp_freq;
      std::cout << std::endl;

      if (temp_freq > final_freq) {
         final_freq = temp_freq;
         final_sentence = gen_sentence;
         final_key = char_bits_string;
      }
   }
   std::cout << std::endl << std::endl << "Final key and value: "
      << final_key << std::endl << final_sentence << std::endl
      << "frequency value: " << final_freq << std::endl;
   */
   /*
   // Test for challenge 4
   std::string file = DIR + "4.txt";
   std::ifstream fin(file.c_str());
   std::string temp;

   std::vector<char> hex_vals = SetOne::get_hex_values();

   std::string final_sentence;
   double final_freq = 0.0;
   std::string final_key;

   while(fin >> temp) {
      std::vector<bool> bits = SetOne::hex_string_to_bits(temp);

      for (int i = 0; i < 127; ++i) {
         // Take hex string and convert it to a vector of bits:
         std::string char_bits_string = SetOne::num_to_bit_string(i);
         std::vector<bool> char_bits = SetOne::bit_string_to_bit_vec(char_bits_string);

         // Create a vector bit pattern
         std::vector<bool> bit_pattern = SetOne::bit_pattern(bits.size()/8, char_bits);

         // XOR two equally sized vectors of bits
         std::vector<bool> xor_bits = SetOne::xor_against(bits, bit_pattern);

         // Printing (unnecessary)
         // std::cout << std::endl << "Key: ";
         // for (std::vector<bool>::iterator it = char_bits.begin(); it != char_bits.end(); ++it)
         //   std::cout << *it;
         // std::cout << std::endl << "Value: " << gen_sentence << std::endl;
         // std::cout << "temp_freq: " << temp_freq;
         // std::cout << std::endl;

         // Convert vector of bits to an ASCII string
         std::string gen_sentence = SetOne::bits_to_ascii_string(xor_bits);
         // Get value of word frequency of ASCII string from a word frequency list
         double temp_freq = SetOne::calc_word_frequency(gen_sentence);

         // Store sentence, key, and frequency of the most relevant sentence
         if (temp_freq > final_freq) {
            final_freq = temp_freq;
            final_sentence = gen_sentence;
            final_key = char_bits_string;
         }
      }
   }
   // Print final key, value, and frequency
   std::cout
      << "Final key and value: "
      << std::endl << final_key
      << std::endl << final_sentence
      << "Frequency value: "
      << final_freq << std::endl;
   */

   return 0;
}
