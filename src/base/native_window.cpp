#include "includes/cef.h"
#include "includes/cef_handler.h"
#include "base/native_window.h"

extern CefRefPtr<ClientHandler> g_handler;

namespace appjs {

using namespace v8;

NativeWindow::NativeWindow(char* url, Settings* settings){
  width = settings->getNumber("width",800);
  height = settings->getNumber("height",600);
  x = settings->getNumber("x",-1);
  y = settings->getNumber("y",-1);
  opacity = settings->getNumber("opacity",1);
  show_chrome = settings->getBoolean("showChrome",true);
  resizable = settings->getBoolean("resizable",true);
  show_resize_grip = settings->getBoolean("showResizeGrip",false);
  auto_resize = settings->getBoolean("autoResize",false);
  fullscreen = settings->getBoolean("fullscreen",false);
  icons = new Settings(settings->getObject("icons", Object::New()));

  this->Init(url, settings);

  Cef::Run();
}

NativeWindow::~NativeWindow(){
  browser_ = NULL;
}

void NativeWindow::OpenDevTools(){
  if (browser_) {
    browser_->ShowDevTools();
  }
}

void NativeWindow::CloseDevTools(){
  if (browser_) {
    browser_->CloseDevTools();
  }
}

void NativeWindow::RunInBrowser(char* script){
  if (browser_) {
    browser_->GetMainFrame()->ExecuteJavaScript(script, "", 0);
  }
}

void NativeWindow::SetBrowser(CefRefPtr<CefBrowser> browser) {
  browser_ = browser;
}

void NativeWindow::SetV8Handle(Handle<Object> v8handle) {
  v8handle_ = v8handle;
}

CefRefPtr<CefBrowser> NativeWindow::GetBrowser() {
  return browser_ ? browser_ : NULL;
}

Handle<Object> NativeWindow::GetV8Handle() {
  return v8handle_;
}

} /* appjs */
