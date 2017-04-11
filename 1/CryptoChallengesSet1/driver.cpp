#include "SetOne.h"
#include <iostream>
#include <fstream>
#include <algorithm>

const std::string DIR = "text_files/";

int main () {

   // Test for challenge 1

   std::string given = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
   std::string output = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

   std::string base64_string = SetOne::hex_to_base64(given);

   std::cout << "Challenge 1" << std::endl;
   SetOne::check_equality(base64_string, output);
   std::cout << std::endl << std::endl;


   // test for challenge 2

   std::string first_hex = "1c0111001f010100061a024b53535009181c";
   std::string second_hex = "686974207468652062756c6c277320657965";
   std::string output_2 = "746865206b696420646f6e277420706c6179";

   std::string xor_string(SetOne::xor_hex_strings(first_hex, second_hex));
/*
   std::vector<bool> first_bits = SetOne::hex_string_to_bits(first_hex);
   std::vector<bool> second_bits = SetOne::hex_string_to_bits(second_hex);

   std::vector<bool> xor_bits = SetOne::xor_against(first_bits, second_bits);
   std::string xor_string = SetOne::bits_to_hex_string(xor_bits);
*/
   std::cout << "Challenge 2" << std::endl;
   SetOne::check_equality(xor_string, output_2);
   std::cout << std::endl << std::endl;

   // test for challenge 3

   std::string freq_list_location = DIR + "word_freq_list.txt";
   std::string given_3 = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
   std::string key, message;
   double freq_value = 0.0;

   SetOne::single_byte_xor(given, key, message, freq_value, freq_list_location);

   std::cout << "Challenge 3" << std::endl;
   std::cout << "Final message: " << message << std::endl
             << "Decrypted by the key " << key << std::endl
             << "Frequency value: " << freq_value
             << std::endl << std::endl;


   // Test for challenge 4

   std::string freq_list_location_ch4 = DIR + "word_freq_list.txt";
   std::string encrypted_lines_loc = DIR + "4.txt";
   std::string key_4, message_4;
   double freq_value_4 = 0.0;

   SetOne::multi_line_single_byte_xor(encrypted_lines_loc, key_4, message_4, freq_value_4, freq_list_location);

   std::cout << "Challenge 4" << std::endl;
   std::cout << "Final message: " << message_4 << std::endl
             << "Decrypted by the key " << key_4 << std::endl
             << "Frequency value: " << freq_value_4
             << std::endl << std::endl;




/*
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

   // Test for challenge 5
   /*
   // open ifstream file
   std::string input_file = DIR + "5_to_encrypt.txt";
   std::ifstream fin(input_file.c_str());

   std::string expected_output = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272\
a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";
   std::string key = "ICE";

   std::string line, temp;
   while (std::getline(fin, temp)) {
      line += temp;
      line.append(1, '\n'); // newline for notepad files
   }
   // An extra '\n' is created in the end, that must be removed!
   line.erase(line.end() - 1);

   // obtain bit version of string
   std::vector<bool> ascii_line = SetOne::ascii_str_to_bit_vec(line);

   // obtain bit version of key
   std::vector<bool> static key_bits = SetOne::ascii_str_to_bit_vec(key);

   // xor string against key (improved different xor method)
   std::vector<bool> encrypted_line = SetOne::xor_against(ascii_line, key_bits);
   std::string hex_out(SetOne::bits_to_hex_string(encrypted_line));

   SetOne::check_equality(hex_out, expected_output);
   */
   return 0;
}
