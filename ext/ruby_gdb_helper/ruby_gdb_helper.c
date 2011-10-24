#include "ruby.h"

VALUE ruby_gdb_helper = Qnil;

const char*
gdbc_get_string(VALUE s) {
    return RSTRING_PTR(s);
}

/* version for testing from ruby */
static int
backtrace_iter_fn(void *arg, VALUE file, int line, VALUE method) {
  char ** c = (char **) arg;
  char *old_string = *c;

  asprintf(c, "\t from %s:%d:in `%s'\n%s", RSTRING_PTR(file), line, RSTRING_PTR(method), old_string);
  if (old_string) {
    free(old_string);
  }
  return Qfalse;
}

/* the return value of this will be eventually garbage collected,
 * therefore it is safe to use only from within gdb. I want this to
 * depend as little as possible on ruby itself, in order to ensure
 * that I can call this from strange places from gdb. */
char*
ruby_gdb_backtrace() {
  char *c = NULL;
  rb_backtrace_each(backtrace_iter_fn, &c);
  return c;
}

static VALUE
gdb_backtrace() {
  char* backtrace = ruby_gdb_backtrace();
  VALUE ret = rb_str_new2(backtrace);
  free(backtrace);
  return ret;
}

// The initialization method for this module
void Init_ruby_gdb_helper() {
  VALUE cRubyGdb;
  ruby_gdb_helper = rb_define_module("ruby_gdb_helper");

  cRubyGdb = rb_eval_string("RubyGdbBacktrace");
  rb_define_singleton_method(cRubyGdb, "get", gdb_backtrace, 0);
}
