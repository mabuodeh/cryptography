#include "SetOne.h"
#include <iostream>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <cctype>

const std::string DIR = "text_files/";

/* challenge 1
This routine converts a hex string to a base64 string.
It will first convert the hex string to a vector of bits,
then it will convert this vector of bits to a base64 string.
input: hex string
returns: base64 string */
std::string SetOne::hex_to_base64(std::string hex_string) {
   std::string ret;

   // convert the received string into a bit vector
   std::vector<bool> bits = hex_string_to_bits(hex_string);
   // convert bit vector into a base64 string
   ret = bits_to_base64_string(bits);
   // return base64 string
   return ret;
}

/* challenge 2
This routine xor's two hex strings by first converting them to bit vectors.
The xor value is then converted back to a hex string and returned
*/
std::string SetOne::xor_hex_strings(std::string first_hex, std::string second_hex) {
   std::string ret;
   std::vector<bool> first_bit, second_bit;

   // convert first hex string to a bit vector
   first_bit = hex_string_to_bits(first_hex);
   // convert second hex string to a bit vector
   second_bit = hex_string_to_bits(second_hex);
   // xor bit vectors
   std::vector<bool> xor_vec = xor_against(first_bit, second_bit);
   // convert xor'ed bit vector into string
   ret = bits_to_hex_string(xor_vec);
   // return xor'ed string
   return ret;
}

/* challenge 3
This routine takes a hex encoded message as an input. This message can be decoded by a single byte xor.
The message will be xor'ed with different single byte combinations, and the result will be compared
against a word frequency list (the list location is given in order to generate the list).
The message and key which yields the highest frequency will be returned.
The key that decodes the message, the final message, and the frequency value are returned by reference.
*/
void SetOne::get_key_by_word_list(std::string message, std::string &key, std::string &output, double &frequency_value, const std::string &freq_location) {
   // initialize a constant container that contains the word frequency list
   std::map<std::string, double> static freq_list = gen_word_freq_table(freq_location);
   // initialize a final container, key container, and frequency value to keep track of the best decoded message
   std::vector<bool> final_msg, final_key;
   double final_val = 0.0;

   // convert the hex message into bits
   std::vector<bool> bit_msg = hex_string_to_bits(message);
   // loop 128 times (which is the number of different byte combinations)
   for (int i = 0; i < 128; ++i) {
      // initialize a temp container, key container, and frequency value to keep track of the values within the loop
      std::vector<bool> temp_cont, temp_key;
      double temp_val = 0.0;
      // get the bit value of the loop number and store in a temp key container
      num_to_bin(i, temp_key, HEX_OCTET_DIGIT_SZ);
      // xor message with bit value and store in the temp output container
      temp_cont = xor_against(bit_msg, temp_key);
      // convert xor'ed message to an ascii string to pass to frequency calculator function
      std::string xor_msg = bits_to_ascii_string(temp_cont);
      // obtain frequency value by comparing words of the temp output container with the frequency word list, and assign to temp val
      temp_val = calc_word_frequency(xor_msg, freq_list);

      // if the frequency value of the temp container is higher than the current frequency value (final value)
      if (temp_val > final_val) {
         // store current message (found in the temp container) into the final container
         final_msg = temp_cont;
         // store current key (found in the temp key) into the final key
         final_key = temp_key;
         // store current frequency value (found in the temp value) into the final value
         final_val = temp_val;
      } // endif
   } // endloop
   // convert the final message bit vector into a string and assign it to the output
   output = bits_to_ascii_string(final_msg);
   // convert the final key bit vector into a string and assign it to the key output
   key = bits_to_hex_string(final_key);

   frequency_value = final_val;
   // - END: final values are assign by reference -
}

