#include <boost/program_options.hpp>
#include <g3log/g3log.hpp>

#include "software/ai/ai_wrapper.h"
#include "software/typedefs.h"
#include "software/backend/simulator_backend.h"
#include "software/gui/visualizer_wrapper.h"
#include "software/util/logger/init.h"

using namespace boost::program_options;

// clang-format off
std::string BANNER =
"        ,/                                                                                                                     ,/   \n"
"      ,'/         _    _ ____   _____   _______ _    _ _    _ _   _ _____  ______ _____  ____   ____ _______ _____           ,'/    \n"
"    ,' /         | |  | |  _ \\ / ____| |__   __| |  | | |  | | \\ | |  __ \\|  ____|  __ \\|  _ \\ / __ \\__   __/ ____|        ,' /     \n"
"  ,'  /_____,    | |  | | |_) | |         | |  | |__| | |  | |  \\| | |  | | |__  | |__) | |_) | |  | | | | | (___        ,'  /_____,\n"
".'____    ,'     | |  | |  _ <+ |         | |  |  __  | |  | | . ` | |  | |  __| |  _  /|  _ <+ |  | | | |  \\___ \\     .'____    ,' \n"
"     /  ,'       | |__| | |_) | |____     | |  | |  | | |__| | |\\  | |__| | |____| | \\ \\| |_) | |__| | | |  ____) |         /  ,'   \n"
"    / ,'          \\____/|____/ \\_____|    |_|  |_|  |_|\\____/|_| \\_|_____/|______|_|  \\_\\____/ \\____/  |_| |_____/         / ,'     \n"
"   /,'                                                                                                                    /,'       \n"
"  /'                                                                                                                     /'          \n";
// clang-format on

typedef struct CommandLineParams_t {
    bool valid;
    bool headless;
} CommandLineParams;

CommandLineParams parseCommandLineArgs(int argc, char **argv)
{
    CommandLineParams params;
    params.headless = false;
    params.valid = true;

    try
    {
        options_description desc{"Options"};
        desc.add_options()
            ("help,h", "Help screen")
            ("headless", boost::program_options::bool_switch(&(params.headless)),"Run without the Visualizer");

        variables_map vm;
        store(parse_command_line(argc, argv, desc), vm);

        // We only process notifications if "help" was not given, which allows us to
        // avoid issues where required arguments are not required if "help" is given
        if (vm.count("help"))
        {
            std::cout << desc << std::endl;
            params.valid = false;
        }
        else
        {
            notify(vm);
        }
    }
    catch (const error &ex)
    {
        std::cerr << ex.what() << '\n';
        params.valid = false;
    }

    return params;
}

int main(int argc, char **argv)
{
    std::cout << BANNER << std::endl;

    Util::Logger::LoggerSingleton::initializeLogger();

    auto params = parseCommandLineArgs(argc, argv);

    if(params.valid) {
        auto backend = std::make_shared<SimulatorBackend>();
        auto ai = std::make_shared<AIWrapper>();

        backend->Subject<World>::registerObserver(ai);
        ai->Subject<ConstPrimitiveVectorPtr>::registerObserver(backend);
        std::shared_ptr<VisualizerWrapper> visualizer;

        if(!params.headless) {
            visualizer = std::make_shared<VisualizerWrapper>(argc, argv);

            backend->Subject<World>::registerObserver(visualizer);
            ai->Subject<AIDrawFunction>::registerObserver(visualizer);
            ai->Subject<PlayInfo>::registerObserver(visualizer);
            backend->Subject<RobotStatus>::registerObserver(visualizer);
        }

        // All observers must be connected before starting
        backend->start();

        if(!params.headless) {
            // This blocks forever without using the CPU
            // Wait for the visualizer to shut down before shutting
            // down the rest of the system
            visualizer->getTerminationPromise()->get_future().wait();
        }else {
            // This blocks forever without using the CPU
            std::promise<void>().get_future().wait();
        }
    }

    return params.valid ? 0 : 1;
}
