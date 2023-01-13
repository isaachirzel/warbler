#ifndef WARBLER_UTIL_PRINT_H
#define WARBLER_UTIL_PRINT_H

// local headers
#include <warbler/token.h>
#include <warbler/snippet.h>
#include <stdnoreturn.h>

noreturn void _exitWithError(const char *file, usize line, const char *fmt, ...);
#define exitWithErrorFmt(fmt, ...) _exitWithError(__FILE__, __LINE__, fmt, __VA_ARGS__)
#define exitWithError(message) _exitWithError(__FILE__, __LINE__, message)

noreturn void _exitNotImplemented(const char *file, usize line, const char *func);
#define exitNotImplemented() _exitNotImplemented(__FILE__, __LINE__, __func__)

void enableColorPrinting(bool enabled);

void _print(const char *file, u32 line, const char *msg);
void _printFmt(const char *file, u32 line, const char *msg, ...);
#define print(msg) _print(__FILE__, __LINE__, msg)

#define printFmt(msg, ...) _printFmt(__FILE__, __LINE__, msg, __VA_ARGS__)

void printTokenNote(const Token *token, const char *format, ...);
void printTokenWarning(const Token *token, const char *format, ...);
void printTokenError(const Token *token, const char *format, ...);

void printNote(const char *format, ...);
void printWarning(const char *format, ...);
void printError(const char *format, ...);
void printSuccess(const char *format, ...);

void printParseError(const Token *token, const char *expected, const char *message);

usize getNoteCount(void);
usize getWarningCount(void);
usize getErrorCount(void);

#endif
