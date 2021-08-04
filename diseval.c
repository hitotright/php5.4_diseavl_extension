/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2014 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_diseval.h"

/* If you declare any globals in php_diseval.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(diseval)
*/

/* True global resources - no need for thread safety here */
static int le_diseval;

void (*zend_execute_old)(zend_op_array *op_array TSRMLS_DC);
/* {{{ diseval_functions[]
 *
 * Every user visible function must have an entry in diseval_functions[].
 */
const zend_function_entry diseval_functions[] = {
	PHP_FE(diseval,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in diseval_functions[] */
};
/* }}} */

/* {{{ diseval_module_entry
 */
zend_module_entry diseval_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	"diseval",
	diseval_functions,
	PHP_MINIT(diseval),
	PHP_MSHUTDOWN(diseval),
	PHP_RINIT(diseval),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(diseval),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(diseval),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_DISEVAL_VERSION,
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_DISEVAL
ZEND_GET_MODULE(diseval)
#endif

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("diseval.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_diseval_globals, diseval_globals)
    STD_PHP_INI_ENTRY("diseval.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_diseval_globals, diseval_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_diseval_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_diseval_init_globals(zend_diseval_globals *diseval_globals)
{
	diseval_globals->global_value = 0;
	diseval_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(diseval)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	zend_execute_old = zend_execute;
	zend_execute = zend_execute_diseval;
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(diseval)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
  zend_execute = zend_execute_old;
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(diseval)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(diseval)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(diseval)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "diseval support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */


/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_diseval_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(diseval)
{
	php_printf("diseval extension working\n");
	RETURN_FALSE;
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/

void zend_execute_diseval(zend_op_array *op_array TSRMLS_DC)
{
	if (op_array->type == ZEND_EVAL_CODE) {
		zend_error(E_ERROR, "eval function is forbidden");
		zend_bailout();
	}
	zend_execute_old(op_array TSRMLS_CC);
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