/* Still challenge 5, but using character frequency rather word frequency */
void SetOne::get_key_by_char_list(std::string message, std::string &key, std::string &output, double &frequency_value) {
   // initialize a final container, key container, and frequency value to keep track of the best decoded message
   std::vector<bool> final_msg, final_key;
   double final_val = 0.0;

   // convert the hex message into bits
   std::vector<bool> bit_msg = hex_string_to_bits(message);
   // loop 128 times (which is the number of different byte combinations)
   for (int i = 0; i < 127; ++i) {
      // initialize a temp container, key container, and frequency value to keep track of the values within the loop
      std::vector<bool> temp_cont, temp_key;
      double temp_val = 0.0;
      // get the bit value of the loop number and store in a temp key container
      num_to_bin(i, temp_key, HEX_OCTET_DIGIT_SZ);
      // xor message with bit value and store in the temp output container
      temp_cont = xor_against(bit_msg, temp_key);
      // convert xor'ed message to an ascii string to pass to frequency calculator function
      std::string xor_msg = bits_to_ascii_string(temp_cont);
      // obtain frequency value by comparing words of the temp output container with the frequency word list, and assign to temp val
      temp_val = calc_char_frequency(xor_msg);

      // if the frequency value of the temp container is higher than the current frequency value (final value)
      if (temp_val > final_val) {
         // store current message (found in the temp container) into the final container
         final_msg = temp_cont;
         // store current key (found in the temp key) into the final key
         final_key = temp_key;
         // store current frequency value (found in the temp value) into the final value
         final_val = temp_val;
      } // endif
   } // endloop
   // convert the final message bit vector into a string and assign it to the output
   output = bits_to_ascii_string(final_msg);
   // convert the final key bit vector into a string and assign it to the key output
   key = bits_to_hex_string(final_key);

   frequency_value = final_val;
   // - END: final values are assign by reference -
}


/* Challenge 4
This routine deciphers hex encoded lines with a single character (byte).
For each line read, character combinations will be xor'ed with that line,
and the xor'ed text with the highest word frequency score will be taken.
*/
void SetOne::multi_line_single_byte_xor(std::string encrypted_file_loc, std::string &key, std::string &output,
                                       double &frequency_value, const std::string &freq_location) {
   // initialize a final container, key container, and frequency value to keep track of the best decoded message
   std::string final_msg, final_key;
   double final_val = 0.0;

   // open an ifstream using the file location
   std::ifstream fin(encrypted_file_loc.c_str());

   // loop until all file lines are read
   std::string line;
   while (fin >> line) {
      // initialize temp container, key, and frequency value for loop
      std::string temp_cont, temp_key;
      double temp_val = 0.0;
      // for each lines, obtain the the container and key with the highest frequency value
      get_key_by_word_list(line, temp_key, temp_cont, temp_val, freq_location);
      // if the temp frequency value is higher than the stored frequency value (final)
      if (temp_val > final_val) {
         // replace the final container and key with newly received values
         final_msg = temp_cont;
         final_key = temp_key;
         final_val = temp_val;
      } // endif
   } // endloop
   // assign key, output, and frequency value to the referenced variables
   output = final_msg;
   key = final_key;
   frequency_value = final_val;

   fin.close();
}

/* Challenge 5
This string encodes a string with a key using the repeating xor technique.
Inputs: message, key, output
*/
void SetOne::multi_byte_key_xor(const std::string &message, const std::string &key, std::string &output) {
   std::vector<bool> bit_msg, bit_key;
   // convert message from ascii characters into a bit vector
   bit_msg = ascii_string_to_bits(message);
   // convert key from ascii characters into a bit vector
   bit_key = ascii_string_to_bits(key);
   // xor message and key bits, and assign them to a bit vector
   std::vector<bool> xor_out = xor_against(bit_msg, bit_key);
   // convert the xor bit vector into a string and assign it to the output
   output = bits_to_hex_string(xor_out);
   // END - 'output' is called by reference.
}

/* Challenge 6
This routine takes a file of encrypted lines.
It will first determine the length of the key using hamming distance.
It will then use this information to decrypted the message based on combinations.
The message information with the best frequency will be returned.
*/
void SetOne::break_repeating_key_xor(std::string i_file, std::string o_msg, std::string o_key) {
   // open file i_file
   std::ifstream fin(i_file.c_str());
   // check if file opened
   if (fin == NULL)
      std::cerr << "6.txt not opening!" << std::endl;
   // read lines into an encrypted_message string
   std::string encrypted_msg, temp;
   while (fin >> temp) {
      encrypted_msg.append(temp);
   }

   // -step one: find the smallest normalized value (quotient)-
   int final_quotient = 10000.0;
   std::vector<int> keysize_vals;
   // loop through keysize from 2 to 40 (this is the number of characters the key can be)
   for (int i = 2; i <= 40; ++i) {
      // initialize keysize
      int keysize = i;
      // obtain a keysize number of bytes (characters), twice. We now have two blocks of keysize bytes each.
      // obtain first keysize characters [0, keysize)
      std::string first_chars(encrypted_msg.begin(), encrypted_msg.begin() + keysize);
      // obtain second keysize characters [keysize, keysize * 2)
      std::string second_chars(encrypted_msg.begin() + keysize, encrypted_msg.begin() + keysize + keysize * 2);
      // convert these two character blocks into bits
      std::vector<bool> first_block = ascii_string_to_bits(first_chars);
      std::vector<bool> second_block = ascii_string_to_bits(second_chars);
      // find the hamming distance of the blocks
      int ham_dis = get_hamming_distance(first_block, second_block);
      // divide the hamming distance by the keysize
      int temp_quotient = ham_dis / keysize;
      // if the quotient is less than the previously stored quotient
      if (temp_quotient < final_quotient) {
         // clear all old keysize values
         keysize_vals.clear();
         // push the current one in
         keysize_vals.push_back(keysize);
         // replace the temporarily stored quotient with the current quotient
         final_quotient = temp_quotient;
      } // else if the quotient is the same
      else if (temp_quotient == final_quotient) {
         // add it to the vector
         keysize_vals.push_back(keysize);
      }
   } // endloop
   // print out the keysize
   std::cout << "final_quotient: " << final_quotient << std::endl << "keysize values: " <<std::endl;
   for (int j = 0; j < keysize_vals.size(); ++j)
      std::cout << keysize_vals[j] << " ";
   std::cout << std::endl;

   // - step two: get all the keysizes with final_quotient
   //


}


