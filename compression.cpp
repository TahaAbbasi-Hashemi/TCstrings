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


#include "compression.h"

compression::compression()
{
    //ctor
}

compression::~compression()
{
    //dtor
}


bool compression::get_shortened_string()
{
    /*
    * The purpose of this function is to fill the vector called shortended_strings
    * This function reads from a file, and copies each line down.
    * Each line represents character(s).
    * This just stores the lines into a vector doesn't do anything else.
    * Class variables used: Shortended_string, maxium_compressed_string_length
    */
	ifstream Combined_Characters("Shortened characters.txt");
	if (!Combined_Characters){ return false; }

    string current_line = "";
    while (getline(Combined_Characters, current_line, '\n'))
    {
        if (current_line != null_string)
        {
            if (maxium_compressed_string_length < current_line.length())
            {
                maxium_compressed_string_length = current_line.length();
            }
        }
        shortened_strings.push_back(current_line);
    }
    return true;
}

vector<char> compression::return_compressed_string(string home_string)
{
    /*
    * The purpose of this function is to take a string and compress it.
    * The function returns a vector of characters, because each character is a number
    * This number represents the character or characters it represents.
    * Class variables used: Shortended_string, string_max_size
    *
    * Home string is our reference string. It shouldn't change unless we are adding
    * null characters at the end.
    * Editing string is the string that will constantly be edited, and have characters
    * removed and changed.
    * This is just so that it makes it easier for variable control.
    *
    * There have been questions about why the null_characters are there
    * at the end of the home_string so here is the aligrythum.
    *
    * Let us say our string_max_size is 4, just for my ease.
    * It will check 4 characters at a time.
    * If our home_variable is the word 'Monkey'. We would now add 4 null characters
    * at the end of our home_string. Let our null_string be = '~'
    * Our home_string would now be 'Monkey~~~~'. Now it is going to be chuncked into smaller
    * strings by using editing_string. This will just be shown as [] on our string.
    * editing_string would be 'Monk' but we will show it as '[Monk]ey~~~~' just so you can see why
    * Next we see if we can reduce each editing string. It would then shrink, if it can't fit the set of characters.
    * If we can't store 'Monk' we try 'Mon' and then try 'Mo' then 'M' till it can store it.
    * then we just move down the string 'M[onke]y~~~~' see it just keeps going.
    * lets move further down.
    * 'Mon[key~]~~~' without the null characters we would have an error here. because we are trying to
    * have 4 characters but we would only have 3. This would give us a error, why we have to add the null characters.
    * It would stop when it reaches 'Monkey[~~~~]'.
    */
    string editing_string;
    vector<char> new_string;
    // Adding the null characters at the end of the home_string
    for (unsigned int x=0; x<maxium_compressed_string_length; x++) { home_string += null_string; }

    for (unsigned int x=0; x<home_string.length()-maxium_compressed_string_length; x++)
    {
        // Making a smaller string that I can work with.
        editing_string = home_string;
        editing_string.erase(x+maxium_compressed_string_length, editing_string.length());
        editing_string.erase(0, x);

        // Checking to see if if I can compress said string
        int compressed_characters = 0;
        for (unsigned int y=0; y<maxium_compressed_string_length; y++)
        {
            for (unsigned int z=0; z<shortened_strings.size(); z++)
            {
                if (editing_string == shortened_strings[z])
                {
                    // We store numbers as characters. The numbers would turn into a character.
                    // To decompress we would convert them back into numbers.
                    //cout << z << endl;
                    new_string.push_back(z);
                    compressed_characters += editing_string.length()-1;
                }
            }
            if (compressed_characters == 0){ editing_string.erase(editing_string.length()-1, editing_string.length()); }
            else { break; }
        }
        x += compressed_characters;
    }
    return new_string;
}


string compression::return_decompresed_string(vector<char> compressed_string)
{
    /*
    * The purpose of this function is to return a std::string of the compressed file.
    * The way this works is we would have int just moving down the vector and storing groups of characters
    * at a time.
    * Because the conversion between character and int is weird.
    * it doesn't reconize the fact that it is unsigned.
    * to avoid the situation what I had to do was subtract (2^32 - 128)
    * 2^32 is 4 bytes. This problem only occures after the number 127.
    * This little fix just allows me to get to 255 characters
    * anything more and we overload the byte.
    */
    string return_string = "";
    for (unsigned int x=0; x<compressed_string.size(); x++)
    {
        unsigned int given_number = compressed_string[x];
        if (given_number > 255)
        {
            given_number -= 4294967040;
            // subtract 2^32 -128.
        }
       return_string += shortened_strings[given_number];
    }
    return return_string;
}
