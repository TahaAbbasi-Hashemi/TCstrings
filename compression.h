/*
    This file is part of Tcompression.
    Tcompression is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Tcompression is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Tcompression.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef COMPRESSION_H
#define COMPRESSION_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class compression
{
    public:
        compression();
        virtual ~compression();
        bool get_shortened_string();
        vector<char> return_compressed_string(string home_string);
        string return_decompresed_string(vector<char> compressed_string);
    private:
        unsigned int maxium_compressed_string_length = 0;
        string null_string = "ý";
        vector<string> shortened_strings;
};

#endif // COMPRESSION_H