/* This routine converts a hex string to a vector of bits */
std::vector<bool> SetOne::hex_string_to_bits(std::string str) {

   // create a bit container to store bit equivalent of our hex string
   std::vector<bool> bit_vals;
   // get the map of hex values to get numeric values of hex digits
   static std::map<char,int> hex_vals(hex_num_map());

   // for loop (iterate) through the characters of the string
   for (std::string::iterator i = str.begin(); i != str.end() ; ++i) {
      // get numeric value of character
      int num_val = hex_vals[*i];
      // convert numeric value to bits
      // add converted bits to the bit container
      num_to_bin(num_val, bit_vals, HEX_QUART_DIGIT_SZ);
   } // end loop

   // return bit container
   return bit_vals;
}

/* This routine takes an ASCII string and converts it to a bit vector */
std::vector<bool> SetOne::ascii_string_to_bits(std::string str) {
   // initialize container to be returned
   std::vector<bool> ret;

   // loop through the ASCII strings characters
   for (std::string::size_type i = 0; i < str.size(); ++i) {
      // convert each character to a numeric value
      int temp = str[i];
      // convert the numeric value to bits, and push them into the container
      num_to_bin(temp, ret, HEX_OCTET_DIGIT_SZ);
   }

   // return container
   return ret;
}


/* create a map container, assigning each hex digit its respective numeric value */
std::map<char, int> SetOne::hex_num_map() {
   // create map container
   std::map<char, int> hex_vals;
   // assign each hex digit its numeric value
   hex_vals['0'] = 0; hex_vals['1'] = 1; hex_vals['2'] = 2; hex_vals['3'] = 3;
   hex_vals['4'] = 4; hex_vals['5'] = 5; hex_vals['6'] = 6; hex_vals['7'] = 7;
   hex_vals['8'] = 8; hex_vals['9'] = 9; hex_vals['a'] = 10; hex_vals['b'] = 11;
   hex_vals['c'] = 12; hex_vals['d'] = 13; hex_vals['e'] = 14; hex_vals['f'] = 15;

   // return map container
   return hex_vals;

}

/* create a map container, assigning each numeric value its respective hex digit */
std::map<int, char> SetOne::num_hex_map() {
   // create map container
   std::map<int, char> hex_vals;
   // assign each hex digit its numeric value
   hex_vals[0] = '0'; hex_vals[1] = '1'; hex_vals[2] = '2'; hex_vals[3] = '3';
   hex_vals[4] = '4'; hex_vals[5] = '5'; hex_vals[6] = '6'; hex_vals[7] = '7';
   hex_vals[8] = '8'; hex_vals[9] = '9'; hex_vals[10] = 'a'; hex_vals[11] = 'b';
   hex_vals[12] = 'c'; hex_vals[13] = 'd'; hex_vals[14] = 'e'; hex_vals[15] = 'f';

   // return map container
   return hex_vals;

}

