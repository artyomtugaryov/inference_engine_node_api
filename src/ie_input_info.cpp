#include "ie_input_info.h"


Napi::Object InferenceEngineJS::IEInputInfo::Init(Napi::Env env, Napi::Object exports) {
    Napi::Function func = DefineClass(env, "IEInputInfo", {
    });

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();
    exports.Set("IEInputInfo", func);
    return exports;
}

InferenceEngineJS::IEInputInfo::IEInputInfo(const Napi::CallbackInfo &info) : Napi::ObjectWrap<IEInputInfo>(info) {
    if (info[0].IsUndefined()) {
        throw Napi::Error::New(info.Env(),
                               "Set pointer to InputInfo to InferenceEngineJS::IEInputInfo constructor for initialize");
    }
    auto layerPtr = info[0].As < Napi::External < InferenceEngine::InputInfo >> ().Data();
    this->_ieInputInfo = std::shared_ptr<InferenceEngine::InputInfo>(layerPtr);
}

Napi::FunctionReference InferenceEngineJS::IEInputInfo::constructor;