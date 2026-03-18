#include <QApplication>
#include <QTemporaryDir>

#include <cstdio>

#include "ApplicationSettings.h"

namespace {

int Fail(const char *message) {
    std::fprintf(stderr, "%s\n", message);
    return 1;
}

}

int main(int argc, char **argv) {
    QTemporaryDir tempConfigHome;
    if (!tempConfigHome.isValid()) {
        return Fail("failed to create temporary config directory");
    }

    qputenv("XDG_CONFIG_HOME", tempConfigHome.path().toUtf8());

    QApplication app(argc, argv);
    ApplicationSettings settings;

    if (!settings.restorePreviousSession()) {
        return Fail("restorePreviousSession should default to enabled");
    }
    if (!settings.restoreUnsavedFiles()) {
        return Fail("restoreUnsavedFiles should default to enabled");
    }
    if (!settings.restoreTempFiles()) {
        return Fail("restoreTempFiles should default to enabled");
    }

    return 0;
}
