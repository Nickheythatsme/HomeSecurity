#include <cstdio>
#include <string>

#ifndef HOME_SECURITY_HELPER_
#define HOME_SECURITY_HELPER_

namespace helper {

std::string long_to_string(long str)
{
  char buff[1024];
  sprintf(buff, "%d", str);
  return std::string(buff);
}

std::string unsigned_long_to_string(unsigned long str)
{
  char buff[1024];
  sprintf(buff, "%u", str);
  return std::string(buff);
}

}
#endif // HOME_SECURITY_HELPER_