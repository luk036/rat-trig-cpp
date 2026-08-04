CPMAddPackage(
  NAME Fractions
  GIT_TAG v1.1.4
  GITHUB_REPOSITORY luk036/fractions-cpp
  OPTIONS "FRACTIONS_BUILD_TESTS OFF"
)

CPMAddPackage(
  NAME rapidcheck
  GITHUB_REPOSITORY emil-e/rapidcheck
  GIT_TAG master
  OPTIONS "RC_BUILD_TESTS OFF" "RC_BUILD_EXAMPLES OFF" "RC_INSTALL OFF"
)

set(SPECIFIC_LIBS Fractions::Fractions)
