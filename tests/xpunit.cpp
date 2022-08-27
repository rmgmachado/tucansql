/*****************************************************************************\
*  Copyright (c) 2012 - 2022 Tucan Software Pty Ltd. All rights reserved.
*
*  MIT License
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to
*  deal in the Software without restriction, including without limitation the
*  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
*  sell copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in
*  all copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
*  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
*  IN THE SOFTWARE.
*
*  You should have received a copy of the MIT License along with this program.
*  If not, see https://opensource.org/licenses/MIT.
\*****************************************************************************/
#include "xpunit.h"

class test_t
{
   inline static std::vector<int> test_;

public:
   test_t() = delete;
   ~test_t() = default;

   test_t(int val) noexcept
   {
      test_.push_back(val);
   }

   size_t count() const noexcept
   {
      return test_.size();
   }

   int get(size_t index)
   {
      if (index < count())
      {
         return test_[index];
      }
      return 0;
   }
};

TEST_CASE("Test static vector", "static")
{
   test_t val1(1);
   REQUIRE(val1.count() == 1 && val1.get(0) == 1);
   SECTION("Enter new context")
   {
      test_t val2(2);
      REQUIRE(val2.count() == 2 && val2.get(0) == 1);
   }
   REQUIRE(val1.count() == 2 && val1.get(0) == 1 && val1.get(1) == 2);
}

XPUNIT_MAIN("Test xpunit.h");
