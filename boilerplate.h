#define print_ok() if (debug) printf ("%s: OK.\n", __FUNCTION__);
#define print_error() if (!silent) perror (__FUNCTION__);
#define test(block) if (block == -1) { print_error (); return false; }
#define final_test(block) test (block) else { print_ok (); return true; }
