/*
 *  Copyright 2017 Bruno Ribeiro
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cursed/Text.hh>
#include <stdarg.h>


namespace cursed {


std::wstring Text::toWide(
	const std::string &input )
{
	wchar_t *temp = new(std::nothrow) wchar_t[input.length() + 1]();
	if (temp == NULL) return L"";

	mbstowcs(temp, input.c_str(), input.length());

	std::wstring output(temp);
	delete[] temp;

	return output;
}


std::string Text::toSingle(
	const std::wstring &input )
{
	char *temp = new(std::nothrow) char[input.length() * 2]();
	if (temp == NULL) return "";

	wcstombs(temp, input.c_str(), input.length());

	std::string output(temp);
	delete[] temp;

	return output;
}


std::wstring Text::wrap(
	const std::wstring &input,
	int columns )
{
	int i = 0;
	bool newline = false;
	std::wstring output;

	while (input[i] != 0)
	{
		int c = 0;
		int start = i;
		newline = true;

		//std::cerr << "start at " << i << " == '" << input[i] << "'" << std::endl;

		while (input[i] != '\n' && input[i] != 0 && c < columns)
		{
			++i;
			++c;
		}

		//std::cerr << "end at " << i << " == '" << input[i] << "'" << std::endl;

		int end = i;

		if (c >= columns)
		{
			if (input[i] == L'\n' || input[i] == L' ')
			{
				// discard the space
				end = i - 1;
				++i;
				newline = false;
			}
			else
			if (input[i] != 0)
			{
				// find the previous white-space
				while (i >= 0 && input[i] != L' ') --i;
				if (i < 0) abort();

				// discard the space
				end = i - 1;
				++i;
			}
		}
		else
		if (input[i] == L'\n')
		{
			// discard the new line
			end = i - 1;
			++i;
		}

		if (end - start > 0)
		{
			//std::cerr << "from" << start << " to "<< end << std::endl;
			//std::cerr << "Current: '" << input.substr(start, end - start + 1) << "'" << std::endl;
			output += input.substr(start, end - start + 1);
		}
		if (newline) output += L'\n';
	}

	return output;
}


std::wstring Text::format(
	const wchar_t *format,
	... )
{
	static const size_t MAX_INPUT = 1024 * 256 - 1;
	wchar_t *temp = new(std::nothrow) wchar_t[MAX_INPUT + 1];

    va_list argptr;
    va_start(argptr, format);
    vswprintf(temp, MAX_INPUT, format, argptr);
    va_end(argptr);

	std::wstring output(temp);
	delete[] temp;

	return output;
}


void Text::scale(
	const std::wstring &input,
	int &height,
	int &width )
{
	height = 0;
	width = 0;
	if (input.empty()) return;

	height = 1;
	int w = 0;

	for (size_t i = 0; i < input.length(); ++i)
	{
		if (input[i] == '\n')
		{
			++height;
			if (width < w) width = w;
			w = 0;
		}
		else
		{
			// count UTF-8 characters
			if ((input[i] & 0xc0) != 0x80) ++w;
		}
	}

	width++;
}

} // namespace cursed