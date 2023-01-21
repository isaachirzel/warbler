#ifndef WARBLER_SYMBOL_TABLE_H
#define WARBLER_SYMBOL_TABLE_H

#include "warbler/util/array.h"
#include "warbler/util/string.h"
#include "warbler/util/table.h"
#include "warbler/util/primitives.h"
#include "warbler/type.h"
#include "warbler/util/memory.h"
#include "warbler/scope.h"
#include "warbler/ast.h"

#include <assert.h>

typedef enum ValidationStatus
{
	VALIDATION_PENDING,
	VALIDATION_INVALID,
	VALIDATION_VALID
} ValidationStatus;

typedef struct Symbol
{
	char *key;
	usize index;
	SymbolType type;
	ValidationStatus status;
} Symbol;

typedef struct BlockInfo
{
	Block *node;
	usize offset;
} BlockInfo;

typedef struct LocalSymbolTable
{
	Symbol *symbols;
	usize symbolCount;
	usize symbolCapacity;

	BlockInfo *blocks;
	usize blockCount;
	usize blockCapacity;

	Function *function;
	const Scope *packageScope;
} LocalSymbolTable;

typedef bool (*SymbolAction)(Symbol *symbol);

void symbolTableInitialize(const char *projectName);
void symbolTableDestroy(void);

usize symbolTableAddPackage(void);
usize symbolTableAddStruct(void);
usize symbolTableAddFunction(void);
usize symbolTableAddVariable(void);
usize symbolTableAddParameter(void);

bool symbolTableDeclareGlobal(SymbolType type, usize index);
bool symbolTableDeclareLocal(LocalSymbolTable *localTable, SymbolType type, usize index);

Symbol *symbolTableResolve(LocalSymbolTable *localTable, const Token *token);
Symbol *symbolTableResolveGlobal(const Scope *scope, const Token *token);


void symbolTableSetScopeFromSymbol(const char *symbol);
Symbol *symbolTableGetSymbol(usize index);
const char *symbolTypeGetName(SymbolType type);
const Token *symbolTableGetToken(usize symbolIndex);
const char *symbolGetKey(SymbolType type, usize index);

bool symbolTableForEachEntity(SymbolType type, IdAction action);

Package *symbolTableGetPackage(usize index);
Local *symbolTableGetVariable(usize index);
Local *symbolTableGetParameter(usize index);
Function *symbolTableGetFunction(usize index);
Struct *symbolTableGetStruct(usize index);
const Primitive *symbolTableGetPrimitive(usize index);

LocalSymbolTable localSymbolTableCreate(const Scope *packageScope);
void localSymbolTableDestroy(LocalSymbolTable *localTable);
void localSymbolTableClear(LocalSymbolTable *localTable);
void localSymbolTablePushBlock(LocalSymbolTable *localTable, Block *block);
Block *localSymbolTableGetCurrentBlock(LocalSymbolTable *localTable);
void localSymbolTablePopBlock(LocalSymbolTable *localTable);

#endif
