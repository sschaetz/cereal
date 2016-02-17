/*
  Copyright (c) 2014, Randolph Voorhies, Shane Grant
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
      * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
      * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
      * Neither the name of cereal nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL RANDOLPH VOORHIES AND SHANE GRANT BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "common.hpp"
#include <boost/test/unit_test.hpp>


template <typename T>
struct template_test_struct
{
    T x;
};

template <typename Archive, typename T>
std::string save_minimal(Archive const &,
        template_test_struct<T> const & m)
{
    return std::to_string(m.x);
}

template <typename Archive, typename T>
void load_minimal(Archive const &,
        template_test_struct<T>& m, std::string const & str)
{
    m.x = std::stoi(str);
}

template <class IArchive, class OArchive>
void test_template_structs_minimal()
{
    template_test_struct <uint32_t> mb_i;

    std::ostringstream os;
    {
      OArchive oar(os);
      oar(mb_i);
    }

    decltype(mb_i) mb_o;

    std::istringstream is(os.str());
    {
      IArchive iar(is);
      iar(mb_o);
    }

    BOOST_CHECK(mb_i.x == mb_o.x);

}

BOOST_AUTO_TEST_CASE( template_test_struct_minimal_all )
{
    test_template_structs_minimal<cereal::BinaryInputArchive, cereal::BinaryOutputArchive>();
    test_template_structs_minimal<cereal::PortableBinaryInputArchive, cereal::PortableBinaryOutputArchive>();
    test_template_structs_minimal<cereal::XMLInputArchive, cereal::XMLOutputArchive>();
    test_template_structs_minimal<cereal::JSONInputArchive, cereal::JSONOutputArchive>();
}
