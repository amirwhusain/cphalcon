
#ifdef HAVE_CONFIG_H
#include "../../ext_config.h"
#endif

#include <php.h>
#include "../../php_ext.h"
#include "../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/memory.h"
#include "kernel/concat.h"
#include "ext/spl/spl_exceptions.h"
#include "kernel/exception.h"
#include "kernel/operators.h"
#include "kernel/object.h"
#include "kernel/hash.h"
#include "kernel/array.h"
#include "kernel/string.h"
#include "kernel/fcall.h"


/*
 +------------------------------------------------------------------------+
 | Phalcon Framework                                                      |
 +------------------------------------------------------------------------+
 | Copyright (c) 2011-2014 Phalcon Team (http://www.phalconphp.com)       |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file docs/LICENSE.txt.                        |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
 |          Eduar Carvajal <eduar@phalconphp.com>                         |
 +------------------------------------------------------------------------+
 */
/**
 * Phalcon\Db\Dialect
 *
 * This is the base class to each database dialect. This implements
 * common methods to transform intermediate code into its RDBM related syntax
 */
ZEPHIR_INIT_CLASS(Phalcon_Db_Dialect) {

	ZEPHIR_REGISTER_CLASS(Phalcon\\Db, Dialect, phalcon, db_dialect, phalcon_db_dialect_method_entry, ZEND_ACC_EXPLICIT_ABSTRACT_CLASS);

	zend_declare_property_null(phalcon_db_dialect_ce, SL("_escapeChar"), ZEND_ACC_PROTECTED TSRMLS_CC);

	return SUCCESS;

}

/**
 * Generates the SQL for LIMIT clause
 *
 *<code>
 * $sql = $dialect->limit('SELECT * FROM robots', 10);
 * echo $sql; // SELECT * FROM robots LIMIT 10
 *</code>
 *
 * @param string sqlQuery
 * @param int number
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect, limit) {

	int number;
	zval *sqlQuery_param = NULL, *number_param = NULL, _0, _1;
	zval *sqlQuery = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &sqlQuery_param, &number_param);

	if (Z_TYPE_P(sqlQuery_param) != IS_STRING && Z_TYPE_P(sqlQuery_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'sqlQuery' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(sqlQuery_param) == IS_STRING) {
		sqlQuery = sqlQuery_param;
	} else {
		ZEPHIR_INIT_VAR(sqlQuery);
		ZVAL_EMPTY_STRING(sqlQuery);
	}
	number = zephir_get_intval(number_param);


	ZEPHIR_SINIT_VAR(_0);
	ZVAL_LONG(&_0, number);
	if (zephir_is_numeric(&_0)) {
		ZEPHIR_SINIT_VAR(_1);
		ZVAL_LONG(&_1, number);
		ZEPHIR_CONCAT_VSV(return_value, sqlQuery, " LIMIT ", &_1);
		RETURN_MM();
	}
	RETURN_CTOR(sqlQuery);

}

/**
 * Returns a SQL modified with a FOR UPDATE clause
 *
 *<code>
 * $sql = $dialect->forUpdate('SELECT * FROM robots');
 * echo $sql; // SELECT * FROM robots FOR UPDATE
 *</code>
 *
 * @param	string sqlQuery
 * @return	string
 */
PHP_METHOD(Phalcon_Db_Dialect, forUpdate) {

	zval *sqlQuery_param = NULL;
	zval *sqlQuery = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &sqlQuery_param);

	if (Z_TYPE_P(sqlQuery_param) != IS_STRING && Z_TYPE_P(sqlQuery_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'sqlQuery' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(sqlQuery_param) == IS_STRING) {
		sqlQuery = sqlQuery_param;
	} else {
		ZEPHIR_INIT_VAR(sqlQuery);
		ZVAL_EMPTY_STRING(sqlQuery);
	}


	ZEPHIR_CONCAT_VS(return_value, sqlQuery, " FOR UPDATE");
	RETURN_MM();

}

/**
 * Returns a SQL modified with a LOCK IN SHARE MODE clause
 *
 *<code>
 * $sql = $dialect->sharedLock('SELECT * FROM robots');
 * echo $sql; // SELECT * FROM robots LOCK IN SHARE MODE
 *</code>
 *
 * @param	string sqlQuery
 * @return	string
 */
