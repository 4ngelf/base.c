/*
 * base.c - Base number conversion utility
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2024 Angel Fuenmayor
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define VERSION "v0.1.0"

#define STREQ(STR1, STR2) strcmp(STR1, STR2) == 0

// used by print_help and print_version
static char* argv0;

// parsed arguments to operate
struct ParsedArgs {
		char from;
		char to;
		size_t count;
		const char **numbers_raw;
};

/* prints help on given stream */
void print_help(FILE *stream) {
		fprintf(stream, "%s - Base number conversion utility\n\n", argv0);
		fprintf(stream, "Usage: %s [OPTIONS] NUMBER...\n\n", argv0);
		const char *options = ""
				"Options:\n"
				"    -f, --from N     convert from N base (default: 10)\n"
				"    -t, -to N        convert to N base (default: 16)\n"
				"    -h, --help       show this help page\n"
				"    -v, --version    prints version\n"
				"";

		fprintf(stream, options);
}

/* prints version on given stream */
void print_version(FILE *stream){
		fprintf(stream, "%s %s\n", argv0, VERSION);
}

/* parse non-negative numbers from a string up to 'len' characters and returns the result.
 *
 * return -1 in case of failure. */
int parseuintl(char *string, int len){
	int result = 0;
	for (int i = 0; i < len; i++){
		if (string[i] >= '0' && string[i] <= '9'){
			result += (int)(string[i] - '0');
		} else {
			return -1;
		}
	}
	return result;
}

/* Compare two strings up to 'len' characters.
 *
 * returns 0 on equal.
 * returns non zero on non equal */
int strcmpl(const char *str1, const char *str2, int len){
	int cmp = 0;
	for (int i = 0; i < len; i++){
		cmp = str1[i] - str2[i];
	}
	return cmp;
}

/* Take argv and returns index as option.
 * returns -1 if not an option.
 * */
int get_option(size_t *index, int *value, const char *argv[], int size_args){
	// If invalid option use this:
	// print_help(stderr, argv[0]);
	// exit(EXIT_FAILURE);
	if (argv[*index][0] != '-' || !argv[*index][1]){
		return -1;
	}



	(*index)++;
}

/* Process list argc and argv and return a struct of ParsedArgs
 *
 * NOTE: print_help works with hardcoded text so changes here are not
 *       reflected and need to be edited manually */
struct ParsedArgs parse_args(size_t argc, const char *argv[]){
	// ---------------------------------------
	// Defaults
	// ---------------------------------------
	int from = 10;
	int to = 16;

	// ---------------------------------------
	// loop controllers
	// ---------------------------------------
	int index = 1;
	bool finished = false;
	while (index < argc || !finished){
		// ---------------------------------------
		// action controllers
		// ---------------------------------------
		int selected_option = -1;
		int int_value;

		struct {
			char *name;
			char *long_name;
			bool has_value;
		} options[] = {
			{ "-v", "--version", false },
			{ "-h", "--help", false },
			{ "-t", "--to", true },
			{ "-f", "--from", true }
		};

		// ---------------------------------------
		// Checks
		// ---------------------------------------
		if (strcmpl("--", argv[index], 3) == 0){
			index++;
			break;
		}

		if (argv[index][0] != '-' || !argv[index][1]){
			finished = true;
			break;
		}

		// ---------------------------------------
		// Determine which option to operate
		// ---------------------------------------
		int is_long = strcmpl("--", argv[index], 2) == 0;

		for (int j = 0; j < (sizeof(options) / sizeof(options[0])); j++){
			char *subject = is_long ? options[j].long_name : options[j].name;
			int subject_len = strlen(subject);
			if (strcmpl(subject, argv[index], subject_len) == 0){
				selected_option = j;
			} else {
				print_help(stderr);
				exit(EXIT_FAILURE);
			}

			if (options[j].has_value){
				char *str_value;
				if (strlen(argv[index]) == subject_len){
					index++;
					str_value = argv[index];
				} else {
					str_value = argv[index] + subject_len;
				}

				int_value = parseuintl(str_value, 2);
			}

			if (int_value == -1){
				print_help(stderr);
				exit(EXIT_FAILURE);
			}
		}
		index++;

		// ---------------------------------------
		// Actions on options
		// ---------------------------------------
		switch (selected_option){
		// Option --version
		case 0:
			print_version(stdout);
			exit(EXIT_SUCCESS);
			break;
		// Option --help
		case 1:
			print_help(stdout);
			exit(EXIT_SUCCESS);
			break;
		// Option --to
		case 2:
			to = int_value;
			break;
		// Option --from
		case 3:
			from = int_value;
			break;
		// No more options
		default:
			finished = true;
			break;
		}

	}

	struct ParsedArgs parsed = { (char) from, (char) to, argc - index, argv + index };
	return parsed;
}

int main(int argc, const char *argv[]) {
	argv0 = argv[0];
	struct ParsedArgs parsed = parse_args(argc, argv);
	printf(
		"Data parsed:\n"
		" --from: %i\n"
		" --to: %i\n"
		" Numbers: ", parsed.from, parsed.to);

	for (size_t i = 0; i < parsed.count; i += 1){
		printf("%s ", parsed.numbers_raw[i]);
	}
	puts("");

	return 0;
}
