#include <boost/test/unit_test.hpp>
#include <lib_manager/Dummy.hpp>

using namespace lib_manager;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    lib_manager::DummyClass dummy;
    dummy.welcome();
}
