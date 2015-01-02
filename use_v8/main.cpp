#pragma comment(lib, "icui18n.lib")
#pragma comment(lib, "icuuc.lib")
#pragma comment(lib, "v8_base.ia32.lib")
#pragma comment(lib, "v8_nosnapshot.ia32.lib")
#pragma comment(lib, "Ws2_32.lib")
#include "v8.h"

// Extracts a C string from a V8 Utf8Value.
const char* ToCString(const v8::String::Utf8Value& value) 
{
    return *value ? *value : "<string conversion failed>";
}

// The callback that is invoked by v8 whenever the JavaScript 'print'
// function is called.  Prints its arguments on stdout separated by
// spaces and ending with a newline.
void Print(const v8::FunctionCallbackInfo<v8::Value>& args) 
{
    bool first = true;
    for (int i = 0; i < args.Length(); i++) 
    {
        v8::HandleScope handle_scope(args.GetIsolate());
        if (first)
            first = false;
        else
            printf(" ");
        v8::String::Utf8Value str(args[i]);
	const char* cstr = ToCString(str);
        printf("%s", cstr);
    }
}
int main()
{
    v8::V8::InitializeICU();
    v8::Isolate *isolate = v8::Isolate::GetCurrent(); // JS VM created
    v8::HandleScope handle_scope(isolate);
    v8::Handle<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);

    global->Set(v8::String::NewFromUtf8(isolate, "print"),
    v8::FunctionTemplate::New(isolate, Print));

    v8::Handle<v8::Context> context =  v8::Context::New(isolate, NULL, global);
    context->Enter();
    
    v8::Handle<v8::String> source = v8::String::NewFromUtf8(context->GetIsolate(), "print(42);");
    v8::Handle<v8::String> name = v8::String::NewFromUtf8(context->GetIsolate(), "(shell)");

    v8::Handle<v8::Script> script = v8::Script::Compile(source, name);
    v8::Handle<v8::Value> result = script->Run();


    v8::String::Utf8Value str(result);
    const char* cstr = ToCString(str);
    printf("%s\n", cstr);
    return 0;
}