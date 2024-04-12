/**
 * @file chroniclec.h
 * @author Fedi Nabli (fedinabli@gmail.com)
 * @version 1.0
 * @date 2024-04-11
 * 
 * @copyright Copyright (c) 2024 Fedi Nabli
 * 
 * @brief This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `chroniclec.c` or `LICENSE` for details.
 */

#ifndef CHRONICLEC_H
#define CHRONICLEC_H

#include <stdbool.h>

#define CHRONOC_VERSION "1.0.0"

// < Terminal colors definitions start

#define ANSI_RESET_ALL            "\x1b[0m"

#define ANSI_STYLE_BOLD           "\x1b[1m"
#define ANSI_STYLE_ITALIC         "\x1b[3m"
#define ANSI_STYLE_UNDERLINE      "\x1b[4m"

#define ANSI_COLOR_BLACK          "\x1b[30m"
#define ANSI_COLOR_RED            "\x1b[31m"
#define ANSI_COLOR_GREEN          "\x1b[32m"
#define ANSI_COLOR_YELLOW         "\x1b[33m"
#define ANSI_COLOR_BLUE           "\x1b[34m"
#define ANSI_COLOR_MAGENTA        "\x1b[35m"
#define ANSI_COLOR_CYAN           "\x1b[36m"
#define ANSI_COLOR_WHITE          "\x1b[37m"
#define ANSI_COLOR_DARK_BLUE      "\x1b[94m"

#define ANSI_BACKGROUND_BLACK     "\x1b[40m"
#define ANSI_BACKGROUND_RED       "\x1b[41m"
#define ANSI_BACKGROUND_GREEN     "\x1b[42m"
#define ANSI_BACKGROUND_YELLOW    "\x1b[43m"
#define ANSI_BACKGROUND_BLUE      "\x1b[44m"
#define ANSI_BACKGROUND_MAGENTA   "\x1b[45m"
#define ANSI_BACKGROUND_CYAN      "\x1b[46m"
#define ANSI_BACKGROUND_WHITE     "\x1b[47m"

// > Terminal colors definitions end

// struct log_event;

// typedef void* (*LOG_FN_CALLBACK)(struct log_event* event, void* private);

enum Level
{
  TRACE,
  DEBUG,
  INFO,
  SUCCESS,
  WARN,
  DANGER,
  FATAL
};

struct event_data
{
  int line;
  const char* date;
  const char* time;
  const char* file;
};

struct log_event
{
  struct event_data data;
  int level;
  bool quiet;
  const char* fmt;
  const char* file_out;
  void* private;
};

#endif