#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <QString>
#include <QSysInfo>

#ifdef _WIN32
#include<windows.h>
#endif

QString get_cpu();
QString get_os_name();
QString get_total_memory();
QString get_available_memory();
QString get_used_memory();

#endif // SYSTEMINFO_H
