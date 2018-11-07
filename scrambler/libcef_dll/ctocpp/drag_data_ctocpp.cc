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

#include "ctocpp/drag_data_ctocpp.h"
#include "ctocpp/stream_writer_ctocpp.h"
#include "transfer_util.h"


// STATIC METHODS - Body may be edited by hand.

CefRefPtr<CefDragData> CefDragData::Create() {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_drag_data_t* _retval = cef_drag_data_create();

  // Return type: refptr_same
  return CefDragDataCToCpp::Wrap(_retval);
}


// VIRTUAL METHODS - Body may be edited by hand.

CefRefPtr<CefDragData> CefDragDataCToCpp::Clone() {
  if (CEF_MEMBER_MISSING(struct_, clone))
    return NULL;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_drag_data_t* _retval = struct_->clone(struct_);

  // Return type: refptr_same
  return CefDragDataCToCpp::Wrap(_retval);
}

bool CefDragDataCToCpp::IsReadOnly() {
  if (CEF_MEMBER_MISSING(struct_, is_read_only))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = struct_->is_read_only(struct_);

  // Return type: bool
  return _retval?true:false;
}

bool CefDragDataCToCpp::IsLink() {
  if (CEF_MEMBER_MISSING(struct_, is_link))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = struct_->is_link(struct_);

  // Return type: bool
  return _retval?true:false;
}

bool CefDragDataCToCpp::IsFragment() {
  if (CEF_MEMBER_MISSING(struct_, is_fragment))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = struct_->is_fragment(struct_);

  // Return type: bool
  return _retval?true:false;
}

bool CefDragDataCToCpp::IsFile() {
  if (CEF_MEMBER_MISSING(struct_, is_file))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = struct_->is_file(struct_);

  // Return type: bool
  return _retval?true:false;
}

CefString CefDragDataCToCpp::GetLinkURL() {
  if (CEF_MEMBER_MISSING(struct_, get_link_url))
    return CefString();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_string_userfree_t _retval = struct_->get_link_url(struct_);

  // Return type: string
  CefString _retvalStr;
  _retvalStr.AttachToUserFree(_retval);
  return _retvalStr;
}

CefString CefDragDataCToCpp::GetLinkTitle() {
  if (CEF_MEMBER_MISSING(struct_, get_link_title))
    return CefString();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_string_userfree_t _retval = struct_->get_link_title(struct_);

  // Return type: string
  CefString _retvalStr;
  _retvalStr.AttachToUserFree(_retval);
  return _retvalStr;
}

CefString CefDragDataCToCpp::GetLinkMetadata() {
  if (CEF_MEMBER_MISSING(struct_, get_link_metadata))
    return CefString();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_string_userfree_t _retval = struct_->get_link_metadata(struct_);

  // Return type: string
  CefString _retvalStr;
  _retvalStr.AttachToUserFree(_retval);
  return _retvalStr;
}

CefString CefDragDataCToCpp::GetFragmentText() {
  if (CEF_MEMBER_MISSING(struct_, get_fragment_text))
    return CefString();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_string_userfree_t _retval = struct_->get_fragment_text(struct_);

  // Return type: string
  CefString _retvalStr;
  _retvalStr.AttachToUserFree(_retval);
  return _retvalStr;
}

CefString CefDragDataCToCpp::GetFragmentHtml() {
  if (CEF_MEMBER_MISSING(struct_, get_fragment_html))
    return CefString();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_string_userfree_t _retval = struct_->get_fragment_html(struct_);

  // Return type: string
  CefString _retvalStr;
  _retvalStr.AttachToUserFree(_retval);
  return _retvalStr;
}

CefString CefDragDataCToCpp::GetFragmentBaseURL() {
  if (CEF_MEMBER_MISSING(struct_, get_fragment_base_url))
    return CefString();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_string_userfree_t _retval = struct_->get_fragment_base_url(struct_);

  // Return type: string
  CefString _retvalStr;
  _retvalStr.AttachToUserFree(_retval);
  return _retvalStr;
}

