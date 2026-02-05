#ifndef ULTILS_H
#define ULTILS_H

#include <stddef.h> /* For size_t */

/* * Remove the trailing newline character ('\n') from a string.
 * This is useful when processing input from fgets().
 * str: The string to modify.
 */
void removeNewline(char* str);

/* * Clear the console screen.
 * Supports both Windows (cls) and Linux/Unix (clear).
 */
void clearScreen();

/* * Safely prompt and get an integer input from the user.
 * Handles invalid inputs and prevents buffer overflow or leftover newlines.
 * prompt: The message to display to the user.
 * Returns: The valid integer entered by the user.
 */
int getIntInput(const char* prompt);

/* * Safely prompt and get a string input with a maximum length.
 * Automatically removes the trailing newline character.
 * prompt: The message to display to the user.
 * buffer: The character array to store the input.
 * size: The maximum size of the buffer.
 */
void getStringInput(const char* prompt, char* buffer, size_t size);

#endif