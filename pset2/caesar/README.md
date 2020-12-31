## SPECIFICATION ##
Design and implement a program, caesar, that encrypts messages using Caesar’s cipher.

1. Implement your program in a file called caesar.c in a ~/pset2/caesar directory.
2. Your program must accept a single command-line argument, a non-negative integer. Let’s call it k for the sake of discussion.
3. If your program is executed without any command-line arguments or with more than one command-line argument, your program should print an error message of your choice (with printf) and return from main a value of 1 (which tends to signify an error) immediately.
4. If any of the characters of the command-line argument is not a decimal digit, your program should print the message Usage: ./caesar key and return from main a value of 1.
5. Do not assume that k will be less than or equal to 26. Your program should work for all non-negative integral values of k less than 2^31 - 26. In other words, you don’t need to worry if your program eventually breaks if the user chooses a value for k that’s too big or almost too big to fit in an int. (Recall that an int can overflow.) But, even if k is greater than 26, alphabetical characters in your program’s input should remain alphabetical characters in your program’s output. For instance, if k is 27, A should not become [ even though [ is 27 positions away from A in ASCII, per http://www.asciichart.com/[asciichart.com]; A should become B, since B is 27 positions away from A, provided you wrap around from Z to A.
6. Your program must output plaintext: (without a newline) and then prompt the user for a string of plaintext (using get_string).
7. Your program must output ciphertext: (without a newline) followed by the plaintext’s corresponding ciphertext, with each alphabetical character in the plaintext “rotated” by k positions; non-alphabetical characters should be outputted unchanged.
8. Your program must preserve case: capitalized letters, though rotated, must remain capitalized letters; lowercase letters, though rotated, must remain lowercase letters.
9. After outputting ciphertext, you should print a newline. Your program should then exit by returning 0 from main.

How to begin? Let’s approach this problem one step at a time.

## Pseudocode ##
First, write some pseudocode that implements this program, even if not (yet!) sure how to write it in code. There’s no one right way to write pseudocode, but short English sentences suffice. Recall how we wrote pseudocode for finding Mike Smith. Odds are your pseudocode will use (or imply using!) one or more functions, conditions, Boolean expressions, loops, and/or variables.

# Spoiler
There’s more than one way to do this, so here’s just one!

1. Check that program was run with one command-line argument
2. Iterate over the provided argument to make sure all characters are digits
3. Convert that command-line argument from a string to an int
4. Prompt user for plaintext
5. Iterate over each character of the plaintext:
	a. If it is an uppercase letter, rotate it, preserving case, then print out the rotated character
	b. If it is a lowercase letter, rotate it, preserving case, then print out the rotated character
	c. If it is neither, print out the character as is
6. Print a newline
It’s okay to edit your own after seeing this pseudocode here, but don’t simply copy/paste ours into your own!

## Counting Command-Line Arguments
Whatever your pseudocode, let’s first write only the C code that checks whether the program was run with a single command-line argument before adding additional functionality.

Specifically, in a new file called caesar.c write code such that: if the user provides exactly one command-line argument, it prints Success; if the user provides no command-line arguments, or two or more, it prints Usage: ./caesar key. Remember, since this key is coming from the command line at runtime, and not via get_string, we don’t have an opportunity to re-prompt the user. The behavior of the resulting program should be like the below.

$ ./caesar 20
Success
or

$ ./caesar
Usage: ./caesar key
or

$ ./caesar 1 2 3
Usage: ./caesar key

# Hints
1. Recall that you can compile your program with make.
2. Recall that you can print with printf.
3. Recall that argc and argv give you information about what was provided at the command line.
4. Recall that the name of the program itself (here, ./caesar) is in argv[0].

# Accessing the Key
Now that your program is (hopefully!) accepting input as prescribed, it’s time for another step.

Recall that in our program, we must defend against users who technically provide a single command-line argument (the key), but provide something that isn’t actually an integer, for example:

$ ./caesar xyz
Before we start to analyze the key for validity, though, let’s make sure we can actually read it. Further modify caesar.c such that it not only checks that the user has provided just one command-line argument, but after verifying that, prints out that single command-line argument. So, for example, the behavior might look like this:

$ ./caesar 20
Success
20

# Hints
1. Recall that argc and argv give you information about what was provided at the command line.
2. Recall that argv is an array of strings.
3. Recall that with printf we can print a string using %s as the placeholder.
4. Recall that computer scientists like counting starting from 0.
5. Recall that we can access individual elements of an array, such as argv using square brackets, for example: argv[0].

# Validating the Key
Now that you know how to read the key, let’s analyze it. Modify caesar.c such that instead of printing out the command-line argument provided, your program instead checks to make sure that each character of that command line argument is a decimal digit (i.e., 0, 1, 2, etc.) and, if any of them are not, terminates after printing the message Usage: ./caesar key. But if the argument consists solely of digit characters, you should convert that string (recall that argv is an array of strings, even if those strings happen to look like numbers) to an actual integer, and print out the integer, as via %i with printf. So, for example, the behavior might look like this:

$ ./caesar 20
Success
20
or

$ ./caesar 20x
Usage: ./caesar key

# Hints
1. Recall that argv is an array of strings.
2. Recall that a string, meanwhile, is just an array of chars.
3. Recall that the string.h header file contains a number of useful functions that work with strings.
4. Recall that we can use a loop to iterate over each character of a string if we know its length.
5. Recall that the ctype.h header file contains a number of useful functions that tell us things about characters.
6. Recall that we can return nonzero values from main to indicate that our program did not finish successfully.
7. Recall that with printf we can print an integer using %i as the placeholder.
8. Recall that the atoi function converts a string that looks like a number into that number.

## Peeking Underneath the Hood
As human beings it’s easy for us to intuitively understand the formula described above, inasmuch as we can say “H + 1 = I”. But can a computer understand that same logic? Let’s find out. For now, we’re going to temporarily ignore the key the user provided and instead prompt the user for a secret message and attempt to shift all of its characters by just 1.

Extend the functionality of caesar.c such that, after validating the key, we prompt the user for a string and then shift all of its characters by 1, printing out the result. We can also at this point probably remove the line of code we wrote earlier that prints Success. All told, this might result in this behavior:

$ ./caesar 1
plaintext:  hello
ciphertext: ifmmp

# Hints
1. Try to iterate over every character in the plaintext and literally add 1 to it, then print it.
2. If c is a variable of type char in C, what happens when you call printf("%c", c + 1)?

## Your Turn
Now it’s time to tie everything together! Instead of shifting the characters by 1, modify caesar.c to instead shift them by the actual key value. And be sure to preserve case! Uppercase letters should stay uppercase, lowercase letters should stay lowercase, and characters that aren’t alphabetical should remain unchanged.

# Hints
1. Best to use the modulo (i.e., remainder) operator, %, to handle wraparound from Z to A! But how?
2. Things get weird if we try to wrap Z or z by 1 using the technique in the previous section.
3. Things get weird also if we try to wrap punctuation marks using that technique.
4. Recall that ASCII maps all printable characters to numbers.
5. Recall that the ASCII value of A is 65. The ASCII value of a, meanwhile, is 97.
6. If you’re not seeing any output at all when you call printf, odds are it’s because you’re printing characters outside of the valid ASCII range from 0 to 127. Try printing characters as numbers (using %i instead of %c) at first to see what values you’re printing, and make sure you’re only ever trying to print valid characters!