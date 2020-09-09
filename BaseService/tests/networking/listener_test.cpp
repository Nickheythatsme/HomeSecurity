#define BOOST_TEST_MODULE boost_test_macro_overview
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE( test_macro_overview )
{
  namespace tt = boost::test_tools;
  int a = 1;
  int b = 2;
  BOOST_TEST(a == b - 1);
  BOOST_TEST((int)(a + 1) < b);
  BOOST_TEST((int)(b - 1) > a, a << " < " << b - 1 << " does not hold");
  BOOST_TEST(a == b, tt::bitwise());
}