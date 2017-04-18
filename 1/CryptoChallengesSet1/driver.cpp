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

   std::cout << "Challenge 2" << std::endl;
   SetOne::check_equality(xor_string, output_2);
   std::cout << std::endl << std::endl;

   // test for challenge 3

   std::string freq_list_location = DIR + "word_freq_list.txt";
   std::string given_3 = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
   std::string key, message;
   double freq_value = 0.0;

   SetOne::get_key_by_word_list(given, key, message, freq_value, freq_list_location);

   std::cout << "Challenge 3a: by word list" << std::endl;
   std::cout << "Final message: " << message << std::endl
             << "Decrypted by the key " << key << std::endl
             << "Frequency value: " << freq_value
             << std::endl << std::endl;

   //std::string given_3b = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
   std::string key_3b, message_3b;
   double freq_value_3b = 0.0;

   SetOne::get_key_by_index_of_co(given_3, key_3b, message_3b, freq_value_3b);

   std::cout << "Challenge 3b: by char list" << std::endl;
   std::cout << "Final message: " << message_3b << std::endl
             << "Decrypted by the key " << key_3b << std::endl
             << "Frequency value: " << freq_value_3b
             << std::endl << std::endl;


   // Test for challenge 4

   std::string encrypted_lines_loc = DIR + "4.txt";
   std::string key_4, message_4;
   double freq_value_4 = 0.0;

   SetOne::multi_line_single_byte_xor(encrypted_lines_loc, key_4, message_4, freq_value_4);

   std::cout << "Challenge 4" << std::endl
             << "Final message: " << message_4
             << "Decrypted by the key " << key_4 << std::endl
             << "Frequency value: " << freq_value_4
             << std::endl << std::endl;

   // Test for challenge 5

   std::string to_encode = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
   std::string encode_with_key = "ICE";
   std::string output_5 = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";

   std::string xor_string_5;
   SetOne::multi_byte_key_xor(to_encode, encode_with_key, xor_string_5);

   std::cout << "Challenge 5" << std::endl;
   SetOne::check_equality(xor_string_5, output_5);
   std::cout << std::endl << std::endl;

   // Test for challenge 6

   std::string cha6 = DIR + "6.txt";
   std::string o_msg_6, o_key_6;
   // send filename to function
   std::cout << "Challenge 6: " << std::endl;
   SetOne::break_repeating_key_xor(cha6, o_msg_6, o_key_6);

   return 0;

}
