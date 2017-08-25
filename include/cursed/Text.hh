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

#ifndef CURSED_TEXT_HH
#define CURSED_TEXT_HH


#include <string>


namespace cursed {


class Text
{
	public:
		static std::wstring toWide(
			const std::string &input );

		static std::string toSingle(
			const std::wstring &input );

		static std::wstring wrap(
			const std::wstring &input,
			int columns );

		static void scale(
			const std::wstring &input,
			int &height,
			int &width );

		static std::wstring format(
			const wchar_t *format,
			... );
};



} // namespace cursed


#endif // CURSED_TEXT_HH