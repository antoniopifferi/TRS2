#pragma once

#include <string>
#include <functional>

// Forward-declare Qt QObject type for GUI-only use (no Qt headers included here)
class QObject;

// Provide access to the internal AppLogger QObject instance for GUI sources only
QObject* AppLoggerObject();

// C-linkage primitives implemented in src/gui/AppLogger.cpp (avoid C++ name mangling across modules)
extern "C" {
    void outText_c(const char* s);
    void ErrHandler_c(const char* device, int code, const char* message);
    bool askYesNo_c(const char* title, const char* text);
    bool getTextInput_c(const char* title, const char* label, char* outBuf, int outBufLen);
    void showPanel_c(const char* name);
}

// C++ wrappers used by the codebase (header-only, no Qt types included)
inline void outText(const std::string& s) { outText_c(s.c_str()); }
inline void outText(const char* s) { outText_c(s); }

inline void displayPanel(const std::string& name) { showPanel_c(name.c_str()); }
inline void displayPanel(const char* name) { showPanel_c(name); }

inline void ErrHandler(const char* Device, int Code, const char* Message) { ErrHandler_c(Device, Code, Message); }
inline void ErrHandler(const std::string& Device, int Code, const std::string& Message) { ErrHandler_c(Device.c_str(), Code, Message.c_str()); }
inline void ErrHandler(const std::string& Device, int Code, const std::string& Function, const std::string& Message) { 
    // Simplified wrapper: include function name in message
    std::string combined = "Function: "; combined += Function; combined += "\n"; combined += Message;
    ErrHandler_c(Device.c_str(), Code, combined.c_str());
}

inline bool askYesNo(const char* title, const char* text) { return askYesNo_c(title, text); }
inline bool getTextInput(const char* title, const char* label, char* outBuf, int outBufLen) { return getTextInput_c(title, label, outBuf, outBufLen); }

// Run a callable on the Qt UI thread (implemented in AppLogger.cpp; kept non-exported C++ function)
void runOnUiThread(const std::function<void()>& fn);