/* This routine converts a bit vector to a base64 string. */
std::string SetOne::bits_to_base64_string(std::vector<bool>& bit_vals) {
   // create an int vector that stores bits in groups of six
   std::vector<int> sixes;
   std::string ret;

   bin_to_num(bit_vals, sixes, BASE64_DIGIT_SZ);


   // loop through the int vector, converting the int values into base64 characters, and appending them to the ret string
   for (std::vector<int>::iterator it = sixes.begin(); it != sixes.end(); ++it) {
      if (0 <= *it && *it <= 25)
         ret.append(std::string(1, ('A' + (*it))));
      else if(26 <= *it && *it <= 51)
         ret.append(std::string(1, ('a' + (*it % 26))));
      else if(52 <= *it && *it <= 61)
         ret.append(std::string(1, ('0' + (*it % 52))));
      else if(*it == 62)
         ret.append(std::string(1, ('+')));
      else if(*it == 63)
         ret.append(std::string(1, ('/')));
      else
         ret.append(std::string(1, ('=')));
   }

   // return base64 string
   return ret;

}

/* This routine converts a bit vector to an ASCII string.
It splits the bit vector into bytes and stores them as integers.
It then converts these integers into characters, and appends them to the final string.
Finally, it returns this final string.
*/
std::string SetOne::bits_to_ascii_string(std::vector<bool>& bit_vals) {
   // initialize string to be returned
   std::string ret;

   // convert bits into bytes, storing them as integers
   std::vector<int> eighths;
   bin_to_num(bit_vals, eighths, HEX_OCTET_DIGIT_SZ);

   // loop through the integer container
   for (std::vector<int>::iterator it = eighths.begin(); it != eighths.end(); ++it) {
      // for each integer, convert into a char
      char temp = *it;
      // append the char to the final string
      ret.append(1, temp);
   } // endloop
   // return the final string
   return ret;
} // end bits_to_ascii_string

/* converts a numeric value to a bit vector
input: numeric value num, bit vector bool_vals to push to, desired number of bits desired_sz */
void SetOne::num_to_bin(int num, std::vector<bool>& bool_vals, int desired_sz) {

    std::vector<bool> temp;

    // loop desired_sz times, where desired_sz is the desired binary number size
    for (int i = 0; i < desired_sz; ++i) {
      // if number is even, add 0 to bit vector
      if (num % 2 == 0)
         temp.push_back(0);
      // else add 1 to bit vector
      else
         temp.push_back(1);
      // divide numeric value (functions as a bit shift)
      num /= 2;
    }
   /*
   for (std::vector<bool>::iterator it = temp.begin(); it != temp.end(); ++it) {
      std::cout << *it;
   }
   std::cout << std::endl;
   */
   // copy temp bit vector in reverse order to the final bit vector
   std::copy(temp.rbegin(), temp.rend(), std::back_inserter(bool_vals));
}

/* This routine converts a vector of bits into a numeric value */
void SetOne::bin_to_num(std::vector<bool> bit_vals, std::vector<int> &num_vals, int n) {
   int sum = 0, count = 0;
   int diff = n - 1;

   // loop through bit vector
   for (std::vector<bool>::iterator i = bit_vals.begin(); i != bit_vals.end(); ++i) {
      // use bit equation, multiplying 1 or 0 by 2^x, where x is the position of the bit in the vector
      sum += (*i) * pow(2, diff - count);
      ++count;
      if (count == n) {
         //std::cout << " " << sum << " " << std::endl;
         num_vals.push_back(sum);
         count = 0;
         sum = 0;
      }
   }
}

/* This routine converts a bit vector to a hex string */
std::string SetOne::bits_to_hex_string(std::vector<bool> bits) {
   std::string ret;
   std::vector<int> hex_quarts;

   // split bits into groups of four, and convert and store them in a quarts (int) vector
   bin_to_num(bits, hex_quarts, HEX_QUART_DIGIT_SZ);

   // loop through quarts vector, converting each number to its equivalent hex value
   static std::map<int, char> hex_vals(num_hex_map());
   for (std::vector<int>::iterator it = hex_quarts.begin(); it != hex_quarts.end(); ++it) {
      ret.append(1, hex_vals[*it]);
   }

   // return hex string
   return ret;
}

