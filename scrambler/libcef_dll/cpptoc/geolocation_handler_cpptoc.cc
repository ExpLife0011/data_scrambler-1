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

#include "cpptoc/geolocation_handler_cpptoc.h"
#include "ctocpp/browser_ctocpp.h"
#include "ctocpp/geolocation_callback_ctocpp.h"


// MEMBER FUNCTIONS - Body may be edited by hand.

int CEF_CALLBACK geolocation_handler_on_request_geolocation_permission(
    struct _cef_geolocation_handler_t* self, cef_browser_t* browser,
    const cef_string_t* requesting_url, int request_id,
    cef_geolocation_callback_t* callback) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;
  // Verify param: browser; type: refptr_diff
  DCHECK(browser);
  if (!browser)
    return 0;
  // Verify param: requesting_url; type: string_byref_const
  DCHECK(requesting_url);
  if (!requesting_url)
    return 0;
  // Verify param: callback; type: refptr_diff
  DCHECK(callback);
  if (!callback)
    return 0;

  // Execute
  bool _retval = CefGeolocationHandlerCppToC::Get(
      self)->OnRequestGeolocationPermission(
      CefBrowserCToCpp::Wrap(browser),
      CefString(requesting_url),
      request_id,
      CefGeolocationCallbackCToCpp::Wrap(callback));

  // Return type: bool
  return _retval;
}

void CEF_CALLBACK geolocation_handler_on_cancel_geolocation_permission(
    struct _cef_geolocation_handler_t* self, cef_browser_t* browser,
    const cef_string_t* requesting_url, int request_id) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;
  // Verify param: browser; type: refptr_diff
  DCHECK(browser);
  if (!browser)
    return;
  // Verify param: requesting_url; type: string_byref_const
  DCHECK(requesting_url);
  if (!requesting_url)
    return;

  // Execute
  CefGeolocationHandlerCppToC::Get(self)->OnCancelGeolocationPermission(
      CefBrowserCToCpp::Wrap(browser),
      CefString(requesting_url),
      request_id);
}


// CONSTRUCTOR - Do not edit by hand.

CefGeolocationHandlerCppToC::CefGeolocationHandlerCppToC(
    CefGeolocationHandler* cls)
    : CefCppToC<CefGeolocationHandlerCppToC, CefGeolocationHandler,
        cef_geolocation_handler_t>(cls) {
  struct_.struct_.on_request_geolocation_permission =
      geolocation_handler_on_request_geolocation_permission;
  struct_.struct_.on_cancel_geolocation_permission =
      geolocation_handler_on_cancel_geolocation_permission;
}

#ifndef NDEBUG
template<> base::AtomicRefCount CefCppToC<CefGeolocationHandlerCppToC,
    CefGeolocationHandler, cef_geolocation_handler_t>::DebugObjCt = 0;
#endif
