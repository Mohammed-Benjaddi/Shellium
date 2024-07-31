#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Parse a string and remove quotes if present.
 *
 * @param str The input string to parse.
 * @return The parsed string.
 */
char* parse_string(const char* str) {
    // Check if the string is NULL
    if (str == NULL) {
        return NULL;
    }

    // Allocate memory for the output string
    char* output = malloc(strlen(str) + 1);
    if (output == NULL) {
        return NULL;
    }

    // Initialize the output string index
    int output_index = 0;

    // Initialize a flag to track if we are inside a quoted string
    int in_quote = 0;

    // Iterate over the input string
    for (int i = 0; i < strlen(str); i++) {
        // Check if the current character is a quote
        if (str[i] == '"' || str[i] == '\'') {
            // If we are not inside a quoted string, set the flag to 1
            if (!in_quote) {
                in_quote = 1;
            } else {
                // If we are inside a quoted string and the current character is a quote,
                // set the flag to 0
                in_quote = 0;
            }
        } else if (in_quote) {
            // If we are inside a quoted string, add the current character to the output string
            output[output_index++] = str[i];
        } else if (!isspace(str[i])) {
            // If we are not inside a quoted string and the current character is not a space,
            // add the current character to the output string
            output[output_index++] = str[i];
        } else if (output_index > 0 && output[output_index - 1] != ' ') {
            // If the current character is a space and the last character in the output string is not a space,
            // add a space to the output string
            output[output_index++] = ' ';
        }
    }

    // Null-terminate the output string
    output[output_index] = '\0';

    // Return the parsed string
    return output;
}

int main() {
    // Test the function
    char* str1 = parse_string("\"hello world\"");
    printf("%s\n", str1);  // Output: hello world
    free(str1);

    char* str2 = parse_string("\"hello\" \"world\"");
    printf("%s\n", str2);  // Output: hello world
    free(str2);

    char* str3 = parse_string("\"hello\'world\"");
    printf("---> %s\n", str3);  // Output: hello'world
    free(str3);

    return 0;
}