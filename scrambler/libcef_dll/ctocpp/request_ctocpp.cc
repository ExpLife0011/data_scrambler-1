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

#include "ctocpp/post_data_ctocpp.h"
#include "ctocpp/request_ctocpp.h"
#include "transfer_util.h"


// STATIC METHODS - Body may be edited by hand.

CefRefPtr<CefRequest> CefRequest::Create() {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_request_t* _retval = cef_request_create();

  // Return type: refptr_same
  return CefRequestCToCpp::Wrap(_retval);
}


// VIRTUAL METHODS - Body may be edited by hand.

bool CefRequestCToCpp::IsReadOnly() {
  if (CEF_MEMBER_MISSING(struct_, is_read_only))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = struct_->is_read_only(struct_);

  // Return type: bool
  return _retval?true:false;
}

CefString CefRequestCToCpp::GetURL() {
  if (CEF_MEMBER_MISSING(struct_, get_url))
    return CefString();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_string_userfree_t _retval = struct_->get_url(struct_);

  // Return type: string
  CefString _retvalStr;
  _retvalStr.AttachToUserFree(_retval);
  return _retvalStr;
}

void CefRequestCToCpp::SetURL(const CefString& url) {
  if (CEF_MEMBER_MISSING(struct_, set_url))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: url; type: string_byref_const
  DCHECK(!url.empty());
  if (url.empty())
    return;

  // Execute
  struct_->set_url(struct_,
      url.GetStruct());
}

CefString CefRequestCToCpp::GetMethod() {
  if (CEF_MEMBER_MISSING(struct_, get_method))
    return CefString();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_string_userfree_t _retval = struct_->get_method(struct_);

  // Return type: string
  CefString _retvalStr;
  _retvalStr.AttachToUserFree(_retval);
  return _retvalStr;
}

void CefRequestCToCpp::SetMethod(const CefString& method) {
  if (CEF_MEMBER_MISSING(struct_, set_method))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: method; type: string_byref_const
  DCHECK(!method.empty());
  if (method.empty())
    return;

  // Execute
  struct_->set_method(struct_,
      method.GetStruct());
}

CefRefPtr<CefPostData> CefRequestCToCpp::GetPostData() {
  if (CEF_MEMBER_MISSING(struct_, get_post_data))
    return NULL;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_post_data_t* _retval = struct_->get_post_data(struct_);

  // Return type: refptr_same
  return CefPostDataCToCpp::Wrap(_retval);
}

void CefRequestCToCpp::SetPostData(CefRefPtr<CefPostData> postData) {
  if (CEF_MEMBER_MISSING(struct_, set_post_data))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: postData; type: refptr_same
  DCHECK(postData.get());
  if (!postData.get())
    return;

  // Execute
  struct_->set_post_data(struct_,
      CefPostDataCToCpp::Unwrap(postData));
}

void CefRequestCToCpp::GetHeaderMap(HeaderMap& headerMap) {
  if (CEF_MEMBER_MISSING(struct_, get_header_map))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Translate param: headerMap; type: string_map_multi_byref
  cef_string_multimap_t headerMapMultimap = cef_string_multimap_alloc();
  DCHECK(headerMapMultimap);
  if (headerMapMultimap)
    transfer_string_multimap_contents(headerMap, headerMapMultimap);

  // Execute
  struct_->get_header_map(struct_,
      headerMapMultimap);

  // Restore param:headerMap; type: string_map_multi_byref
  if (headerMapMultimap) {
    headerMap.clear();
    transfer_string_multimap_contents(headerMapMultimap, headerMap);
    cef_string_multimap_free(headerMapMultimap);
  }
}

void CefRequestCToCpp::SetHeaderMap(const HeaderMap& headerMap) {
  if (CEF_MEMBER_MISSING(struct_, set_header_map))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Translate param: headerMap; type: string_map_multi_byref_const
  cef_string_multimap_t headerMapMultimap = cef_string_multimap_alloc();
  DCHECK(headerMapMultimap);
  if (headerMapMultimap)
    transfer_string_multimap_contents(headerMap, headerMapMultimap);

  // Execute
  struct_->set_header_map(struct_,
      headerMapMultimap);

  // Restore param:headerMap; type: string_map_multi_byref_const
  if (headerMapMultimap)
    cef_string_multimap_free(headerMapMultimap);
}

void CefRequestCToCpp::Set(const CefString& url, const CefString& method,
    CefRefPtr<CefPostData> postData, const HeaderMap& headerMap) {
  if (CEF_MEMBER_MISSING(struct_, set))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: url; type: string_byref_const
  DCHECK(!url.empty());
  if (url.empty())
    return;
  // Verify param: method; type: string_byref_const
  DCHECK(!method.empty());
  if (method.empty())
    return;
  // Unverified params: postData

  // Translate param: headerMap; type: string_map_multi_byref_const
  cef_string_multimap_t headerMapMultimap = cef_string_multimap_alloc();
  DCHECK(headerMapMultimap);
  if (headerMapMultimap)
    transfer_string_multimap_contents(headerMap, headerMapMultimap);

  // Execute
  struct_->set(struct_,
      url.GetStruct(),
      method.GetStruct(),
      CefPostDataCToCpp::Unwrap(postData),
      headerMapMultimap);

  // Restore param:headerMap; type: string_map_multi_byref_const
  if (headerMapMultimap)
    cef_string_multimap_free(headerMapMultimap);
}

int CefRequestCToCpp::GetFlags() {
  if (CEF_MEMBER_MISSING(struct_, get_flags))
    return UR_FLAG_NONE;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = struct_->get_flags(struct_);

  // Return type: simple
  return _retval;
}

void CefRequestCToCpp::SetFlags(int flags) {
  if (CEF_MEMBER_MISSING(struct_, set_flags))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  struct_->set_flags(struct_,
      flags);
}

CefString CefRequestCToCpp::GetFirstPartyForCookies() {
  if (CEF_MEMBER_MISSING(struct_, get_first_party_for_cookies))
    return CefString();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_string_userfree_t _retval = struct_->get_first_party_for_cookies(struct_);

  // Return type: string
  CefString _retvalStr;
  _retvalStr.AttachToUserFree(_retval);
  return _retvalStr;
}

void CefRequestCToCpp::SetFirstPartyForCookies(const CefString& url) {
  if (CEF_MEMBER_MISSING(struct_, set_first_party_for_cookies))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: url; type: string_byref_const
  DCHECK(!url.empty());
  if (url.empty())
    return;

  // Execute
  struct_->set_first_party_for_cookies(struct_,
      url.GetStruct());
}

CefRequest::ResourceType CefRequestCToCpp::GetResourceType() {
  if (CEF_MEMBER_MISSING(struct_, get_resource_type))
    return RT_SUB_RESOURCE;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_resource_type_t _retval = struct_->get_resource_type(struct_);

  // Return type: simple
  return _retval;
}

CefRequest::TransitionType CefRequestCToCpp::GetTransitionType() {
  if (CEF_MEMBER_MISSING(struct_, get_transition_type))
    return TT_EXPLICIT;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_transition_type_t _retval = struct_->get_transition_type(struct_);

  // Return type: simple
  return _retval;
}


#ifndef NDEBUG
template<> base::AtomicRefCount CefCToCpp<CefRequestCToCpp, CefRequest,
    cef_request_t>::DebugObjCt = 0;
#endif