CefString CefDragDataCToCpp::GetFileName() {
  if (CEF_MEMBER_MISSING(struct_, get_file_name))
    return CefString();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_string_userfree_t _retval = struct_->get_file_name(struct_);

  // Return type: string
  CefString _retvalStr;
  _retvalStr.AttachToUserFree(_retval);
  return _retvalStr;
}

size_t CefDragDataCToCpp::GetFileContents(CefRefPtr<CefStreamWriter> writer) {
  if (CEF_MEMBER_MISSING(struct_, get_file_contents))
    return 0;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: writer

  // Execute
  size_t _retval = struct_->get_file_contents(struct_,
      CefStreamWriterCToCpp::Unwrap(writer));

  // Return type: simple
  return _retval;
}

bool CefDragDataCToCpp::GetFileNames(std::vector<CefString>& names) {
  if (CEF_MEMBER_MISSING(struct_, get_file_names))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Translate param: names; type: string_vec_byref
  cef_string_list_t namesList = cef_string_list_alloc();
  DCHECK(namesList);
  if (namesList)
    transfer_string_list_contents(names, namesList);

  // Execute
  int _retval = struct_->get_file_names(struct_,
      namesList);

  // Restore param:names; type: string_vec_byref
  if (namesList) {
    names.clear();
    transfer_string_list_contents(namesList, names);
    cef_string_list_free(namesList);
  }

  // Return type: bool
  return _retval?true:false;
}

void CefDragDataCToCpp::SetLinkURL(const CefString& url) {
  if (CEF_MEMBER_MISSING(struct_, set_link_url))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: url

  // Execute
  struct_->set_link_url(struct_,
      url.GetStruct());
}

void CefDragDataCToCpp::SetLinkTitle(const CefString& title) {
  if (CEF_MEMBER_MISSING(struct_, set_link_title))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: title

  // Execute
  struct_->set_link_title(struct_,
      title.GetStruct());
}

void CefDragDataCToCpp::SetLinkMetadata(const CefString& data) {
  if (CEF_MEMBER_MISSING(struct_, set_link_metadata))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: data

  // Execute
  struct_->set_link_metadata(struct_,
      data.GetStruct());
}

void CefDragDataCToCpp::SetFragmentText(const CefString& text) {
  if (CEF_MEMBER_MISSING(struct_, set_fragment_text))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: text

  // Execute
  struct_->set_fragment_text(struct_,
      text.GetStruct());
}

void CefDragDataCToCpp::SetFragmentHtml(const CefString& html) {
  if (CEF_MEMBER_MISSING(struct_, set_fragment_html))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: html

  // Execute
  struct_->set_fragment_html(struct_,
      html.GetStruct());
}

void CefDragDataCToCpp::SetFragmentBaseURL(const CefString& base_url) {
  if (CEF_MEMBER_MISSING(struct_, set_fragment_base_url))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: base_url

  // Execute
  struct_->set_fragment_base_url(struct_,
      base_url.GetStruct());
}

void CefDragDataCToCpp::ResetFileContents() {
  if (CEF_MEMBER_MISSING(struct_, reset_file_contents))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  struct_->reset_file_contents(struct_);
}

void CefDragDataCToCpp::AddFile(const CefString& path,
    const CefString& display_name) {
  if (CEF_MEMBER_MISSING(struct_, add_file))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: path; type: string_byref_const
  DCHECK(!path.empty());
  if (path.empty())
    return;
  // Unverified params: display_name

  // Execute
  struct_->add_file(struct_,
      path.GetStruct(),
      display_name.GetStruct());
}


#ifndef NDEBUG
template<> base::AtomicRefCount CefCToCpp<CefDragDataCToCpp, CefDragData,
    cef_drag_data_t>::DebugObjCt = 0;
#endif

