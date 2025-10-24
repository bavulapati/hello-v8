#include "libplatform/libplatform.h"
#include "v8.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

// C++ function exposed to JavaScript
void PrintFunction(const v8::FunctionCallbackInfo<v8::Value> &args) {
  v8::Isolate *isolate = args.GetIsolate();
  v8::String::Utf8Value str(isolate, args[0]);
  std::cout << *str << std::endl;
}

// Function to read JavaScript file into a string
std::string ReadFile(const std::string &filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "Error: Cannot open file " << filename << std::endl;
    return "";
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <script.js>" << std::endl;
    return 1;
  }

  // Read the JavaScript file
  std::string script_content = ReadFile(argv[1]);
  if (script_content.empty()) {
    return 1;
  }

  // Initialize V8.
  v8::V8::InitializeICUDefaultLocation(argv[0]);
  v8::V8::InitializeExternalStartupData(argv[0]);
  std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform();
  v8::V8::InitializePlatform(platform.get());
  v8::V8::Initialize();

  // Create a new Isolate and make it the current one.
  v8::Isolate::CreateParams create_params;
  create_params.array_buffer_allocator =
      v8::ArrayBuffer::Allocator::NewDefaultAllocator();
  v8::Isolate *isolate = v8::Isolate::New(create_params);
  {
    v8::Isolate::Scope isolate_scope(isolate);
    // Create a stack-allocated handle scope.
    v8::HandleScope handle_scope(isolate);

    // Create a global object template
    v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);

    // Map the JavaScript function logMessage to the C++ function PrintFunction
    // global->Set sets the global object in V8, effectively making
    // the JavaScript function logMessage available in the global scope
    global->Set(v8::String::NewFromUtf8(isolate, "logMessage").ToLocalChecked(),
                v8::FunctionTemplate::New(isolate, PrintFunction));

    // Create a new context.
    v8::Local<v8::Context> context = v8::Context::New(isolate, NULL, global);
    // Enter the context for compiling and running the hello world script.
    v8::Context::Scope context_scope(context);
    {
      // Create a string containing the JavaScript source code.
      v8::Local<v8::String> source =
          v8::String::NewFromUtf8(isolate, script_content.c_str())
              .ToLocalChecked();
      // Compile the source code.
      v8::Local<v8::Script> script =
          v8::Script::Compile(context, source).ToLocalChecked();

      script->Run(context).ToLocalChecked();
    }
  }

  // Dispose the isolate and tear down V8.
  isolate->Dispose();
  v8::V8::Dispose();
  v8::V8::DisposePlatform();
  delete create_params.array_buffer_allocator;
  return 0;
}
