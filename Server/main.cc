#include <drogon/drogon.h>

int main(const int argc, const char *argv[])
{
    std::string config_file = "config.json";
    if (argc == 2)
    {
        config_file = argv[1];
    }
    auto& app = drogon::app();
    try
    {
        app.loadConfigFile(config_file);
    }
    catch (const std::exception &e)
    {
        LOG_ERROR << e.what();
        return 1;
    }

    app.registerBeginningAdvice([&app]() {
        for (auto &listener : app.getListeners())
        {
            LOG_INFO << "Server listening on " << listener.toIp() << ":" << listener.toPort();
        }
    });

    app.run();

    return 0;
}