PHP_METHOD(Phalcon_Db_Dialect, sharedLock) {

	zval *sqlQuery_param = NULL;
	zval *sqlQuery = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &sqlQuery_param);

	if (Z_TYPE_P(sqlQuery_param) != IS_STRING && Z_TYPE_P(sqlQuery_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'sqlQuery' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(sqlQuery_param) == IS_STRING) {
		sqlQuery = sqlQuery_param;
	} else {
		ZEPHIR_INIT_VAR(sqlQuery);
		ZVAL_EMPTY_STRING(sqlQuery);
	}


	ZEPHIR_CONCAT_VS(return_value, sqlQuery, " LOCK IN SHARE MODE");
	RETURN_MM();

}

/**
 * Gets a list of columns with escaped identifiers
 *
 *<code>
 * echo $dialect->getColumnList(array('column1', 'column'));
 *</code>
 *
 * @param	array columnList
 * @return	string
 */
PHP_METHOD(Phalcon_Db_Dialect, getColumnList) {

	HashTable *_1;
	HashPosition _0;
	zval *columnList, *strList, *escapeChar, *column = NULL, **_2, *_3 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &columnList);



	ZEPHIR_INIT_VAR(strList);
	array_init(strList);
	ZEPHIR_OBS_VAR(escapeChar);
	zephir_read_property_this(&escapeChar, this_ptr, SL("_escapeChar"), PH_NOISY_CC);
	zephir_is_iterable(columnList, &_1, &_0, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HVALUE(column, _2);
		ZEPHIR_INIT_LNVAR(_3);
		ZEPHIR_CONCAT_VVV(_3, escapeChar, column, escapeChar);
		zephir_array_append(&strList, _3, PH_SEPARATE);
	}
	zephir_fast_join_str(return_value, SL(", "), strList TSRMLS_CC);
	RETURN_MM();

}

