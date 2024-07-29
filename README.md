# unicode-getch

A better version of `conio.h`'s `getch()` function that includes full support for Unicode and can retrieve more keyboard combinations.

## Why Use unicode-getch?

The `getch()` (and `getche()`) functions in `conio.h` are cumbersome and often require multiple calls to handle a single event. For example, `getch()` returns the value 224 (0xE0) after pressing a non-printable character, which is inconvenient. Additionally, `getch()` cannot handle Unicode characters properly, causing your program to crash and introducing a vulnerability. `unicode-getch` addresses these issues by using a struct to store character and control data separately, thus avoiding the need for complex filtering or repeated calls, while fixing the crashes caused by multiple bytes being written simultaneously.

## Features

- Handles Unicode characters correctly.
- Detects individual control keys (Alt, Control, Shift).
- Stores character and control data separately.

## Usage

[!NOTE]
> This library is Windows-only. Depending on your compiler, you may need to link against `user32` by adding `-luser32` to your compiler options.

The program defines a struct `InputUTF8` as follows:

```c
typedef struct InputUTF8
{
    long utf8char;
    long flags;
} InputUTF8;
```
- `utf8char` contains the retrieved Unicode character in UTF-8 Big Endian. For example, the lowercase Greek theta (θ) is represented as `0xceb8` in UTF-8 encoding.
- `flags` contains information about pressed keys that are non-printable, which the lowest byte is the [WinAPI virtual key code equivalent](https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes).

The most significant bits are toggled for modifier keys: `0x80000000` for <kbd>Alt</kbd>, `0x40000000` for <kbd>Control</kbd>, and `0x20000000` for <kbd>Shift</kbd>. This allows the program to capture both Unicode characters and control keys simultaneously (e.g., <kbd>Alt + A</kbd>).

## Example
Using the unicode-getch library is straightforward. Simply include the library with `#include "unicode_getch.h"`. Below is an example demonstrating how to use unicode-getch. You only need to call `unicode_getch()` and store its result in an `InputUTF8` struct.

```c
#include "unicode_getch.h"

int main()
{
    InputUTF8 uchr = {0};
    while (1)
    {
        uchr = unicode_getch();
        printf("UTF8Char: 0x%02lx\t(%c)\tCTRL: 0x%02lx\n", uchr.utf8char, uchr.utf8char, uchr.flags);
    }
}
```

## Technical Limitation

Due to the internal use of UTF-16 by WinAPI, unicode-getch only supports codepoints up to U+FFFF. This means that some characters, like the grinning face emoji (😀), return the replacement character code (0xefbfbd), while others, like the star and crescent emoji (☪), are supported. All Unicode characters with codepoints less than or equal to U+FFFF are supported.



## Contributing
If you want to contribute to unicode-getch, feel free to fork the project and create a [pull request](https://github.com/anic17/unicode-getch/pulls) with the changes you want to do, describing the changes you made. 
A modified version of this library is used in the rewritten version of [Newtrodit](https://github.com/anic17/Newtrodit/tree/unicode-newtrodit).

## Contact

Feel free to contact me on Discord (@anic17) or my server <a href="https://discord.gg/J628dBqQgb">Program Dream</a>.  
<a href="https://discord.gg/J628dBqQgb"><img src="https://img.shields.io/discord/728958932210679869?style=flat-square&logo=appveyor"></a>


**Copyright &copy; 2024 anic17 Software**
<!-- 
View counter 
-->
<img src="https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2Fanic17%2Funicode-getch&count_bg=%23FFFFFF&title_bg=%23FFFFFF&icon=&icon_color=%23FFFFFF&title=hits&edge_flat=false" height=0 width=0>
