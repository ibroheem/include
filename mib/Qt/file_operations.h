#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <QTextStream>

namespace mvc_utils
{
   namespace file_operations
   {
      QString read_file(const QString &_fl)
      {
         QFile data(_fl);
         data.open(QFile::OpenModeFlag::ReadOnly);
         return QTextStream(&data).readAll();
      }

      QString load_file(const QString &fl)
      {
         QString tmp;
         if (!fl.isEmpty())
         {
            QFile file(fl);
            if (file.open(QIODevice::ReadOnly))
            {
               QTextStream in(&file);
               tmp = in.readAll();
            }
         }
         return tmp;
      }
   }
}

#endif//FILE_OPERATIONS_H
