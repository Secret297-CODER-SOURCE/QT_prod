#include "../include/systemInfo.h"

QString get_cpu()
{
    QString result = QSysInfo::currentCpuArchitecture() + " on build " + QSysInfo::buildCpuArchitecture();
    return result;
}

QString get_os_name()
{
    QString pretty_name = QSysInfo::prettyProductName();

    if (!pretty_name.isEmpty()) {
        return pretty_name;
    }

    QString product_type = QSysInfo::productType();
    QString product_version = QSysInfo::productVersion();

    return product_type + " " + product_version;
}

QString get_total_memory()
{
#ifdef _WIN32
    MEMORYSTATUSEX memory1;
    memory1.dwLength = sizeof(memory1);
    if (GlobalMemoryStatusEx(&memory1))
    {
        return QString::number(memory1.ullPhys / (1024.0 * 1024 * 1024), 'f', 2) + " Gb";
    }
#else
    return "";
#endif
}

QString get_available_memory()
{
#ifdef _WIN32
    MEMORYSTATUSEX memory2;
    memory2.dwLength = sizeof(memory2);
    if (GlobalMemoryStatusEx(&memory2))
    {
        return QString::number(memory2.ullAvailPhys / (1024.0 * 1024 * 1024), 'f', 2) + " Gb";
    }
#else
    return "";
#endif
}

QString get_used_memory()
{
#ifdef _WIN32
    MEMORYSTATUSEX memory3;
    memory3.dwLength = sizeof(memory3);
    if (GlobalMemoryStatusEx(&memory3))
    {
        double use = memory3.ullTotalPhys - memory3.ullAvailPhys;
        return QString::number(use / (1024.0 * 1024 * 1024), 'f', 2) + " Gb";
    }
#else
    return "";
#endif
}