/* This routine takes two bit vectors and xors them.
If the bits vectors have equal length, then a bit by bit xor will occur.
If the bit vectors are of unequal length (main vector and key vector), the key vector will be
xor'ed against the main vector until the main vector is covered. */
std::vector<bool> SetOne::xor_against(std::vector<bool> main_vec, std::vector<bool> key_vec) {
   // initialize container to be returned
   std::vector<bool> ret;

   // assign iterators the beginning and end of bit vectors
   std::vector<bool>::iterator it1 = main_vec.begin(), it1e = main_vec.end();
   std::vector<bool>::iterator it2 = key_vec.begin(), it2e = key_vec.end();

   // loop until the end of the main vector is reached
   while (it1 != it1e) {
      // loop until the end of either the main vector or key vector is reached
      while (it2 != it2e && it1 != it1e) {
         // store the xor'ed bit in the return container
         ret.push_back((*it1) ^ (*it2));
         // increment main and key vector iterators
         ++it1;
         ++it2;
      }
      // when key iterator reaches the end, we must reset it to continue acting on the main vector
      it2 = key_vec.begin();
   }
   // return container filled with xor'ed bits
   return ret;
}

/* This routine generates a word frequency list from a text file */
std::map<std::string, double> SetOne::gen_word_freq_table(const std::string &file) {
   // initialize container to be returned
   std::map<std::string, double> ret;
   // define frequency list filename, and open file

   std::ifstream fin(file.c_str());

   std::string a;
   double b;
   // loop through lines of the file. The first variable is the word, the second is the frequency percentage
   while(fin >> a >> b) {
      // map each frequency percentage to its respective word
      ret[a] = b;
   }

   fin.close();

   // return container
   return ret;
}

/* This routine generates a char frequency list from a text file */
std::map<char, double> SetOne::gen_char_freq_table(const std::string &file) {
   // initialize container to be returned
   std::map<char, double> ret;
   // define frequency list filename, and open file

   std::ifstream fin(file.c_str());

   char a;
   double b;
   // loop through lines of the file. The first variable is the word, the second is the frequency percentage
   while(fin >> a >> b) {
      // map each frequency percentage to its respective word
      ret[a] = b;
   }

   fin.close();

   // return container
   return ret;
}

/* This routine calculates the word frequency of a string.
It checks each word to see if it exists in the given word frequency table, and assigns the respective percentage.
*/
double SetOne::calc_word_frequency(const std::string &str, const std::map<std::string, double> &words) {
   // initialize frequency value to be returned
   double ret = 0.0;

   // initialize iterators for the given string
   std::string::const_iterator i = str.begin(), j;
   // initialize iterator for the frequency word list
   std::map<std::string, double>::const_iterator it;

   // loop through the given string until the end
   while (i != str.end()) {
      // reset the end iterator to point to the same location as the beginning iterator
      j = i;
      // increment the end iterator until the end of the string is reached or a space
      while (j != str.end() && (*j) != ' ')
         ++j;
      // check whether the end iterator is still equal to the beginning iterator (meaning we reached the end of the string)
      // if it isnt equal:
      if (j != i) {
         // search in the frequency list for the word between the beginning and end iterators
         it = words.find(std::string(i,j));
         // if the word is found:
         if ((it != words.end()))
            // add it's respective frequency value to the frequency value variable
            ret += it->second;
      }
      // keep incrementing the end iterator until either the next word or the end of the string is reached
      while (j != str.end() && (*j) == ' ')
         ++j;
      // assign the beginning iterator the value of the end iterator, to start the same process again for the next word
      i = j;
   }
   // return the frequency value of the string
   return ret;
}

/* This routine calculates the character frequency of a string. */
double SetOne::calc_char_frequency(const std::string &str) {
   // initialize letter count
   int letter_count = 0;
   // create a map to keep track of frequency of letters
   std::map<char, double> char_list;
   // initialize an index of coincidence variable
   double indCo = 0.0;

   // initialize iterators for the given string
   std::string::const_iterator it = str.begin();
   //loop through the string for each character
   while (it != str.end()) {
      // if the character is a letter
      if (('A' <= (*it) && (*it) <= 'Z') || ('a' <= (*it) && (*it) <= 'z') || ((*it) == ' ')) {
         // increment that character within the map
         ++char_list[*it];
         // increment letter count

      } // endif
      // increment iterator
      ++letter_count;
      ++it;
   } // endloop

   // index of coincidence:
   // loop through the character map
   std::map<char, double>::iterator map_it = char_list.begin();
   while (map_it != char_list.end()) {
      // add to the indCo variable the product of the character value with the character value - 1
      indCo += ((map_it->second) * (map_it->second - 1));
      // increment it
      ++map_it;
   } // end loop
   // divide indCo by the product of the total letter count and the total letter count - 1
   indCo /= (letter_count) * (letter_count - 1);

   // return indCo
   return indCo;
}

