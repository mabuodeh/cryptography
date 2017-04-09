#include "SetOne.h"
#include <iostream>
#include <algorithm>
#include <math.h>
#include <fstream>

const std::string DIR = "text_files/";

/* This routine converts a hex string to a base64 string.
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

/* This routine converts a hex string to a vector of bits */
std::vector<bool> SetOne::hex_string_to_bits(std::string str) {

   // create a bit container to store bit equivalent of our hex string
   std::vector<bool> bit_vals;
   // get the map of hex values to get numeric values of hex digits
   static std::map<char,int> hex_vals(get_hex_values());

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

/* create a map container, assigning each hex digit its respective numeric value */
std::map<char, int> SetOne::get_hex_values() {
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

/* This routine converts a bit vector to a base64 string. */
std::string SetOne::bits_to_base64_string(std::vector<bool>& bit_vals) {
   // create an int vector that stores bits in groups of six
   std::vector<int> sixes(bin_to_num(bit_vals, BASE64_DIGIT_SZ));
   std::string ret;

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

void SetOne::check_equality(std::string s1, std::string s2) {
   std::cout << s1 << std::endl;
   std::cout << s2 << std::endl;
   std::cout << "equal? " << std::endl;
   (s1 == s2) ? std::cout <<"YES" : std::cout <<"NO";
   std::cout << std::endl;

}

/* This routine converts a vector of bits into a numeric value */
std::vector<int> SetOne::bin_to_num(std::vector<bool> bit_vals, int n) {
   std::vector<int> ret;
   int sum = 0, count = 0;
   int diff = n - 1;

   // loop through bit vector
   for (std::vector<bool>::iterator i = bit_vals.begin(); i != bit_vals.end(); ++i) {
      // use bit equation, multiplying 1 or 0 by 2^x, where x is the position of the bit in the vector
      sum += (*i) * pow(2, diff - count);
      ++count;
      if (count == n) {
         //std::cout << " " << sum << " " << std::endl;
         ret.push_back(sum);
         count = 0;
         sum = 0;
      }
   }

   return ret;
}
/*
std::map<std::string, double> SetOne::gen_word_freq_table() {
   std::map<std::string, double> ret;
   std::string file = DIR + "word_freq_list.txt";
   std::ifstream fin(file.c_str());

   std::string a;
   double b;
   while(fin >> a >> b) {
      ret[a] = b;
   }
   return ret;
}

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

std::string SetOne::bits_to_hex_string(std::vector<bool> bits) {
   std::string ret;

   std::vector<int> hex_quarts = bin_to_num(bits, HEX_QUART_DIGIT_SZ);
   static std::vector<char> hex_vals(get_hex_values());

   for (std::vector<int>::iterator it = hex_quarts.begin(); it != hex_quarts.end(); ++it) {
      ret.append(1, hex_vals[*it]);
   }

   return ret;
}

std::string SetOne::bits_to_ascii_string(std::vector<bool>& bit_vals) {
   std::string ret;

   std::vector<int> eighths(bin_to_num(bit_vals, HEX_OCTET_DIGIT_SZ));

   for (std::vector<int>::iterator it = eighths.begin(); it != eighths.end(); ++it) {
      char temp = *it;
      //std::cout << *it << " " << temp << std::endl;
      ret.append(1, temp);
   }

   return ret;
}

std::vector<bool> SetOne::ascii_str_to_bit_vec(std::string str) {
   std::vector<bool> ret;

   for (std::string::size_type i = 0; i < str.size(); ++i) {
      int temp = str[i];
      num_to_bin(temp, ret, HEX_OCTET_DIGIT_SZ);
   }

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

double SetOne::calc_word_frequency(std::string str) {
   double ret = 0.0;

   static std::map<std::string, double> words = gen_word_freq_table();

   std::string::iterator i = str.begin(), j;
   std::map<std::string, double>::iterator it;
   //std::cout << str << std::endl;
   while (i != str.end()) {
      j = i;
      while (j != str.end() && (*j) != ' ')
         ++j;
      if (j != i) {
         it = words.find(std::string(i,j));
         if ((it != words.end()))
            ret += it->second;
      }
      while (j != str.end() && (*j) == ' ')
         ++j;
      i = j;
   }

   return ret;
}
*/
