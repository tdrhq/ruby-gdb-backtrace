#include "ruby.h"

VALUE ruby_gdb_helper = Qnil;

const char*
gdbc_get_string(VALUE s) {
    return RSTRING_PTR(s);
}

/* version for testing from ruby */
VALUE
rb_ruby_gdb_backtrace() {
  return rb_eval_string("begin; raise 'nowhere'; rescue Exception => e; e.backtrace.join('\n'); end");
}


/* the return value of this will be eventually garbage collected,
 * therefore it is safe to use only from within gdb */
const char*
ruby_gdb_backtrace() {
  return RSTRING_PTR(rb_ruby_gdb_backtrace());
}

// The initialization method for this module
void Init_ruby_gdb_helper() {
  VALUE cRubyGdb;
  ruby_gdb_helper = rb_define_module("ruby_gdb_helper");

  cRubyGdb = rb_eval_string("RubyGdbBacktrace");
  rb_define_singleton_method(cRubyGdb, "get", rb_ruby_gdb_backtrace, 0);
}
