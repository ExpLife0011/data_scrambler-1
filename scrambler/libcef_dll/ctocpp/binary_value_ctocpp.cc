// Copyright (c) 2014 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//

#include "ctocpp/binary_value_ctocpp.h"


// STATIC METHODS - Body may be edited by hand.

CefRefPtr<CefBinaryValue> CefBinaryValue::Create(const void* data,
    size_t data_size) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: data; type: simple_byaddr
  DCHECK(data);
  if (!data)
    return NULL;

  // Execute
  cef_binary_value_t* _retval = cef_binary_value_create(
      data,
      data_size);

  // Return type: refptr_same
  return CefBinaryValueCToCpp::Wrap(_retval);
}


// VIRTUAL METHODS - Body may be edited by hand.

bool CefBinaryValueCToCpp::IsValid() {
  if (CEF_MEMBER_MISSING(struct_, is_valid))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = struct_->is_valid(struct_);

  // Return type: bool
  return _retval?true:false;
}

bool CefBinaryValueCToCpp::IsOwned() {
  if (CEF_MEMBER_MISSING(struct_, is_owned))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = struct_->is_owned(struct_);

  // Return type: bool
  return _retval?true:false;
}

CefRefPtr<CefBinaryValue> CefBinaryValueCToCpp::Copy() {
  if (CEF_MEMBER_MISSING(struct_, copy))
    return NULL;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_binary_value_t* _retval = struct_->copy(struct_);

  // Return type: refptr_same
  return CefBinaryValueCToCpp::Wrap(_retval);
}

size_t CefBinaryValueCToCpp::GetSize() {
  if (CEF_MEMBER_MISSING(struct_, get_size))
    return 0;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  size_t _retval = struct_->get_size(struct_);

  // Return type: simple
  return _retval;
}

size_t CefBinaryValueCToCpp::GetData(void* buffer, size_t buffer_size,
    size_t data_offset) {
  if (CEF_MEMBER_MISSING(struct_, get_data))
    return 0;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: buffer; type: simple_byaddr
  DCHECK(buffer);
  if (!buffer)
    return 0;

  // Execute
  size_t _retval = struct_->get_data(struct_,
      buffer,
      buffer_size,
      data_offset);

  // Return type: simple
  return _retval;
}


#ifndef NDEBUG
template<> base::AtomicRefCount CefCToCpp<CefBinaryValueCToCpp, CefBinaryValue,
    cef_binary_value_t>::DebugObjCt = 0;
#endif

