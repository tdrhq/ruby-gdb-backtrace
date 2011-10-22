#include "ruby.h"

VALUE gdbc = Qnil;


const char*
gdbc_get_string(VALUE s) {
  
  return RSTRING_PTR(s);
}

const char*
gdbc_backtrace() {
  VALUE str = rb_eval_string("begin; raise 'nowhere'; rescue Exception => e; e.backtrace.join('\n'); end");
  return RSTRING_PTR(str);
}

// The initialization method for this module
void Init_gdbc() {
  gdbc = rb_define_module("gdbc");
}
