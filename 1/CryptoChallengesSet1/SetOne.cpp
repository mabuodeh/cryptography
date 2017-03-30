#include "SetOne.h"
#include <iostream>
#include <algorithm>
#include <math.h>
#include <fstream>

const std::string DIR = "text_files/";

void SetOne::num_to_bin(int num, std::vector<bool>& bool_vals, int desired_sz) {

    std::vector<bool> temp;

    for (int i = 0; i < desired_sz; ++i) {
    //while (num != 0) {
      if (num % 2 == 0)
         temp.push_back(0);
      else
         temp.push_back(1);
      num /= 2;
    }
   /*
   for (std::vector<bool>::iterator it = temp.begin(); it != temp.end(); ++it) {
      std::cout << *it;
   }
   std::cout << std::endl;
   */
    std::copy(temp.rbegin(), temp.rend(), std::back_inserter(bool_vals));
}

std::vector<int> SetOne::bin_to_num(std::vector<bool> bit_vals, int n) {
   std::vector<int> ret;
   int sum = 0, count = 0;
   int diff = n - 1;

   for (std::vector<bool>::iterator i = bit_vals.begin(); i != bit_vals.end(); ++i) {
      //std::cout << *i << " ";
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


std::vector<char> SetOne::get_hex_values() {
   std::vector<char> hex_vals;
   hex_vals.push_back('0'); hex_vals.push_back('1'); hex_vals.push_back('2'); hex_vals.push_back('3');
   hex_vals.push_back('4'); hex_vals.push_back('5'); hex_vals.push_back('6'); hex_vals.push_back('7');
   hex_vals.push_back('8'); hex_vals.push_back('9'); hex_vals.push_back('a'); hex_vals.push_back('b');
   hex_vals.push_back('c'); hex_vals.push_back('d'); hex_vals.push_back('e'); hex_vals.push_back('f');

   return hex_vals;
}

std::map<std::string, double> SetOne::gen_word_freq_table() {
   std::map<std::string, double> ret;
   std::string file = DIR + "word_freq_list.txt";
   std::ifstream fin(fil.c_str());

   std::string a;
   double b;
   while(fin >> a >> b) {
      ret[a] = b;
   }
   return ret;
}

std::vector<bool> SetOne::hex_string_to_bits(std::string str) {
   static std::vector<char> hex_vals(get_hex_values());

   std::vector<char> str_char(str.begin(), str.end());

   std::vector<bool> bit_vals;

   // won't check if it's not found since a hex value will always be given
   for (std::vector<char>::iterator i = str_char.begin(); i != str_char.end() ; ++i) {
      std::vector<char>::iterator c = std::find(hex_vals.begin(), hex_vals.end(), *i);

      std::vector<char>::size_type hex_weight = std::distance(hex_vals.begin(), c);

      num_to_bin(hex_weight, bit_vals, HEX_QUART_DIGIT_SZ);
   }
   return bit_vals;
}

std::vector<bool> SetOne::bit_string_to_bit_vec(std::string char_string) {
   std::vector<bool> ret;

   //for (std::string::iterator it = char_string.begin(); it != char_string.end(); ++it) {
   for (std::string::size_type i = 0; i < char_string.size(); ++i) {
      bool temp = char_string[i] == '0'? 0 : 1;
      ret.push_back(temp);
   }
   /*
   for (std::vector<bool>::iterator it = ret.begin(); it != ret.end(); ++it) {
      std::cout << *it;
   }
   std::cout << std::endl;
   */

   return ret;
}

/*
std::vector<bool> SetOne::base64_string_to_bits(const std::string& base_string) {

}
*/


std::string SetOne::bits_to_hex_string(std::vector<bool> bits) {
   std::string ret;

   std::vector<int> hex_quarts = bin_to_num(bits, HEX_QUART_DIGIT_SZ);
   static std::vector<char> hex_vals(get_hex_values());

   for (std::vector<int>::iterator it = hex_quarts.begin(); it != hex_quarts.end(); ++it) {
      ret.append(1, hex_vals[*it]);
   }

   return ret;
}

std::string SetOne::bits_to_base64_string(std::vector<bool>& bit_vals) {
   std::vector<int> sixes(bin_to_num(bit_vals, BASE64_DIGIT_SZ));
   //std::vector<char> ret;
   std::string ret;

   for (std::vector<int>::iterator it = sixes.begin(); it != sixes.end(); ++it) {
      //std::cout << *it << " ";
      if (0 <= *it && *it <= 25)
         ret.append(std::string(1, ('A' + (*it))));
         //ret.append('A' + (*it));
      else if(26 <= *it && *it <= 51)
         ret.append(std::string(1, ('a' + (*it % 26))));
         //ret.push_back('a' + (*it % 26));
      else if(52 <= *it && *it <= 61)
         ret.append(std::string(1, ('0' + (*it % 52))));
         //ret.push_back('0' + (*it % 52));
      else if(*it == 62)
         ret.append(std::string(1, ('+')));
         //ret.push_back('+');
      else if(*it == 63)
         ret.append(std::string(1, ('/')));
         //ret.push_back('/');
      else
         ret.append(std::string(1, ('=')));
         //ret.push_back('=');
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

void SetOne::check_equality(std::string s1, std::string s2) {
   std::cout << s1 << std::endl;
   std::cout << s2 << std::endl;
   std::cout << "equal? " << std::endl;
   (s1 == s2) ? std::cout <<"YES" : std::cout <<"NO";
   std::cout << std::endl;

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
