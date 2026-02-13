CPMAddPackage(
  NAME Fractions
  GIT_TAG 1.0.1
  GITHUB_REPOSITORY luk036/fractions-cpp
)

CPMAddPackage(
  NAME rapidcheck
  GITHUB_REPOSITORY emil-e/rapidcheck
  GIT_TAG master
  OPTIONS "RC_BUILD_TESTS OFF" "RC_BUILD_EXAMPLES OFF" "RC_INSTALL OFF"
)

set(SPECIFIC_LIBS Fractions::Fractions)
