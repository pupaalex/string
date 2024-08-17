#include "main.h"

int main() {
  Suite *str, *sprintf, *parser;
  SRunner *strsr, *sprintfsr, *parserfsr;
  int nfailed;

  str = string_suite();
  sprintf = sprintf_suite();
  parser = parser_suite();
  strsr = srunner_create(str);
  sprintfsr = srunner_create(sprintf);
  parserfsr = srunner_create(parser);
  srunner_run_all(strsr, CK_NORMAL);
  srunner_run_all(sprintfsr, CK_NORMAL);
  srunner_run_all(parserfsr, CK_NORMAL);
  nfailed = srunner_ntests_failed(strsr);
  nfailed += srunner_ntests_failed(sprintfsr);
  nfailed += srunner_ntests_failed(parserfsr);
  srunner_free(strsr);
  srunner_free(sprintfsr);
  srunner_free(parserfsr);
  return nfailed != 0;
}