/**
 * Transforms an intermediate representation for a expression into a database system valid expression
 *
 * @param array expression
 * @param string escapeChar
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect, getSqlExpression) {

	HashTable *_8, *_13;
	HashPosition _7, _12;
	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *escapeChar = NULL, *_1 = NULL;
	zval *expression, *escapeChar_param = NULL, *type, *domain, *operator, *left = NULL, *right = NULL, *name = NULL, *sqlItems, *escapedName = NULL, *sqlArguments, *arguments, *argument = NULL, *item = NULL, *_0, *_2, *_4, *_5, *_6 = NULL, **_9, *_10 = NULL, *_11 = NULL, **_14, *_15, *_16;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &expression, &escapeChar_param);

	if (!escapeChar_param) {
		ZEPHIR_INIT_VAR(escapeChar);
		ZVAL_EMPTY_STRING(escapeChar);
	} else {
		zephir_get_strval(escapeChar, escapeChar_param);
	}


	if (ZEPHIR_GLOBAL(db).escape_identifiers) {
		if (ZEPHIR_IS_STRING(escapeChar, "")) {
			ZEPHIR_OBS_VAR(_0);
			zephir_read_property_this(&_0, this_ptr, SL("_escapeChar"), PH_NOISY_CC);
			zephir_get_strval(_1, _0);
			ZEPHIR_CPY_WRT(escapeChar, _1);
		}
	}
	if (Z_TYPE_P(expression) != IS_ARRAY) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "Invalid SQL expression", "phalcon/db/dialect.zep", 127);
		return;
	}
	ZEPHIR_OBS_VAR(type);
	if (!(zephir_array_isset_string_fetch(&type, expression, SS("type"), 0 TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "Invalid SQL expression", "phalcon/db/dialect.zep", 131);
		return;
	}
	if (ZEPHIR_IS_STRING(type, "qualified")) {
		ZEPHIR_OBS_VAR(name);
		zephir_array_fetch_string(&name, expression, SL("name"), PH_NOISY TSRMLS_CC);
		if (ZEPHIR_GLOBAL(db).escape_identifiers) {
			ZEPHIR_INIT_VAR(escapedName);
			ZEPHIR_CONCAT_VVV(escapedName, escapeChar, name, escapeChar);
		} else {
			ZEPHIR_CPY_WRT(escapedName, name);
		}
		ZEPHIR_OBS_VAR(domain);
		if (zephir_array_isset_string_fetch(&domain, expression, SS("domain"), 0 TSRMLS_CC)) {
			if (ZEPHIR_GLOBAL(db).escape_identifiers) {
				ZEPHIR_CONCAT_VVVSV(return_value, escapeChar, domain, escapeChar, ".", escapedName);
				RETURN_MM();
			} else {
				ZEPHIR_CONCAT_VSV(return_value, domain, ".", escapedName);
				RETURN_MM();
			}
		}
		RETURN_CCTOR(escapedName);
	}
	if (ZEPHIR_IS_STRING(type, "literal")) {
		zephir_array_fetch_string(&_2, expression, SL("value"), PH_NOISY | PH_READONLY TSRMLS_CC);
		RETURN_CTOR(_2);
	}
	if (ZEPHIR_IS_STRING(type, "binary-op")) {
		zephir_array_fetch_string(&_2, expression, SL("left"), PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&left, this_ptr, "getsqlexpression", &_3, _2, escapeChar);
		zephir_check_call_status();
		zephir_array_fetch_string(&_4, expression, SL("right"), PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&right, this_ptr, "getsqlexpression", &_3, _4, escapeChar);
		zephir_check_call_status();
		zephir_array_fetch_string(&_5, expression, SL("op"), PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CONCAT_VSVSV(return_value, left, " ", _5, " ", right);
		RETURN_MM();
	}
	if (ZEPHIR_IS_STRING(type, "unary-op")) {
		ZEPHIR_OBS_VAR(operator);
		zephir_array_fetch_string(&operator, expression, SL("op"), PH_NOISY TSRMLS_CC);
		ZEPHIR_OBS_NVAR(left);
		if (zephir_array_isset_string_fetch(&left, expression, SS("left"), 0 TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(&_6, this_ptr, "getsqlexpression", &_3, left, escapeChar);
			zephir_check_call_status();
			ZEPHIR_CONCAT_VV(return_value, _6, operator);
			RETURN_MM();
		}
		ZEPHIR_OBS_NVAR(right);
		if (zephir_array_isset_string_fetch(&right, expression, SS("right"), 0 TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(&_6, this_ptr, "getsqlexpression", &_3, right, escapeChar);
			zephir_check_call_status();
			ZEPHIR_CONCAT_VV(return_value, _6, operator);
			RETURN_MM();
		}
	}
	if (ZEPHIR_IS_STRING(type, "placeholder")) {
		zephir_array_fetch_string(&_2, expression, SL("value"), PH_NOISY | PH_READONLY TSRMLS_CC);
		RETURN_CTOR(_2);
	}
	if (ZEPHIR_IS_STRING(type, "parentheses")) {
		zephir_array_fetch_string(&_2, expression, SL("left"), PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_6, this_ptr, "getsqlexpression", &_3, _2, escapeChar);
		zephir_check_call_status();
		ZEPHIR_CONCAT_SVS(return_value, "(", _6, ")");
		RETURN_MM();
	}
	if (ZEPHIR_IS_STRING(type, "functionCall")) {
		ZEPHIR_OBS_NVAR(name);
		zephir_array_fetch_string(&name, expression, SL("name"), PH_NOISY TSRMLS_CC);
		ZEPHIR_INIT_VAR(sqlArguments);
		array_init(sqlArguments);
		ZEPHIR_OBS_VAR(arguments);
		if (zephir_array_isset_string_fetch(&arguments, expression, SS("arguments"), 0 TSRMLS_CC)) {
			zephir_is_iterable(arguments, &_8, &_7, 0, 0);
			for (
			  ; zephir_hash_get_current_data_ex(_8, (void**) &_9, &_7) == SUCCESS
			  ; zephir_hash_move_forward_ex(_8, &_7)
			) {
				ZEPHIR_GET_HVALUE(argument, _9);
				ZEPHIR_CALL_METHOD(&_10, this_ptr, "getsqlexpression", &_3, argument, escapeChar);
				zephir_check_call_status();
				zephir_array_append(&sqlArguments, _10, PH_SEPARATE);
			}
			ZEPHIR_INIT_VAR(_11);
			zephir_fast_join_str(_11, SL(", "), sqlArguments TSRMLS_CC);
			ZEPHIR_CONCAT_VSVS(return_value, name, "(", _11, ")");
			RETURN_MM();
		} else {
			ZEPHIR_CONCAT_VS(return_value, name, "()");
			RETURN_MM();
		}
	}
	if (ZEPHIR_IS_STRING(type, "list")) {
		ZEPHIR_INIT_VAR(sqlItems);
		array_init(sqlItems);
		zephir_array_fetch_long(&_2, expression, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
		zephir_is_iterable(_2, &_13, &_12, 0, 0);
		for (
		  ; zephir_hash_get_current_data_ex(_13, (void**) &_14, &_12) == SUCCESS
		  ; zephir_hash_move_forward_ex(_13, &_12)
		) {
			ZEPHIR_GET_HVALUE(item, _14);
			ZEPHIR_CALL_METHOD(&_6, this_ptr, "getsqlexpression", &_3, item, escapeChar);
			zephir_check_call_status();
			zephir_array_append(&sqlItems, _6, PH_SEPARATE);
		}
		ZEPHIR_INIT_NVAR(_11);
		zephir_fast_join_str(_11, SL(", "), sqlItems TSRMLS_CC);
		ZEPHIR_CONCAT_SVS(return_value, "(", _11, ")");
		RETURN_MM();
	}
	if (ZEPHIR_IS_STRING(type, "all")) {
		RETURN_MM_STRING("*", 1);
	}
	if (ZEPHIR_IS_STRING(type, "cast")) {
		zephir_array_fetch_string(&_2, expression, SL("left"), PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&left, this_ptr, "getsqlexpression", &_3, _2, escapeChar);
		zephir_check_call_status();
		zephir_array_fetch_string(&_4, expression, SL("right"), PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&right, this_ptr, "getsqlexpression", &_3, _4, escapeChar);
		zephir_check_call_status();
		ZEPHIR_CONCAT_SVSVS(return_value, "CAST(", left, " AS ", right, ")");
		RETURN_MM();
	}
	if (ZEPHIR_IS_STRING(type, "convert")) {
		zephir_array_fetch_string(&_2, expression, SL("left"), PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&left, this_ptr, "getsqlexpression", &_3, _2, escapeChar);
		zephir_check_call_status();
		zephir_array_fetch_string(&_4, expression, SL("right"), PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&right, this_ptr, "getsqlexpression", &_3, _4, escapeChar);
		zephir_check_call_status();
		ZEPHIR_CONCAT_SVSVS(return_value, "CONVERT(", left, " USING ", right, ")");
		RETURN_MM();
	}
	ZEPHIR_INIT_VAR(_15);
	object_init_ex(_15, phalcon_db_exception_ce);
	ZEPHIR_INIT_VAR(_16);
	ZEPHIR_CONCAT_SVS(_16, "Invalid SQL expression type '", type, "'");
	ZEPHIR_CALL_METHOD(NULL, _15, "__construct", NULL, _16);
	zephir_check_call_status();
	zephir_throw_exception_debug(_15, "phalcon/db/dialect.zep", 273 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();
	return;

}

/**
 * Transform an intermediate representation for a schema/table into a database system valid expression
 *
 * @param array table
 * @param string escapeChar
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect, getSqlTable) {

	zval *escapeChar = NULL, *_1 = NULL;
	zval *table, *escapeChar_param = NULL, *sqlTable = NULL, *sqlSchema = NULL, *aliasName, *sqlTableAlias = NULL, *schemaName, *tableName, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &table, &escapeChar_param);

	if (!escapeChar_param) {
		ZEPHIR_INIT_VAR(escapeChar);
		ZVAL_EMPTY_STRING(escapeChar);
	} else {
		zephir_get_strval(escapeChar, escapeChar_param);
	}


	if (ZEPHIR_IS_STRING(escapeChar, "")) {
		ZEPHIR_OBS_VAR(_0);
		zephir_read_property_this(&_0, this_ptr, SL("_escapeChar"), PH_NOISY_CC);
		zephir_get_strval(_1, _0);
		ZEPHIR_CPY_WRT(escapeChar, _1);
	}
	if (Z_TYPE_P(table) == IS_ARRAY) {
		ZEPHIR_OBS_VAR(tableName);
		zephir_array_fetch_long(&tableName, table, 0, PH_NOISY TSRMLS_CC);
		if (ZEPHIR_GLOBAL(db).escape_identifiers) {
			ZEPHIR_INIT_VAR(sqlTable);
			ZEPHIR_CONCAT_VVV(sqlTable, escapeChar, tableName, escapeChar);
		} else {
			ZEPHIR_CPY_WRT(sqlTable, tableName);
		}
		ZEPHIR_OBS_VAR(schemaName);
		zephir_array_fetch_long(&schemaName, table, 1, PH_NOISY TSRMLS_CC);
		if (Z_TYPE_P(schemaName) != IS_ARRAY) {
			ZEPHIR_INIT_VAR(sqlSchema);
			if (ZEPHIR_GLOBAL(db).escape_identifiers) {
				ZEPHIR_CONCAT_VVVSV(sqlSchema, escapeChar, schemaName, escapeChar, ".", sqlTable);
			} else {
				ZEPHIR_CONCAT_VSV(sqlSchema, schemaName, ".", sqlTable);
			}
		} else {
			ZEPHIR_CPY_WRT(sqlSchema, sqlTable);
		}
		ZEPHIR_OBS_VAR(aliasName);
		if (zephir_array_isset_long_fetch(&aliasName, table, 2, 0 TSRMLS_CC)) {
			ZEPHIR_INIT_VAR(sqlTableAlias);
			if (ZEPHIR_GLOBAL(db).escape_identifiers) {
				ZEPHIR_CONCAT_VSVVV(sqlTableAlias, sqlSchema, " AS ", escapeChar, aliasName, escapeChar);
			} else {
				ZEPHIR_CONCAT_VSV(sqlTableAlias, sqlSchema, " AS ", aliasName);
			}
		} else {
			ZEPHIR_CPY_WRT(sqlTableAlias, sqlSchema);
		}
		RETURN_CCTOR(sqlTableAlias);
	}
	if (ZEPHIR_GLOBAL(db).escape_identifiers) {
		ZEPHIR_CONCAT_VVV(return_value, escapeChar, table, escapeChar);
		RETURN_MM();
	}
	RETURN_CCTOR(table);

}

/**
 * Builds a SELECT statement
 *
 * @param array definition
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect, select) {

	zephir_fcall_cache_entry *_8 = NULL;
	zephir_nts_static zephir_fcall_cache_entry *_3 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	HashTable *_1, *_5, *_10, *_15, *_21, *_25;
	HashPosition _0, _4, _9, _14, _20, _24;
	zval *definition, *tables, *columns = NULL, *escapeChar, *columnItem = NULL, *column = NULL, *selectedColumns, *columnSql = NULL, *columnDomainSql = NULL, *columnAlias = NULL, *selectedTables, *sqlJoin = NULL, *joinExpressions = NULL, *joinCondition = NULL, *joinConditionsArray = NULL, *tablesSql = NULL, *columnDomain = NULL, *columnAliasSql = NULL, *columnsSql = NULL, *table = NULL, *sql, *joins, *join = NULL, *sqlTable = NULL, *whereConditions, *groupFields, *groupField = NULL, *groupItems, *havingConditions, *orderFields, *orderItem = NULL, *orderItems, *orderSqlItem = NULL, *sqlOrderType = NULL, *orderSqlItemType = NULL, *limitValue, *number, *offset, **_2, **_6, *_7 = NULL, **_11, *_12, *_13, **_16, *_17 = NULL, *_18 = NULL, *_19 = NULL, **_22, *_23 = NULL, **_26, *_27, *_28;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &definition);



	if (Z_TYPE_P(definition) != IS_ARRAY) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "Invalid SELECT definition", "phalcon/db/dialect.zep", 361);
		return;
	}
	ZEPHIR_OBS_VAR(tables);
	if (!(zephir_array_isset_string_fetch(&tables, definition, SS("tables"), 0 TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "The index 'tables' is required in the definition array", "phalcon/db/dialect.zep", 365);
		return;
	}
	ZEPHIR_OBS_VAR(columns);
	if (!(zephir_array_isset_string_fetch(&columns, definition, SS("columns"), 0 TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_db_exception_ce, "The index 'columns' is required in the definition array", "phalcon/db/dialect.zep", 369);
		return;
	}
	ZEPHIR_INIT_VAR(escapeChar);
	if (ZEPHIR_GLOBAL(db).escape_identifiers) {
		zephir_read_property_this(&escapeChar, this_ptr, SL("_escapeChar"), PH_NOISY_CC);
	} else {
		ZVAL_NULL(escapeChar);
	}
	ZEPHIR_OBS_NVAR(columns);
	zephir_array_fetch_string(&columns, definition, SL("columns"), PH_NOISY TSRMLS_CC);
	if (Z_TYPE_P(columns) == IS_ARRAY) {
		ZEPHIR_INIT_VAR(selectedColumns);
		array_init(selectedColumns);
		zephir_is_iterable(columns, &_1, &_0, 0, 0);
		for (
		  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
		  ; zephir_hash_move_forward_ex(_1, &_0)
		) {
			ZEPHIR_GET_HVALUE(column, _2);
			ZEPHIR_OBS_NVAR(columnItem);
			zephir_array_fetch_long(&columnItem, column, 0, PH_NOISY TSRMLS_CC);
			if (Z_TYPE_P(columnItem) == IS_ARRAY) {
				ZEPHIR_CALL_METHOD(&columnSql, this_ptr, "getsqlexpression", &_3, columnItem, escapeChar);
				zephir_check_call_status();
			} else {
				if (ZEPHIR_IS_STRING(columnItem, "*")) {
					ZEPHIR_CPY_WRT(columnSql, columnItem);
				} else {
					if (ZEPHIR_GLOBAL(db).escape_identifiers) {
						ZEPHIR_INIT_NVAR(columnSql);
						ZEPHIR_CONCAT_VVV(columnSql, escapeChar, columnItem, escapeChar);
					} else {
						ZEPHIR_CPY_WRT(columnSql, columnItem);
					}
				}
			}
			ZEPHIR_OBS_NVAR(columnDomain);
			if (zephir_array_isset_long_fetch(&columnDomain, column, 1, 0 TSRMLS_CC)) {
				if (zephir_is_true(columnDomain)) {
					ZEPHIR_INIT_NVAR(columnDomainSql);
					if (ZEPHIR_GLOBAL(db).escape_identifiers) {
						ZEPHIR_CONCAT_VVVSV(columnDomainSql, escapeChar, columnDomain, escapeChar, ".", columnSql);
					} else {
						ZEPHIR_CONCAT_VSV(columnDomainSql, columnDomain, ".", columnSql);
					}
				} else {
					ZEPHIR_CPY_WRT(columnDomainSql, columnSql);
				}
			} else {
				ZEPHIR_CPY_WRT(columnDomainSql, columnSql);
			}
			ZEPHIR_OBS_NVAR(columnAlias);
			if (zephir_array_isset_long_fetch(&columnAlias, column, 2, 0 TSRMLS_CC)) {
				if (zephir_is_true(columnAlias)) {
					ZEPHIR_INIT_NVAR(columnAliasSql);
					if (ZEPHIR_GLOBAL(db).escape_identifiers) {
						ZEPHIR_CONCAT_VSVVV(columnAliasSql, columnDomainSql, " AS ", escapeChar, columnAlias, escapeChar);
					} else {
						ZEPHIR_CONCAT_VSV(columnAliasSql, columnDomainSql, " AS ", columnAlias);
					}
				} else {
					ZEPHIR_CPY_WRT(columnAliasSql, columnDomainSql);
				}
			} else {
				ZEPHIR_CPY_WRT(columnAliasSql, columnDomainSql);
			}
			zephir_array_append(&selectedColumns, columnAliasSql, PH_SEPARATE);
		}
		ZEPHIR_INIT_VAR(columnsSql);
		zephir_fast_join_str(columnsSql, SL(", "), selectedColumns TSRMLS_CC);
	} else {
		ZEPHIR_CPY_WRT(columnsSql, columns);
	}
	if (Z_TYPE_P(tables) == IS_ARRAY) {
		ZEPHIR_INIT_VAR(selectedTables);
		array_init(selectedTables);
		zephir_is_iterable(tables, &_5, &_4, 0, 0);
		for (
		  ; zephir_hash_get_current_data_ex(_5, (void**) &_6, &_4) == SUCCESS
		  ; zephir_hash_move_forward_ex(_5, &_4)
		) {
			ZEPHIR_GET_HVALUE(table, _6);
			ZEPHIR_CALL_METHOD(&_7, this_ptr, "getsqltable", &_8, table, escapeChar);
			zephir_check_call_status();
			zephir_array_append(&selectedTables, _7, PH_SEPARATE);
		}
		ZEPHIR_INIT_VAR(tablesSql);
		zephir_fast_join_str(tablesSql, SL(", "), selectedTables TSRMLS_CC);
	} else {
		ZEPHIR_CPY_WRT(tablesSql, tables);
	}
	ZEPHIR_INIT_VAR(sql);
	ZEPHIR_CONCAT_SVSV(sql, "SELECT ", columnsSql, " FROM ", tablesSql);
	ZEPHIR_OBS_VAR(joins);
	if (zephir_array_isset_string_fetch(&joins, definition, SS("joins"), 0 TSRMLS_CC)) {
		zephir_is_iterable(joins, &_10, &_9, 0, 0);
		for (
		  ; zephir_hash_get_current_data_ex(_10, (void**) &_11, &_9) == SUCCESS
		  ; zephir_hash_move_forward_ex(_10, &_9)
		) {
			ZEPHIR_GET_HVALUE(join, _11);
			zephir_array_fetch_string(&_12, join, SL("source"), PH_NOISY | PH_READONLY TSRMLS_CC);
			ZEPHIR_CALL_METHOD(&sqlTable, this_ptr, "getsqltable", &_8, _12, escapeChar);
			zephir_check_call_status();
			zephir_array_append(&selectedTables, sqlTable, PH_SEPARATE);
			zephir_array_fetch_string(&_13, join, SL("type"), PH_NOISY | PH_READONLY TSRMLS_CC);
			ZEPHIR_INIT_NVAR(sqlJoin);
			ZEPHIR_CONCAT_SVSV(sqlJoin, " ", _13, " JOIN ", sqlTable);
			ZEPHIR_OBS_NVAR(joinConditionsArray);
			if (zephir_array_isset_string_fetch(&joinConditionsArray, join, SS("conditions"), 0 TSRMLS_CC)) {
				if (zephir_fast_count_int(joinConditionsArray TSRMLS_CC)) {
					ZEPHIR_INIT_NVAR(joinExpressions);
					array_init(joinExpressions);
					zephir_is_iterable(joinConditionsArray, &_15, &_14, 0, 0);
					for (
					  ; zephir_hash_get_current_data_ex(_15, (void**) &_16, &_14) == SUCCESS
					  ; zephir_hash_move_forward_ex(_15, &_14)
					) {
						ZEPHIR_GET_HVALUE(joinCondition, _16);
						ZEPHIR_CALL_METHOD(&_7, this_ptr, "getsqlexpression", &_3, joinCondition, escapeChar);
						zephir_check_call_status();
						zephir_array_append(&joinExpressions, _7, PH_SEPARATE);
					}
					ZEPHIR_INIT_NVAR(_17);
					zephir_fast_join_str(_17, SL(" AND "), joinExpressions TSRMLS_CC);
					ZEPHIR_INIT_LNVAR(_18);
					ZEPHIR_CONCAT_SVS(_18, " ON ", _17, " ");
					zephir_concat_self(&sqlJoin, _18 TSRMLS_CC);
				}
			}
			zephir_concat_self(&sql, sqlJoin TSRMLS_CC);
		}
	}
	ZEPHIR_OBS_VAR(whereConditions);
	if (zephir_array_isset_string_fetch(&whereConditions, definition, SS("where"), 0 TSRMLS_CC)) {
		if (Z_TYPE_P(whereConditions) == IS_ARRAY) {
			ZEPHIR_CALL_METHOD(&_7, this_ptr, "getsqlexpression", &_3, whereConditions, escapeChar);
			zephir_check_call_status();
			ZEPHIR_INIT_LNVAR(_18);
			ZEPHIR_CONCAT_SV(_18, " WHERE ", _7);
			zephir_concat_self(&sql, _18 TSRMLS_CC);
		} else {
			ZEPHIR_INIT_VAR(_19);
			ZEPHIR_CONCAT_SV(_19, " WHERE ", whereConditions);
			zephir_concat_self(&sql, _19 TSRMLS_CC);
		}
	}
	ZEPHIR_OBS_VAR(groupFields);
	if (zephir_array_isset_string_fetch(&groupFields, definition, SS("group"), 0 TSRMLS_CC)) {
		ZEPHIR_INIT_VAR(groupItems);
		array_init(groupItems);
		zephir_is_iterable(groupFields, &_21, &_20, 0, 0);
		for (
		  ; zephir_hash_get_current_data_ex(_21, (void**) &_22, &_20) == SUCCESS
		  ; zephir_hash_move_forward_ex(_21, &_20)
		) {
			ZEPHIR_GET_HVALUE(groupField, _22);
			ZEPHIR_CALL_METHOD(&_7, this_ptr, "getsqlexpression", &_3, groupField, escapeChar);
			zephir_check_call_status();
			zephir_array_append(&groupItems, _7, PH_SEPARATE);
		}
		ZEPHIR_INIT_NVAR(_17);
		zephir_fast_join_str(_17, SL(", "), groupItems TSRMLS_CC);
		ZEPHIR_INIT_LNVAR(_19);
		ZEPHIR_CONCAT_SV(_19, " GROUP BY ", _17);
		zephir_concat_self(&sql, _19 TSRMLS_CC);
		ZEPHIR_OBS_VAR(havingConditions);
		if (zephir_array_isset_string_fetch(&havingConditions, definition, SS("having"), 0 TSRMLS_CC)) {
			ZEPHIR_CALL_METHOD(&_7, this_ptr, "getsqlexpression", &_3, havingConditions, escapeChar);
			zephir_check_call_status();
			ZEPHIR_INIT_VAR(_23);
			ZEPHIR_CONCAT_SV(_23, " HAVING ", _7);
			zephir_concat_self(&sql, _23 TSRMLS_CC);
		}
	}
	ZEPHIR_OBS_VAR(orderFields);
	if (zephir_array_isset_string_fetch(&orderFields, definition, SS("order"), 0 TSRMLS_CC)) {
		ZEPHIR_INIT_VAR(orderItems);
		array_init(orderItems);
		zephir_is_iterable(orderFields, &_25, &_24, 0, 0);
		for (
		  ; zephir_hash_get_current_data_ex(_25, (void**) &_26, &_24) == SUCCESS
		  ; zephir_hash_move_forward_ex(_25, &_24)
		) {
			ZEPHIR_GET_HVALUE(orderItem, _26);
			zephir_array_fetch_long(&_12, orderItem, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
			ZEPHIR_CALL_METHOD(&orderSqlItem, this_ptr, "getsqlexpression", &_3, _12, escapeChar);
			zephir_check_call_status();
			ZEPHIR_OBS_NVAR(sqlOrderType);
			if (zephir_array_isset_long_fetch(&sqlOrderType, orderItem, 1, 0 TSRMLS_CC)) {
				ZEPHIR_INIT_NVAR(orderSqlItemType);
				ZEPHIR_CONCAT_VSV(orderSqlItemType, orderSqlItem, " ", sqlOrderType);
			} else {
				ZEPHIR_CPY_WRT(orderSqlItemType, orderSqlItem);
			}
			zephir_array_append(&orderItems, orderSqlItemType, PH_SEPARATE);
		}
		ZEPHIR_INIT_VAR(_27);
		zephir_fast_join_str(_27, SL(", "), orderItems TSRMLS_CC);
		ZEPHIR_INIT_LNVAR(_19);
		ZEPHIR_CONCAT_SV(_19, " ORDER BY ", _27);
		zephir_concat_self(&sql, _19 TSRMLS_CC);
	}
	if (zephir_array_isset_string_fetch(&limitValue, definition, SS("limit"), 1 TSRMLS_CC)) {
		if (Z_TYPE_P(limitValue) == IS_ARRAY) {
			zephir_array_fetch_string(&_12, limitValue, SL("number"), PH_NOISY | PH_READONLY TSRMLS_CC);
			zephir_array_fetch_string(&number, _12, SL("value"), PH_NOISY | PH_READONLY TSRMLS_CC);
			if (zephir_array_isset_string_fetch(&offset, limitValue, SS("offset"), 1 TSRMLS_CC)) {
				zephir_array_fetch_string(&_13, offset, SL("value"), PH_NOISY | PH_READONLY TSRMLS_CC);
				ZEPHIR_INIT_LNVAR(_23);
				ZEPHIR_CONCAT_SVSV(_23, " LIMIT ", number, " OFFSET ", _13);
				zephir_concat_self(&sql, _23 TSRMLS_CC);
			} else {
				ZEPHIR_INIT_VAR(_28);
				ZEPHIR_CONCAT_SV(_28, " LIMIT ", number);
				zephir_concat_self(&sql, _28 TSRMLS_CC);
			}
		} else {
			ZEPHIR_INIT_LNVAR(_19);
			ZEPHIR_CONCAT_SV(_19, " LIMIT ", limitValue);
			zephir_concat_self(&sql, _19 TSRMLS_CC);
		}
	}
	RETURN_CCTOR(sql);

}

/**
 * Checks whether the platform supports savepoints
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Dialect, supportsSavepoints) {


	RETURN_BOOL(1);

}

/**
 * Checks whether the platform supports releasing savepoints.
 *
 * @return boolean
 */
