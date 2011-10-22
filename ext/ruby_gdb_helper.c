#include "ruby.h"

VALUE ruby_gdb_helper = Qnil;


const char*
gdbc_get_string(VALUE s) {
    return RSTRING_PTR(s);
}

const char*
ruby_gdb_backtrace() {
  VALUE str = rb_eval_string("begin; raise 'nowhere'; rescue Exception => e; e.backtrace.join('\n'); end");
  return RSTRING_PTR(str);
}

// The initialization method for this module
void Init_ruby_gdb_helper() {
  ruby_gdb_helper = rb_define_module("ruby_gdb_helper");
}
