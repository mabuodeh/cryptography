#include "SetOne.h"
#include <iostream>
#include <algorithm>
#include <math.h>


void SetOne::binary(int num, std::vector<bool>& bool_vals) {

    std::vector<bool> temp;

    for (int i = 0; i < 4; ++i) {
      if (num % 2 == 0)
         temp.push_back(0);
      else
         temp.push_back(1);
      num /= 2;
    }
    std::copy(temp.rbegin(), temp.rend(), std::back_inserter(bool_vals));
}

std::vector<char> SetOne::get_hex_values() {
   std::vector<char> hex_vals;
   hex_vals.push_back('0'); hex_vals.push_back('1'); hex_vals.push_back('2'); hex_vals.push_back('3');
   hex_vals.push_back('4'); hex_vals.push_back('5'); hex_vals.push_back('6'); hex_vals.push_back('7');
   hex_vals.push_back('8'); hex_vals.push_back('9'); hex_vals.push_back('a'); hex_vals.push_back('b');
   hex_vals.push_back('c'); hex_vals.push_back('d'); hex_vals.push_back('e'); hex_vals.push_back('f');

   return hex_vals;
}

std::vector<bool> SetOne::hex_string_to_bits(std::string str) {
   std::vector<char> hex_vals(get_hex_values());

   std::vector<char> str_char(str.begin(), str.end());

   std::vector<bool> bit_vals;

   // won't check if it's not found since a hex value will always be given
   for (std::vector<char>::iterator i = str_char.begin(); i != str_char.end() ; ++i) {
      std::vector<char>::iterator c = std::find(hex_vals.begin(), hex_vals.end(), *i);

      std::vector<char>::size_type hex_weight = std::distance(hex_vals.begin(), c);

      binary(hex_weight, bit_vals);
   }
   return bit_vals;
}

/*
std::vector<bool> SetOne::base64_string_to_bits(const std::string& base_string) {

}
*/
std::vector<int> SetOne::bits_to_n(std::vector<bool> bit_vals, int n) {
   std::vector<int> ret;
   int sum = 0, count = 0;
/*
   for (std::vector<bool>::iterator i = bit_vals.begin(); i != bit_vals.end(); ++i) {
         std::cout << *i << " ";
   }
   std::cout << std::endl << "checking bit_vals before sixes " << bit_vals.size() << std::endl;
*/

   for (std::vector<bool>::iterator i = bit_vals.begin(); i != bit_vals.end(); ++i) {
      int diff = n - 1;
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
   //std::cout << std::endl << std::endl;

   return ret;
}

std::string SetOne::bits_to_base64_string(std::vector<bool>& bit_vals) {
   std::vector<int> sixes(bits_to_n(bit_vals, BASE64_DIGIT_SZ));
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

void SetOne::check_equality(std::string s1, std::string s2) {
   std::cout << s1 << std::endl;
   std::cout << s2 << std::endl;
   std::cout << "equal? ";
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
   std::cout << "equal? " << std::endl;
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

std::string SetOne::bits_to_hex_string(std::vector<bool> bits) {
   std::string ret;

   std::vector<int> hex_quarts = bits_to_n(bits, HEX_DIGIT_SZ);
   std::vector<char> hex_vals(get_hex_values());

   for (std::vector<int>::iterator it = hex_quarts.begin(); it != hex_quarts.end(); ++it) {
      ret.append(1, hex_vals[*it]);
   }

   return ret;
}
