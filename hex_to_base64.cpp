#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>

//static char hex_vals[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

void binary(int num, std::vector<bool>& bool_vals) {

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

std::vector<bool> hex_to_bin(std::string str) {
   std::vector<char> hex_vals;
   hex_vals.push_back('0'); hex_vals.push_back('1'); hex_vals.push_back('2'); hex_vals.push_back('3');
   hex_vals.push_back('4'); hex_vals.push_back('5'); hex_vals.push_back('6'); hex_vals.push_back('7');
   hex_vals.push_back('8'); hex_vals.push_back('9'); hex_vals.push_back('a'); hex_vals.push_back('b');
   hex_vals.push_back('c'); hex_vals.push_back('d'); hex_vals.push_back('e'); hex_vals.push_back('f');

   std::vector<char> str_char(str.begin(), str.end());

   std::vector<bool> bit_vals;

   // won't check if it's not found since a hex value will always be given
   for (std::vector<char>::iterator i = str_char.begin(); i != str_char.end() ; ++i) {
      std::vector<char>::iterator c = std::find(hex_vals.begin(), hex_vals.end(), *i);

      std::vector<char>::size_type hex_weight = std::distance(hex_vals.begin(), c);
   //   std::cout << "hex: " << hex_weight << "\t";

      binary(hex_weight, bit_vals);
   }
   //std::cout << std::endl;
   //for (std::vector<bool>::iterator it = bit_vals.begin(); it != bit_vals.end(); ++it)
   //   std::cout << *it;

   return bit_vals;
}

std::vector<int> bits_to_sixes(std::vector<bool> bit_vals) {
   std::vector<int> ret;
   int sum = 0, count = 0;
/*
   for (std::vector<bool>::iterator i = bit_vals.begin(); i != bit_vals.end(); ++i) {
         std::cout << *i << " ";
   }
   std::cout << std::endl << "checking bit_vals before sixes " << bit_vals.size() << std::endl;
*/

   for (std::vector<bool>::iterator i = bit_vals.begin(); i != bit_vals.end(); ++i) {

      //std::cout << *i << " ";
      sum += (*i) * pow(2, 5 - count);
      ++count;
      if (count == 6) {
         //std::cout << " " << sum << " " << std::endl;
         ret.push_back(sum);
         count = 0;
         sum = 0;
      }
   }
   //std::cout << std::endl << std::endl;

   return ret;
}

std::vector<char> base64(std::vector<bool>& bit_vals) {
   //std::cout << "base64" << std::endl;
   std::vector<int> sixes(bits_to_sixes(bit_vals));
   std::vector<char> ret;

   for (std::vector<int>::iterator it = sixes.begin(); it != sixes.end(); ++it) {
      //std::cout << *it << " ";
      if (0 <= *it && *it <= 25)
         ret.push_back('A' + (*it));
      else if(26 <= *it && *it <= 51)
         ret.push_back('a' + (*it % 26));
      else if(52 <= *it && *it <= 61)
         ret.push_back('0' + (*it % 52));
      else if(*it == 62)
         ret.push_back('+');
      else if(*it == 63)
         ret.push_back('/');
      else
         ret.push_back('=');
   }
   //std::cout << std::endl;

   return ret;

}

std::string chars_to_string(std::vector<char>& chars_of_sixes) {
   std::string ret = "";
   for (std::vector<char>::iterator i = chars_of_sixes.begin(); i != chars_of_sixes.end(); ++i) {
      ret.append(std::string(1, *i));
   }
   return ret;
}

std::string hex_to_base64(std::string str) {
   // convert the hex string into a vector of bits
   std::vector<bool> bit_vals(hex_to_bin(str));
   // convert bits into base64 chars
   std::vector<char> chars_of_sixes(base64(bit_vals));
   // combine chars into one string
   std::string base64_string(chars_to_string(chars_of_sixes));
   return base64_string;
}

void equal_strings(std::string s1, std::string s2) {
   std::cout << s1 << std::endl;
   std::cout << s2 << std::endl;
   std::cout << "equal? ";
   (s1 == s2) ? std::cout <<"YES" : std::cout <<"NO";
   std::cout << std::endl;

}

std::string xor_against(std::string str, std::string xor_with) {
   std::string ret;

   std::vector<bool> st1 = hex_to_bin(str);
   std::vector<bool> st2 = hex_to_bin(xor_with);

   std::vector<bool>::iterator it1 = st1.begin(), it1e = st1.end();
   std::vector<bool>::iterator it2 = st2.begin(), it2e = st2.end();

   while (it1 != it1e && it2 != it2e) {
      char temp = ((*it1) ^ (*it2)) + '0' ;
      //char temp = std::abs(str[i] - xor_with[i]) + '0';
      ret.append(std::string(1, temp));
      ++it1;
      ++it2;
   }
   return ret;
}

int main () {

   std::string given = "1c0111001f010100061a024b53535009181c";
   std::string xor_with = "686974207468652062756c6c277320657965";
   std::string test_with = "746865206b696420646f6e277420706c6179";

 //  std::string str(hex_to_base64(given));
   std::string str = xor_against(given, xor_with);

   equal_strings(str, test_with);


   return 0;
}

/* hex to base64 */
/*
int main () {

   //std::string str = "0123456789abcdef";
   std::string str = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
   std::string test_with = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";

   std::string base64_string(hex_to_base64(str));

   equal_strings(base64_string, test_with);

   return 0;
}
*/
