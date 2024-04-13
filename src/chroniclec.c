/**
 * @file chroniclec.c
 * @author Fedi Nabli (fedinabli@gmail.com)
 * @version 1.0
 * @date 2024-04-11
 * 
 * @copyright Copyright (c) 2024 Fedi Nabli

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.

 */

#include "chroniclec.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>

void initialize_logger(struct log_event* logger, const char* file, int line, const char* file_out, bool output_to_console_and_file)
{
  logger->data.date = __DATE__;
  logger->data.time = __TIME__;
  logger->data.file = file;
  logger->data.line = line;
  logger->quiet = false;

  if (file_out)
  {
    logger->file_out = file_out;
    FILE* file = fopen(file_out, "a");
    logger->out_file = file;

    if (output_to_console_and_file)
    {
      logger->quiet = output_to_console_and_file;
    }
    else
    {
      logger->quiet = true;
    }
  }
}

void destruct_logger(struct log_event* logger)
{
  assert(logger);
  if (logger->file_out)
  {
    fclose(logger->out_file);
  }
  free(logger);
}

const char* get_style(int level)
{
  const char* style = NULL;

  switch (level)
  {
    case TRACE:
      style = ANSI_COLOR_DARK_BLUE;
      break;

    case DEBUG:
      style = ANSI_COLOR_CYAN;
      break;

    case INFO:
      style = ANSI_COLOR_BLUE;
      break;

    case SUCCESS:
      style = ANSI_COLOR_GREEN;
      break;
    
    case WARN:
      style = ANSI_COLOR_YELLOW;
      break;

    case DANGER:
      style = ANSI_COLOR_RED;
      break;

    case FATAL:
      style = ANSI_COLOR_MAGENTA;
      break;

    default:
      style = ANSI_COLOR_WHITE;
  }

  return style;
}

void log_log(int level, const char* file, int line, const char* file_out, void* private, char* fmt, ...)
{
  struct log_event* event = calloc(1, sizeof(struct log_event));
  initialize_logger(event, file, line, file_out, file_out != NULL);
  event->level = level;
  
  char buf[1024];
  va_list args;
  va_start(args, fmt);
  vsprintf(buf, fmt, args);
  va_end(args);
  event->fmt = buf;

  if (!event->quiet)
  {
    printf("%s%s %s in file %s on line %d: %s\n" ANSI_RESET_ALL, get_style(event->level), event->data.date, event->data.time, event->data.file, event->data.line, event->fmt);
  }

  if (file_out)
  {
    vfprintf(event->out_file, fmt, args);
    fprintf(event->out_file, "\n");
  }
  
  destruct_logger(event);
}