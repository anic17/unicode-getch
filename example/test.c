#include "..\unicode_getch.h" // Include the library

int main()
{
    InputUTF8 uchr = {0};
    while (1)
    {
        uchr = unicode_getch(); // Call unicode_getch() function
        printf("UTF8Char: 0x%02lx\t(%c)\tCTRL: 0x%02lx\n", uchr.utf8char, uchr.utf8char, uchr.flags); // Display the character and flags obtained
    }
}