PHP_METHOD(Phalcon_Db_Dialect, supportsReleaseSavepoints) {

	int ZEPHIR_LAST_CALL_STATUS;

	ZEPHIR_MM_GROW();

	ZEPHIR_RETURN_CALL_METHOD(this_ptr, "supportssavepoints", NULL);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Generate SQL to create a new savepoint
 *
 * @param string name
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect, createSavepoint) {

	zval *name_param = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	if (Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(name_param) == IS_STRING) {
		name = name_param;
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}


	ZEPHIR_CONCAT_SV(return_value, "SAVEPOINT ", name);
	RETURN_MM();

}

/**
 * Generate SQL to release a savepoint
 *
 * @param string name
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect, releaseSavepoint) {

	zval *name_param = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	if (Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(name_param) == IS_STRING) {
		name = name_param;
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}


	ZEPHIR_CONCAT_SV(return_value, "RELEASE SAVEPOINT ", name);
	RETURN_MM();

}

/**
 * Generate SQL to rollback a savepoint
 *
 * @param string name
 * @return string
 */
PHP_METHOD(Phalcon_Db_Dialect, rollbackSavepoint) {

	zval *name_param = NULL;
	zval *name = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &name_param);

	if (Z_TYPE_P(name_param) != IS_STRING && Z_TYPE_P(name_param) != IS_NULL) {
		zephir_throw_exception_string(spl_ce_InvalidArgumentException, SL("Parameter 'name' must be a string") TSRMLS_CC);
		RETURN_MM_NULL();
	}

	if (Z_TYPE_P(name_param) == IS_STRING) {
		name = name_param;
	} else {
		ZEPHIR_INIT_VAR(name);
		ZVAL_EMPTY_STRING(name);
	}


	ZEPHIR_CONCAT_SV(return_value, "ROLLBACK TO SAVEPOINT ", name);
	RETURN_MM();

}
