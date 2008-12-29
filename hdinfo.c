#include <stdio.h>
#include <stdlib.h>
#include <linux/hdreg.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "ruby.h"

static VALUE t_init(VALUE self,VALUE anObject){

  struct hd_driveid id;
  int disk ;
  int opened;


  disk=open(STR2CSTR(anObject), O_RDONLY|O_NONBLOCK);
  opened = ioctl(disk, HDIO_GET_IDENTITY, &id);

  VALUE k[4],v[4];
  k[0]=rb_str_new2("serial_no");
  k[1]=rb_str_new2("model");
  k[2]=rb_str_new2("fw_rev");
  k[3]=rb_str_new2("device_name");

  v[0]=rb_str_new2((char*) id.serial_no);
  v[1]=rb_str_new2((char*) id.model);
  v[2]=rb_str_new2((char*) id.fw_rev);
  v[3]=anObject;
  int i;
  for (i=0;i<4;i++){ 
    rb_hash_aset(self,k[i],v[i]);

  }

  VALUE err=(opened)?Qtrue:Qfalse;
  
  rb_iv_set(self, "@error",err); 

  return self;

}

static VALUE t_error(VALUE self, VALUE anObject){
  return  rb_iv_get(self, "@error");
}

VALUE cHdInfo;

void Init_HdInfo() {
  cHdInfo = rb_define_class("HdInfo", rb_cHash);
  rb_define_method(cHdInfo, "initialize", t_init, 1);
  rb_define_method(cHdInfo, "error?", t_error, 0);
}
