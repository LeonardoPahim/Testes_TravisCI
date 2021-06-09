#include "identifier.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(identifier);

TEST_SETUP(identifier)
{
}

TEST_TEAR_DOWN(identifier)
{
}

void IniciaNumero(void){
   int result = 0;
   result = system("echo '123e' | ./identifier");
   TEST_ASSERT_EQUAL_INT(1, result);
}


/*
TEST(identifier, identifierTest2)
{
  // This test will fail
  TEST_ASSERT_EQUAL(2, foo(1,2));
}
*/