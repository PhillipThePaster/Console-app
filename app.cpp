#include <windows.h>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

void update() {
    const int stringL = 20;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    wchar_t module[MAX_PATH];
    GetModuleFileName(nullptr, module, MAX_PATH);
    std::wstring ofn = module;

    while (true) {
        std::wstring rstring;
        const wchar_t Char[] = L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        const int CLen = sizeof(Char) / sizeof(Char[0]) - 1;
        for (int i = 0; i < stringL; ++i) {
            rstring += Char[rand() % CLen];
        }

        size_t lsp = ofn.find_last_of(L"\\");
        std::wstring nfn = ofn.substr(0, lsp + 1) + rstring + L".exe";

        SetConsoleTitle(rstring.c_str());
        MoveFile(ofn.c_str(), nfn.c_str());

        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // delay
    }
}

int main() {
    std::thread titleThread(update);

    titleThread.join();
    return 0;
}
 