void SetOne::check_equality(std::string s1, std::string s2) {
   std::cout << s1 << std::endl;
   std::cout << s2 << std::endl;
   std::cout << "equal? " << std::endl;
   (s1 == s2) ? std::cout <<"YES" : std::cout <<"NO";
   std::cout << std::endl;

}

/* This routine calculates the hamming distance of two boolean vectors */
int SetOne::get_hamming_distance(std::vector<bool> first_vec, std::vector<bool> second_vec) {
   // initialize return value
   int ret = 0;
   // get the xor value of the two bit vectors
   std::vector<bool> xor_val = xor_against(first_vec, second_vec);
   // initialize iterator to the beginning of xor vector
   std::vector<bool>::iterator it = xor_val.begin();
   // loop through each bit of the xor vector
   while (it != xor_val.end()) {
      // if the bit in the vector is 1
      if ((*it) == 1) {
         // increment ret
         ++ret;
      } // endif
      // increment it
      ++it;
   } // endloop
   // return ret
   return ret;
}

/*

std::vector<bool> SetOne::bit_string_to_bit_vec(std::string char_string) {
   std::vector<bool> ret;

   //for (std::string::iterator it = char_string.begin(); it != char_string.end(); ++it) {
   for (std::string::size_type i = 0; i < char_string.size(); ++i) {
      bool temp = char_string[i] == '0'? 0 : 1;
      ret.push_back(temp);
   }
   //for (std::vector<bool>::iterator it = ret.begin(); it != ret.end(); ++it) {
   //   std::cout << *it;
   //}
   //std::cout << std::endl;


   return ret;
}



void SetOne::check_equality(std::vector<bool> first_vec, std::vector<bool> second_vec) {
   for (std::vector<bool>::iterator it = first_vec.begin(); it != first_vec.end(); ++it) {
      std::cout << *it;
   }
   std::cout << std::endl;
   for (std::vector<bool>::iterator it = second_vec.begin(); it != second_vec.end(); ++it) {
      std::cout << *it;
   }
   std::cout << std::endl << "equal? " << std::endl;
   (first_vec == second_vec) ? std::cout <<"YES" : std::cout <<"NO";
   std::cout << std::endl;

}

// xor main vec against key
std::vector<bool> SetOne::xor_against(std::vector<bool> first_vec, std::vector<bool> second_vec) {
   std::vector<bool> ret;

   std::vector<bool>::iterator it1 = first_vec.begin(), it1e = first_vec.end();
   std::vector<bool>::iterator it2 = second_vec.begin(), it2e = second_vec.end();

   while (it1 != it1e) {
      while (it2 != it2e && it1 != it1e) {
         //std::cout << (*it1) << " " << *it2 << std::endl;
         ret.push_back((*it1) ^ (*it2));
         ++it1;
         ++it2;
      }
      it2 = second_vec.begin();
   }
   return ret;
}

std::string SetOne::num_to_bit_string(int num) {
   std::string ret;
   std::vector<bool> char_bits;

   num_to_bin(num, char_bits, HEX_OCTET_DIGIT_SZ);

   while (char_bits.size() != 8) {
      char_bits.insert(char_bits.begin(), 0);
   }
   for (std::vector<bool>::iterator it = char_bits.begin(); it != char_bits.end(); ++it) {
      char temp = *it + '0';
      ret.append(1, temp);
   }
   return ret;

}

std::string SetOne::bit_string_pattern(int sz, std::string char_bits) {
   std::string ret;
   for (int i = 0; i < sz; ++i) {
      ret.append(char_bits);
   }
   return ret;
}

std::vector<bool> SetOne::bit_pattern(std::vector<bool>::size_type sz, std::vector<bool> hex_char) {
   std::vector<bool> ret;

   for (std::vector<bool>::size_type i = 0; i < sz; ++i) {
      ret.insert(ret.end(), hex_char.begin(), hex_char.end());
   }
   return ret;
}

*/

/*
std::vector<bool> SetOne::xor_against(std::vector<bool> first_vec, std::vector<bool> second_vec) {
   std::vector<bool> ret;

   std::vector<bool>::iterator it1 = first_vec.begin(), it1e = first_vec.end();
   std::vector<bool>::iterator it2 = second_vec.begin(), it2e = second_vec.end();

   while (it1 != it1e && it2 != it2e) {
      ret.push_back((*it1) ^ (*it2));
      //char temp = std::abs(str[i] - xor_with[i]) + '0';
      //ret.append(std::string(1, temp));
      ++it1;
      ++it2;
   }
   return ret;
}
*/
