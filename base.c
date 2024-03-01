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

struct ParsedArgs {
		char from;
		char to;
		size_t count;
		const char **numbers_raw;
};

void print_help(FILE *stream, const char *arg0) {
		fprintf(stream, "%s - Base number conversion utility\n\n", arg0);
		fprintf(stream, "Usage: %s [OPTIONS] NUMBER...\n\n", arg0);
		const char *options = ""
				"Options:\n"
				"    -f, --from N     convert from N base (default: 10)\n"
				"    -t, -to N        convert to N base (default: 16)\n"
				"    -h, --help       show this help page\n"
				"    -v, --version    prints version\n"
				"";

		fprintf(stream, options);
}

void print_version(FILE *stream, const char *arg0){
		fprintf(stream, "%s %s\n", arg0, VERSION);
}

struct ParsedArgs parse_args(size_t argc, const char *argv[]){
		// Iterate over passed args
		// Look for - characters for options
		// Stop looking for options if - not found on arg
		// Stop looking for options if -- without long name found
		// return struct with the rest of args
		char from = 10;
		char to = 16;
		int i;
		last_option = false;
		for (i = 0; i < argc; i++){
				if ('-' == argv[i][0]) {
						switch (argv[i][1]){
								case '-':
										break;
								default:
										print_help(stderr, argv[0]);
										exit(EXIT_FAILURE);
										break;
						}
				


				if (last_option) {
						argv += i;
						argc -= i;
						break;
				}

		}
		struct ParsedArgs parsed = { from, to, argc, argv };
		return parsed;
}

int main(size_t argc, const char *argv[]) {
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
